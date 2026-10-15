#include "GameObjectManager.h"

#define NOMINMAX
#include "MathHelper.h"
#include "Collider.h"

void GameObjectManager::Finalize()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Finalize();
	}
}

void GameObjectManager::Update(float dt)
{
	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsActive()) gameObject->Update(dt);
	}
	CheckHitAll(m_GameObjects);
}

void GameObjectManager::Draw()
{
	for (auto& gameObject : m_GameObjects)
	{
		if (gameObject->IsActive())gameObject->Draw();
	}
}


//------------------------------------------------------------------
// “–‚½‚è”»’èƒ`ƒFƒbƒN
//------------------------------------------------------------------
void GameObjectManager::CheckHitAll(const std::vector<std::unique_ptr<GameObject>>& objects)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		for (size_t j = i + 1; j < objects.size(); j++)
		{
			if (!objects[i]->IsActive() || !objects[j]->IsActive()) continue;

			Collider* colliderA = objects[i]->GetCollider();
			Collider* colliderB = objects[j]->GetCollider();

			HitInfo hitA;
			if (!colliderA || !colliderB) continue;

			if (!CheckHit(*colliderA, *colliderB, &hitA)) continue;

			HitInfo hitB = hitA;
			hitB.diff *= -1.0f;
			hitB.normal *= -1.0f;

			objects[i]->OnCollision(objects[j].get(), hitA);
			objects[j]->OnCollision(objects[i].get(), hitB);
		}
	}
}

bool GameObjectManager::CheckHit(const Collider& a, const Collider& b, HitInfo* out)
{
	ShapeType typeA = a.GetShapeType();
	ShapeType typeB = b.GetShapeType();

	if (typeA == ShapeType::Rect && typeB == ShapeType::Rect)
	{
		return CheckHit(a.GetWorldRect(), b.GetWorldRect(), out);
	}
	if (typeA == ShapeType::Rect && typeB == ShapeType::Circle)
	{
		return CheckHit(a.GetWorldRect(), b.GetWorldCircle(), out);
	}
	if (typeA == ShapeType::Circle && typeB == ShapeType::Rect)
	{
		return CheckHit(a.GetWorldCircle(), b.GetWorldRect(), out);
	}
	if (typeA == ShapeType::Circle && typeB == ShapeType::Circle)
	{
		return CheckHit(a.GetWorldCircle(), b.GetWorldCircle(), out);
	}

	return false;
}

bool GameObjectManager::CheckHit(const Rect& rect1, const Rect& rect2, HitInfo* out)
{
	float rightA = rect1.position.x + rect1.width * 0.5f;
	float leftA = rect1.position.x - rect1.width * 0.5f;
	float bottomA = rect1.position.y + rect1.height * 0.5f;
	float topA = rect1.position.y - rect1.height * 0.5f;

	float rightB = rect2.position.x + rect2.width * 0.5f;
	float leftB = rect2.position.x - rect2.width * 0.5f;
	float bottomB = rect2.position.y + rect2.height * 0.5f;
	float topB = rect2.position.y - rect2.height * 0.5f;

	if (rightA < leftB || leftA > rightB || bottomA < topB || topA > bottomB) return false;

	//“–‚½‚Á‚Ä‚¢‚½‚çÕ“Ëî•ñ‚ðŒvŽZ‚·‚é
	if (out)
	{
		out->diff = rect2.position - rect1.position;

		float ox, oy;//ŠeŽ²‚Ì‚ß‚èž‚Ý
		ox = (rect1.width + rect2.width) * 0.5f - std::abs(out->diff.x);
		oy = (rect1.height + rect2.height) * 0.5f - std::abs(out->diff.y);

		if (ox < oy)
		{
			out->normal.x = (out->diff.x > 0.0f) ? 1.0f : -1.0f;
			out->normal.y = 0.0f;
			out->depth = ox;
		}
		else
		{
			out->normal.x = 0.0f;
			out->normal.y = (out->diff.y > 0.0f) ? 1.0f : -1.0f;
			out->depth = oy;
		}
	}

	return true;
}

bool GameObjectManager::CheckHit(const Rect& rect, const Circle& circle, HitInfo* out)
{
	float right = rect.position.x + rect.width * 0.5f;
	float left = rect.position.x - rect.width * 0.5f;
	float bottom = rect.position.y + rect.height * 0.5f;
	float top = rect.position.y - rect.height * 0.5f;

	float closestX = math_helper::clamp(circle.position.x, left, right);
	float closestY = math_helper::clamp(circle.position.y, top, bottom);

	Vector2 diff{ circle.position.x - closestX, circle.position.y - closestY };
	float distSq = diff.LengthSquared();

	if (distSq > circle.radius * circle.radius) return false;

	//“–‚½‚Á‚Ä‚¢‚½‚çÕ“Ëî•ñ‚ðŒvŽZ‚·‚é
	if (out)
	{
		if (distSq > 0.0f)
		{	//‰~‚Ì’†S‚ªŽlŠp‚ÌŠO
			float dist = std::sqrt(distSq);
			out->depth = circle.radius - dist;
		}
		else
		{	//‰~‚Ì’†S‚ªŽlŠp‚Ì’†
			float distToLeft = circle.position.x - left;
			float distToRight = right - circle.position.x;
			float distToTop = circle.position.y - top;
			float distToBottom = bottom - circle.position.y;

			float distMin = std::min(std::min(distToLeft, distToRight), std::min(distToTop, distToBottom));
			out->depth = distMin + circle.radius;
		}

		out->diff = diff;
		diff.Normalize();
		out->normal = diff;
	}

	return true;
}

bool GameObjectManager::CheckHit(const Circle& circle, const Rect& rect, HitInfo* out)
{
	if (!CheckHit(rect, circle, out)) return false;

	out->diff *= -1.0f;
	out->normal *= -1.0f;

	return true;
}

bool GameObjectManager::CheckHit(const Circle& circle1, const Circle& circle2, HitInfo* out)
{
	Vector2 diff = circle2.position - circle1.position;
	float radiusSum = circle1.radius + circle2.radius;

	if (diff.LengthSquared() > radiusSum * radiusSum) return false;

	//“–‚½‚Á‚Ä‚¢‚½‚çÕ“Ëî•ñ‚ðŒvŽZ‚·‚é
	if (out)
	{
		out->depth = radiusSum - diff.Length();

		out->diff = diff;
		diff.Normalize();
		out->normal = diff;
	}

	return true;
}
