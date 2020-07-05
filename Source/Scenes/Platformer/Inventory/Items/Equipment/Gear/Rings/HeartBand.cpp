#include "HeartBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeartBand::SaveKey = "heart-band";

HeartBand* HeartBand::create()
{
	HeartBand* instance = new HeartBand();

	instance->autorelease();

	return instance;
}

HeartBand::HeartBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemStats(
	// Health
	2,
	// Mana
	2,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

HeartBand::~HeartBand()
{
}

Item* HeartBand::clone()
{
	return HeartBand::create();
}

std::string HeartBand::getItemName()
{
	return HeartBand::SaveKey;
}

LocalizedString* HeartBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_HeartBand::create();
}

std::string HeartBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_HeartBand;
}

std::string HeartBand::getSerializationKey()
{
	return HeartBand::SaveKey;
}
