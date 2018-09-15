#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"
#include "Engine/Dialogue/Dialogue.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Cutscenes/Objects/FlyingCar.h"
#include "Scenes/Cutscenes/Objects/StarLayer.h"

using namespace cocos2d;

class NeonCity : public CutsceneClip
{
public:
	enum NeonCityScene {
		Intro,
		Return,
		Singularity
	};

	static NeonCity* create(NeonCityScene neonCityScene);

protected:
	NeonCity(NeonCityScene neonCityScene);
	~NeonCity();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void cutscenePan();
	void onDialogueShown();

	NeonCityScene activeScene;

	LayerGradient* sky;
	LayerColor* darkFilter;
	StarLayer* starLayer;
	InfiniteParallaxNode* cityBackground;
	InfiniteParallaxNode* cityMidground;
	Sprite* vaporCorp;
	FlyingCar* junker1;
	FlyingCar* viper1;
	FlyingCar* viper2;
	FlyingCar* propeller1;
	InfiniteParallaxNode* cityForeground;

	LayerColor* dialoguePlate;
	Dialogue* dialogue;
	Label* escapeLabel;

	static const float vaporCorpOffset;
};