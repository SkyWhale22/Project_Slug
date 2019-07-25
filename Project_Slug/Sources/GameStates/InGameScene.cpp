#include <iostream>
#include "GameStates/InGameScene.hpp"
#include <GameStates/GameStateMachine.hpp>
#include <Managers/MouseManager.hpp>

//-----------------------------------------------------------------
// UI
//-----------------------------------------------------------------
//#include "UI/UIButton.hpp"

//-----------------------------------------------------------------
// UI
//-----------------------------------------------------------------
#include "GameObjects/Spartan.hpp"

namespace Slug
{
	namespace GameStates
	{
		//------------------------------------------------------
		// In Game Scene
		//------------------------------------------------------
		InGameScene::InGameScene()
			: m_pPlayer(new Objects::Spartan({100, 100}))
		{
		}

		InGameScene::~InGameScene()
		{
			delete m_pPlayer;
			m_pPlayer = nullptr;
		}

		void InGameScene::OnEnter(GameStateMachine* pStateMachine)
		{
			GameState::OnEnter(pStateMachine);
			std::cout << "In game state!!" << std::endl;
		}

		void InGameScene::OnExit()
		{
		}

		void InGameScene::OnUpdate(double deltaSeconds)
		{
			m_pPlayer->Update(deltaSeconds);
		}

		void InGameScene::OnHandleInput(const SDL_Event& event)
		{			
			
			// --- Quitting the game ---
			if (event.type == SDL_QUIT)
			{
				m_pStateMachine->QuitGame();
			}

			// --- Keyboard input ---
			if (event.type == SDL_KEYDOWN)
			{
				SDL_Keycode key = event.key.keysym.sym;

				if (key == SDLK_ESCAPE)
				{
					m_pStateMachine->QuitGame();
				}
				
				m_pPlayer->Input(event);
			}

			if (event.type == SDL_KEYUP)
			{
				m_pPlayer->Input(event);
			}

		}

		void InGameScene::OnRender(SDL_Renderer* const pRenderer)
		{
			SDL_SetRenderDrawColor(pRenderer, 32, 64, 128, 255);
			SDL_RenderClear(pRenderer);

			// ------ Put objects to render below! ------
			m_pPlayer->Render(pRenderer);

			// Change color to yellow
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);


			// Render mouse
			SDL_Rect dest = { (int)Managers::MouseManager::GetInstance()->GetMousePosition().m_x - 5, (int)Managers::MouseManager::GetInstance()->GetMousePosition().m_y - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);

			//-------------------------------------------

			SDL_RenderPresent(pRenderer);
		}
	}
}