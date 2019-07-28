#include "Camera.hpp"
#include "GameObjects/GameObject.hpp"

namespace Slug
{
	namespace Core
	{
		Camera::Camera()
			: m_dest({ 0, 0, kWindowWidth, kWindowHeight })
			, m_boundary({ (kWindowWidth/2) - (kBoundaryWidth/2), (kWindowHeight / 2) - (kBoundaryHeight / 2), kBoundaryWidth, kBoundaryHeight})
			, m_pFollow(nullptr)
			, m_out(false)
			, m_center({kWindowWidth / 2, kWindowHeight / 2})
		{ 
		}

		Camera::~Camera()
		{
		}

		void Camera::Update(double deltaSeconds)
		{
			float speed = 0.8;
			if (m_pFollow)
			{
				Vector2 playerPos = m_pFollow->GetTransform().GetPosition();

				SDL_Rect playerDest = m_pFollow->GetDestRect();
				Vector2 playerCenter = { (playerDest.x + (playerDest.x + playerDest.w)) / 2, (playerDest.y + (playerDest.y + playerDest.h)) / 2 };
 				
				m_out = false;
				
				if((int)playerCenter.m_x < m_boundary.x)
				{ 
					m_dest.x -= (kMovingSpeed * speed) * deltaSeconds;
					m_out = true;
				}
				else if ((int)playerCenter.m_x > m_boundary.x + m_boundary.w)
				{
					m_dest.x += (kMovingSpeed * speed) * deltaSeconds;
					m_out = true;
				}

				if ((int)playerCenter.m_y < m_boundary.y)
				{
					m_dest.y -= (kMovingSpeed * speed) * deltaSeconds;
					m_out = true;
				}
				else if ((int)playerCenter.m_y > m_boundary.y + m_boundary.h)
				{
					m_dest.y += (kMovingSpeed * speed) * deltaSeconds;
					m_out = true;
				}
			}

			if (m_dest.x < 0)
				m_dest.x = 0;
			if (m_dest.y < 0)
				m_dest.y = 0;

			if (m_dest.x > m_dest.w)
				m_dest.x = m_dest.w;
			if (m_dest.y > m_dest.h)
				m_dest.y = m_dest.h;
		}

		void Camera::DrawDebug(SDL_Renderer* const pRenderer)
		{
			Vector2 centerPos = { (m_boundary.x + (m_boundary.x + m_boundary.w)) / 2, (m_boundary.y + (m_boundary.y + m_boundary.h)) / 2 };
			SDL_Rect test = { (int)centerPos.m_x-6, (int)centerPos.m_y-6, 12, 12 };
			SDL_Rect playerDest = m_pFollow->GetDestRect();
			Vector2 playerCenter = { (playerDest.x + (playerDest.x + playerDest.w)) / 2, (playerDest.y + (playerDest.y + playerDest.h)) / 2 };


			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_Rect dest = { 0, 0, kWindowWidth, kWindowHeight };
			SDL_RenderDrawRect(pRenderer, &dest);

			if(!m_out)
				SDL_SetRenderDrawColor(pRenderer, 125, 125, 255, 255);
			else
				SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
			
			//SDL_Rect newBoundary = { m_boundary.x - m_dest.x, m_boundary.y - m_dest.y, m_boundary.w, m_boundary.h };
			SDL_RenderDrawRect(pRenderer, &m_boundary);
			SDL_SetRenderDrawColor(pRenderer, 125, 125, 125, 255);
			SDL_RenderFillRect(pRenderer, &test);

			SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
			SDL_RenderDrawLine(pRenderer, centerPos.m_x, centerPos.m_y, playerCenter.m_x, playerCenter.m_y);
		}

		const Vector2 Camera::GetPosition()
		{
			Vector2 pos{ m_dest.x, m_dest.y };
			return pos;
		}

		void Camera::SetPosition(const Vector2& vec)
		{
			m_dest.x = vec.m_x;
			m_dest.y = vec.m_y;
		}

	/*	void Camera::SetPosition(float x, float y)
		{
			m_dest.x = (int)x;
			m_dest.y = (int)y;
		}*/

		void Camera::SetFollowingObj(const Objects::GameObject* pObj)
		{
			m_pFollow = const_cast<Objects::GameObject*>(pObj);
		}
	}
}