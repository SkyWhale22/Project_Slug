#include <iostream>
#include "GameStates/InGameScene.hpp"
#include <GameStates/GameStateMachine.hpp>

//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include "Core/Camera.hpp"

//-----------------------------------------------------------------
// Game Objects
//-----------------------------------------------------------------
#include "GameObjects/Spartan.hpp"
#include "GameObjects/Weapons/Bullet.hpp"

//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include <Managers/MouseManager.hpp>
#include <Managers/BulletPoolManager.hpp>

namespace Slug
{
	namespace GameStates
	{
		//------------------------------------------------------
		// In Game Scene
		//------------------------------------------------------
		InGameScene::InGameScene()
			: m_pPlayer(new Objects::Spartan(640, 360))
		{
			Managers::BulletPoolManager::GetInstance();
		}

		InGameScene::~InGameScene()
		{
			delete m_pPlayer;
			m_pPlayer = nullptr;
		}

		void InGameScene::OnEnter(GameStateMachine* pStateMachine)
		{
			GameState::OnEnter(pStateMachine);
			Core::Camera::GetInstance()->SetFollowingObj(m_pPlayer);
			std::cout << "In game state!!" << std::endl;
		}

		void InGameScene::OnExit()
		{
		}

		void InGameScene::OnUpdate(double deltaSeconds)
		{
			m_pPlayer->Update(deltaSeconds);
			Managers::BulletPoolManager::GetInstance()->UpdateBullets(deltaSeconds);
			Core::Camera::GetInstance()->Update(deltaSeconds);
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

			if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONDOWN)
			{
				m_pPlayer->Input(event);
			}

		}

		void InGameScene::OnRender(SDL_Renderer* const pRenderer)
		{
			SDL_SetRenderDrawColor(pRenderer, 32, 64, 128, 255);
			SDL_RenderClear(pRenderer);

			// ------ Put objects to render below! ------

			// Change color to yellow
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);


			// Render mouse
			SDL_Rect dest = { (int)Managers::MouseManager::GetInstance()->GetMousePosition().m_x - 5, (int)Managers::MouseManager::GetInstance()->GetMousePosition().m_y - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);

			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();
			
			// --- For testing ---
			dest = { 500 - (int)cameraPos.m_x , 500 - (int)cameraPos.m_y, 300, 300 };
			//dest = { 500 , 500, 300, 300 };
			SDL_RenderFillRect(pRenderer, &dest);


			m_pPlayer->Render(pRenderer);

			Managers::BulletPoolManager::GetInstance()->RenderBullets(pRenderer);
#if DEBUG_CAMERA
			Core::Camera::GetInstance()->DrawDebug(pRenderer);
#endif
			//-------------------------------------------

			SDL_RenderPresent(pRenderer);
		}
	}
}