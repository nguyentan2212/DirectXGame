#include "GameObject.h"
#include "Camera.h"
#include "../Utils/Debug.h"

GameObject::GameObject()
{
	this->_position = VECTOR2D(0.0f, 0.0f);
	this->_isTransformChanged = false;
	this->_direction = DIRECTION::LEFT;
	this->_parent = nullptr;
	this->_children = vector<GameObject*>(0);
	this->_showBoundingBox = true;
	this->_isFlipped = false;
	this->_renderable = nullptr;
	this->_state = nullptr;
	SetState(0);
}

GameObject::GameObject(State* state)
{
	this->_position = VECTOR2D(0.0f, 0.0f);
	this->_isTransformChanged = false;
	this->_direction = DIRECTION::LEFT;
	this->_parent = nullptr;
	this->_children = vector<GameObject*>(0);
	this->_showBoundingBox = true;
	this->_isFlipped = false;
	this->_renderable = nullptr;
	TransitionTo(state);
	SetState(0);
}

GameObject::GameObject(Renderable* renderable, State* state)
{
	this->_position = VECTOR2D(0.0f, 0.0f);
	this->_isTransformChanged = false;
	this->_direction = DIRECTION::LEFT;
	this->_parent = nullptr;
	this->_children = vector<GameObject*>(0);
	this->_showBoundingBox = true;
	this->_isFlipped = false;
	this->_renderable = renderable;
	TransitionTo(state);
	SetState(0);
}

GameObject::~GameObject()
{
	delete this->_state;
	delete this->_parent;
}

void GameObject::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (this->_state != nullptr)
	{
		this->_state->Update(deltaTime);
	}

	this->_velocity += this->_acceleration * deltaTime / 1000;
	Translate(this->_velocity * deltaTime / 1000);

	Renderable* r = GetRenderable();
	if (r)
	{
		r->Update(deltaTime);
	}
}

void GameObject::Render()
{
	Render(0.0f);
}

void GameObject::Render(float zIndex)
{
	if (this->_isActive == false)
	{
		return;
	}

	Camera* camera = Camera::GetInstance();
	VECTOR2D cameraPosition = camera->position;

	VECTOR2D worldPosition = GetWorldPosition() - cameraPosition;
	Renderable* r = GetRenderable();
	if (r != nullptr)
	{
		r->Render(worldPosition.x, worldPosition.y, this->_isFlipped, zIndex);
	}
}

/// <summary>
/// Called when [key up].
/// </summary>
/// <param name="keyCode">The key code.</param>
void GameObject::OnKeyUp(int keyCode)
{
}

/// <summary>
/// Called when [key down].
/// </summary>
/// <param name="keyCode">The key code.</param>
void GameObject::OnKeyDown(int keyCode)
{
}

void GameObject::IsBlocking()
{
	if (this->_isBlocking)
	{
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
	}
}

void GameObject::SetState(UINT stateValue, string stateName)
{
	this->_states[stateName] = stateValue;
}

UINT GameObject::GetState(string stateName)
{
	auto it = this->_states.find(stateName);
	if (it != this->_states.end())
	{
		return it->second;
	}
	DebugOut((wchar_t*)L"[ERROR] GameObject set to	WRONG STATE");
	return -1;
}

/// <summary>
/// Translates object follow the specified VECTOR2D(x, y).
/// </summary>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
void GameObject::Translate(float x, float y)
{
	Translate(VECTOR2D(x, y));
}

/// <summary>
/// Translates object follow the specified VECTOR2D
/// </summary>
/// <param name="vec">The vec.</param>
void GameObject::Translate(VECTOR2D vec)
{
	this->_position += vec;
	OnTransformChanged();
}

/// <summary>
/// Adds the child object.
/// </summary>
/// <param name="child">The child.</param>
void GameObject::AddChildObject(GameObject* child)
{
	vector<GameObject*>::iterator it = find(this->_children.begin(), this->_children.end(), child);
	if (it == this->_children.end())
	{
		this->_children.push_back(child);
		child->_parent = this;
	}
}

/// <summary>
/// Removes the child object.
/// </summary>
/// <param name="child">The child.</param>
void GameObject::RemoveChildObject(GameObject* child)
{
	vector<GameObject*>::iterator it = find(this->_children.begin(), this->_children.end(), child);
	if (it != this->_children.end())
	{
		this->_children.erase(it);
		child->_parent = nullptr;
	}
}

GameObject* GameObject::GetChildWithName(string name)
{
	for (GameObject* child : this->_children)
	{
		if (child->name == name)
		{
			return child;
		}
	}
	return nullptr;
}

string GameObject::GetStateName() const
{
	if (this->_state)
	{
		return this->_state->name;
	}
	return "";
}

/// <summary>
/// Gets the world position.
/// </summary>
/// <returns></returns>
VECTOR2D GameObject::GetWorldPosition()
{
	CalculateWorldMatrix();

	VECTOR2D origin = VECTOR2D(0.0f, 0.0f);
	VECTOR result;
	D3DXVec2Transform(&result, &origin, &this->_worldMatrix);
	return VECTOR2D(result);
}

/// <summary>
/// Transitions to specific state.
/// </summary>
/// <param name="state">The state.</param>
void GameObject::TransitionTo(State* state)
{
	if (state == nullptr)
	{
		DebugOut((wchar_t*)L"[ERROR] GameObject transition to NULL STATE");
		return;
	}

	if (this->_state != nullptr)
		delete this->_state;
	this->_state = state;
	this->_state->context = this;
	this->_state->OnTransition();
}

/// <summary>
/// Gets the bounding box.
/// </summary>
/// <returns></returns>
Box GameObject::GetBoundingBox()
{
	VECTOR2D result = this->GetWorldPosition();
	result -= VECTOR2D(this->_width, this->_height) / 2;

	return Box(result.x, result.y, this->_width, this->_height);
}

/// <summary>
/// Draws the bounding box.
/// </summary>
void GameObject::DrawBoundingBox()
{
	Camera* camera = Camera::GetInstance();

	Graphic* graphic = Graphic::GetInstance();
	Box boundingBox = GetBoundingBox();
	boundingBox.x -= camera->position.x;
	boundingBox.y -= camera->position.y;

	graphic->DrawBox(boundingBox.x, boundingBox.y, boundingBox.width, boundingBox.height);

	for (GameObject* obj : this->_children)
	{
		obj->DrawBoundingBox();
	}
}

void GameObject::OnCollision(CollisionEvent colEvent)
{
}

/// <summary>
/// Calculates the world matrix.
/// </summary>
void GameObject::CalculateWorldMatrix()
{
	// if the transform is changed => re-calculate the world matrix
	if (this->_isTransformChanged)
	{
		MATRIX parentWorldMatrix;
		D3DXMatrixIdentity(&parentWorldMatrix); // initialize with an identity matrix

		MATRIX translationMatrix;
		D3DXMatrixTranslation(&translationMatrix, this->_position.x, this->_position.y, 0.0f);

		// if this is a child => get its parent's world matrix
		if (this->_parent != nullptr)
		{
			this->_parent->CalculateWorldMatrix();
			parentWorldMatrix = this->_parent->_worldMatrix;
		}
		this->_worldMatrix = translationMatrix * parentWorldMatrix;
		this->_isTransformChanged = false;
	}
}

Renderable* GameObject::GetRenderable()
{
	return this->_renderable;
}

/// <summary>
/// Called when [transform changed].
/// </summary>
void GameObject::OnTransformChanged()
{
	this->_isTransformChanged = true;
	for (GameObject* child : this->_children)
	{
		child->OnTransformChanged();
	}
}
