#pragma once
#include <vector>
#include "State.h"
#include "../Graphic/Graphic.h"
#include "../Graphic/AnimationService.h"
#include "../Utils/Property.h"
#include "../Utils/CMath.h"
#include "../Physic/CollisionEvent.h"

using namespace::std;

class GameObject
{
public: 
	GameObject();
	GameObject(State* state);
	GameObject(Renderable* renderable, State* state = nullptr);
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Render(float zIndex);

	virtual void Translate(float x, float y);
	virtual void Translate(VECTOR2D vec);

	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);

	virtual void IsBlocking();

	void AddChildObject(GameObject* child);
	void RemoveChildObject(GameObject* child);
	GameObject* GetChildWithName(string name);

	string GetStateName() const;

	VECTOR2D GetWorldPosition();
	void TransitionTo(State* state);

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

	PROPERTY(VECTOR2D, acceleration);
	GET(acceleration) { return this->_acceleration; }
	SET(acceleration) { this->_acceleration = value; }

	PROPERTY(DIRECTION, direction);
	GET(direction) { return this->_direction; }
	SET(direction) { this->_direction = value; }

	PROPERTY(bool, showBoundingBox);
	GET(showBoundingBox) { return this->_showBoundingBox; }
	SET(showBoundingBox) { this->_showBoundingBox = value; }

	PROPERTY(string, name);
	GET(name) { return this->_name; }
	SET(name) { this->_name = value; }

	PROPERTY(float, width);
	GET(width) { return this->_width; }
	SET(width) { this->_width = value; }

	PROPERTY(float, height);
	GET(height) { return this->_height; }
	SET(height) { this->_height = value; }

	PROPERTY(bool, isActive);
	GET(isActive) { return this->_isActive; }
	SET(isActive) { this->_isActive = value; }

	PROPERTY(bool, isGrounded);
	GET(isGrounded) { return this->_isGrounded; }
	SET(isGrounded) { this->_isGrounded = value; }

	PROPERTY(bool, isBlocking);
	GET(isBlocking) { return this->_isBlocking; }
	SET(isBlocking) { this->_isBlocking = value; }

	PROPERTY(UINT, figure);
	GET(figure) { return this->_figure; }
	SET(figure) { this->ChangeFigure(value); }
#pragma endregion

protected:
	GameObject* _parent;
	vector<GameObject*> _children;
	State* _state;
	bool _showBoundingBox;
	bool _isFlipped;
	string _name;
	float _width = 0.0f;
	float _height = 0.0f;
	bool _isActive = true;
	bool _isGrounded = false;
	UINT _figure;
	bool _isBlocking = false;

#pragma region Transform
	VECTOR2D _position;
	VECTOR2D _velocity; // units per second.
	VECTOR2D _acceleration;
	MATRIX _worldMatrix;
	bool _isTransformChanged;
	DIRECTION _direction;
	Renderable* _renderable;

	virtual void OnTransformChanged();
	void CalculateWorldMatrix();
	virtual Renderable* GetRenderable();
	void ChangeFigure(UINT figure) {};
#pragma endregion
};

