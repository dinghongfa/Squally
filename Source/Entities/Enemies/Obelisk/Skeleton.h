#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Skeleton : public Enemy
{
public:
	static Skeleton * create();

private:
	Skeleton();
	~Skeleton();
};