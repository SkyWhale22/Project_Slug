#pragma once
#include <SDL.h>
#include "Utils/Transform.hpp"

namespace Slug
{
	namespace Utils
	{
		class Transform;
	}

	namespace Objects
	{
		class GameObject
		{
		// --- Member Variables ---
		protected:
			Movement		m_moveDir;
			SDL_Rect		m_destRect;
			SDL_Rect		m_resourceRect;
			SDL_Texture*	m_pTexture;
			Utils::Transform m_transform;

			// Currently Not being used.

		// --- Member Functions ---
		private:
		public:
			virtual ~GameObject() = 0{};

			virtual void Initialize() = 0;
			virtual void Update(double deltaSeconds) = 0;
			virtual void Render(SDL_Renderer* const pRenderer) = 0;
			virtual void SetTexture(const char* pSpritePath) = 0;

			SDL_Rect GetDestRect() { return m_destRect; }
			inline Utils::Transform& GetTransform() { return m_transform; }
			
			
			//inline Vector2 GetPosition() const { return m_pos; }
			//inline void SetPosition(const Vector2& pos) { m_pos = pos; }
		};
	}
}

