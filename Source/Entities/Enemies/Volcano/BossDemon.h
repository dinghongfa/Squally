#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossDemon : public Enemy
{
public:
	static BossDemon * create();

private:
	BossDemon();
	~BossDemon();
};