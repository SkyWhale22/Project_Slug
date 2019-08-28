//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include "Utils/tinyxml2.h"
#include <chrono>
#include <assert.h>
#include "Core/Camera.hpp"

//-----------------------------------------------------------------
// Objects
//-----------------------------------------------------------------
#include "GameObjects\Weapons\Bullet.hpp"

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

namespace Slug
{
	namespace Objects
	{
		//--------------------------------------------------------------------
		// Ctors
		//--------------------------------------------------------------------
		Bullet::Bullet()
		{
			m_transform = Utils::Transform(0, 0, 0);

			Initialize();
		}

		Bullet::Bullet(float posX, float posY)
		{
			m_transform = Utils::Transform(posX, posY, 0);

			Initialize();
		}

		Bullet::Bullet(const Vector2& pos)
		{
			m_transform = Utils::Transform(pos, 0);

			Initialize();
		}

		Bullet::Bullet(const Bullet& instance)
		{
			m_transform = instance.m_transform;
			m_destRect = instance.m_destRect;
		}

		Bullet::~Bullet()
		{
		}

		void Bullet::Initialize()
		{
			m_doc.LoadFile("Includes/Data/SpriteData.xml");

			XMLElement* pRoot = m_doc.RootElement();
			m_pBulletData = pRoot->FirstChildElement("Bullets");
			assert(m_pBulletData != nullptr && "m_pBulletData was nullptr");

			m_destRect.w = 16;
			m_destRect.h = 32;

			this->SetInUse(false);

			SetTexture(m_pBulletData->FirstChildElement("SpritePath")->GetText());
		}

		void Bullet::Update(double deltaSeconds)
		{
			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();

			m_destRect.x = (int)(m_transform.GetPositionX()) - (int)cameraPos.m_x;
			m_destRect.y = (int)(m_transform.GetPositionY()) - (int)cameraPos.m_y;
		}
		
		void Bullet::Render(SDL_Renderer* const pRenderer)
		{
			// After all, render the sprite
			SDL_RenderCopyEx(pRenderer, m_pTexture, &m_resourceRect, &m_destRect, m_transform.GetAngle(), &m_center, SDL_FLIP_NONE);
		}

		void Bullet::SetBulletData(std::string_view name)
		{
			if (this == nullptr)
				return;
			//const char* pName = name.data();
			XMLElement* pFrame = m_pBulletData->FirstChildElement("BulletFrame")->FirstChildElement(name.data());
			assert(pFrame != nullptr && "pFrame was nullptr!");

			m_resourceRect =
			{ 
			(int)pFrame->IntAttribute("posX"),
			(int)pFrame->IntAttribute("posY"),
			(int)pFrame->IntAttribute("sizeX"),
			(int)pFrame->IntAttribute("sizeY")
			};

			//m_destRect = { (int)this->GetTransform().GetPositionX(), (int)this->GetTransform().GetPositionY(), 32, 32 };
			// Search center position wherer the sprite will be rendererd.
			m_center = { (int)pFrame->IntAttribute("centerX"), (int)pFrame->IntAttribute("centerY") };
		}

#pragma region IPoolable
		//----------------------------------------------------------------------------------------------------------------------------------
		//										Functions under are inherited via IPoolable
		//----------------------------------------------------------------------------------------------------------------------------------
		void Bullet::Reset()
		{
			m_inUse = false;
		}

		void Bullet::PrintStatus()
		{
			std::cout << "Bullet's ID: " << this->m_id << ", Currently in use: " << this->IsUse() << std::endl;
		}

		Bullet* Bullet::GetNext()
		{
			return m_pNext;
		}

		Bullet* Bullet::GetPrev()
		{
			return m_pPrev;
		}

		void Bullet::SetNext(Bullet* pObject)
		{
			m_pNext = pObject;
		}

		void Bullet::SetPrev(Bullet* pObject)
		{
			m_pPrev = pObject;
		}

#pragma endregion IPoolable
	}
}
