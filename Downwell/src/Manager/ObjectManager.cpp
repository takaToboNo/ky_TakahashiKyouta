#include "ObjectManager.h"
#include "Object.h"

ObjectManager::ObjectManager() = default;
ObjectManager::~ObjectManager() = default;

void ObjectManager::Finalize()
{
	for (auto& object : m_Objects)
	{
		object->Finalize();
	}
}

void ObjectManager::Update(float dt)
{
	for (auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void ObjectManager::Draw()
{
	for (auto& object : m_Objects)
	{
		object->Draw();
	}
}

Object* ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	Object* ptr = object.get();

	m_Objects.push_back(std::move(object));
	m_Objects.back()->Initialize();

	return ptr;
}
