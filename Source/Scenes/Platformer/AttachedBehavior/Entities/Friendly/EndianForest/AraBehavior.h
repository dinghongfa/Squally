#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class AraBehavior : public AttachedBehavior
{
public:
	static AraBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	AraBehavior(GameObject* owner);
	virtual ~AraBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
