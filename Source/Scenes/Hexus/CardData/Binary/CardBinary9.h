#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary9 : public CardData
{
public:
	CardBinary9();
	~CardBinary9();

private:
	static const std::string StringKeyCardName;
};