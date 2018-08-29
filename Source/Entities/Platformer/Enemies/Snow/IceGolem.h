#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class IceGolem : public PlatformerEnemy
{
public:
	static IceGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyIceGolem;

private:
	IceGolem(ValueMap* initProperties);
	~IceGolem();
};