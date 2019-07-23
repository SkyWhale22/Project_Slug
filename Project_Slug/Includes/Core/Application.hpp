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
// Managers
//-----------------------------------------------------------------
#include "Managers/MouseManager.hpp"


//-----------------------------------------------------------------
// STL
//-----------------------------------------------------------------
#include <memory>
#include <time.h>
 
namespace Slug
{
	namespace Core
	{
		class Application : public Singleton<Application>
		{
		// ----- Member Variables -----
		private:
			SDL_Window* m_pWindow;
			SDL_Renderer* m_pRenderer;

			Uint64 m_frameCounter;
			Uint64 m_lastFrameCounter;

			double m_deltaSeconds;

			// ==== Managers ====
			GameStates::GameStateMachine* m_pGsm;
			Managers::MouseManager* m_pMouseTracker;
			
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

			inline bool IsPlaying() const { return m_pGsm->IsPlaying(); }
		};
	};
};