#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "GameObject.h"
#include "Tag.h"

class Camera;

class GameObjectManager
{
private:
	std::vector<std::unique_ptr<GameObject>> m_GameObjects = {};
	std::vector<std::unique_ptr<GameObject>> m_PendingGameObjects = {};

	int m_ActiveObjects = 0;
	int m_DeadObjects = 0;

	bool m_IsDirtyGameObjects = false;

	Camera* m_Camera = nullptr;

public:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	void Finalize();
	void Update(float dt);
	void Draw();
	void DrawDebug();

	//Initializeでのみ呼ぶこと
	template<class T>
	T* AddGameObject(std::unique_ptr<T> gameObject)
	{
		if (!gameObject) return nullptr;

		T* ptr = gameObject.get();

		m_GameObjects.push_back(std::move(gameObject));
		m_GameObjects.back()->SetGameObjectManager(this);
		m_GameObjects.back()->Initialize();

		m_IsDirtyGameObjects = true;

		return ptr;
	}

	//UpdateでGameObjectを作りたいとき
	template<class T>
	T* AddPendingGameObject(std::unique_ptr<T> gameObject)
	{
		if (!gameObject) return nullptr;

		T* ptr = gameObject.get();

		m_PendingGameObjects.push_back(std::move(gameObject));
		m_PendingGameObjects.back()->SetGameObjectManager(this);
		m_PendingGameObjects.back()->Initialize();

		m_IsDirtyGameObjects = true;

		return ptr;
	}

	void SortGameObjectsByLayer();

	void SetCamera(Camera* camera) { m_Camera = camera; }

private:
	std::string ToStringTag(Tag tag) const;

	void ApplyPendingGameObjects();
	//当たり判定チェック
	void CheckHitAll(const std::vector<std::unique_ptr<GameObject>>& objects);

	bool CheckHit(const Collider& a, const Collider& b, HitInfo* out);
	bool CheckHit(const Rect& rect1, const Rect& rect2, HitInfo* out);
};