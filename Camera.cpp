#include "GameObject.h"
#include "Player.h"
#include "Camera.h"

Camera::Camera(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_CAMERA);
	SetUpdateOrder(6);
}


void Camera::Spawn()
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_CAMERA) < 1)
	{
		Point2f initialPos = { (S_DISPLAY_WIDTH / 2), (S_DISPLAY_HEIGHT / 2) };
		GameObject* camera = new Camera(initialPos);
	}
}

void Camera::Update(GameState& state)
{
}

void Camera::Draw(GameState& state) const {}