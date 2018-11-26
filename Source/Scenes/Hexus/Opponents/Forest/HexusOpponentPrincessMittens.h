#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPrincessMittens : public HexusOpponentData
{
public:
	static HexusOpponentPrincessMittens* getInstance();

private:
	HexusOpponentPrincessMittens();
	~HexusOpponentPrincessMittens();

	static const std::string OpponentSaveKey;
	static HexusOpponentPrincessMittens* instance;
};
