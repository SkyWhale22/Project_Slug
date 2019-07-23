#include <iostream>
#include <GameStates/MainTitleScene.hpp>
#include <GameStates/GameStateMachine.hpp>

//-----------------------------------------------------------------
// UI
//-----------------------------------------------------------------
#include "UI/UIButton.hpp"

//-----------------------------------------------------------------
// UI
//-----------------------------------------------------------------
#include "GameObjects/Spartan.hpp"

//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include "Managers/MouseManager.hpp"


namespace Slug
{
	namespace GameStates
	{
		//------------------------------------------------------
		// Main Title Scene
		//------------------------------------------------------
		MainTitleScene::MainTitleScene()
			: m_pStart(new UI::UIButton({ 950, 420, 250, 65 }))
			, m_pSetting(new UI::UIButton({ 950, 500, 250, 65 }))
			, m_pQuit(new UI::UIButton({ 950, 580, 250, 65 }))
		{
		}

		MainTitleScene::~MainTitleScene()
		{
			delete m_pStart;
			m_pStart = nullptr;

			delete m_pSetting;
			m_pSetting = nullptr;
			
			delete m_pQuit;
			m_pQuit = nullptr;
		}

		void MainTitleScene::OnEnter(GameStateMachine* pStateMachine)
		{
			GameState::OnEnter(pStateMachine);
			std::cout << "MenuState!" << std::endl;

			m_pStart->SetClickEnter([]()
				{
					std::cout << "You've clicked the Start button!" << std::endl; 
					GameStateMachine::GetInstance()->SetDesiredState(GameState::Type::kGamePlay);
				});

			m_pSetting->SetClickEnter([](){ std::cout << "You've clicked the Setting button!" << std::endl; });

			m_pQuit->SetClickEnter([]() 
				{
					std::cout << "You've clicked the Quit button!" << std::endl;
					GameStateMachine::GetInstance()->QuitGame();
				});
		}

		void MainTitleScene::OnExit()
		{
		}

		void MainTitleScene::OnUpdate(double deltaSeconds)
		{
		}

		void MainTitleScene::OnHandleInput(const SDL_Event& event)
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
					std::cout << "ESC!" << std::endl;
					m_pStateMachine->QuitGame();
				}
			}

			// --- Mouse Input ---
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				Managers::MouseManager* pManager = Managers::MouseManager::GetInstance();
				pManager->SetPosition(event.motion.x, event.motion.y);
				pManager->PrintClikedPos();

				m_pStart->CheckMousePosition(event.motion.x, event.motion.y);
				m_pSetting->CheckMousePosition(event.motion.x, event.motion.y);
				m_pQuit->CheckMousePosition(event.motion.x, event.motion.y);
			}
		}

		void MainTitleScene::OnRender(SDL_Renderer* const pRenderer)
		{
			SDL_SetRenderDrawColor(pRenderer, 32, 64, 128, 255);
			SDL_RenderClear(pRenderer);

			// ------ Put objects to render below! ------
			m_pStart->Render(pRenderer);
			m_pSetting->Render(pRenderer);
			m_pQuit->Render(pRenderer);
			//-------------------------------------------

			SDL_RenderPresent(pRenderer);
		}
	}
}
