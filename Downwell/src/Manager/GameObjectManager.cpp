#include "GameObjectManager.h"

#define NOMINMAX
#include "MathHelper.h"
#include "Collider.h"
#include "Camera.h"

#include "DxLib.h"

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

	ApplyPendingGameObjects();

#ifdef _DEBUG
	m_ActiveObjects = 0;
	m_DeadObjects = 0;
	for (auto& obj : m_GameObjects)
	{
		if (obj->IsActive())
		{
			m_ActiveObjects++;
		}
	}
	for (auto& obj : m_GameObjects)
	{
		if (obj->IsDead())
		{
			m_DeadObjects++;
		}
	}
#endif
}

void GameObjectManager::Draw(const Camera& camera)
{
	for (auto& gameObject : m_GameObjects)
	{
		const Vector2& pos = camera.GetPosition();
		const float CAMERA_MARGIN = 100.0f;	//カメラ範囲より少し広い領域を描画するための値

		if (gameObject->GetPosition().y >= pos.y - CAMERA_MARGIN && gameObject->GetPosition().y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
		{
			if (gameObject->IsActive())gameObject->Draw(camera);
		}
	}

#ifdef _DEBUG
	const int startPosX = 1000;
	const int startPosY = 200;
	DrawFormatString(startPosX, startPosY, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "ActiveObject : %d/%d", m_ActiveObjects, m_GameObjects.size());
	DrawFormatString(startPosX, startPosY + 20, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "DeadObject : %d/%d", m_DeadObjects, m_GameObjects.size());
#endif
}


void GameObjectManager::ApplyPendingGameObjects()
{
	for (auto& gameObject : m_PendingGameObjects)
	{
		m_GameObjects.push_back(std::move(gameObject));
	}

	SortGameObjectsByLayer();
	m_PendingGameObjects.clear();
}

void GameObjectManager::SortGameObjectsByLayer()
{
	std::sort(m_GameObjects.begin(), m_GameObjects.end(),
		[](const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b)
		{ return a->GetLayer() < b->GetLayer(); });
}

//------------------------------------------------------------------
// 当たり判定チェック
//------------------------------------------------------------------
void GameObjectManager::CheckHitAll(const std::vector<std::unique_ptr<GameObject>>& objects)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		for (size_t j = i + 1; j < objects.size(); j++)
		{
			if (!objects[i] || !objects[j]) continue;

			if (objects[i]->GetTag() == Tag::Block && objects[j]->GetTag() == Tag::Block) continue;

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
	return CheckHit(a.GetWorldRect(), b.GetWorldRect(), out);
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

	if (out)
	{	//当たっていたら衝突情報を計算する
		float oldRightA = rect1.oldPosition.x + rect1.width * 0.5f;
		float oldLeftA = rect1.oldPosition.x - rect1.width * 0.5f;
		float oldBottomA = rect1.oldPosition.y + rect1.height * 0.5f;
		float oldTopA = rect1.oldPosition.y - rect1.height * 0.5f;

		float oldRightB = rect2.oldPosition.x + rect2.width * 0.5f;
		float oldLeftB = rect2.oldPosition.x - rect2.width * 0.5f;
		float oldBottomB = rect2.oldPosition.y + rect2.height * 0.5f;
		float oldTopB = rect2.oldPosition.y - rect2.height * 0.5f;

		//前フレームでの軸ごとの離れ状態
		const float EPSILON = 0.01f;
		bool wasSeparateX = oldRightA <= oldLeftB + EPSILON || oldLeftA >= oldRightB - EPSILON;
		bool wasSeparateY = oldBottomA <= oldTopB + EPSILON || oldTopA >= oldBottomB - EPSILON;
		bool useX;

		out->diff = rect2.position - rect1.position;
		//各軸のめり込み
		float ox, oy;
		ox = (rect1.width + rect2.width) * 0.5f - std::abs(out->diff.x);
		oy = (rect1.height + rect2.height) * 0.5f - std::abs(out->diff.y);

		if (wasSeparateX && !wasSeparateY)
		{
			useX = true;
		}
		else if (!wasSeparateX && wasSeparateY)
		{
			useX = false;
		}
		else
		{
			//前フレームからの相対移動量
			Vector2 relativeMove = (rect1.position - rect1.oldPosition) - (rect2.position - rect2.oldPosition);

			if (std::abs(relativeMove.x) < std::abs(relativeMove.y))
			{
				useX = true;
			}
			else if (std::abs(relativeMove.y) < std::abs(relativeMove.x))
			{
				useX = false;
			}
			else
			{
				useX = (ox < oy);
			}
		}

		if (useX)
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