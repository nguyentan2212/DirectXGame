#include "GameObject.h"
#include "../Utils/Debug.h"
#include "../Graphic/Graphic.h"

GameObject::GameObject(ObjectState* state)
{
	this->_position = VECTOR2D(0.0f, 0.0f);
	this->_isTransformChanged = false;
	this->_direction = DIRECTION::LEFT;
	this->_parent = nullptr;
	this->_children = vector<GameObject*>(0);
	this->_showBoundingBox = false;
	this->_isFlipped = false;
	TransitionTo(state);
}

GameObject::~GameObject()
{
	delete this->_state;
	delete this->_parent;
}

void GameObject::Update(float deltaTime)
{
	if (this->_velocity != VECTOR2D(0.0f, 0.0f))
	{
		Translate(this->_velocity * deltaTime / 1000);
	}
	this->_state->Update(deltaTime);
	for (GameObject* obj : this->_children)
	{
		obj->Update(deltaTime);
	}
}

void GameObject::Render()
{
	Graphic* graphic = Graphic::GetInstance();
	VECTOR2D cameraPosition = graphic->cameraPosition;

	VECTOR2D worldPosition = GetWorldPosition() - cameraPosition;
	Animation* animation = this->_state->GetAnimation();
	if (animation != nullptr)
	{
		animation->Render(worldPosition.x, worldPosition.y, this->_isFlipped);
	}
	for (GameObject* obj : this->_children)
	{
		obj->Render();
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
void GameObject::TransitionTo(ObjectState* state)
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
}

/// <summary>
/// Gets the bounding box.
/// </summary>
/// <returns></returns>
Box GameObject::GetBoundingBox()
{
	if (this->_state != nullptr)
	{
		return this->_state->GetBoundingBox();
	}
	return Box();
}

/// <summary>
/// Draws the bounding box.
/// </summary>
void GameObject::DrawBoundingBox()
{
	Graphic* graphic = Graphic::GetInstance();
	Box boundingBox = GetBoundingBox();
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
