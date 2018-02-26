#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Entities/Npcs/NpcBase.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

class Knight : public NpcBase
{
public:
	static Knight * create();

private:
	Knight();
	~Knight();

	void update(float) override;

	Animation* idleAnimation;

	Sprite* knightSprite;
};