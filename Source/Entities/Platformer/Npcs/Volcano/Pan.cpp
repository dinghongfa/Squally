#include "Pan.h"

const std::string Pan::MapKeyNpcPan = "pan";

Pan* Pan::deserialize(ValueMap* initProperties)
{
	Pan* instance = new Pan(initProperties);

	instance->autorelease();

	return instance;
}

Pan::Pan(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Pan_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Pan::~Pan()
{
}