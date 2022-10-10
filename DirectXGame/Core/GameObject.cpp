#include "GameObject.h"

GameObject::GameObject(Animation* animation)
{
	this->_position = VECTOR2D(0.0f, 0.0f);
	this->_animation = animation;
	this->_isTransformChanged = false;
	this->_parent = nullptr;
	this->_child = vector<GameObject*>(0);
}

GameObject::~GameObject()
{
	delete this->_animation;
}

void GameObject::Update(float deltaTime)
{
	this->_animation->Update(deltaTime);
}

void GameObject::Render()
{
	VECTOR2D worldPosition = GetWorldPosition();
	this->_animation->Render(worldPosition.x, worldPosition.y);
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
	D3DXMatrixTranslation(&this->_translationMatrix, x, y, 0.0f);
	OnTransformChanged();
}

/// <summary>
/// Translates object follow the specified VECTOR2D
/// </summary>
/// <param name="vec">The vec.</param>
void GameObject::Translate(VECTOR2D vec)
{
	Translate(vec.x, vec.y);
}

/// <summary>
/// Gets the world position.
/// </summary>
/// <returns></returns>
VECTOR2D GameObject::GetWorldPosition()
{
	CalculateWorldMatrix();
	VECTOR result;
	D3DXVec2Transform(&result, &this->_position, &this->_worldMatrix);
	return VECTOR2D(result);
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

		// if this is a child => get its parent's world matrix
		if (this->_parent != nullptr)
		{
			this->_parent->CalculateWorldMatrix(&parentWorldMatrix);
		}
		this->_worldMatrix = this->_translationMatrix * parentWorldMatrix;
		this->_isTransformChanged = false;
	}
}

/// <summary>
/// Calculates the world matrix.
/// </summary>
/// <param name="matrixOut">A copy of the world matrix that was re-calculated.</param>
void GameObject::CalculateWorldMatrix(MATRIX* matrixOut)
{
	CalculateWorldMatrix();
	matrixOut = new MATRIX(this->_worldMatrix);
}

/// <summary>
/// Called when [transform changed].
/// </summary>
void GameObject::OnTransformChanged()
{
	this->_isTransformChanged = true;
	for (GameObject* child : this->_child)
	{
		child->OnTransformChanged();
	}
}
