//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include <assert.h>
#include "Core/Application.hpp"
#include "Core/Camera.hpp"

//-----------------------------------------------------------------
// Utils
//-----------------------------------------------------------------
#include "Utils/tinyxml2.h"

//-----------------------------------------------------------------
// Objects
//-----------------------------------------------------------------
#include "GameObjects/Weapons/Magnum.hpp"

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

namespace Slug
{
	namespace Objects
	{
		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		Magnum::Magnum()
		{
			m_transform = Utils::Transform(0, 0, 0);

			Initialize();
		}

		Magnum::Magnum(const Vector2& pos)
		{
			m_transform = Utils::Transform(pos, 0);

			Initialize();
		}

		Magnum::Magnum(float posX, float posY)
		{
			m_transform = Utils::Transform(posX, posY, 0);

			Initialize();
		}

		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		Magnum::Magnum(const Magnum& instance)
		{
			m_transform = instance.m_transform;
			m_destRect = instance.m_destRect;

			Initialize();
		}

		void Magnum::Initialize()
		{
			// Call parent class's initialization
			Weapon::Initialize();
			//SetTexture("Resources/Sprites/Spartan.png");

			this->SetWeaponType(WeaponType::kMagnum);

			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			m_destRect = { (int)m_transform.GetPositionX() - (int)camera.m_x, (int)m_transform.GetPositionY() - (int)camera.m_y, 55, 55 };

			XMLDocument	m_doc;
			m_doc.LoadFile("Includes/Data/SpriteData.xml");

			XMLElement* m_pRoot = m_doc.RootElement();
			XMLElement* pWeaponData = m_pRoot->FirstChildElement("Weapons");
			assert(pWeaponData != nullptr && "pWeaponData was nullptr");

			XMLElement* pMagnumData = pWeaponData->FirstChildElement("SpriteFrame")->FirstChildElement("Magnum");
			assert(pMagnumData != nullptr && "pMagnum was nullptr");

			m_resourceRect =
			{ 
			(int)pMagnumData->IntAttribute("posX"),
			(int)pMagnumData->IntAttribute("posY"),
			(int)pMagnumData->IntAttribute("sizeX"),
			(int)pMagnumData->IntAttribute("sizeY")
			};

			// Search center position wherer the sprite will be rendererd.
			m_center = { (int)pMagnumData->IntAttribute("centerX"), (int)pMagnumData->IntAttribute("centerY") };
		}

		void Magnum::Update(double deltaSeconds)
		{
			// Calculate destination rect.
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			m_destRect.x = (int)m_transform.GetPositionX() - (int)camera.m_x - m_center.x;
			m_destRect.y = (int)m_transform.GetPositionY() - (int)camera.m_y - m_center.y;

#if DEBUG_POSITION
			Weapon::Update(deltaSeconds);
#endif
		}

		void Magnum::Render(SDL_Renderer* const pRenderer)
		{
			// Calling Render() from parent class(Weapon)
			Weapon::Render(pRenderer);

			// Get vector position from the camera and mouse
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();

			const float transformX = GetTransform().GetPositionX() - camera.m_x;
			const float mouseX = Managers::MouseManager::GetInstance()->GetMousePosition().m_x;

			// Determine whether an image should be flipped or not.
			SDL_RendererFlip renderFlip = (transformX < mouseX) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_VERTICAL;

			// After all, render the sprite
			SDL_RenderCopyEx(pRenderer, m_pTexture, &m_resourceRect, &m_destRect, m_transform.GetAngle(), &m_center, renderFlip);
		}

		void Magnum::Shoot()
		{
			
		}

		void Magnum::Reload()
		{
		}
	}
}