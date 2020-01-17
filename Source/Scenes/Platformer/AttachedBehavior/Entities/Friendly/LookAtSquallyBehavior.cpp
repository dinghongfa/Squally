#include "LookAtSquallyBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string LookAtSquallyBehavior::MapKeyAttachedBehavior = "face-squally";

LookAtSquallyBehavior* LookAtSquallyBehavior::create(GameObject* owner)
{
	LookAtSquallyBehavior* instance = new LookAtSquallyBehavior(owner);

	instance->autorelease();

	return instance;
}

LookAtSquallyBehavior::LookAtSquallyBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

LookAtSquallyBehavior::~LookAtSquallyBehavior()
{
}

void LookAtSquallyBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void LookAtSquallyBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr)
	{
		return;
	}

	if (this->entity->getPositionX() > GameUtils::getWorldCoords(this->squally).x)
	{
		this->entity->getAnimations()->setFlippedX(true);
	}
	else
	{
		this->entity->getAnimations()->setFlippedX(false);
	}
}
