#include <iostream>
#include <string>
#include <Windows.h>
#include "Core/Application.hpp"


//-----------------------------------------------------------------
// SDL
//-----------------------------------------------------------------
#include <SDL_image.h>

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}


namespace Slug
{
	namespace Core
	{
		Application::Application()
			: m_deltaSeconds(0)
		{                      
				// --- Initialize the game --- 
			srand((unsigned)time(nullptr));

			// For deltaTime.
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
			//m_pScreen = (WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_SWSURFACE);
			m_pWindow = SDL_CreateWindow("Project: Slug", 30, 80, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			SDL_CHECK(m_pWindow);

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
															  //SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);  // < -makes delay
			SDL_CHECK(m_pRenderer);


			int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
			bool imgInitialized = (IMG_Init(imgFlags) == imgFlags);

			if (!imgInitialized)
			{
				std::cout << "Error loading SDL_image: " << SDL_GetError() << std::endl;
			}


			// Enable alpha blending
			SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

			// HACK: No even handling, stay open for x frams.
			//int frameCounter = 60;
			//int framsToDisplay = 1000 / frameCounter;

			// ===== Game State Machine =====
			m_pGsm = GameStates::GameStateMachine::GetInstance();
			m_pGsm->SetDesiredState(GameStates::GameState::Type::kGamePlay);
			m_pGsm->SetPlaying(m_pWindow && m_pRenderer && imgInitialized);
			

			// Delta Time
			m_frameCounter = SDL_GetPerformanceCounter();
			m_lastFrameCounter = 0;

			// ===== Mouse Tracker =====
			//SDL_ShowCursor(0);
			m_pMouseTracker = Managers::MouseManager::GetInstance();

			ShowConsoleCursor(false);
		}

		Application::~Application()
		{
			IMG_Quit();
			SDL_DestroyWindow(m_pWindow);
		}
		
		void Application::AfterInit()
		{
		}

		void Application::Update()
		{
			//system("cls");
			while (m_pGsm->IsPlaying())
			{
				GetFrameCount();

				//Uint64 start = SDL_GetPerformanceCounter();

				m_pGsm->CheckState();

				// --- Read Input
				Input();

				m_pGsm->Update(m_deltaSeconds); 

				// --- Render
				m_pGsm->Render(m_pRenderer);

				//Uint64 end = SDL_GetPerformanceCounter();
				//float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
				//std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
				
				//float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

				// Cap to 60 FPS

				COORD pos{0, 2};
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			}

		}

		void Application::Input()
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
			{
				m_pGsm->HandleInput(event);

				if (event.type == SDL_MOUSEMOTION)
				{
					Managers::MouseManager::GetInstance()->SetPosition(event.motion.x, event.motion.y);
				}
			}
		}

		void Application::GetFrameCount()
		{
			const int targetFPS = 60;
			const int frameDelay = 1000 / targetFPS;

			// Get the counter
			m_frameCounter = SDL_GetPerformanceCounter();

			// Calculate delata time ( * 1000 millliseconds)
			m_deltaSeconds = ((double)((m_frameCounter - m_lastFrameCounter) * 1000) / (double)SDL_GetPerformanceFrequency() * 0.001);

			//printf("Delta Seconds: %.41f\n", 1000 / m_deltaSeconds());

			float elapsed = (m_frameCounter - m_lastFrameCounter) / (float)SDL_GetPerformanceFrequency();

			// Cap to 60 FPS
			if (frameDelay > elapsed)
			{
				SDL_Delay(frameDelay - elapsed);
			}
			

			std::cout << "Current FPS: " << std::to_string((1.0f / elapsed)) << std::endl;

			// Remember the last counter
			m_lastFrameCounter = m_frameCounter;
			
		}
	}
}