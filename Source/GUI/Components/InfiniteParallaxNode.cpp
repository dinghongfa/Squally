#include "InfiniteParallaxNode.h"

InfiniteParallaxNode* InfiniteParallaxNode::create(std::string spriteResourcePath)
{
	InfiniteParallaxNode* node = new InfiniteParallaxNode(spriteResourcePath);

	node->autorelease();

	return node;
}

InfiniteParallaxNode::InfiniteParallaxNode(std::string spriteResourcePath)
{
	const int overlap = 2;

	this->nodes = new std::vector<Node*>();

	Sprite* nextSprite = Sprite::create(spriteResourcePath);
	this->spriteWidth = nextSprite->getContentSize().width;
	// TODO: Grab screen width from config
	float remainingSize = 1920.0f * 4.0f;

	Vec2 nextPosition = Vec2(-this->spriteWidth, 0.0f);

	do
	{
		nextSprite->setPosition(nextPosition);

		this->nodes->push_back(nextSprite);
		this->addChild(nextSprite, 0, Vec2(1.0f, 1.0f), nextPosition);

		remainingSize -= this->spriteWidth;

		if (remainingSize > 0.0f)
		{
			nextSprite = Sprite::create(spriteResourcePath);
			nextPosition.x += this->spriteWidth - overlap;
		}

	} while (remainingSize > 0.0f);

	this->scheduleUpdate();
}

InfiniteParallaxNode::~InfiniteParallaxNode()
{
	delete(this->nodes);
}

void InfiniteParallaxNode::update(float dt)
{
	Node* firstNode = this->nodes->at(0);
	Node* lastNode = this->nodes->at(this->nodes->size() - 1);
	Vec2 position = this->getParent()->convertToWorldSpace(this->getPosition());

	if (position.x < -this->spriteWidth)
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}

	if (position.x > this->spriteWidth)
	{
		this->setPosition(Vec2(0, this->getPosition().y));
	}
}
