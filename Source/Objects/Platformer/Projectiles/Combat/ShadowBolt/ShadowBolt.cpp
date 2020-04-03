#include "ShadowBolt.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/Combat/ShadowBolt/ShadowBoltClippy.h"
#include "Objects/Platformer/Projectiles/Combat/ShadowBolt/ShadowBoltGenericPreview.h"
#include "Objects/Platformer/Projectiles/Combat/ShadowBolt/ShadowBoltSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FIREBALL_SPEED 11

ShadowBolt* ShadowBolt::create(PlatformerEntity* owner, PlatformerEntity* target)
{
	ShadowBolt* instance = new ShadowBolt(owner, target);

	instance->autorelease();

	return instance;
}

ShadowBolt::ShadowBolt(PlatformerEntity* owner, PlatformerEntity* target)
	: super(owner, target, true, Node::create(), Size(32.0f, 32.0f))
{
	this->shadowBoltAnim = SmartAnimationSequenceNode::create(FXResources::ShadowImpact_ShadowImpact_0000);

	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->launchSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Fireball2);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_FireHit1);
	this->reverseClippy = ShadowBoltClippy::create();

	this->shadowBoltAnim->playAnimationRepeat(FXResources::ShadowBolt_ShadowBolt_0000, 0.05f);

	this->registerClippy(this->reverseClippy);
	this->postFXNode->addChild(this->launchSound);
	this->postFXNode->addChild(this->impactSound);
	this->postFXNode->addChild(this->explosionAnim);
	this->object->addChild(this->shadowBoltAnim);
}

ShadowBolt::~ShadowBolt()
{
}

void ShadowBolt::update(float dt)
{
	super::update(dt);

	if (!this->canUpdate)
	{
		return;
	}
	
	this->setShadowBoltSpeed();

	this->shadowBoltAnim->setFlippedX(this->getLaunchVelocity().x < 0.0f);
}

void ShadowBolt::enableClippy()
{
	this->reverseClippy->setIsEnabled(true);
}

void ShadowBolt::runSpawnFX()
{
	this->launchSound->play();
}

void ShadowBolt::runImpactFX()
{
	this->explosionAnim->playAnimation(FXResources::ShadowImpact_ShadowImpact_0000, 0.05f, true);

	this->impactSound->play();
}

Vec2 ShadowBolt::getButtonOffset()
{
	return Vec2::ZERO;
}

void ShadowBolt::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FIREBALL_SPEED,
			HackableCode::HackableCodeInfo(
				"ShadowBolt",
				Strings::Menus_Hacking_Objects_ShadowBolt_ApplySpeed_ApplySpeed::create(),
				UIResources::Menus_Icons_CrossHair,
				ShadowBoltSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_ShadowBolt_ApplySpeed_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_ShadowBolt_ApplySpeed_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_ShadowBolt_ApplySpeed_RegisterXmm1::create() }
				},
				int(HackFlags::None),
				5.0f,
				0.0f,
				this->reverseClippy,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Objects_ShadowBolt_ApplySpeed_StopShadowBolt::create(),
						// x86
						"mov dword ptr [eax], 0.0\n"
						"movss xmm1, dword ptr [eax]\n\n"
						"mulps xmm0, xmm1",
						// x64
						"mov dword ptr [rax], 0.0\n"
						"movss xmm1, dword ptr [rax]\n\n"
						"mulps xmm0, xmm1"
					)
				}
			)
		},
	};

	auto shadowBoltFunc = &ShadowBolt::setShadowBoltSpeed;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)shadowBoltFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* ShadowBolt::createDefaultPreview()
{
	return ShadowBoltGenericPreview::create();
}

NO_OPTIMIZE void ShadowBolt::setShadowBoltSpeed()
{
	volatile static float* freeMemoryForUser = new float[16];
	volatile float speedMultiplier = 1.0f;
	volatile float speedMultiplierTemp = 1.0f;
	volatile float* speedMultiplierPtr = &speedMultiplier;
	volatile float* speedMultiplierTempPtr = &speedMultiplierTemp;

	// Initialize xmm0 and xmm1
	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierPtr);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierTempPtr);
	ASM(movss xmm1, dword ptr [ZAX]);
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, freeMemoryForUser);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FIREBALL_SPEED);
	ASM(mulps xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierPtr);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM(pop ZAX);

	this->setSpeedMultiplier(Vec3(speedMultiplier, speedMultiplier, speedMultiplier));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE