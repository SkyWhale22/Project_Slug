#include "GameObjects/Spartan.hpp"
#include <iostream>
namespace Slug
{
	namespace Objects
	{
		Spartan::Spartan()
		{
			m_pos = { 0, 0 };
			
			m_destRect = { (int)this->m_pos.m_x, (int)this->m_pos.m_y, 0, 0};
		}
		Spartan::Spartan(float posX, float posY)
		{
			m_pos.m_x = posX;
			m_pos.m_y = posY;

			m_destRect = { (int)(posX - (SPRITE_WIDTH / 2)), (int)(posY - (SPRITE_HEIGHT / 2)), SPRITE_WIDTH, SPRITE_HEIGHT };
		}
		Spartan::Spartan(const Vector2& initPos)
		{
			m_pos = initPos;
			
			m_destRect = { (int)(initPos.m_x - (SPRITE_WIDTH / 2)), (int)(initPos.m_y - (SPRITE_HEIGHT / 2)), SPRITE_WIDTH, SPRITE_HEIGHT };
		}

		Spartan::~Spartan()
		{
		}

		void Spartan::Update(double deltaSeconds)
		{
			//std::cout.precision(11);
			//std::cout << "FPS:" << std::fixed << deltaSeconds << std::endl;

			if (m_moveDir.m_up)
			{
				m_pos.m_y -= (float)(kMovingSpeed * deltaSeconds);
			}

			if (m_moveDir.m_down)
			{
				m_pos.m_y += (float)(kMovingSpeed * deltaSeconds);
			}

			if (m_moveDir.m_right)
			{
				m_pos.m_x += (float)(kMovingSpeed * deltaSeconds);
			}

			if (m_moveDir.m_left)
			{
				m_pos.m_x -= (float)(kMovingSpeed * deltaSeconds);
			}

			m_destRect = { (int)(m_pos.m_x - (SPRITE_WIDTH / 2)), (int)(m_pos.m_y - (SPRITE_HEIGHT / 2)), SPRITE_WIDTH, SPRITE_HEIGHT };
		}

		void Spartan::Render(SDL_Renderer* const pRenderer)
		{
			// Change color to red
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

			// Render object
			SDL_RenderFillRect(pRenderer, &m_destRect);

			SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
			SDL_Rect dest = { (int)m_pos.m_x - 5, (int)m_pos.m_y - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);
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
