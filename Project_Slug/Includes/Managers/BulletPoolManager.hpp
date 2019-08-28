#pragma once
#include "Core/Singleton.hpp"
#include "Utils/Utils.hpp"
#include <memory>
#include "SDL.h"

namespace Slug
{
	namespace Utils
	{
		template <class Type>
		class TObjectPool;
	}

	namespace Objects
	{
		class Bullet;
	}

	namespace Managers
	{
		class BulletPoolManager : public Core::Singleton<BulletPoolManager>
		{
		private:
			std::unique_ptr<Utils::TObjectPool<Objects::Bullet>> m_pBulletPool;

		public:
			BulletPoolManager();
			~BulletPoolManager();

			void UpdateBullets(double deltaSeconds);
			Objects::Bullet* GetBullet(Vector2 position, double angle);
			void RenderBullets(SDL_Renderer* const pRenderer);
		};
	}
}



