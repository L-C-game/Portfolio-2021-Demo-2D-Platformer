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

void GameObject::UpdateAll(GameState& gameState)
{
	std::sort(s_vUpdateList.begin(), s_vUpdateList.end(), GameObject::UpdateOrder);

	for (int n = 0; unsigned(n) < s_vUpdateList.size(); n++)
	{
		s_vUpdateList[n]->Update(gameState);

		if (!s_vUpdateList[n]->m_active)
		{
			delete s_vUpdateList[n--];
		}
	}
}

void GameObject::DrawAll(GameState& gameState)
{
	std::sort(s_vDrawList.begin(), s_vDrawList.end(), GameObject::DrawOrder);

	for (int n = 0; unsigned(n) < s_vDrawList.size(); n++)
	{
		s_vDrawList[n]->Draw(gameState);
	}
}

float GameObject::RandomNumGen(int min, int max)
{
	return static_cast<float>((std::rand() % ((max - min) + 1)) + min);
}

bool GameObject::AABBCollision(GameObject* other)
{
	if (other->GetSolid() && this->GetSolid())
	{
		if (abs((this->GetPosition().x) - (other->GetPosition().x)) > (this->GetHalfSize().x + other->GetHalfSize().x))
		{
			return false;
		}

		if (abs((this->GetPosition().y) - (other->GetPosition().y)) > (this->GetHalfSize().y + other->GetHalfSize().y))
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

// Might want to change to giving 2 game objects if the collision moves to it's own file
Point2f GameObject::CalcOverlap(GameObject* other)
{
	Point2f overlap;
	overlap.x = (this->GetHalfSize().x + other->GetHalfSize().x) - (abs((this->GetPosition().x) - (other->GetPosition().x)));
	overlap.y = (this->GetHalfSize().y + other->GetHalfSize().y) - (abs((this->GetPosition().y) - (other->GetPosition().y)));
	return overlap;
}

GameObject::CollidingSide GameObject::ResolveCollision(GameObject* other)
{
	if (AABBCollision(other))
	{
		const Point2f& overlap = CalcOverlap(other);
		Point2f pos = (this->GetPosition());
		Point2f* posPtr = &pos;
		if (overlap.x > overlap.y || overlap.x == overlap.y)
		{
			// resolve vertical
			// Distance between centres for y
			float yDiff = (this->GetPosition().y) - (other->GetPosition().y);
			posPtr->y = posPtr->y + ((yDiff/abs(yDiff)) * (overlap.y));
			this->SetPosition(*posPtr);
			if (yDiff < 0)
			{
				return CollidingSide::SIDE_DOWN;
			}
			else
			{
				return CollidingSide::SIDE_UP;
			}
		}
		else if (overlap.y > overlap.x)
		{
			// resolve horizontal
			float xDiff = (this->GetPosition().x - (other->GetPosition().x));
			posPtr->x = posPtr->x + ((xDiff / abs(xDiff)) * (overlap.x + PIXEL_BUFFER));
			this->SetPosition(*posPtr);
			if (xDiff > 0)
			{
				return CollidingSide::SIDE_RIGHT;
			}
			else
			{
				return CollidingSide::SIDE_LEFT;
			}
		}
	}
	return CollidingSide::SIDE_NULL;
}

//	Gives the no. objects
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
