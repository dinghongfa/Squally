#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

typedef std::string CategoryName;
typedef int CategoryGroup;

class CollisionObject : public HackableObject
{
public:
	static const std::string RequestCollisionMappingEvent;

	struct CollisionMapRequestArgs
	{
		CategoryName categoryName;
		CollisionObject* collisionObject;

		CollisionMapRequestArgs(CategoryName categoryName, CollisionObject* collisionObject) : categoryName(categoryName), collisionObject(collisionObject)
		{
		}
	};

	static void requestCollisionMapping(CollisionMapRequestArgs args);

	CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, CategoryName initCategoryName, bool isDynamic, bool canRotate);
	~CollisionObject();

	void setCollisionGroups(CategoryGroup categoryGroup, std::vector<CategoryGroup>* collidesWith);

	CategoryName getCategoryName();
	CategoryGroup getCategoryGroup();
	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);

	virtual void setPhysicsEnabled(bool enabled);

	static std::string MapKeyTypeCollision;

protected:
	enum CollisionDirection
	{
		None,
		Left,
		Right,
		Up,
		Down,
		StepLeft,
		StepRight,
	};

	struct CollisionData
	{
		CollisionObject* other;
		Vec2 normal;
		CollisionDirection direction;
		Vec2 points[4];
		int pointCount;

		CollisionData(CollisionObject* other, Vec2 normal, CollisionDirection direction, const Vec2* points, int pointCount)
			: other(other), normal(normal), direction(direction), pointCount(pointCount)
		{
		}
	};

	virtual bool contactBegin(CollisionData data);
	virtual bool contactUpdate(CollisionData data);
	virtual bool contactEnd(CollisionData data);

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);

	CollisionData constructCollisionData(PhysicsContact& contact);

	CategoryName categoryName;
	PhysicsBody* physicsBody;

	bool physicsEnabled;
};
