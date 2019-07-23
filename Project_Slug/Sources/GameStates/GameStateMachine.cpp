#include <GameStates/GameStateMachine.hpp>
#include <GameStates/InGameScene.hpp>
#include <GameStates/MainTitleScene.hpp>
//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include "Managers/MouseManager.hpp"

namespace Slug
{
	namespace GameStates
	{
		GameStateMachine::GameStateMachine()
			: m_isPlaying(true)
			, m_pCurrentState(nullptr)
			, m_desiredState(GameState::Type::kMenu)
			, m_stateType(GameState::Type::kInvalid)
		{
		}

		GameStateMachine::~GameStateMachine()
		{
			delete m_pCurrentState;
			m_pCurrentState = nullptr;
		}

		void GameStateMachine::CheckState()
		{
			if (m_stateType == m_desiredState)
				return;

			if (m_pCurrentState != nullptr)
			{
				m_pCurrentState->OnExit();
				delete m_pCurrentState;
			}

			switch (m_desiredState)
			{
			case GameState::Type::kInvalid:
				break;
			case GameState::Type::kMenu:
				m_pCurrentState = new MainTitleScene();
				break;
			case GameState::Type::kGamePlay:
				m_pCurrentState = new InGameScene();
				break;
			case GameState::Type::kCredits:
				break;
			default:
				break;
			}

			m_stateType = m_desiredState;
			m_pCurrentState->OnEnter(this);
		}

		void GameStateMachine::Update(double deltaSeconds)
		{
			m_pCurrentState->OnUpdate(deltaSeconds);
		}

		void GameStateMachine::HandleInput(const SDL_Event& event)
		{
			m_pCurrentState->OnHandleInput(event);
		}

		void GameStateMachine::Render(SDL_Renderer* const pRenderer)
		{
			m_pCurrentState->OnRender(pRenderer);
		}

		void GameStateMachine::SetDesiredState(GameState::Type newState)
		{
			// TODO: Add checks here for edge case of two state transfers in a single frame
			m_desiredState = newState;
		}

	}
}
