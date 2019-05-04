#include "EdxCrystal.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Scenes/PointerTrace/RegisterState.h"

#include "Resources/IsometricObjectResources.h"

#include "Strings/PointerTrace/Assembly/RegisterEdx.h"
#include "Strings/PointerTrace/Assembly/RegisterRdx.h"

using namespace cocos2d;

const std::string EdxCrystal::MapKeyEdxCrystal = "edx-crystal";

EdxCrystal* EdxCrystal::create(ValueMap& initProperties)
{
	EdxCrystal* instance = new EdxCrystal(initProperties);

	instance->autorelease();

	return instance;
}

EdxCrystal::EdxCrystal(ValueMap& initProperties) : super(initProperties)
{
	this->crystal = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_EdxCrystal);
	
	LocalizedString* registerString = (sizeof(void*) == 4)
		? (LocalizedString*)Strings::PointerTrace_Assembly_RegisterEdx::create()
		: (LocalizedString*)Strings::PointerTrace_Assembly_RegisterRdx::create();

	this->buildMovString(registerString);

	this->crystalNode->addChild(this->crystal);
}

EdxCrystal::~EdxCrystal()
{
}

void EdxCrystal::onEnter()
{
	super::onEnter();
}

void EdxCrystal::initializePositions()
{
	super::initializePositions();
}

void EdxCrystal::updateRegister(int value)
{
	RegisterState::setRegisterEdx(value);
}
