#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyCameraFollowBehavior : public AttachedBehavior
{
public:
	static SquallyCameraFollowBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCameraFollowBehavior(GameObject* owner);
	virtual ~SquallyCameraFollowBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	float getLayerZoom();

	Squally* squally;
};
