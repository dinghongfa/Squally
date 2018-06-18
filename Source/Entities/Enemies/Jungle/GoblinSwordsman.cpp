#include "GoblinSwordsman.h"

const std::string GoblinSwordsman::KeyEnemyGoblinSwordsman = "goblin_swordsman";

GoblinSwordsman* GoblinSwordsman::create()
{
	GoblinSwordsman* instance = new GoblinSwordsman();

	instance->autorelease();

	return instance;
}

GoblinSwordsman::GoblinSwordsman() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_GoblinSwordsman_Animations,
	false,
	Size(312.0f, 512.0f),
	0.35f,
	Vec2(0.0f, -224.0f))
{
}

GoblinSwordsman::~GoblinSwordsman()
{
}
