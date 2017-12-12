#include "TutorialMap.h"

TutorialMap::TutorialMap()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->titleLabel = new MenuLabel("Hacking Tutorials - Exact Value Scan", Resources::Fonts_Marker_Felt, this->titleFontSize);
	this->infoLabel = new MenuLabel("Exact Value Scan", Resources::Fonts_Marker_Felt, this->titleFontSize);
	this->background = Sprite::create(Resources::GUI_WorldMaps_TutorialMap);
	this->mouse = new Mouse();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->titleLabel->GetSize().height / 2));
	// this->infoLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + this->infoLabel->GetSize().width / 2, origin.y + visibleSize.height - this->titleLabel->GetSize().height / 2));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	// this->addChild(this->infoLabel);

	this->LoadNodes();

	this->addChild(this->mouse);
}

TutorialMap::~TutorialMap()
{
}

void TutorialMap::LoadNodes()
{
	this->addChild(new MapNode(Vec2(112.0f, 640.0f), true));
}

void TutorialMap::onEnter()
{
	Scene::onEnter();

	this->InitializeListeners();
}

void TutorialMap::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TutorialMap::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TutorialMap::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->replaceScene(new TitleScreen());
		break;
	}
}
