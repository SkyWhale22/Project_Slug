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
			//Vector2			m_pos;
			//double			m_degree;

			Utils::Transform m_transform;
		
			// Currently Not being used.
			//SDL_Texture*	m_pSelectedTexture;

		// --- Member Functions ---
		private:
		public:
			virtual ~GameObject() = 0{};

			virtual void Update(double deltaSeconds) = 0;
			virtual void Render(SDL_Renderer* const pRenderer) = 0;

			inline Utils::Transform& GetTransform() { return m_transform; }
			//inline Vector2 GetPosition() const { return m_pos; }
			//inline void SetPosition(const Vector2& pos) { m_pos = pos; }
		};
	}
}

