//-----------------------------------------------------------------
// SDL
//-----------------------------------------------------------------
#include "SDL_image.h"

//-----------------------------------------------------------------
// Windows
//-----------------------------------------------------------------
#include <math.h>
#include <iostream>

//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include "Core/Application.hpp"
#include "Core/Camera.hpp"

//-----------------------------------------------------------------
// GameObjects
//-----------------------------------------------------------------
#include "GameObjects/Weapon.hpp"

//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include "Managers/MouseManager.hpp"

//-----------------------------------------------------------------
// Utils
//-----------------------------------------------------------------
#include "Utils/Utils.hpp"

namespace Slug
{
	namespace Objects
	{
		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		Weapon::Weapon()
		{
			m_transform = Utils::Transform(0, 0, 0);

			Initialize();
		}

		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		Weapon::Weapon(const Vector2& pos)
		{
			m_transform = Utils::Transform(pos, 0);

			Initialize();
		}
		
		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		Weapon::Weapon(float posX, float posY)
		{
			m_transform = Utils::Transform(posX, posY, 0);

			Initialize();
		}
		
		//--------------------------------------------------------------------
		// Basic constructor
		//--------------------------------------------------------------------
		Weapon::Weapon(const Weapon& instance)
		{
			m_transform = instance.m_transform;
			m_destRect = instance.m_destRect;

			Initialize();
		}

		//--------------------------------------------------------------------
		// Destructor
		//--------------------------------------------------------------------
		Weapon::~Weapon()
		{
		} 

		/**-------------------------------------------------------------------
		 * 
		 * Initialization function.
		 * This function contains common things that should be initialized
		 * in constructors.
		 * 
		 * \param N\A \n
		-------------------------------------------------------------------**/
		void Weapon::Initialize()
		{
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();

			m_destRect = { (int)m_transform.GetPositionX() - (int)camera.m_x, (int)m_transform.GetPositionY()- (int)camera.m_x, 120, 44 };

			SetTexture("Resources/Sprites/Spartan.png");
			UpdateDebugLine();
		}

		// ![ Description ]
		//--------------------------------------------------------------------
		// Update dest rect's x, y position and debug line's coordinate
		//--------------------------------------------------------------------
		void Weapon::Update(double deltaSeconds)
		{
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			m_destRect.x = (int)m_transform.GetPositionX() - (int)camera.m_x - 29;
			
			m_destRect.y = (int)m_transform.GetPositionY() - (int)camera.m_y - 22;
			
			UpdateDebugLine();
		}

		//--------------------------------------------------------------------
		/**
		 * \brief Rendering function.
		 * \param pRenderer	instance that help to render. SDL included. 
		**/
		//--------------------------------------------------------------------
		void Weapon::Render(SDL_Renderer* const pRenderer)
		{
			
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			Vector2 mouse = Managers::MouseManager::GetInstance()->GetMousePosition();

#if DEBUG 
			// --- Debug line ---
			SDL_Point debugRect[4];
			
			for (size_t i = 0; i < 4; ++i)
				debugRect[i] = CalcRotatedDebugPoint(m_points[i]);
		// Rendering function. Currently, it only renders the lines for 

			SDL_RenderDrawLines(pRenderer, debugRect, 4);
			SDL_RenderDrawLine(pRenderer, debugRect[3].x, debugRect[3].y, debugRect[0].x, debugRect[0].y);
#endif
			const float transformX = GetTransform().GetPositionX() - camera.m_x;
			const float mouseX = Managers::MouseManager::GetInstance()->GetMousePosition().m_x;

			SDL_RendererFlip renderFlip = (transformX < mouseX) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_VERTICAL;
			
			SDL_Rect dest = { (int)m_transform.GetPositionX() - 5 - (int)camera.m_x, (int)m_transform.GetPositionY() - 5 - (int)camera.m_y, 10, 10 };
			
			m_resourceRect = { 32, 0, 30, 15 };
			SDL_Point center = { 29, 22 };
			// --- Render Sprite ---
			SDL_RenderCopyEx(pRenderer, m_pTexture, &m_resourceRect, &m_destRect, m_transform.GetAngle(), &center, renderFlip);

			// --- Actual Point ---
#if DEBUG
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(pRenderer, &dest);
#endif
		}

		void Weapon::SetTexture(const char* pSpritePath)
		{
			if (m_pTexture)
				SDL_DestroyTexture(m_pTexture);

			m_pTexture = IMG_LoadTexture(Core::Application::GetRenderer(), "Resources/Sprites/Spartan.png");

		}
		void Weapon::UpdateDebugLine()
		{
			m_points[0] = { m_destRect.x,					m_destRect.y };
			m_points[1] = { m_destRect.x + m_destRect.w,		m_destRect.y };
			m_points[2] = { m_destRect.x + m_destRect.w,		m_destRect.y + m_destRect.h };
			m_points[3] = { m_destRect.x,					m_destRect.y + m_destRect.h };
		}

		void Weapon::FindDegreesToCursor(const Vector2& pos)
		{
			double deltaY = (double)pos.m_y - (double)((m_destRect.y + (m_destRect.y + m_destRect.h)) / 2);
			double deltaX = (double)pos.m_x - (double)((m_destRect.x + (m_destRect.x + m_destRect.w)) / 2);

			//  M_PI / 180.0
			double degree = (atan2(deltaY, deltaX)* 180.0) / M_PI;
			//std::cout << atan2(deltaY, deltaX) << " / " << degree << std::endl;

			m_transform.Rotate(degree);
		}

		SDL_Point Weapon::CalcRotatedDebugPoint(const SDL_Point& origin)
		{
			double degree = m_transform.GetAngle();
			Vector2 camera = Core::Camera::GetInstance()->GetPosition();
			Vector2 transform = { m_transform.GetPositionX() - camera.m_x, m_transform.GetPositionY() - camera.m_y };

			int transX = (int)(m_transform.GetPositionX() - camera.m_x);
			int transY = (int)(m_transform.GetPositionY() - camera.m_y);
			
			int x = (int)(transform.m_x + (((double)origin.y - transY) * sin(-degree)) + (((double)origin.x - transX)  * cos(degree) ));
			int y = (int)(transform.m_y + (((double)origin.y - transY) * cos(degree) ) - (((double)origin.x - transX)  * sin(-degree)));

			return { x, y };
		}
	}
}

