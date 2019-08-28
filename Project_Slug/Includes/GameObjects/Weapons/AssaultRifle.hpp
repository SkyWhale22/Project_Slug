#pragma once
#include "GameObjects/Weapon.hpp"

namespace Slug
{
	namespace Objects
	{

		//---------------------------------------------------------------
		// TODO: Create shooting logic.
		//---------------------------------------------------------------
		class AssaultRifle final : public Weapon
		{
		public:
			AssaultRifle();
			AssaultRifle(const Vector2& pos);
			AssaultRifle(float posX, float posY);
			AssaultRifle(const AssaultRifle& instance);
			~AssaultRifle();

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
