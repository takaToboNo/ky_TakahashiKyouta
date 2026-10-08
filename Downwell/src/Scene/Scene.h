#pragma once
#include "ObjectManager.h"
#include "GameObjectManager.h"

enum class SceneType
{
	None = 0,
	Title,
	Game,
	Result,
};

class Scene
{
protected:
	ObjectManager m_ObjectManager;
	GameObjectManager m_GameObjectManager;
	SceneType m_RequestScene = SceneType::None;
	

	int m_KeyInterval = 30;

public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Initialize();
	virtual void Finalize();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual SceneType GetSceneRequest() { return m_RequestScene; }
};