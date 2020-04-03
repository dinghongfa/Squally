#include "Blind.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/BlindClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/BlindGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_HASTE 1

const std::string Blind::BlindIdentifier = "haste";

// Note: UI sets precision on these to 1 digit
const float Blind::MinSpeed = -1.0f;
const float Blind::DefaultSpeed = 2.0f;
const float Blind::MaxSpeed = 2.5f;
const float Blind::Duration = 6.0f;

Blind* Blind::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Blind* instance = new Blind(caster, target);

	instance->autorelease();

	return instance;
}

Blind::Blind(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(Blind::Duration, Blind::BlindIdentifier))
{
	this->clippy = BlindClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
}

Blind::~Blind()
{
}

void Blind::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Blind::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(-this->target->getEntityCenterPoint().y / 2.0f);
}

void Blind::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Blind::registerHackables()
{
	super::registerHackables();

	if (this->target == nullptr)
	{
		return;
	}

	this->clippy->setIsEnabled(false);

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_HASTE,
			HackableCode::HackableCodeInfo(
				Blind::BlindIdentifier,
				Strings::Menus_Hacking_Abilities_Debuffs_Blind_Blind::create(),
				UIResources::Menus_Icons_Clock,
				BlindGenericPreview::create(),
				{
					{
						HackableCode::Register::zsi, Strings::Menus_Hacking_Abilities_Debuffs_Blind_RegisterEsi::create()
							->setStringReplacementVariables({ ConstantFloat::create(Blind::MinSpeed, 1), ConstantFloat::create(Blind::MaxSpeed, 1) })
					},
					{
						HackableCode::Register::xmm3, Strings::Menus_Hacking_Abilities_Debuffs_Blind_RegisterXmm3::create()
							->setStringReplacementVariables(ConstantFloat::create(Blind::DefaultSpeed, 1))
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				this->clippy,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Debuffs_Blind_ReduceBlind::create(),
						// x86
						"mov dword ptr [esi], 0.0",
						// x64
						"mov dword ptr [rsi], 0.0"
					)
				}
			)
		},
	};

	auto hasteFunc = &Blind::applyBlind;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Blind::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
	super::onModifyTimelineSpeed(timelineSpeed, handleCallback);
	
	this->currentSpeed = *timelineSpeed;

	this->applyBlind();

	*timelineSpeed = this->currentSpeed;
}

NO_OPTIMIZE void Blind::applyBlind()
{
	volatile float speedBonus = 0.0f;
	volatile float increment = Blind::DefaultSpeed;
	volatile float* speedBonusPtr = &speedBonus;
	volatile float* incrementPtr = &increment;

	ASM(push ZSI);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZSI, speedBonusPtr);
	ASM_MOV_REG_VAR(ZBX, incrementPtr);
	ASM(movss xmm3, [ZBX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_HASTE);
	ASM(movss [ZSI], xmm3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZSI);

	this->currentSpeed += MathUtils::clamp(speedBonus, Blind::MinSpeed, Blind::MaxSpeed);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE