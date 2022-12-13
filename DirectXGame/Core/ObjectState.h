#pragma once
#include <string>
#include "../Graphic/Animation.h"
#include "../Utils/Property.h"
#include "../Utils/Debug.h"
#include "../Utils/CMath.h"
#include "../Physic/CollisionEvent.h"

using namespace::std;

class GameObject;
class ObjectState
{
public:
	ObjectState() { this->_context = nullptr; this->_name = ""; }
	~ObjectState();

	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};

	virtual Box GetBoundingBox();
	virtual void OnCollision(CollisionEvent colEvent);

	W_PROPERTY(GameObject*, context);
	SET(context) { this->_context = value; }

	R_PROPERTY(string, name);
	GET(name) { return this->_name; }

protected:
	GameObject* _context;
	float _width = 0.0f;
	float _height = 0.0f;
	string _name;
};

