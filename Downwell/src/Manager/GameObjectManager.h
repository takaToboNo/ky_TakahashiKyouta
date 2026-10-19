#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "GameObject.h"

class Camera;

class GameObjectManager
{
private:
	std::vector<std::unique_ptr<GameObject>> m_GameObjects = {};

public:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	void Finalize();
	void Update(float dt);
	void Draw(const Camera& camera);

	template<class T>
	T* AddGameObject(std::unique_ptr<T> gameObject)
	{
		if (!gameObject) return nullptr;

		T* ptr = gameObject.get();

		m_GameObjects.push_back(std::move(gameObject));
		m_GameObjects.back()->Initialize();

		std::sort(m_GameObjects.begin(), m_GameObjects.end(),
			[](const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b)
			{ return a->GetLayer() < b->GetLayer(); });

		return ptr;
	}


	//当たり判定チェック
	void CheckHitAll(const std::vector<std::unique_ptr<GameObject>>& objects);

	bool CheckHit(const Collider& a, const Collider& b, HitInfo* out);
	bool CheckHit(const Rect& rect1, const Rect& rect2, HitInfo* out);
};