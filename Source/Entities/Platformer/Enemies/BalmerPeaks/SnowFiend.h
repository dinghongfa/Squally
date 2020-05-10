#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class SnowFiend : public PlatformerEnemy
{
public:
	static SnowFiend* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	SnowFiend(cocos2d::ValueMap& properties);
	virtual ~SnowFiend();

private:
	typedef PlatformerEnemy super;
};
