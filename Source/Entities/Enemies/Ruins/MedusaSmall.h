#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MedusaSmall : public Enemy
{
public:
	static MedusaSmall * create();

	static const std::string KeyEnemyMedusaSmall;

private:
	MedusaSmall();
	~MedusaSmall();
};
