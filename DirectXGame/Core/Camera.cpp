#include "Camera.h"

Camera* Camera::_instance = nullptr;

Camera::Camera()
{
	this->_followedObj = nullptr;
	this->_position = VECTOR2D(0.0f, 0.0f);
	this->_width = this->_height = 0.0f;
}

Camera::~Camera()
{
	if (this->_followedObj != nullptr)
	{
		delete this->_followedObj;
	}
}

VECTOR2D Camera::GetFollowObjPosition()
{
	if (this->_followedObj == nullptr)
	{
		VECTOR2D cameraCenter = this->_position + VECTOR2D(this->_width, this->_height) / 2.0f;
		return cameraCenter;
	}
	return this->_followedObj->GetWorldPosition();
}

void Camera::Update(float deltaTime)
{
	VECTOR2D cameraCenter = this->_position + VECTOR2D(this->_width, this->_height) / 2.0f;
	VECTOR2D transVector = GetFollowObjPosition() - cameraCenter;
	this->_position += transVector + this->_translateVector;

	if (this->_position.x < this->_bottomLeft.x)
	{
		this->_position.x = this->_bottomLeft.x;
	}
	if (this->_position.y < this->_bottomLeft.y)
	{
		this->_position.y = this->_bottomLeft.y;
	}

	if (this->_position.x > this->_topRight.x)
	{
		this->_position.x = this->_topRight.x;
	}
	if (this->_position.y > this->_topRight.y)
	{
		this->_position.y = this->_topRight.y;
	}
}

void Camera::Render()
{
}

Camera* Camera::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Camera();
	}
	return _instance;
}

void Camera::Init(float width, float height)
{
	this->_width = width;
	this->_height = height;
}

void Camera::Follow(GameObject* obj, VECTOR2D vec)
{
	this->_followedObj = obj;
	this->_translateVector = vec;
}
