//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include "Managers/BulletPoolManager.hpp"

//-----------------------------------------------------------------
// Objects
//-----------------------------------------------------------------
#include "GameObjects/Weapons/Bullet.hpp"

//-----------------------------------------------------------------
// Utils
//-----------------------------------------------------------------
#include "Utils/ObjectPool.h"

namespace Slug
{
	namespace Managers
	{
		BulletPoolManager::BulletPoolManager()
			: m_pBulletPool(std::make_unique<Utils::TObjectPool<Objects::Bullet>>())
		{
			m_pBulletPool->Create();
		}

		BulletPoolManager::~BulletPoolManager()
		{
		}

		void BulletPoolManager::UpdateBullets(double deltaSeconds)
		{
			m_pBulletPool->CollectUnusedObject();

			Objects::Bullet* pBullet = m_pBulletPool->GetInUseListHead();
			
			while(pBullet)
			{
				pBullet->Update(deltaSeconds);
				pBullet = pBullet->GetNext();
			}
		}

		Objects::Bullet* BulletPoolManager::GetBullet(Vector2 position, double angle)
		{
			Objects::Bullet* pBullet = m_pBulletPool->Get();

			if (!pBullet)
				return nullptr;

			Vector2 adjustedPosition;
			adjustedPosition.m_x = position.m_x;
			adjustedPosition.m_y = position.m_y;

			pBullet->GetTransform().SetPosition(adjustedPosition);
			pBullet->GetTransform().Rotate(angle);
			pBullet->PrintStatus();

			return pBullet;
		}

		void BulletPoolManager::RenderBullets(SDL_Renderer* const pRenderer)
		{
			// ----- Render Bullets -----
			Objects::Bullet* pNode = m_pBulletPool->GetInUseListHead();

			while (pNode)
			{
				//pNode->SetBulletData("Magnum");
				pNode->Render(pRenderer);
				pNode = pNode->GetNext();
			}
		}
	}
}