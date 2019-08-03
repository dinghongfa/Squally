#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class Weapon : public Equipable
{
public:
	int getMinAttack();
	int getMaxAttack();
	virtual float getAttackOnset();
	virtual float getAttackSustain();
	virtual cocos2d::Size getWeaponCollisionSize();
	virtual cocos2d::Vec2 getWeaponOffset();

protected:
	Weapon(CurrencyInventory* cost, int minAttack, int maxAttack);
	virtual ~Weapon();

private:
	typedef Equipable super;

	int minAttack;
	int maxAttack;
};
