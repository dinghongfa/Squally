#include "HexusPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/SmithingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolEFGeneric* HexusPoolEFGeneric::create()
{
	HexusPoolEFGeneric* instance = new HexusPoolEFGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolEFGeneric::HexusPoolEFGeneric() : super(ValueMap(), "hexus-pool-ef-generic", SampleMethod::Random, 1, 2,
	{ CardPoolTier1::create(SampleMethod::Guarantee, 1, 1), AlchemyPoolTier1::create(SampleMethod::Random, 1, 1), SmithingPoolTier1::create(SampleMethod::Random, 1, 1) })
{
}

HexusPoolEFGeneric::~HexusPoolEFGeneric()
{
}
