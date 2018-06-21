#include "BossDemonKing.h"

const std::string BossDemonKing::KeyEnemyBossDemonKing = "boss_demon_king";

BossDemonKing* BossDemonKing::deserialize(ValueMap* initProperties)
{
	BossDemonKing* instance = new BossDemonKing(initProperties);

	instance->autorelease();

	return instance;
}

BossDemonKing::BossDemonKing(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false,
	Size(480.0f, 480.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossDemonKing::~BossDemonKing()
{
}