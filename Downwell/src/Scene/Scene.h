#pragma once

class Scene
{
private:

public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Initialize();
	virtual void Finalize();
	virtual void Update() = 0;
	virtual void Draw() = 0;
};