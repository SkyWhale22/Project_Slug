#pragma once
#include "GameObjects/Weapon.hpp"

namespace Slug
{
	namespace Objects
	{
		class Magnum : public Weapon
		{
		public:
			Magnum();
			Magnum(const Vector2& pos);
			Magnum(float posX, float posY);
			Magnum(const Magnum& instance);

			// Inherited via GameObject
			virtual void Initialize() override;
			virtual void Update(double deltaSeconds) override;
			virtual void Render(SDL_Renderer* const pRenderer) override;
			//virtual void SetTexture(const char* pSpritePath) override;

			// Inherited via Weapon
			virtual void Shoot() override;
			virtual void Reload() override;

		};
	}
}
