#pragma once
#include "GameObjects/GameObject.hpp"

namespace Slug
{
	namespace Objects
	{
		class Bullet : public GameObject
		{
		public:
			Bullet();
			Bullet(float posX, float posY);
			Bullet(const Vector2& initPos);
			Bullet(const Bullet& instance);
			~Bullet();

			// Inherited via GameObject
			virtual void Initialize() override;
			virtual void Update(double deltaSeconds) override;
			virtual void Render(SDL_Renderer* const pRenderer) override;
		};
	}
}


