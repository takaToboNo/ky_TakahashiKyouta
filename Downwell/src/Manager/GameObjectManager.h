#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "GameObject.h"

class GameObjectManager
{
private:
	std::vector<std::unique_ptr<GameObject>> m_GameObjects = {};

public:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	void Finalize();
	void Update(float dt);
	void Draw();

	template<class T>
	T* AddGameObject(std::unique_ptr<T> gameObject)
	{
		T* ptr = gameObject.get();

		m_GameObjects.push_back(std::move(gameObject));
		m_GameObjects.back()->Initialize();

		std::sort(m_GameObjects.begin(), m_GameObjects.end(),
			[](const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b)
			{ return a->GetLayer() < b->GetLayer(); });

		return ptr;
	}

};