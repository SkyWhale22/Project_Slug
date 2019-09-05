#pragma once
#include <memory>
#include "GameObjects/GameObject.hpp"
#include <string_view>

namespace Slug
{
	namespace Objects
	{
		class Bullet;

		//------------------------------------------------------------------------------------------------------
		// x TODO: Make a spot that pointing the muzzle of each gun type. It 
		// x TODO: It should be just a vector 2d position, that rotating whenever player move the mouse.
		//------------------------------------------------------------------------------------------------------
		enum class WeaponType
		{
			kMagnum,
			kAssaultRifle,
			kShotgun,
			kPlasmaPistol,
			kPlasmaRifle,
			kTotal
		};

		class Weapon : public GameObject
		{
		// ----- Member Variables -----
		private:
			SDL_Point m_points[4];
			WeaponType m_weaponType;

			size_t m_clip;
			size_t m_bulletsInStock;

		protected:
			SDL_Point m_muzzel[2];

		// ----- Member Functions -----
		public:
			//Weapon();
			//Weapon(const Vector2& pos);
			//Weapon(float posX, float posY);
			//Weapon(const Weapon& instance);w
			                      
			virtual ~Weapon() = 0 {};
			
			// Inherited via GameObject
			virtual void Initialize() = 0;
			virtual void Update(double deltaSeconds) = 0;
			virtual void Render(SDL_Renderer* const pRenderer) = 0;
			//virtual void SetTexture(const char* pSpritePath) = 0;

			virtual void Shoot() = 0;
			virtual void Reload() = 0;

			void UpdateDebugLine();
			//void FindDegreesToCursor(const Vector2& pos);
			SDL_Point CalcRotatedDebugPoint(const SDL_Point& origin);

			SDL_Point GetMuzzelPoint() const { return m_muzzel[1]; }

			WeaponType GetTypeInfo() const { return m_weaponType; }
			void SetWeaponType(WeaponType type) { m_weaponType = type; }
			
			const std::string_view ConvTypeToStr();

			constexpr size_t GetRemainingBulletNum() { return m_clip; }
			constexpr size_t GetTotalRounds() { return m_bulletsInStock; }
		};
	}
}

