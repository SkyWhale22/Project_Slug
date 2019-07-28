#include "GameObjects/Spartan.hpp"
#include "GameObjects/Weapon.hpp"
#include <iostream>
#include "Managers/MouseManager.hpp"
#include "..//Camera.hpp"
namespace Slug
{
	namespace Objects
	{
		Spartan::Spartan()
			: m_pWeapon(new Weapon(0,0))
		{
			m_transform = Utils::Transform(0, 0, 0);
			
			m_destRect = { (int)m_transform.GetPositionX(), (int)m_transform.GetPositionY(), 0, 0};
		}
		Spartan::Spartan(float posX, float posY)
			: m_pWeapon(new Weapon(posX, posY))
		{
			m_transform = Utils::Transform(posX, posY, 0);

			m_destRect = { (int)(posX - (SPRITE_WIDTH / 2)), (int)(posY - (SPRITE_HEIGHT / 2)), SPRITE_WIDTH, SPRITE_HEIGHT };
		}
		Spartan::Spartan(const Vector2& initPos)
			: m_pWeapon(new Weapon(initPos))
		{
			m_transform = Utils::Transform(initPos, 0);
			
			m_destRect = { (int)(initPos.m_x - (SPRITE_WIDTH / 2)), (int)(initPos.m_y - (SPRITE_HEIGHT / 2)), SPRITE_WIDTH, SPRITE_HEIGHT };
		}

		Spartan::~Spartan()
		{
			delete m_pWeapon;
			m_pWeapon = nullptr;
		}

		void Spartan::Update(double deltaSeconds)
		{
			if (m_moveDir.m_up)
			{
				if ((int)m_destRect.y > 0)
					m_transform.SetPositionY(m_transform.GetPositionY() - (float)(kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_down)
			{
				if ((int)m_destRect.y + m_destRect.h < kWindowHeight)
					m_transform.SetPositionY(m_transform.GetPositionY() + (float)(kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_right)
			{
				if ((int)m_destRect.x + m_destRect.w < kWindowWidth)
					m_transform.SetPositionX(m_transform.GetPositionX() + (float)(kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_left)
			{
				if ((int)m_destRect.x > 0)
					m_transform.SetPositionX(m_transform.GetPositionX() - (float)(kMovingSpeed * deltaSeconds));
			}

			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();

			m_destRect.x = (int)(m_transform.GetPositionX() - (SPRITE_WIDTH / 2)) - (int)cameraPos.m_x;
			m_destRect.y = (int)(m_transform.GetPositionY() - (SPRITE_HEIGHT / 2)) - (int)cameraPos.m_y;

			if (m_destRect.x < 0)
				m_destRect.x = 0;
			if (m_destRect.y < 0)
				m_destRect.y = 0;

			if (m_destRect.x > kWindowWidth)
				m_destRect.x = kWindowWidth - m_destRect.w;
			if (m_destRect.y > kWindowHeight)
				m_destRect.y = kWindowHeight - m_destRect.h;

			//m_transform.Update(deltaSeconds);

			//Vector2 test = { m_destRect.x, m_destRect.y };
			m_pWeapon->GetTransform().SetPosition(GetTransform().GetPosition());
			m_pWeapon->Rotate(Managers::MouseManager::GetInstance()->GetMousePosition());
			m_pWeapon->Update(deltaSeconds);
		}

		void Spartan::Render(SDL_Renderer* const pRenderer)
		{
			// Render object
			
			// --- Position to render ---
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();

			SDL_RenderFillRect(pRenderer, &m_destRect);

			// --- Actual position ---
			//SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
			//SDL_Rect dest = { (int)m_transform.GetPositionX() - 5, (int)m_transform.GetPositionY() - 5, 10, 10 };
			//SDL_RenderFillRect(pRenderer, &dest);
			
			m_pWeapon->Render(pRenderer);
		}

		void Spartan::Input(const SDL_Event& event)
		{
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{

				case SDLK_w:
				{
					m_moveDir.m_up = true;
					//m_transform.SetVelocityY(-1);
				}
				break;
				case SDLK_a:
				{
					m_moveDir.m_left = true;
					//m_transform.SetVelocityX(-1);
				}
				break;
				case SDLK_s:
				{
					m_moveDir.m_down = true;
					//m_transform.SetVelocityY(1);
				}
				break;
				case SDLK_d:
				{
					m_moveDir.m_right = true;
					//m_transform.SetVelocityX(1);
				}
				break;
				}				
			}

			if (event.type == SDL_KEYUP && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				{
					m_moveDir.m_up = false;
					//m_transform.SetVelocityY(0);
				}
				break;
				case SDLK_a:
				{
					m_moveDir.m_left = false;
					//m_transform.SetVelocityX(0);
				}
				break;
				case SDLK_s:
				{
					m_moveDir.m_down = false;
					//m_transform.SetVelocityY(0);
				}
				break;
				case SDLK_d:
				{
					m_moveDir.m_right = false;
					//m_transform.SetVelocityX(0);
				}
				break;
				}
			}
		}
	}
}
