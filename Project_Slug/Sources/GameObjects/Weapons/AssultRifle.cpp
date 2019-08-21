//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include <assert.h>
#include "Core/Application.hpp"
#include "Core/Camera.hpp"
#include <memory.h>

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


		AssultRifle::AssultRifle(const AssultRifle& instance)
		{
			m_transform = instance.m_transform;
			m_destRect = instance.m_destRect;

			Initialize();
		}

		AssultRifle::~AssultRifle()
		{
		}

		void AssultRifle::Initialize()
		{
			// Call parent class's initialization
			Weapon::Initialize();

			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			m_destRect = { (int)m_transform.GetPositionX() - (int)camera.m_x, (int)m_transform.GetPositionY() - (int)camera.m_y, 120, 44 };

			XMLDocument	m_doc;
			m_doc.LoadFile("Includes/Data/SpriteData.xml");
			
			XMLElement* m_pRoot = m_doc.RootElement();
			XMLElement* pWeaponData = m_pRoot->FirstChildElement("Weapons");
			assert(pWeaponData != nullptr && "pWeaponData was nullptr");

			XMLElement* pARData = pWeaponData->FirstChildElement("SpriteFrame")->FirstChildElement("AssultRifle");
			assert(pARData != nullptr && "pARData was nullptr");

			//m_resourceSize = { (float)pARData->IntAttribute("sizeX"), (float)pARData->IntAttribute("sizeY") };
			m_resourceRect =
			{ 
			(int)pARData->IntAttribute("posX"),
			(int)pARData->IntAttribute("posY"),
			(int)pARData->IntAttribute("sizeX"),
			(int)pARData->IntAttribute("sizeY")
			};

			// Search center position wherer the sprite will be rendererd.
			m_center = { (int)pARData->IntAttribute("centerX"), (int)pARData->IntAttribute("centerY") };
		}

		void AssultRifle::Update(double deltaSeconds)
		{
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();

			// Calculate destination rect.
			m_destRect.x = (int)m_transform.GetPositionX() - (int)camera.m_x - m_center.x;
			m_destRect.y = (int)m_transform.GetPositionY() - (int)camera.m_y - m_center.y;

			m_muzzel[0] = { m_destRect.x + m_destRect.w, (m_destRect.y * 2 + m_destRect.h) / 2 };
			m_muzzel[1] = CalcRotatedDebugPoint(m_muzzel[0]);
#if DEBUG_POSITION
			Weapon::Update(deltaSeconds);
#endif
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

			// After all, render the sprite
			SDL_RenderCopyEx(pRenderer, m_pTexture, &m_resourceRect, &m_destRect, m_transform.GetAngle(), &m_center, renderFlip);

			SDL_Rect rect = { m_muzzel[1].x, m_muzzel[1].y, 10, 10 };
			SDL_RenderDrawRect(pRenderer, &rect);
		}

		void AssultRifle::Shoot()
		{
		}

		void AssultRifle::Reload()
		{
		}
	}
}