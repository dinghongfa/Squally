#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class GladiatorSword : public Sword
{
public:
	static GladiatorSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyGladiatorSword;

protected:
	GladiatorSword();
	virtual ~GladiatorSword();

private:
	typedef Sword super;
};
