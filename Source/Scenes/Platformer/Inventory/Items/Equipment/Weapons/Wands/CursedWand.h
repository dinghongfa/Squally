#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Wands/Wand.h"

class CursedWand : public Wand
{
public:
	static CursedWand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyCursedWand;

protected:
	CursedWand();
	virtual ~CursedWand();

private:
	typedef Wand super;
};
