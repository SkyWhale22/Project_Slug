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
#include "GameObjects/Weapons/AssultRifle.hpp"

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

namespace Slug
{
	namespace Objects
	{
		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		AssultRifle::AssultRifle()
		{
			m_transform = Utils::Transform(0, 0, 0);
			
			Initialize();
		}

		AssultRifle::AssultRifle(const Vector2& pos)
		{
			m_transform = Utils::Transform(pos, 0);

			Initialize();
		}

		AssultRifle::AssultRifle(float posX, float posY)
		{
			m_transform = Utils::Transform(posX, posY, 0);

			Initialize();
		}

		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		AssultRifle::AssultRifle(const AssultRifle& instance)
		{
			m_transform = instance.m_transform;
			m_destRect = instance.m_destRect;

			Initialize();
		}

		void AssultRifle::Initialize()
		{
			// Call parent class's initialization
			Weapon::Initialize();

			XMLDocument	m_doc;
			m_doc.LoadFile("Includes/Datas/SpriteData.xml");
			
			XMLElement* m_pRoot = m_doc.RootElement();
			XMLElement* pWeaponData = m_pRoot->FirstChildElement("Weapons");
			assert(pWeaponData != nullptr && "pWeaponData was nullptr");

			XMLElement* pSpriteSize = pWeaponData->FirstChildElement("SpriteSize");
			m_resourceSize = { (float)pSpriteSize->IntAttribute("width"), (float)pSpriteSize->IntAttribute("height") };

			XMLElement* pARData = pWeaponData->FirstChildElement("SpriteFrame")->FirstChildElement("AssultRifle");
			assert(pARData != nullptr && "pARData was nullptr");

			// Search center position wherer the sprite will be rendererd.
			m_center = { (int)pARData->IntAttribute("centerX"), (int)pARData->IntAttribute("centerY") };
			m_renderSize = { 10, 5 };
		}

		void AssultRifle::Render(SDL_Renderer* const pRenderer)
		{
			// Calling Render() from parent class(Weapon)
			Weapon::Render(pRenderer);

			// Get vector position from the camera and mouse
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			Vector2 mouse = Managers::MouseManager::GetInstance()->GetMousePosition();

			const float transformX = GetTransform().GetPositionX() - camera.m_x;
			const float mouseX = Managers::MouseManager::GetInstance()->GetMousePosition().m_x;

			// Determine whether an image should be flipped or not.
			SDL_RendererFlip renderFlip = (transformX < mouseX) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_VERTICAL;

			// Calculate destination rect.
			constexpr int adjustX = 5;
			constexpr int adjustY = 5;
			SDL_Rect dest = { (int)m_transform.GetPositionX() - adjustX - (int)camera.m_x, (int)m_transform.GetPositionY() - adjustY - (int)camera.m_y, m_renderSize.m_x, m_renderSize.m_y };

			// Get resource's starting position and size.
			m_resourceRect = { 32, 0, (int)m_resourceSize.m_x, (int)m_resourceSize.m_y };

			// After all, render the sprite
			SDL_RenderCopyEx(pRenderer, m_pTexture, &m_resourceRect, &m_destRect, m_transform.GetAngle(), &m_center, renderFlip);
		}

		void AssultRifle::Shoot()
		{
		}

		void AssultRifle::Reload()
		{
		}
	}
}