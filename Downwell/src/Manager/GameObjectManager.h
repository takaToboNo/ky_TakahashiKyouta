#pragma once
#include <vector>
#include <memory>

class GameObject;

class GameObjectManager
{
private:
	std::vector<std::unique_ptr<GameObject>> m_GameObjects = {};

public:
	GameObjectManager();
	~GameObjectManager();

	void Finalize();
	void Update(float dt);
	void Draw();

	GameObject* AddGameObject(std::unique_ptr<GameObject> gameObject);

};