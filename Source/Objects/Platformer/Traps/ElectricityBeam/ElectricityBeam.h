#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class ElectricityBeam : public HackableObject
{
public:
	static ElectricityBeam* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ElectricityBeam(cocos2d::ValueMap& properties);
	virtual ~ElectricityBeam();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void updateElectricityBeam(float dt);

	SmartAnimationSequenceNode* electricityAnimation;
	CollisionObject* electricityCollision;
	cocos2d::Sprite* ballLeft;
	cocos2d::Sprite* ballRight;

	float currentElectricityBeamCountDown;
	float maxElectricityBeamCountDown;
	bool isRunningAnimation;
	bool isVertical;

	static const std::string PropertyVertical;
};