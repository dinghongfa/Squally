#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class PlatformerEntity;
class Projectile;

class PlatformerAttack : public SmartNode
{
public:
	enum AttackType
	{
		Damage,
		Healing,
		ProjectileHealing,
		ProjectileDamage,
	};

	virtual PlatformerAttack* clone() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getAttackAnimation();
	std::string getIconResource();
	void execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onAttackComplete);

	float getPriority();
	int getSpecialCost();
	AttackType getAttackType();
	virtual void onAttackTelegraphBegin();
	virtual void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target);
	virtual void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target);
	virtual void onAttackEnd();
	virtual void onCleanup();

protected:
	PlatformerAttack(AttackType attackType, std::string iconResource, float priority, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration = PlatformerAttack::DefaultCleanupDuration);
	~PlatformerAttack() = default;

	int getRandomDamageOrHealing();
	int getBaseDamageOrHealingMin();
	int getBaseDamageOrHealingMax();
	float getAttackDuration();
	float getRecoverDuration();
	void replaceMainhandWithProjectile(PlatformerEntity* owner, Projectile* projectile);
	void replaceOffhandWithProjectile(PlatformerEntity* owner, Projectile* projectile);

	static const float DefaultCleanupDuration;

private:
	typedef SmartNode super;

	void replaceAnimationPartWithProjectile(std::string animationPart, PlatformerEntity* owner, Projectile* projectile);

	float priority;
	AttackType attackType;
	std::string iconResource;
	int baseDamageOrHealingMin;
	int baseDamageOrHealingMax;
	int specialCost;
	float attackDuration;
	float recoverDuration;
};
