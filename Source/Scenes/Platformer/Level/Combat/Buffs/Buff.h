#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

namespace cocos2d
{
	class Sprite;
}

class Clippy;
class HackableCode;
class PlatformerEntity;

class Buff : public SmartNode
{
public:
	struct BuffData
	{
		float duration;
		std::string uniqueId; // If set to non-empty string, the buff will be unique against this key.
		float priority;

		BuffData() : duration(-1.0f), uniqueId(""), priority(0.5f) { }
		BuffData(float duration) : duration(duration), uniqueId(""), priority(0.5f) { }
		BuffData(std::string uniqueId) : duration(-1.0f), uniqueId(uniqueId), priority(0.5f) { }
		BuffData(float duration, std::string uniqueId) : duration(duration), uniqueId(uniqueId), priority(0.5f) { }
		BuffData(float duration, std::string uniqueId, float priority) : duration(duration), uniqueId(uniqueId), priority(priority) { }
	};

	void setBuffIndex(int index, int maxIndex);
	bool hasBuffIcon();
	float getRemainingDuration();
	BuffData getBuffData();
	void setRemoveBuffCallback(std::function<void()> removeBuffCallback);
	void removeBuff();
	void registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc);

protected:
	Buff(PlatformerEntity* caster, PlatformerEntity* owner, std::string buffIconResource, AbilityType abilityType, BuffData buffData);
	virtual ~Buff();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void registerHackables();
	virtual void elapse(float dt);
	virtual void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed);
	virtual void onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onAfterDamageDelt(CombatEvents::DamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onBeforeHealingDelt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing);
	virtual void onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset);

	BuffData buffData;
	PlatformerEntity* caster;
	PlatformerEntity* owner;
	std::vector<HackableCode*> hackables;
	AbilityType abilityType;

private:
	typedef SmartNode super;
	friend class TimelineEntry;

	std::function<void()> removeBuffCallback;
	cocos2d::Node* iconContainer;
	cocos2d::Sprite* buffGlow;
	cocos2d::Sprite* buffIcon;
	
	bool isBuffIconPresent;
	bool wasRemoved;
	float elapsedTime;
	void unregisterHackables();
};
