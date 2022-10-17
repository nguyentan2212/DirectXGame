#include "CollisionManager.h"

CollisionManager* CollisionManager::_instance = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new CollisionManager();
    }
    return _instance;
}

CollisionEvent CollisionManager::CalcAABB(GameObject* objA, GameObject* objB, float deltaTime)
{
    VECTOR2D vA = objA->velocity;
    VECTOR2D vB = objB->velocity;

    Box boxA = objA->GetBoundingBox();
    Box boxB = objB->GetBoundingBox();

    VECTOR2D dA = vA * deltaTime / 1000;
    // broad phase
    Box broadPhaseBox = Box(boxA);
    broadPhaseBox.x += dA.x;
    broadPhaseBox.y += dA.y;
    broadPhaseBox.width += dA.x;
    broadPhaseBox.height += dA.y;

    if (IsCollision(broadPhaseBox, boxB) == false)
    {
        return CollisionEvent::NoCollision();
    }

    // both objs are moving => objA move & objB stand idle
    if (vB != VECTOR2D(0.0f, 0.0f))
    {
        vA -= vB;
        vB = VECTOR2D(0.0f, 0.0f);
    }

    float dxEntry, dxExit;
    float dyEntry, dyExit;

    if (vA.x > 0.0f)
    {
        dxEntry = boxB.x - (boxA.x + boxA.width);
        dxExit = (boxB.x + boxB.width) - boxA.x;
    }
    else
    {
        dxEntry = (boxB.x + boxB.width) - boxA.x;
        dxExit = boxB.x - (boxA.x + boxA.width);
    }
    if (vA.y > 0.0f)
    {
        dyEntry = boxB.y - (boxA.y + boxA.height);
        dyExit = (boxB.y + boxB.height) - boxA.y;
    }
    else
    {
        dyEntry = (boxB.y + boxB.height) - boxA.y;
        dyExit = (boxB.y + boxB.height) - boxA.y;
    }

    float txEntry, txExit;
    float tyEntry, tyExit;
    if (vA.x == 0.0f)
    {
        txEntry = -numeric_limits<float>::infinity();
        txExit = numeric_limits<float>::infinity();
    }
    else
    {
        txEntry = dxEntry / vA.x;
        txExit = dxExit / vA.x;
    }

    if (vA.y == 0.0f)
    {
        tyEntry = -numeric_limits<float>::infinity();
        tyExit = numeric_limits<float>::infinity();
    }
    else
    {
        tyEntry = dyEntry / vA.y;
        tyExit = dyExit / vA.y;
    }
    float entryTime = max(txEntry, tyEntry);
    float exitTime = min(txExit, tyExit);

    if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
    {
        return CollisionEvent::NoCollision();
    }
    DIRECTION direction;

    if (txEntry > tyEntry)
    {
        if (dxEntry > 0.0f)
        {
            direction = DIRECTION::RIGHT;
        }
        else
        {
            direction = DIRECTION::LEFT;
        }
    }
    else
    {
        if (dyEntry > 0.0f)
        {
            direction = DIRECTION::UP;
        }
        else
        {
            direction = DIRECTION::DOWN;
        }
    }
    return CollisionEvent(objB, direction, entryTime, deltaTime);
}

bool CollisionManager::IsCollision(Box boxA, Box boxB)
{
    float d1x = boxB.x - (boxA.x + boxA.width);
    float d1y = boxB.y - (boxA.y + boxA.height);
    float d2x = boxA.x - (boxB.x + boxB.width);
    float d2y = boxA.y - (boxB.y + boxB.height);

    if (d1x > 0.0f || d1y > 0.0f || d2x > 0.0f || d2y > 0.0f)
    {
        return false;
    }
    return true;
}

void CollisionManager::Processing(float deltaTime)
{
    for (GameObject* root : this->_listeners)
    {
        for (GameObject* obj : this->_listeners)
        {
            if (root != obj)
            {
                CollisionEvent colEvent = CalcAABB(root, obj, deltaTime);
                if (colEvent.direction != DIRECTION::NONE)
                {
                    root->OnCollision(colEvent);
                }
            }
        }
    }
}

void CollisionManager::AddListener(GameObject* listener)
{
    this->_listeners.push_back(listener);
}

void CollisionManager::RemoveListener(GameObject* listener)
{
    this->_listeners.remove(listener);
}
