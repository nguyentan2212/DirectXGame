#include "ObjectPool.h"

ObjectPool* ObjectPool::_instance = nullptr;

ObjectPool::ObjectPool()
{

}

ObjectPool* ObjectPool::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new ObjectPool();
    }
    return _instance;
}

GameObject* ObjectPool::GetGameObjectWithName(string name)
{
    for (GameObject* obj : this->_objs)
    {
        if (obj->name == name)
        {
            return obj;
        }
    }
    return nullptr;
}

GameObject* ObjectPool::GetGameObjectWithClass(string className)
{
    for (GameObject* obj : this->_objs)
    {
        if (typeid(*obj).name() == "class " + className)
        {
            return obj;
        }
    }
    return nullptr;
}

vector<GameObject*> ObjectPool::GetAllGameObject()
{
    return this->_objs;
}

void ObjectPool::AddGameObject(GameObject* obj)
{
    this->_objs.push_back(obj);
}

void ObjectPool::Clear()
{
    this->_objs.clear();
}

ObjectPool::~ObjectPool()
{
}
