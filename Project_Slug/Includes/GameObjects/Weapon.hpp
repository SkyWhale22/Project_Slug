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

		// ----- Member Functions -----
		public:
			Weapon();
			Weapon(const Vector2& pos);
			Weapon(float posX, float posY);
			Weapon(const Weapon& instance);

			~Weapon();

			// Inherited via GameObject
			virtual void Initialize() override;
			virtual void Update(double deltaSeconds) override;
			virtual void Render(SDL_Renderer* const pRenderer) override;
			virtual void SetTexture(const char* pSpritePath) override;

			void UpdateDebugLine();
			void FindDegreesToCursor(const Vector2& pos);
			SDL_Point CalcRotatedDebugPoint(const SDL_Point& origin);
		};
	}
}

