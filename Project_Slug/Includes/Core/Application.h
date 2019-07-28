#pragma once


//-----------------------------------------------------------------
// SDL
//-----------------------------------------------------------------
#include <SDL.h>
#include <SDL_render.h>

//-----------------------------------------------------------------
// Cores
//-----------------------------------------------------------------
#include "Utils/Utils.hpp"
#include "Core/Singleton.hpp"
#include "GameStates/GameStateMachine.hpp"

//-----------------------------------------------------------------
// STL
//-----------------------------------------------------------------
#include <memory>
#include <time.h>
 
namespace Slug
{
	namespace Core
	{
		class Camera;

		class Application : public Singleton<Application>
		{
		// ----- Member Variables -----
		private:
			SDL_Window* m_pWindow;
			SDL_Renderer* m_pRenderer;

			Uint64 m_frameCounter;
			Uint64 m_lastFrameCounter;

			double m_deltaSeconds;

			GameStates::GameStateMachine m_gsm;

			Camera m_camera;

		// ----- Member Functions -----
		private:
		public:
			Application();
			~Application();

			//static std::shared_ptr<Application> GetInstance();

			// --- Initialization ---
			void AfterInit();

			// --- Update ---
			void Update();

			// --- Input ---
			void Input();
			
			void GetFrameCount();

			//void DestroyWorld();

			bool IsPlaying() const { return m_gsm.IsPlaying(); }
		};
	};
};