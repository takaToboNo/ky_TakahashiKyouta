#pragma once
#include <vector>
#include <memory>

class Object;

class ObjectManager
{
private:
	std::vector<std::unique_ptr<Object>> m_Objects = {};

public:
	ObjectManager();
	~ObjectManager();

	void Finalize();
	void Update(float dt);
	void Draw();

	Object* AddObject(std::unique_ptr<Object> object);

};