#pragma once
#include <vector>
#include "ObjectState.h"
#include "../Graphic/Graphic.h"
#include "../Graphic/AnimationService.h"
#include "../Utils/Property.h"
#include "../Utils/CMath.h"
#include "../Physic/CollisionEvent.h"

using namespace::std;

class GameObject
{
public: 
	GameObject(ObjectState* state);
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void Translate(float x, float y);
	virtual void Translate(VECTOR2D vec);

	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);

	void AddChildObject(GameObject* child);
	void RemoveChildObject(GameObject* child);

	VECTOR2D GetWorldPosition();
	void TransitionTo(ObjectState* state);

	virtual Box GetBoundingBox();
	void DrawBoundingBox();

	virtual void OnCollision(CollisionEvent colEvent);

#pragma region Properties
	PROPERTY(VECTOR2D, position);
	GET(position) { return this->_position; }
	SET(position) { this->_position = value; OnTransformChanged(); }
	
	PROPERTY(VECTOR2D, velocity);
	GET(velocity) { return this->_velocity; }
	SET(velocity) { this->_velocity = value; }

	R_PROPERTY(DIRECTION, direction);
	GET(direction) { return this->_direction; }

	PROPERTY(bool, showBoundingBox);
	GET(showBoundingBox) { return this->_showBoundingBox; }
	SET(showBoundingBox) { this->_showBoundingBox = value; }

	PROPERTY(string, name);
	GET(name) { return this->_name; }
	SET(name) { this->_name = value; }
#pragma endregion

protected:
	GameObject* _parent;
	vector<GameObject*> _children;
	ObjectState* _state;
	bool _showBoundingBox;
	bool _isFlipped;
	string _name;

#pragma region Transform
	VECTOR2D _position;
	VECTOR2D _velocity; // units per second.
	MATRIX _worldMatrix;
	bool _isTransformChanged;
	DIRECTION _direction;

	virtual void OnTransformChanged();

	void CalculateWorldMatrix();
#pragma endregion
};

