#include "Fortitude.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Fortitude/FortitudeClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Fortitude/FortitudeGenericPreview.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FORTITUDE 1

const std::string Fortitude::FortitudeIdentifier = "fortitude";

const int Fortitude::MaxMultiplier = 4;
const float Fortitude::Duration = 12.0f;

Fortitude* Fortitude::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Fortitude* instance = new Fortitude(caster, target);

	instance->autorelease();

	return instance;
}

Fortitude::Fortitude(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(Fortitude::Duration, Fortitude::FortitudeIdentifier))
{
	this->clippy = FortitudeClippy::create();
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Speed);
	
	this->registerClippy(this->clippy);

	this->addChild(this->spellEffect);
}

Fortitude::~Fortitude()
{
}

void Fortitude::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	CombatEvents::TriggerHackableCombatCue();
}

void Fortitude::initializePositions()
{
	super::initializePositions();

	this->spellEffect->setPositionY(-this->target->getEntityCenterPoint().y / 2.0f);
}

void Fortitude::enableClippy()
{
	if (this->clippy != nullptr)
	{
		this->clippy->setIsEnabled(true);
	}
}

void Fortitude::registerHackables()
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
			LOCAL_FUNC_ID_FORTITUDE,
			HackableCode::HackableCodeInfo(
				Fortitude::FortitudeIdentifier,
				Strings::Menus_Hacking_Abilities_Buffs_Fortitude_Fortitude::create(),
				UIResources::Menus_Icons_Shield,
				FortitudeGenericPreview::create(),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Buffs_Fortitude_RegisterEax::create()->setStringReplacementVariables(
							{
								ConstantString::create(std::to_string(0)),
								Strings::Common_ConstantTimes::create()->setStringReplacementVariables(ConstantString::create(std::to_string(Fortitude::MaxMultiplier)))
							})
					}
				},
				int(HackFlags::None),
				this->getRemainingDuration(),
				0.0f,
				this->clippy,
				{
				}
			)
		},
	};

	auto hasteFunc = &Fortitude::applyFortitude;
	this->hackables = HackableCode::create((void*&)hasteFunc, codeInfoMap);

	for (auto next : this->hackables)
	{
		this->target->registerCode(next);
	}
}

void Fortitude::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageTaken(damageOrHealing, handleCallback, caster, target);

	this->currentDamageTaken = *damageOrHealing;

	this->applyFortitude();

	*damageOrHealing = this->currentDamageTaken;
}

NO_OPTIMIZE void Fortitude::applyFortitude()
{
	volatile int originalDamage = this->currentDamageTaken;
	volatile int damageTaken = this->currentDamageTaken;

	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZBX, damageTaken);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FORTITUDE);
	ASM(sub ZBX, 3);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(damageTaken, ZBX);

	ASM(pop ZBX);

	// Bound multiplier in either direction
	this->currentDamageTaken = MathUtils::clamp(damageTaken, -std::abs(originalDamage) * Fortitude::MaxMultiplier, std::abs(originalDamage) * Fortitude::MaxMultiplier);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE