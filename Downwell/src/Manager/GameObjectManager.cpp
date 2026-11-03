#include "GameObjectManager.h"

#define NOMINMAX
#include "MathHelper.h"
#include "Collider.h"
#include "Camera.h"

//#include "DxLib.h"
#include "imgui.h"

void GameObjectManager::Finalize()
{
	for (std::unique_ptr<GameObject>& gameObject : m_GameObjects)
	{
		gameObject->Finalize();
	}
}

void GameObjectManager::Update(float dt)
{
	if (!m_Camera) return;

	for (std::unique_ptr<GameObject>& gameObject : m_GameObjects)
	{
		const Vector2& pos = m_Camera->GetPosition();
		const float CAMERA_MARGIN = 500.0f;	//カメラ範囲より少し広い領域を更新するための値

		if (gameObject->GetPosition().y >= pos.y - CAMERA_MARGIN && gameObject->GetPosition().y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
		{
			if (gameObject->IsActive()) gameObject->Update(dt);
		}
	}
	CheckHitAll(m_GameObjects);

	ApplyPendingGameObjects();

	m_ActiveObjects = 0;
	m_DeadObjects = 0;
	for (const std::unique_ptr<GameObject>& gameObject : m_GameObjects)
	{
		const GameObject* obj = gameObject.get();
		if (obj->IsActive())
		{
			m_ActiveObjects++;
		}
	}
	for (const std::unique_ptr<GameObject>& gameObject : m_GameObjects)
	{
		const GameObject* obj = gameObject.get();
		if (obj->IsDead())
		{
			m_DeadObjects++;
		}
	}
}

void GameObjectManager::Draw()
{
	if (!m_Camera) return;

	for (std::unique_ptr<GameObject>& gameObject : m_GameObjects)
	{
		const Vector2& pos = m_Camera->GetPosition();
		const float CAMERA_MARGIN = 100.0f;	//カメラ範囲より少し広い領域を描画するための値

		if (gameObject->GetPosition().y >= pos.y - CAMERA_MARGIN && gameObject->GetPosition().y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
		{
			if (gameObject->IsActive())gameObject->Draw(*m_Camera);
		}
	}
}

void GameObjectManager::DrawDebug()
{
#ifdef _DEBUG
	if (ImGui::Begin("GameObjects : Active / Dead"))
	{
		ImGui::Text("Active : %d", m_ActiveObjects);
		ImGui::Text("Dead   : %d", m_DeadObjects);
	}
	ImGui::End();

	if (ImGui::Begin("GameObjects"))
	{
		for (int tagIndex = 0; tagIndex < static_cast<int>(Tag::Max); tagIndex++)
		{
			Tag tag = static_cast<Tag>(tagIndex);

			if (ImGui::TreeNode(ToStringTag(tag).c_str()))
			{
				int objectIndex = 0;

				for (auto& gameObject : m_GameObjects)
				{
					if (gameObject->GetTag() != tag)
					{
						continue;
					}

					ImGui::PushID(gameObject.get());

					std::string label = gameObject->GetName() + " " + std::to_string(objectIndex);

					if (ImGui::TreeNode(label.c_str()))
					{
						gameObject->DrawDebug();

						ImGui::TreePop();
					}

					ImGui::PopID();

					objectIndex++;
				}

				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
#endif
}

void GameObjectManager::ApplyPendingGameObjects()
{
	if (!m_IsDirtyGameObjects)
	{
		return;
	}

	for (std::unique_ptr<GameObject>& gameObject : m_PendingGameObjects)
	{
		m_GameObjects.push_back(std::move(gameObject));
	}

	SortGameObjectsByLayer();
	m_PendingGameObjects.clear();

	m_IsDirtyGameObjects = false;
}

void GameObjectManager::SortGameObjectsByLayer()
{
	std::sort(m_GameObjects.begin(), m_GameObjects.end(),
		[](const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b)
		{ return a->GetLayer() < b->GetLayer(); });
}

std::string GameObjectManager::ToStringTag(Tag tag) const
{
	switch (tag)
	{
	case Tag::None:
		return "None";
	case Tag::Player:
		return "Player";
	case Tag::Enemy:
		return "Enemy";
	case Tag::Block:
		return "Block";
	case Tag::Bullet:
		return "Bullet";
	case Tag::GunBoots:
		return "GunBoots";
	case Tag::Camera:
		return "Camera";
	case Tag::UI:
		return "UI";
	default:
		return "Unnamed";
	}
}


//------------------------------------------------------------------
// 当たり判定チェック
//------------------------------------------------------------------
void GameObjectManager::CheckHitAll(const std::vector<std::unique_ptr<GameObject>>& objects)
{
	//有効な物だけを集める（確保済みの領域を使いまわす）
	m_MovableObjects.clear();
	m_StaticObjects.clear();

	for (const std::unique_ptr<GameObject>& object : objects)
	{
		if (!object || !object->IsActive()) continue;

		if (object->GetTag() == Tag::Block)
		{
			m_StaticObjects.push_back(object.get());
		}
		else
		{
			m_MovableObjects.push_back(object.get());
		}
	}

	//ブロックと動くもの
	for (GameObject* block : m_StaticObjects)
	{
		for (GameObject* movable : m_MovableObjects)
		{
			CheckHitPair(block, movable);
		}
	}

	//動く者同士
	for (size_t i = 0; i < m_MovableObjects.size(); i++)
	{
		for (size_t j = i + 1; j < m_MovableObjects.size(); j++)
		{
			CheckHitPair(m_MovableObjects[i], m_MovableObjects[j]);
		}
	}
}

void GameObjectManager::CheckHitPair(GameObject* a, GameObject* b)
{
	//OnCollision の中で無効になるもの（弾など）があるので、組ごとに確認する
	if (!a->IsActive() || !b->IsActive()) return;

	HitInfo hitA;
	if (!CheckHit(*a->GetCollider(), *b->GetCollider(), &hitA)) return;

	HitInfo hitB = hitA;
	hitB.diff *= -1.0f;
	hitB.normal *= -1.0f;

	a->OnCollision(b, hitA);
	b->OnCollision(a, hitB);
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