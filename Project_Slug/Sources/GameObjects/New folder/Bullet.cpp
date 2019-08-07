#include "GameObjects\Weapons\Bullet.hpp"

namespace Slug
{
	namespace Objects
	{
		//--------------------------------------------------------------------
		// ctors
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
		}

		void Bullet::Update(double deltaSeconds)
		{
		}
		
		void Bullet::Render(SDL_Renderer* const pRenderer)
		{
		}
	}
}
