#include <iostream>
#include "Includes/Core/Application.h"
#include "Includes/Managers/MouseManager.h"
#include <SDL.h>
#include <SDL_image.h>

namespace Slug
{
	namespace Core
	{
		Application::Application()
			: m_isPlaying(true)
			, m_deltaSeconds(0)
		{                      
				// --- Initialize the game --- 
			srand((unsigned)time(nullptr));

			// For deltaTime.
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
			//m_pScreen = (WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_SWSURFACE);
			m_pWindow = SDL_CreateWindow("Project: Whale", 30, 80, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
			SDL_CHECK(m_pWindow);

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED); //| //SOFTWARE is never used
															  //SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC); <- makes delay
			SDL_CHECK(m_pRenderer);


			int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
			bool imgInitialized = (IMG_Init(imgFlags) == imgFlags);

			if (!imgInitialized)
			{
				std::cout << "Error loading SDL_image: " << SDL_GetError() << std::endl;
			}

			//m_pGrassTileSetTexture = IMG_LoadTexture(m_pRenderer, "Assets/Sprites/GrassTileset.png");


			// Enable alpha blending
			SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

			// HACK: No even handling, stay open for x frams.
			//int frameCounter = 0;
			//int framsToDisplay = 1000;

			m_isPlaying = (m_pWindow && m_pRenderer && imgInitialized);

			// Delta Time
			m_frameCounter = SDL_GetPerformanceCounter();
			m_lastFrameCounter = 0;
			// Store what the counter was last time
			// Reason to use 'double', because we are using 64-bits int above.


			//m_pMouseTracker = MouseManager::GetInstance();

		}

		Application::~Application()
		{
			delete m_pRenderer;
			m_pRenderer = nullptr;

			delete m_pWindow;
			m_pWindow = nullptr;
		}
		
		std::shared_ptr<Application> Application::GetInstance()
		{
			// Check does application isn't initialized
			if (m_pInstance == nullptr)
			{
				m_pInstance = std::make_shared<Application>();
			}

			return m_pInstance;
		}

		void Application::AfterInit()
		{
		}
		void Application::Update()
		{
		}
		void Application::DestroyWorld()
		{
		}
	}
}