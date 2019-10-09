#pragma once
#include <set>

#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class NaturePortal : public MagePortal
{
public:
	static NaturePortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyNaturePortal;

protected:
	NaturePortal(cocos2d::ValueMap& properties);
	~NaturePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MagePortal super;

	cocos2d::DrawNode* background;
	cocos2d::ParticleSystem* portalParticles;
	cocos2d::DrawNode* edge;
	cocos2d::ParticleSystem* edgeParticles;
};
