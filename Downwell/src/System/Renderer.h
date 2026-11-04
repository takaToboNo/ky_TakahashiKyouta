#pragma once
#include "Vector2.h"
#include "GameHelper.h"

class Camera;

enum class Space
{
	World = 0,
	Screen,
};

enum class TextAlign
{
	Left = 0,
	Center,
	Right,
};

class Renderer
{
private:
	const Camera* m_Camera = nullptr;

	Vector2 ToScreen(const Vector2& pos, Space space) const;
	static unsigned int ToDxColor(const Color& color);

public:
	bool Initialize();
	void Finalize();
	bool BeginFrame();
	bool EndFrame();

	void SetCamera(const Camera* camera) { m_Camera = camera; }

	//図形
	void DrawRect(const Vector2& center, const Vector2& size, const Color& color, bool fill, Space space = Space::World);
	void DrawRectOutline(const Vector2& center, const Vector2& size, const Color& color, int padding, Space space = Space::Screen);//ゲージの枠用
	void DrawLine(const Vector2& from, const Vector2& to, const Color& color, Space space = Space::World);

	//文字
	void DrawLabel(const Vector2& pos, const Color& color, const char* text, TextAlign align = TextAlign::Left, Space space = Space::Screen);
	void DrawLabelFormat(Space space, const Vector2& pos, const Color& color, TextAlign align, const char* format, ...);
};