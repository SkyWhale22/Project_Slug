#pragma once
#include <SDL.h>
#include "Utils/Utils.hpp"

namespace Slug
{
	namespace Objects
	{
		class GameObject
		{
		// --- Member Variables ---
		public:
			Movement		m_moveDir;
			SDL_Rect		m_destRect;
			Vector2			m_pos;
		
			// Currently Not been used.
			//SDL_Texture*	m_pSelectedTexture;

		public:

		// --- Member Functions ---
		private:
		public:
			virtual ~GameObject() = 0{};

			virtual void Update(double deltaSeconds) = 0;
			virtual void Render(SDL_Renderer* const pRenderer) = 0;
			
			inline Vector2 GetPosition() const { return m_pos; }
		};
	}
}

