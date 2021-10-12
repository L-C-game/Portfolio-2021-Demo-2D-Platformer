#include "Play.h"
#include "GameObject.h"

std::vector< GameObject* > GameObject::s_vUpdateList;
std::vector< GameObject* > GameObject::s_vDrawList;

// Game object constructor
GameObject::GameObject() = default;
GameObject::GameObject(Point2f pos)
{
	m_pos = pos;

	s_vUpdateList.push_back(this);
	s_vDrawList.push_back(this);
}

// Game object destructor
GameObject::~GameObject()
{
	s_vDrawList.erase(std::find(s_vDrawList.begin(), s_vDrawList.end(), this));
	s_vUpdateList.erase(std::find(s_vUpdateList.begin(), s_vUpdateList.end(), this));
}

void GameObject::UpdateAll(GameState & state)
{
	std::sort(s_vUpdateList.begin(), s_vUpdateList.end(), GameObject::UpdateOrder);

	for (int n = 0; unsigned(n) < s_vUpdateList.size(); n++)
	{
		s_vUpdateList[n]->Update(state);

		if (!s_vUpdateList[n]->m_active)
		{
			delete s_vUpdateList[n--];
		}
	}
}

void GameObject::DrawAll(GameState & state)
{
	std::sort(s_vDrawList.begin(), s_vDrawList.end(), GameObject::DrawOrder);

	for (int n = 0; unsigned(n) < s_vDrawList.size(); n++)
	{
		s_vDrawList[n]->Draw(state);
	}
}

float GameObject::RandomNumGen(int min, int max)
{
	return static_cast<float>((std::rand() % ((max - min) + 1)) + min);
}

//bool GameObject::HasCollided(Point2f pos1, Point2f pos2)
//{
//	Vector2f d = pos2 - pos1;
//	float dist = sqrt((d.x * d.x) + (d.y * d.y));
//	if (dist < S_HALF_LIMIT)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool GameObject::AABBCollision( GameObject* other)
{
	if (abs((this->GetCentre().x) - (other->GetCentre().x)) < (this->GetHalfSize().x + other->GetHalfSize().x))
	{
		return true;
	}

	if (abs((this->GetCentre().y) - (other->GetCentre().y)) < (this->GetHalfSize().y + other->GetHalfSize().y))
	{
		return true;
	}

	return false;
}

//bool GameObject::CheckCollisions(GameObject* a, GameObject* b)
//{
//	if (GameObject::HasCollided(a->GetPosition(), b->GetPosition()))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//
//}

void GameObject::ScreenWrapper(Point2f idealPos)
{
	// Only require the x direction wrapping for the scr
	Point2f pos = idealPos;
	if (idealPos.x > S_DISPLAY_WIDTH + S_SCREEN_LIMIT)
	{
		pos = { -S_SCREEN_LIMIT, idealPos.y };
	}
	else if (idealPos.x < -S_SCREEN_LIMIT)
	{
		pos = { S_DISPLAY_WIDTH + S_SCREEN_LIMIT, idealPos.y };
	}
	//else if (idealPos.y < 0)
	//{
	//	pos = { idealPos.x, S_DISPLAY_HEIGHT + S_SCREEN_LIMIT };
	//}
	//else if (idealPos.y > S_DISPLAY_HEIGHT + S_SCREEN_LIMIT)
	//{
	//	pos = { idealPos.x, 0 };
	//}

	SetPosition(pos);
}

// Can give the no. objects
int GameObject::GetObjectCount(GameObject::Type type)
{
	int count = 0;

	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == Type::OBJ_ALL)
			count++;
	}

	return count;
}

int GameObject::GetObjectList(GameObject::Type type, std::vector< GameObject* >& vList)
{
	vList.clear();

	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == Type::OBJ_ALL)
			vList.push_back(p);
	}

	return static_cast<int>(vList.size());
}

std::vector< GameObject* > GameObject::GetTypeList(GameObject::Type type)
{
	std::vector< GameObject* > typeList;
	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type || type == Type::OBJ_ALL)
			typeList.push_back(p);
	}

	return typeList;
}


void GameObject::DestroyAll()
{
	for (int n = 0; unsigned(n) < s_vDrawList.size(); n++)
		delete s_vUpdateList[n--];
}
