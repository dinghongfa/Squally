#include "TigerMan.h"

const std::string TigerMan::KeyEnemyTigerMan = "tiger_man";

TigerMan* TigerMan::deserialize(ValueMap* initProperties)
{
	TigerMan* instance = new TigerMan(initProperties);

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Ruins_TigerMan_Animations,
	false,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TigerMan::~TigerMan()
{
}