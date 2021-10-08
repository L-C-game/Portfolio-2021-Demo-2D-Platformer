#pragma once
#include "Play.h"
#include "MainGame.h"

class GameObject
{
public:

	enum class Type
	{
		OBJ_NULL = -1,
		OBJ_PLAYER,
		OBJ_ALL = 999
	};

	GameObject();
	GameObject(Point2f pos);
	virtual ~GameObject();

	virtual void Update(GameState& state) = 0;
	virtual void Draw(GameState& state) const = 0;

	static float RandomNumGen(int min, int max);

	static bool CheckCollisions(GameObject* a, GameObject* b);
	void ScreenWrapper(Point2f idealPos);

	void SetPosition(Point2f pos) { m_pos = pos; }
	Point2f GetPosition() const { return m_pos; };

	void SetVelocity(Vector2f vel) { m_velocity = vel; }
	Vector2f GetVelocity() const { return m_velocity; };

	void SetRotation(float rot) { m_rot = rot; }
	float GetRotation() const { return m_rot; };

    void SetActive(bool isActive) { m_active = isActive; }
    bool GetActive() const { return m_active; };

    void SetType(Type type) { m_type = type; }
    Type GetType() const { return m_type; }

    void SetDrawOrder(int drawOrder) { m_drawOrder = drawOrder; }
    int GetDrawOrder() const { return m_drawOrder; };

    void SetUpdateOrder(int updateOrder) { m_updateOrder = updateOrder; }
    int GetUpdateOrder() const { return m_updateOrder; };

    static int GetObjectCount(Type eType);
    static int GetObjectList(GameObject::Type eType, std::vector< GameObject* >& vList);
    static std::vector< GameObject* > GetTypeList(GameObject::Type type);

    static void UpdateAll(GameState& state);
    static void DrawAll(GameState& state);
    static void DestroyAll();
    static bool HasCollided(Point2f pos1, Point2f pos2);

protected:

    static bool DrawOrder(const GameObject* a, const GameObject* b) { return a->m_drawOrder > b->m_drawOrder; }
    static bool UpdateOrder(const GameObject* a, const GameObject* b) { return a->m_updateOrder > b->m_updateOrder; }

    Type m_type{ Type::OBJ_NULL };
    bool m_active{ true };
    Point2f m_pos{ 0, 0 };
    Vector2f m_velocity{ 0, 0 };
    int spriteId{ -1 };
    float m_rot{ 0.0f };

    int m_drawOrder{ 0 };
    int m_updateOrder{ 0 };

    // Storing pointers to objects as opposed to the object data
    // This prevents having to move a lot of data around
    // Instead we just reassign the address
    static std::vector< GameObject* > s_vUpdateList;
    static std::vector< GameObject* > s_vDrawList;
};