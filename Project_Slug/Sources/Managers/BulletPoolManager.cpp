//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include "SDL_image.h"
#include "Core/Application.hpp"
#include "Utils/tinyxml2.h"
#include <assert.h>

//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include "Managers/BulletPoolManager.hpp"

//-----------------------------------------------------------------
// Objects
//-----------------------------------------------------------------
#include "GameObjects/Weapons/Bullet.hpp"
#include "GameObjects/Weapon.hpp"

//-----------------------------------------------------------------
// Utils
//-----------------------------------------------------------------
#include "Utils/ObjectPool.h"

using tinyxml2::XMLElement;
using tinyxml2::XMLDocument;

namespace Slug
{
	namespace Managers
	{
		BulletPoolManager::BulletPoolManager()
			: m_pBulletPool(std::make_unique<Utils::TObjectPool<Objects::Bullet>>())
		{
			m_pBulletPool->Create();

			m_spriteCache.m_pTexture = IMG_LoadTexture(Core::Application::GetRenderer(), "Resources/Sprites/Bullets.png");

			XMLDocument doc;
			doc.LoadFile("Includes/Data/SpriteData.xml");
			XMLElement* pBullet = doc.RootElement()->FirstChildElement("Bullets");

			auto getSpriteRect = [pBullet](std::string_view str, BulletSpriteCache::DataChunk& chunk)
			{

				XMLElement* pFrame = pBullet->FirstChildElement("BulletFrame")->FirstChildElement(str.data());
				assert(pFrame != nullptr && "pFrame was nullptr!");

				chunk.m_resource =
				{
					(int)pFrame->IntAttribute("posX"),
					(int)pFrame->IntAttribute("posY"),
					(int)pFrame->IntAttribute("sizeX"),
					(int)pFrame->IntAttribute("sizeY")
				};

				// Center of a rendered sprite.
				chunk.m_center = { (int)pFrame->IntAttribute("centerX"), (int)pFrame->IntAttribute("centerY") };
			};

			getSpriteRect("Magnum", m_spriteCache.m_magnumCache);
			getSpriteRect("AssaultRifle", m_spriteCache.m_arCache);
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

		Objects::Bullet* BulletPoolManager::GetBullet(Vector2 position, double angle, Objects::WeaponType type)
		{
			Objects::Bullet* pBullet = m_pBulletPool->Get();

			if (!pBullet)
				return nullptr;

			Vector2 adjustedPosition;
			adjustedPosition.m_x = position.m_x;
			adjustedPosition.m_y = position.m_y;

			pBullet->GetTransform().SetPosition(adjustedPosition);
			pBullet->GetTransform().Rotate(angle);

			// Set bullet's data
			switch (type)
			{
			case Slug::Objects::WeaponType::kMagnum:
				pBullet->SetBulletData(m_spriteCache.m_magnumCache.m_resource, m_spriteCache.m_magnumCache.m_center);
				break;
			case Slug::Objects::WeaponType::kAssaultRifle:
				pBullet->SetBulletData(m_spriteCache.m_arCache.m_resource, m_spriteCache.m_arCache.m_center);
				break;
			}

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
				//pNode->Render(pRenderer);

				SDL_RenderCopyEx(pRenderer, m_spriteCache.m_pTexture, &pNode->GetResourceRect(), &pNode->GetDestRect(), pNode->GetTransform().GetAngle(), &pNode->GetCenter(), SDL_FLIP_NONE);

				pNode = pNode->GetNext();
			}
		}
	}
}