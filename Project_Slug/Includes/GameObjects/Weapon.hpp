#pragma once
#include "GameObjects/GameObject.hpp"
namespace Slug
{
	namespace Objects
	{
		class Weapon : public GameObject
		{
		// ----- Member Variables -----
		private:
			SDL_Point m_points[4];

		protected:
			SDL_Point m_center;
			Vector2 m_resourceSize;
			Vector2 m_renderSize;

		// ----- Member Functions -----
		public:
			//Weapon();
			//Weapon(const Vector2& pos);
			//Weapon(float posX, float posY);
			//Weapon(const Weapon& instance);

			virtual ~Weapon() = 0 {};

			// Inherited via GameObject
			virtual void Initialize() = 0;
			virtual void Update(double deltaSeconds) final;
			virtual void Render(SDL_Renderer* const pRenderer) = 0;
			//virtual void SetTexture(const char* pSpritePath) = 0;

			virtual void Shoot() = 0;
			virtual void Reload() = 0;

			void UpdateDebugLine();
			void FindDegreesToCursor(const Vector2& pos);
			SDL_Point CalcRotatedDebugPoint(const SDL_Point& origin);
		};
	}
}

