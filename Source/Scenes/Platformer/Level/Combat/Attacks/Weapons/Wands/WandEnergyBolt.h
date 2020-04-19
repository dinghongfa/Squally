#pragma once

#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

class WorldSound;

class WandEnergyBolt : public PlatformerAttack
{
public:
	static WandEnergyBolt* create(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);

	LocalizedString* getString() override;
	std::string getAttackAnimation() override;
	void onAttackTelegraphBegin() override;

protected:
	WandEnergyBolt(int damageMin, int damageMax, float attackDuration, float recoverDuration, Priority priority);
	virtual ~WandEnergyBolt();

	void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) override;
	void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target) override;

private:
	typedef PlatformerAttack super;
	
	PlatformerAttack* cloneInternal() override;

	WorldSound* slashSound;
	WorldSound* hitSound;

	static const float DamageMultiplier;
};
