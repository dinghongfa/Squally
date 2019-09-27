#include "ItemPool.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Objects/Platformer/Collectables/Cards/CardPools/CardPool.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ItemPool::ItemPool(std::string poolName) : ItemPool(ValueMap(), poolName)
{
}

ItemPool::ItemPool(const ValueMap& properties, std::string poolName) : super(properties)
{
	this->poolName = poolName;
	this->itemPool = std::vector<std::tuple<Item*, float>>();
	this->weightSum = 0.0f;
	this->itemsNode = Node::create();

	this->addChild(this->itemsNode);
}

ItemPool::~ItemPool()
{
}

void ItemPool::initializeListeners()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(ItemEvents::EventRequestItemFromPoolPrefix + this->poolName, [=](EventCustom* eventCustom)
	{
		ItemEvents::ItemRequestArgs* args = static_cast<ItemEvents::ItemRequestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			args->callback(this->getItemFromPool());
		}
	}));
}

std::vector<Item*> ItemPool::getItemsFromPool(int count)
{
	std::vector<Item*> items = std::vector<Item*>();

	for (int index = 0; index < count; index++)
	{
		items.push_back(this->getItemFromPool());
	}

	return items;
}

Item* ItemPool::getItemFromPool()
{
	float weight = RandomHelper::random_real(0.0f, this->weightSum);

	for (auto it = this->itemPool.begin(); it != this->itemPool.end(); it++)
	{
		weight -= std::get<1>(*it);

		if (weight <= 0.0f)
		{
			return std::get<0>(*it)->clone();
		}
	}

	// Error! Fallback on a uniform random item
	int index = RandomHelper::random_int(0, int(this->itemPool.size()) - 1);

	return std::get<0>(this->itemPool[index])->clone();
}

void ItemPool::addItemToPool(Item* item, float weight)
{
	std::tuple<Item*, float> itemAndWeight = { item, weight };

	this->itemPool.push_back(itemAndWeight);
	this->itemsNode->addChild(item);

	this->calculateWeightSum();
}

void ItemPool::removeCardFromPool(Item* item)
{
	this->itemPool.erase(std::remove_if(this->itemPool.begin(), this->itemPool.end(), [=](std::tuple<Item*, float> entry)
	{
		if (std::get<0>(entry) == item)
		{
			this->itemsNode->removeChild(item);

			return true;
		}

		return false;
	}), this->itemPool.end());
}

void ItemPool::calculateWeightSum()
{
	this->weightSum = 0.0f;

	for (auto it = this->itemPool.begin(); it != this->itemPool.end(); it++)
	{
		this->weightSum += std::get<1>(*it);
	}
}