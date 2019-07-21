#include "UIBoundObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

UIBoundObject* UIBoundObject::create(cocos2d::Node* referencedObject)
{
    UIBoundObject* instance = new UIBoundObject(referencedObject);

    instance->autorelease();

    return instance;
}

UIBoundObject::UIBoundObject(cocos2d::Node* referencedObject)
{
    this->referencedObject = referencedObject;
    this->originalParent = this->referencedObject == nullptr ? nullptr : this->referencedObject->getParent();
}

UIBoundObject::~UIBoundObject()
{
}

void UIBoundObject::onEnter()
{
    super::onEnter();

    if (this->referencedObject != nullptr && this->referencedObject->getParent() != this)
    {
        Vec3 position = this->referencedObject->getPosition3D();
        
        GameUtils::changeParent(this->referencedObject, this, false);

        this->referencedObject->setPosition3D(position);
    }
}

void UIBoundObject::initializeListeners()
{
    super::initializeListeners();

    this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventUnbindObject, [=](EventCustom* eventCustom)
    {
        ObjectEvents::RelocateObjectArgs* args = static_cast<ObjectEvents::RelocateObjectArgs*>(eventCustom->getUserData());
        
        if (args != nullptr)
        {
            if (this->referencedObject != nullptr && this->referencedObject == args->relocatedObject)
            {
                this->removeChild(referencedObject);

                if (this->getParent() != nullptr)
                {
                    this->getParent()->removeChild(this);
                }
            }
        }
    }));
}

Vec3 UIBoundObject::getRealCoords(UIBoundObject* uiBoundObject)
{
    if (uiBoundObject == nullptr || uiBoundObject->referencedObject == nullptr || uiBoundObject->originalParent == nullptr)
    {
        return Vec3::ZERO;
    }

    Vec3 thisCoords = GameUtils::getWorldCoords3D(uiBoundObject);
    Vec3 originalParentCoords = GameUtils::getWorldCoords3D(uiBoundObject->originalParent);
    Vec3 originalCoords = uiBoundObject->referencedObject->getPosition3D();
    Vec3 anchorOffset = Vec3(0.5f * uiBoundObject->originalParent->getContentSize().width * uiBoundObject->originalParent->getScaleX(),
        0.5f * uiBoundObject->originalParent->getContentSize().height * uiBoundObject->originalParent->getScaleY(), 0.0f);
    Vec3 delta = originalParentCoords - thisCoords + anchorOffset;

    return originalCoords + delta;
}

float UIBoundObject::getRealScale(UIBoundObject* uiBoundObject)
{
    if (uiBoundObject == nullptr || uiBoundObject->referencedObject == nullptr || uiBoundObject->originalParent == nullptr)
    {
        return 1.0f;
    }

    float parentScale = GameUtils::getScale(uiBoundObject->originalParent);

    return parentScale * uiBoundObject->referencedObject->getScale();
}

cocos2d::Node* UIBoundObject::getReferencedObject()
{
    return this->referencedObject;
}

cocos2d::Node* UIBoundObject::getOriginalParent()
{
    return this->originalParent;
}

void UIBoundObject::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    if (this->referencedObject == nullptr)
    {
        return;
    }

    Vec3 originalCoords = this->referencedObject->getPosition3D();
    float originalScale = this->referencedObject->getScale();
    Vec3 realCoords = UIBoundObject::getRealCoords(this);
    float realScale = UIBoundObject::getRealScale(this);

    this->referencedObject->setPosition3D(realCoords);
    this->referencedObject->setScale(realScale);

	super::visit(renderer, parentTransform, parentFlags);

    this->referencedObject->setPosition3D(originalCoords);
    this->referencedObject->setScale(originalScale);
}
