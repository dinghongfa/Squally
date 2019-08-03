#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class Gear : public Equipable
{
public:
	int getDefense();

protected:
	Gear(CurrencyInventory* cost, int defense);
	virtual ~Gear();

private:
	typedef Equipable super;

	int defense;
};
