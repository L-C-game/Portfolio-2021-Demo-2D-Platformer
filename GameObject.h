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
        OBJ_FLOOR,
        OBJ_LBARRIER,
        OBJ_CEILING,
        OBJ_RBARRIER,
        OBJ_PLATFORM,
        OBJ_CAMERA,
		OBJ_ALL = 999
	};

    enum class CollidingSide
    {
        SIDE_NULL = -1,
        SIDE_UP,
        SIDE_RIGHT,
        SIDE_DOWN,
        SIDE_LEFT
    };

	GameObject();
	GameObject(Point2f pos);
	virtual ~GameObject();

	virtual void Update(GameState& gameState) = 0;
	virtual void Draw(GameState& gameState) const = 0;

	static float RandomNumGen(int min, int max);

	void SetPosition(Point2f pos) { m_pos = pos; }
	Point2f GetPosition() const { return m_pos; };

	void SetVelocity(Vector2f vel) { m_velocity = vel; }
	Vector2f GetVelocity() const { return m_velocity; };

    void SetAcceleration(Vector2f accel) { m_acceleration = accel; }
    Vector2f GetAcceleration() const { return m_acceleration; };

	void SetRotation(float rot) { m_rot = rot; }
	float GetRotation() const { return m_rot; };

    // AABB getters and setters 
    void SetHalfSize(Point2f halfSize) { m_halfSize = halfSize; }
    Point2f GetHalfSize() const { return m_halfSize; };

    // Work out overlap
    Point2f CalcOverlap(GameObject* other);
    CollidingSide ResolveCollision(GameObject* other);

    void SetStatic(bool isStatic) { m_static = isStatic; }
    bool GetStatic() const { return m_static; };

    void SetSolid(bool isSolid) { m_solid = isSolid; }
    bool GetSolid() const { return m_solid; };

    // Type specific getters and setters
    void SetActive(bool isActive) { m_active = isActive; }
    bool GetActive() const { return m_active; };

    void SetType(Type type) { m_type = type; }
    Type GetType() const { return m_type; };

    void SetSide(CollidingSide side) { m_side = side; }
    CollidingSide GetSide() const { return m_side; };

    void SetDrawOrder(int drawOrder) { m_drawOrder = drawOrder; }
    int GetDrawOrder() const { return m_drawOrder; };

    void SetUpdateOrder(int updateOrder) { m_updateOrder = updateOrder; }
    int GetUpdateOrder() const { return m_updateOrder; };

    // Utilities to cycle through game objects, and delete them where necessary
    static int GetObjectCount(Type eType);
    static int GetObjectList(GameObject::Type eType, std::vector< GameObject* >& vList);
    static std::vector< GameObject* > GetTypeList(GameObject::Type type);

    // Update, draw and free memory methods for all objects, called in main game
    static void UpdateAll(GameState& gameState);
    static void DrawAll(GameState& gameState);
    static void DestroyAll();
    bool AABBCollision(GameObject* other);

protected:
    // Comparing if object a has a greater draw order than object b
    static bool DrawOrder(const GameObject* a, const GameObject* b) { return a->m_drawOrder > b->m_drawOrder; }
    static bool UpdateOrder(const GameObject* a, const GameObject* b) { return a->m_updateOrder > b->m_updateOrder; }

    // Enum class variables
    Type m_type{ Type::OBJ_NULL };
    CollidingSide m_side{ CollidingSide::SIDE_NULL };

    // Decides if the GameObject should be deleted or not
    bool m_active{ true };

    // Movement member variables
    Point2f m_pos{ 0.0f, 0.0f };
    Vector2f m_velocity{ 0.0f, 0.0f };
    Vector2f m_acceleration{ 0.0f, 0.0f };

    // Setting up game objects with AABB's
    Point2f m_halfSize{ 0.0f, 0.0f }; // Half the width and half the height of the object

    // Is the GameObject fixed in space (independent of forces) or not:
    bool m_static{ false };
    bool m_solid{ true };

    float m_rot{ 0.0f };

    // Set the order of update and draw
    int m_drawOrder{ 0 };
    int m_updateOrder{ 0 };

    // Storing pointers to objects as opposed to the object data
    // This prevents having to move a lot of data around
    // Instead we just reassign the address
    static std::vector< GameObject* > s_vUpdateList;
    static std::vector< GameObject* > s_vDrawList;
};