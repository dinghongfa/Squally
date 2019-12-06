#include "ItemsMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float ItemsMenu::Radius = 384.0f;

ItemsMenu* ItemsMenu::create()
{
	ItemsMenu* instance = new ItemsMenu();

	instance->autorelease();

	return instance;
}

ItemsMenu::ItemsMenu() : super(ItemsMenu::Radius)
{
}

ItemsMenu::~ItemsMenu()
{
}

void ItemsMenu::buildAttackList(TimelineEntry* entry)
{
	this->clearItems();

	if (entry == nullptr)
	{
		return;
	}

	PlatformerEntity* entity = entry->getEntity();

	if (entity == nullptr)
	{
		return;
	}

	entity->getAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		for (auto consumable : attackBehavior->getAvailableConsumables())
		{
			this->addEntry(consumable->getString(), Sprite::create(consumable->getIconResource()), UIResources::Combat_ItemsCircle, [=]()
			{
				entry->stageCast(consumable);

				switch (consumable->getAttackType())
				{
					case PlatformerAttack::AttackType::Healing:
					case PlatformerAttack::AttackType::ProjectileHealing:
					case PlatformerAttack::AttackType::ProjectileBuffSpeed:
					{
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget, entry));
						break;
					}
					case PlatformerAttack::AttackType::Damage:
					case PlatformerAttack::AttackType::ProjectileDamage:
					{
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget, entry));
						break;
					}
					default:
					{
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget, entry));
						break;
					}
				}
			});
		}
	});
}
