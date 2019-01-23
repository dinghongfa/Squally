#include "Laser.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Traps/Laser/LaserAnimation.h"
#include "Objects/Platformer/Traps/Laser/LaserCountDownPreview.h"
#include "Objects/Platformer/Traps/Laser/LaserGenericPreview.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Laser/UpdateCountDown/RegisterSt0.h"
#include "Strings/Hacking/Objects/Laser/UpdateCountDown/UpdateCountDown.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string Laser::MapKeyLaser = "laser";

Laser* Laser::create(ValueMap* initProperties)
{
	Laser* instance = new Laser(initProperties);

	instance->autorelease();

	return instance;
}

Laser::Laser(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->currentLaserCountDown = RandomHelper::random_real(0.0f, 3.0f);
	this->maxLaserCountDown = 4.0f;
	this->isRunningAnimation = false;

	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->laserAnimation = LaserAnimation::create(height);
	this->laserCollision = CollisionObject::create(PhysicsBody::createBox(Size(21.0f, height)), (CollisionType)PlatformerCollisionType::Damage, false, false);

	this->setDefaultPreview(LaserGenericPreview::create());
	this->registerHackables();

	this->addChild(this->laserCollision);
	this->addChild(this->laserAnimation);
}

Laser::~Laser()
{
}

void Laser::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Laser::update(float dt)
{
	super::update(dt);

	this->updateLaser(dt);
}

void Laser::initializePositions()
{
	super::initializePositions();

	this->laserCollision->setPosition(Vec2::ZERO);
}

void Laser::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				Laser::MapKeyLaser,
				Strings::Hacking_Objects_Laser_UpdateCountDown_UpdateCountDown::create(),
				UIResources::Menus_Icons_SpellImpactWhite,
				LaserCountDownPreview::create(),
				{
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_Laser_UpdateCountDown_RegisterSt0::create() },
				}
			)
		},
	};

	auto updateLaserFunc = &Laser::updateLaser;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateLaserFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 Laser::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Laser::updateLaser(float dt)
{
	if (this->isRunningAnimation)
	{
		return;
	}

	volatile float* countDownPtr = &this->currentLaserCountDown;
	volatile float* deltaTimePtr = &dt;

	ASM(push EAX);
	ASM(push EBX);
	ASM_MOV_REG_VAR(EAX, countDownPtr);
	ASM_MOV_REG_VAR(EBX, deltaTimePtr);

	ASM(fld dword ptr [EAX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(fsub dword ptr [EBX]);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr [EAX])

	ASM(pop EAX);
	ASM(pop EBX);

	HACKABLES_STOP_SEARCH();

	if (this->currentLaserCountDown <= 0.0f)
	{
		const float stayActiveDuration = 1.5f;

		this->isRunningAnimation = true;
		this->currentLaserCountDown = this->maxLaserCountDown - RandomHelper::random_real(0.0f, 0.5f);

		this->laserAnimation->runAnimation(
		[=]()
		{
			this->laserCollision->setPhysicsEnabled(true);
		},
		[=]()
		{
			this->laserCollision->setPhysicsEnabled(false);
			this->isRunningAnimation = false;
		});
	}
}