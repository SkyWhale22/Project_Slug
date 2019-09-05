#pragma once
//-----------------------------------------------------------------
// GameObject
//-----------------------------------------------------------------
#include <string>

//-----------------------------------------------------------------
// GameObject
//-----------------------------------------------------------------
#include "GameObjects/GameObject.hpp"

//-----------------------------------------------------------------
// Utils
//-----------------------------------------------------------------
#include "Utils/tinyxml2.h"
#include "Utils/ObjectPool.h"

namespace Slug
{
	namespace Objects
	{
		enum class WeaponType;

		class Bullet : public GameObject
					 , public Utils::IPoolable<Bullet>
		{
		// --- Member Variables ---
		private:
			//tinyxml2::XMLDocument m_doc;
			//tinyxml2::XMLElement* m_pBulletData;

		// --- Member Functions ---
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

			// Inherited via IPoolable
			virtual void Reset() override;
			virtual void PrintStatus() override;

			virtual Bullet* GetNext() override;
			virtual Bullet* GetPrev() override;
			virtual void SetNext(Bullet* pObject) override;
			virtual void SetPrev(Bullet* pObject) override;
			
			//void SetBulletData(std::string_view name);
			void SetBulletData(SDL_Rect res, SDL_Point center);
		};
	}
}


