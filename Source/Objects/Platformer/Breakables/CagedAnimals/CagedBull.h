#pragma once

#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimal.h"

namespace cocos2d
{
	class Sprite;
};

class CagedBull : public CagedAnimal
{
public:
	static CagedBull* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCagedBull;

protected:
	CagedBull(cocos2d::ValueMap& initProperties);
	virtual ~CagedBull();

	void initializePositions() override;

private:
	typedef CagedAnimal super;

	cocos2d::Sprite* animalSprite;
};