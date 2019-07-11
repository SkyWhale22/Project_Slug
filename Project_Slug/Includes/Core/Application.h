#pragma once
#include <memory>
#include "Includes/Utils/Utils.h"

#include <time.h>


namespace Slug
{
	namespace Core
	{
		class Application
		{
		// ----- Member Variables -----
		private:
			static std::shared_ptr<Application> m_pInstance;
			
			SDL_Window* m_pWindow;
			SDL_Renderer* m_pRenderer;

			Uint64 m_frameCounter;
			Uint64 m_lastFrameCounter;
			class MouseManager* m_pMouseTracker;

			double m_deltaSeconds;
			bool m_isPlaying;

		// ----- Member Functions -----
		private:
			Application() = default;
			~Application();
		public:

			static std::shared_ptr<Application> GetInstance();
			void AfterInit();
			void Update();
			void DestroyWorld();
		};
	};
};