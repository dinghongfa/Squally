#include "SkeletonArcher.h"

const std::string SkeletonArcher::KeyEnemySkeletonArcher = "skeleton_archer";

SkeletonArcher* SkeletonArcher::deserialize(ValueMap* initProperties)
{
	SkeletonArcher* instance = new SkeletonArcher(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonArcher::SkeletonArcher(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Caverns_SkeletonArcher_Animations,
	false,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonArcher::~SkeletonArcher()
{
}