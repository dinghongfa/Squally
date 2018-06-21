#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Resources.h"
#include "Utils/StrUtils.h"

#include "ComponentBase.h"

using namespace cocos2d;

class Avatars : public ComponentBase
{
public:
	static Avatars * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	Avatars();
	~Avatars();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void setAvatars(GameState* gameState);

	ClippingNode* clipPlayer;
	ClippingNode* clipEnemy;
	Sprite* framePlayer;
	Sprite* frameEnemy;
	Node* avatarPlayer;
	Node* avatarEnemy;
};