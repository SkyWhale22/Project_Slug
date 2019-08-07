#include "GameObjects/Weapons/AssultRifle.hpp"

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

		void AssultRifle::Shoot()
		{
		}

		void AssultRifle::Reload()
		{
		}
	}
}