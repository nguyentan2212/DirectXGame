#pragma once
#include "../Utils/Property.h"
#include "../Math/Vector.h"
#include "../Graphic/Animation.h"

class GameObject
{
public: 
	GameObject(Animation* animation);
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);

	PROPERTY(Vector, position);
	GET(position) { return this->_position; }
	SET(position) { this->_position = value; }

private:
	Vector _position;
	Animation* _animation;
};

