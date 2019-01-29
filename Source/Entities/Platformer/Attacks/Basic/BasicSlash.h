#pragma once

#include "Entities/Platformer/Attacks/PlatformerAttack.h"

class BasicSlash : public PlatformerAttack
{
public:
	static BasicSlash* create();

	PlatformerAttack* clone() override;
	LocalizedString* getString() override;

protected:
	BasicSlash();
	~BasicSlash() = default;

private:
	typedef PlatformerAttack super;

	static const std::string AttackKeyBasicSlash;
};