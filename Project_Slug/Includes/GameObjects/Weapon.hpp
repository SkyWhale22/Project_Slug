#pragma once
#include <memory>
#include "GameObjects/GameObject.hpp"

namespace Slug
{
	namespace Objects
	{
		class Bullet;

		//-------------------------------------------------------------------
		// TODO: Make a spot that pointing the muzzle of each gun type. It 
		// TODO: It should be just a vector 2d position, that rotating whenever player move the mouse. 
		//-------------------------------------------------------------------

		class Weapon : public GameObject
		{
		// ----- Member Variables -----
		private:
			SDL_Point m_points[4];
		protected:

		// ----- Member Functions -----
		public:
			//Weapon();
			//Weapon(const Vector2& pos);
			//Weapon(float posX, float posY);
			//Weapon(const Weapon& instance);

			virtual ~Weapon() = 0 {};

			// Inherited via GameObject
			virtual void Initialize() = 0;
			virtual void Update(double deltaSeconds) = 0;
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

