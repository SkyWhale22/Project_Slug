#include <GameObjects/Character.hpp>

namespace Slug
{
	namespace Objects
	{
		class Weapon;

		class Spartan : public Character
		{
		private:
			Weapon* m_pWeapon;

		public:
			Spartan();
			Spartan(float posX, float posY);
			Spartan(const Vector2& initPos);
			~Spartan();

			// Inherited via GameObject
			virtual void Initialize() override;
			virtual void Update(double deltaSeconds) override;
			virtual void Render(SDL_Renderer* const pRenderer) override;
			virtual void SetTexture(const char* pSpritePath) override;
			
			// Inherited via Character
			virtual void InitAnimation() override;
			virtual void SetAnimation(int type) override;
	
			void Input(const SDL_Event& event);
			void TestFunction(double deltaSeconds);

		};
	}
}