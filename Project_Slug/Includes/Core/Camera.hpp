#pragma once
#include "Utils/Utils.hpp"
#include "Core/Singleton.hpp"
#include <SDL.h>

namespace Slug
{
	namespace Objects
	{
		class GameObject;
	}

	namespace Core
	{
		class Camera : public Singleton<Camera>
		{
		private:
			SDL_Rect m_dest;
			SDL_Rect m_boundary;
			Objects::GameObject* m_pFollow;
			bool m_out;
			Vector2 m_center;

		public:
			Camera();
			~Camera();

			void Update(double deltaSeconds);
			void DrawDebug(SDL_Renderer* const pRenderer);

			const Vector2 GetPosition();

			void SetPosition(const Vector2& vec);
			//void SetPosition(float x, float y);
			void SetFollowingObj(const Objects::GameObject* pObj);
		};
	}
}


