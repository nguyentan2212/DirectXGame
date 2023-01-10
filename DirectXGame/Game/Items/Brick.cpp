#include "Brick.h"
#include "../../Graphic/SpriteService.h"
#include "../../Core/Camera.h"

Brick::Brick(): GameObject(new ObjectState())
{

}

void Brick::Update(float deltaTime)
{
	
}

void Brick::Render()
{
	
}

Renderable* Brick::GetRenderable()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("brick");
}

void Brick::OnCollision(CollisionEvent colEvent)
{
	
}
