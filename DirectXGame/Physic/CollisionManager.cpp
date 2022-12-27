#include "CollisionManager.h"
#include "../Core/ObjectPool.h"

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

    // both objs are moving => objA move & objB stand idle
    if (vB != VECTOR2D(0.0f, 0.0f))
    {
        vA -= vB;
        vB = VECTOR2D(0.0f, 0.0f);
    }

    Box boxA = objA->GetBoundingBox();
    Box boxB = objB->GetBoundingBox();

    VECTOR2D dA = vA * deltaTime / 1000;
    // broad phase
    Box broadPhaseBox = Box(boxA);
    broadPhaseBox.x = vA.x > 0 ? boxA.x : boxA.x + dA.x;
    broadPhaseBox.y = vA.y > 0 ? boxA.y : boxA.y + dA.y;
    broadPhaseBox.width = vA.x > 0 ? boxA.width + dA.x : boxA.width - dA.x;
    broadPhaseBox.height = vA.y > 0 ? boxA.height + dA.y : boxA.height - dA.y;

    if (IsCollision(broadPhaseBox, boxB) == false)
    {
        return CollisionEvent::NoCollision();
    }

    /*if (objB->name == "pine" && objA->name == "small mario")
    {
        DebugOut((wchar_t*)L"[INFO] Mario and pine\n");
    }*/
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
        dyExit = boxB.y - (boxB.height + boxA.y);
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

CollisionEvent CollisionManager::CalcAABB(GameObject* objA, VECTOR2D vA, GameObject* objB, VECTOR2D vB, float deltaTime)
{
    // both objs are moving => objA move & objB stand idle
    if (vB != VECTOR2D(0.0f, 0.0f))
    {
        vA -= vB;
        vB = VECTOR2D(0.0f, 0.0f);
    }

    Box boxA = objA->GetBoundingBox();
    Box boxB = objB->GetBoundingBox();

    VECTOR2D dA = vA * deltaTime / 1000;
    // broad phase
    Box broadPhaseBox = Box(boxA);
    broadPhaseBox.x = vA.x > 0 ? boxA.x : boxA.x + dA.x;
    broadPhaseBox.y = vA.y > 0 ? boxA.y : boxA.y + dA.y;
    broadPhaseBox.width = vA.x > 0 ? boxA.width + dA.x : boxA.width - dA.x;
    broadPhaseBox.height = vA.y > 0 ? boxA.height + dA.y : boxA.height - dA.y;

    if (IsCollision(broadPhaseBox, boxB) == false)
    {
        return CollisionEvent::NoCollision();
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

bool CollisionManager::RayCastBetween(GameObject* objA, GameObject* objB, DIRECTION direction, float distance, float deltaTime)
{
    VECTOR2D vA;
    switch (direction)
    {
    case UP:
        vA = VECTOR2D(0, distance);
        break;
    case DOWN:
        vA = VECTOR2D(0, -distance);
        break;
    case LEFT:
        vA = VECTOR2D(-distance, 0);
        break;
    case RIGHT:
        vA = VECTOR2D(distance, 0);
        break;
    default:
        break;
    }
    vA = vA / (deltaTime / 1000) + objA->velocity;
    VECTOR2D vB = objB->velocity;

    CollisionEvent e = CalcAABB(objA, vA, objB, vB, deltaTime);

    return e.direction == direction;
}

list<GameObject*> CollisionManager::RayCastWith(GameObject* objRoot, DIRECTION direction, float distance, float deltaTime)
{
    ObjectPool* pool = ObjectPool::GetInstance();
    vector<GameObject*> objs = pool->GetAllGameObjectWithQuadtree(objRoot);

    list<GameObject*> results;
    for (GameObject* obj : objs)
    {
        if (objRoot != obj)
        {
            if (RayCastBetween(objRoot, obj, direction, distance, deltaTime))
            {
                results.push_back(obj);
            }
        }
    }
    return results;
}

void CollisionManager::Processing(float deltaTime)
{
    ObjectPool* pool = ObjectPool::GetInstance();

    vector<GameObject*> objs = pool->GetAllGameObject();

    for (GameObject* root : objs)
    {
        if (root->isActive == false)
        {
            continue;
        }
        /*if (root->name == "small mario")
        {
            DebugOut((wchar_t*)L"[INFO] Mario region\n");
        }*/

        vector<GameObject*> entities = pool->GetAllGameObjectWithQuadtree(root);
        /*if (root->name == "small mario")
        {
            DebugOut((wchar_t*)L"[INFO] Mario region has: %d objects\n", entities.size());
        }*/
        for (GameObject* obj : entities)
        {
            if (obj->isActive == false)
            {
                continue;
            }
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
