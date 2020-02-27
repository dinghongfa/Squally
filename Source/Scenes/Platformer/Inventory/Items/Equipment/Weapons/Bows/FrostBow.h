#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class FrostBow : public Bow
{
public:
	static FrostBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyFrostBow;

protected:
	FrostBow();
	virtual ~FrostBow();

private:
	typedef Bow super;
};
