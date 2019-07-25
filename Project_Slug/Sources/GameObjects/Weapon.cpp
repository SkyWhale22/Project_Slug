#include "GameObjects/Weapon.hpp"
#include <math.h>

namespace Slug
{
	namespace Objects
	{
		Weapon::Weapon()
		{
			m_transform = Utils::Transform(0, 0, 0);
			m_destRect = { 0, 0, 30, 0 };

			m_points[0] = { 300, 300 };
			m_points[1] = { 400, 300 };
			m_points[2] = { 400, 400 };
			m_points[3] = { 300, 400 };
		}
		
		Weapon::Weapon(const Vector2& pos)
		{
			m_transform = Utils::Transform(pos, 0);
			m_destRect = { (int)pos.m_x, (int)pos.m_y, 120, 30 };

			m_points[0] = { 300, 300 };
			m_points[1] = { 400, 300 };
			m_points[2] = { 400, 400 };
			m_points[3] = { 300, 400 };
		}
		
		Weapon::Weapon(float posX, float posY)
		{
			m_transform = Utils::Transform(posX, posY, 0);
			m_destRect = { (int)posX, (int)posY - 15, 120, 30 };

			m_points[0] = { m_destRect.x, m_destRect.y };
			m_points[1] = { m_destRect.x + m_destRect.w, m_destRect.y };
			m_points[2] = { m_destRect.x + m_destRect.w, m_destRect.y + m_destRect.h };
			m_points[3] = { m_destRect.x, m_destRect.y + m_destRect.h };
		}
		
		Weapon::Weapon(const Weapon& instance)
		{
			m_transform = instance.m_transform;
			m_destRect = instance.m_destRect;

			m_points[0] = { 300, 300 };
			m_points[1] = { 400, 300 };
			m_points[2] = { 400, 400 };
			m_points[3] = { 300, 400 };
		}
		
		Weapon::~Weapon()
		{
		}

		void Weapon::Update(double deltaSeconds)
		{
			m_destRect = { (int)m_transform.GetPositionX(), (int)m_transform.GetPositionY() - 15, 120, 30 };
			m_points[0] = { m_destRect.x, m_destRect.y };
			m_points[1] = { m_destRect.x + m_destRect.w, m_destRect.y };
			m_points[2] = { m_destRect.x + m_destRect.w, m_destRect.y + m_destRect.h };
			m_points[3] = { m_destRect.x, m_destRect.y + m_destRect.h };
		}

		void Weapon::Render(SDL_Renderer* const pRenderer)
		{
			// Change color to yellow
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);

			SDL_RenderDrawLines(pRenderer, m_points2, 4);
			SDL_RenderDrawLine(pRenderer, m_points2[3].x, m_points2[3].y, m_points2[0].x, m_points2[0].y);


			SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
			SDL_Rect dest = { (int)m_transform.GetPositionX() - 5, (int)m_transform.GetPositionY() - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);
		}
	
		void Weapon::Rotate(const Vector2& pos)
		{
			double deltaY = (double)pos.m_y - (double)m_transform.GetPositionY();
			double deltaX = (double)pos.m_x - (double)m_transform.GetPositionX();
			double angle = atan2(deltaY, deltaX) + M_PI / 180.0;

			m_transform.Rotate(angle);

			m_points2[0] = GetRotatedPoint_Test(m_points[0]);
			m_points2[1] = GetRotatedPoint_Test(m_points[1]);
			m_points2[2] = GetRotatedPoint_Test(m_points[2]);
			m_points2[3] = GetRotatedPoint_Test(m_points[3]);
		}

		SDL_Point Weapon::GetRotatedPoint_Test(const SDL_Point& origin)
		{
			double radian = m_transform.GetAngle();

			int x = (int)(m_transform.GetPositionX() + ((double)origin.y - m_transform.GetPositionY()) * sin(-radian) + ((double)origin.x - m_transform.GetPositionX()) * cos(radian));
			int y = (int)(m_transform.GetPositionY() + ((double)origin.y - m_transform.GetPositionY()) * cos(radian) - ((double)origin.x - m_transform.GetPositionX()) * sin(-radian));

			return { x, y };
		}
	}
}

