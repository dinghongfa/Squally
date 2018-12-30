#include "HexusOpponentPreview.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCLayer.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

HexusOpponentPreview* HexusOpponentPreview::create(HexusOpponentData* opponentData)
{
	HexusOpponentPreview* instance = new HexusOpponentPreview(opponentData);

	instance->autorelease();

	return instance;
}

HexusOpponentPreview::HexusOpponentPreview(HexusOpponentData* opponentData)
{
	this->hexusOpponentData = opponentData;
	this->opponentSprite = SmartAnimationNode::create(opponentData->animationResourceFile);
	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentSprite->playAnimation();
	this->disabledLayer = LayerColor::create(Color4B(0, 0, 0, 0), 512, 512);

	this->frame = MenuSprite::create(UIResources::Menus_MinigamesMenu_Hexus_EnemyFrame, UIResources::Menus_MinigamesMenu_Hexus_EnemyFrameHover);
	this->frame->setClickSound(SoundResources::Menus_Simple_Button);

	DrawNode* clipStencil = DrawNode::create();
	Size frameSize = Size(this->frame->getContentSize().width, this->frame->getContentSize().height);
	Size clipSize = Size(frameSize.width - 48.0f, frameSize.height - 48.0f);
	clipStencil->drawSolidRect(Vec2(-clipSize.width / 2.0f, -clipSize.height / 2.0f), Vec2(clipSize.width / 2.0f, clipSize.height / 2.0f), Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(clipStencil);

	this->frameClip = ClippingNode::create(clipStencil);
	this->frameClip->setAnchorPoint(Vec2::ZERO);

	this->opponentSprite->setCascadeOpacityEnabled(false);

	this->setContentSize(this->frame->getContentSize());

	this->frame->setClickCallback(CC_CALLBACK_1(HexusOpponentPreview::onOpponentClick, this));

	this->frameClip->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->frameClip->addChild(this->opponentSprite);
	this->frameClip->addChild(this->disabledLayer);
	this->addChild(this->frameClip);
	this->addChild(this->frame);
}

HexusOpponentPreview::~HexusOpponentPreview()
{
}

void HexusOpponentPreview::initializePositions()
{
	SmartNode::initializePositions();

	this->disabledLayer->setPosition(Vec2(-256.0f, -256.0f));

	if (this->hexusOpponentData != nullptr)
	{
		this->opponentSprite->setPosition(this->hexusOpponentData->animationOffset);
	}
}

void HexusOpponentPreview::onOpponentClick(MenuSprite* HexusOpponentPreview)
{
	NavigationEvents::navigateHexus(NavigationEvents::NavigateHexusArgs(this->hexusOpponentData));
}

void HexusOpponentPreview::disableInteraction()
{
	this->frame->disableInteraction();
	this->frameClip->setOpacity(128);
	this->disabledLayer->setOpacity(196);
}

void HexusOpponentPreview::enableInteraction()
{
	this->frame->enableInteraction();
	this->frameClip->setOpacity(255);
	this->disabledLayer->setOpacity(0);
}
