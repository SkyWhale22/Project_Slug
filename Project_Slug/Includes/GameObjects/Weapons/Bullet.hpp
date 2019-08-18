#pragma once
#include "GameObjects/GameObject.hpp"
#include "Utils/ObjectPool.h"

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace Slug
{
	namespace Objects
	{
		class Bullet : public GameObject
					 , public Utils::IPoolable<Bullet>
		{
		// --- Member Variables ---
		private:
			tinyxml2::XMLDocument m_doc;
			tinyxml2::XMLElement* m_pBulletData;

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

			void SetBulletData(const char* pName);

			// Inherited via IPoolable
			virtual void Reset() override;
			virtual void PrintStatus() override;

			virtual Bullet* GetNext() override;
			virtual Bullet* GetPrev() override;
			virtual void SetNext(Bullet* pObject) override;
			virtual void SetPrev(Bullet* pObject) override;
		};
	}
}


