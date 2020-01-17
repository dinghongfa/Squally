#pragma once

#include "Objects/Platformer/Traps/Launchers/PivotLauncher.h"

namespace cocos2d
{
	class Sprite;
}

class AnimationPart;
class HackableData;
class SmartAnimationNode;

class DartTripodLauncher : public PivotLauncher
{
public:
	static DartTripodLauncher* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyDartTripodLauncher;

protected:
	DartTripodLauncher(cocos2d::ValueMap& properties);
	virtual ~DartTripodLauncher();

	void initializePositions() override;

private:
	typedef PivotLauncher super;

	static const std::string PivotBone;
};