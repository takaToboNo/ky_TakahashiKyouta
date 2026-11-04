#pragma once
#include "GameObjectManager.h"
#include "Camera.h"

class Renderer;

enum class SceneType
{
	None = 0,
	Title,
	Game,
};

class Scene
{
protected:
	GameObjectManager m_GameObjectManager;
	SceneType m_RequestScene = SceneType::None;
	Camera m_Camera;

	int m_KeyInterval = 30;

public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual bool Initialize();
	virtual void Finalize();
	virtual void Update(float dt) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	SceneType GetSceneRequest() const { return m_RequestScene; }
};