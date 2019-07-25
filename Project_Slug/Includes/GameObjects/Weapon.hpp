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
			//SDL_Point m_points3D[4];
			SDL_Point m_points2[4];

		// ----- Member Functions -----
		public:
			Weapon();
			Weapon(const Vector2& pos);
			Weapon(float posX, float posY);
			Weapon(const Weapon& instance);

			~Weapon();

			// Inherited via GameObject
			virtual void Update(double deltaSeconds) override;
			virtual void Render(SDL_Renderer* const pRenderer) override;
			
			void Rotate(const Vector2& pos);
			SDL_Point GetRotatedPoint_Test(const SDL_Point& origin);
		};
	}
}

