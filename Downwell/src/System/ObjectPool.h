#pragma once
#include "GameObjectManager.h"

template <typename T>
class ObjectPool
{
private:
	std::vector<T*> m_ObjectPool = {};

public:
	ObjectPool() = default;
	~ObjectPool() = default;

	void Setup(GameObjectManager& manager, int poolSize);
	T* Get();

};

template<typename T>
inline void ObjectPool<T>::Setup(GameObjectManager& manager, int poolSize)
{
	//中身を空にする
	m_ObjectPool.clear();
	//要素数を先に確保
	m_ObjectPool.reserve(poolSize);

	for (int i = 0; i < poolSize; i++)
	{
		T* gameObject = manager.AddGameObject(std::make_unique<T>());

		if (!gameObject)
		{
			continue;
		}

		//プール状態にしておく
		gameObject->SetActive(false);
		m_ObjectPool.push_back(gameObject);
	}
}

template<typename T>
inline T* ObjectPool<T>::Get()
{
	for (T* object : m_ObjectPool)
	{
		if (!object->IsActive())
		{
			object->SetActive(true);
			return object;
		}
	}
	return nullptr;
}
