#include <cstring>
#include <cstdarg>
#include <cstdio>
#include "Renderer.h"
#include "Camera.h"
#include "DxLib.h"

Vector2 Renderer::ToScreen(const Vector2& pos, Space space) const
{
	if (space == Space::Screen) return pos;
	if (!m_Camera) return pos;

	return pos - m_Camera->GetPosition();
}

unsigned int Renderer::ToDxColor(const Color& color)
{
	return GetColor(color.r, color.g, color.b);
}

bool Renderer::Initialize()
{
	if (SetDrawScreen(DX_SCREEN_BACK) != 0) return false;

	m_Camera = nullptr;

	return true;
}

void Renderer::Finalize()
{
	m_Camera = nullptr;
}

bool Renderer::BeginFrame()
{
	int result = ClearDrawScreen();
	return (result == 0) ? true : false;
}

bool Renderer::EndFrame()
{
	int result = ScreenFlip();
	return (result == 0) ? true : false;
}

void Renderer::DrawRect(const Vector2& center, const Vector2& size, const Color& color, bool fill, Space space)
{
	const Vector2 screenCenter = ToScreen(center, space);
	const Vector2 half = size * 0.5f;

	const Vector2 leftTop = screenCenter - half;
	const Vector2 rightBottom = screenCenter + half;

	DxLib::DrawBox(static_cast<int>(leftTop.x), static_cast<int>(leftTop.y), static_cast<int>(rightBottom.x), static_cast<int>(rightBottom.y), ToDxColor(color), fill ? TRUE : FALSE);
}

void Renderer::DrawRectOutline(const Vector2 & center, const Vector2 & size, const Color & color, int padding, Space space)
{
	const float p = static_cast<float>(padding);
	const Vector2 outlineSize{ size.x + p * 2.0f, size.y + p * 2.0f };   // 左右・上下に padding ずつ

	DrawRect(center, outlineSize, color, false, space);
}

void Renderer::DrawLine(const Vector2 & from, const Vector2 & to, const Color & color, Space space)
{
	const Vector2 start = ToScreen(from, space);
	const Vector2 end = ToScreen(to, space);

	DxLib::DrawLine(static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y), ToDxColor(color));
}

void Renderer::DrawLabel(const Vector2 & pos, const Color & color, const char* text, TextAlign align, Space space)
{
	const Vector2 start = ToScreen(pos, space);

	const int width = GetDrawStringWidth(text, static_cast<int>(std::strlen(text)));

	int x = static_cast<int>(start.x);
	switch (align)
	{
	case TextAlign::Left:
		break;
	case TextAlign::Center: x -= width / 2;
		break;
	case TextAlign::Right:  x -= width;
		break;
	default:
		break;
	}

	DxLib::DrawString(x, static_cast<int>(start.y), text, ToDxColor(color));
}

void Renderer::DrawLabelFormat(Space space, const Vector2& pos, const Color& color, TextAlign align, const char* format, ...)
{
	char buffer[256];

	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DrawLabel(pos, color, buffer, align, space);
}
