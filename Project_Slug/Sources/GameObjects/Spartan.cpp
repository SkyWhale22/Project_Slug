#include "GameObjects/Spartan.hpp"
#include "GameObjects/Weapon.hpp"
#include <iostream>
#include "Managers/MouseManager.hpp"
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
			m_transform = Utils::Transform(0, 0, 0);

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
			//std::cout.precision(11);
			//std::cout << "FPS:" << std::fixed << deltaSeconds << std::endl;

			if (m_moveDir.m_up)
			{
				m_transform.SetPositionY(m_transform.GetPositionY() - (float)(kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_down)
			{
				m_transform.SetPositionY(m_transform.GetPositionY() + (float)(kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_right)
			{
				m_transform.SetPositionX(m_transform.GetPositionX() + (float)(kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_left)
			{
				m_transform.SetPositionX(m_transform.GetPositionX() - (float)(kMovingSpeed * deltaSeconds));
			}

			m_destRect = { (int)(m_transform.GetPositionX() - (SPRITE_WIDTH / 2)), (int)(m_transform.GetPositionY() - (SPRITE_HEIGHT / 2)), SPRITE_WIDTH, SPRITE_HEIGHT };
		
			m_pWeapon->GetTransform().SetPosition(m_transform.GetPositionRef());
			m_pWeapon->Update(deltaSeconds);
			m_pWeapon->Rotate(Managers::MouseManager::GetInstance()->GetMousePosition());
		}

		void Spartan::Render(SDL_Renderer* const pRenderer)
		{
			// Change color to red
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

			// Render object
			SDL_RenderFillRect(pRenderer, &m_destRect);

			SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
			SDL_Rect dest = { (int)m_transform.GetPositionX() - 5, (int)m_transform.GetPositionY() - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);

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
				}
				break;
				case SDLK_a:
				{
					m_moveDir.m_left = true;
				}
				break;
				case SDLK_s:
				{
					m_moveDir.m_down = true;
				}
				break;
				case SDLK_d:
				{
					m_moveDir.m_right = true;
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
				}
				break;
				case SDLK_a:
				{
					m_moveDir.m_left = false;
				}
				break;
				case SDLK_s:
				{
					m_moveDir.m_down = false;
				}
				break;
				case SDLK_d:
				{
					m_moveDir.m_right = false;
				}
				break;
				}
			}
		}
	}
}
