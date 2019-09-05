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
		enum class WeaponType;
	}

	namespace Managers
	{
		class BulletPoolManager : public Core::Singleton<BulletPoolManager>
		{
		private:
			std::unique_ptr<Utils::TObjectPool<Objects::Bullet>> m_pBulletPool;

			struct BulletSpriteCache
			{
			private:
				friend class BulletPoolManager;

				struct DataChunk
				{

					SDL_Rect m_resource;
					SDL_Point m_center;
				};

			public:
				
				SDL_Texture* m_pTexture;
				DataChunk m_magnumCache;
				DataChunk m_arCache;
			} m_spriteCache;

		public:
			BulletPoolManager();
			~BulletPoolManager();

			void UpdateBullets(double deltaSeconds);
			Objects::Bullet* GetBullet(Vector2 position, double angle, Objects::WeaponType type);
			void RenderBullets(SDL_Renderer* const pRenderer);
		};
	}
}



