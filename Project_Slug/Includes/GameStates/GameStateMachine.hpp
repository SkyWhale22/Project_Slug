#pragma once
#include "Core/Singleton.hpp"
#include "GameStates/GameState.hpp"

#include <SDL_events.h>

namespace Slug
{
	namespace GameStates
	{
		/*************************************************************************
			Class Definition
		**************************************************************************/
		class GameStateMachine : public Core::Singleton<GameStateMachine>
		{
		// ----- Member Variables -----
		private:
			GameState* m_pCurrentState;
			GameState::Type m_stateType;
			GameState::Type m_desiredState;

			bool m_isPlaying;

		// ----- Member Functions -----
		public:
			GameStateMachine();
			~GameStateMachine();

			void CheckState();
			void Update(double deltaSeconds);
			void HandleInput(const SDL_Event& event);
			void Render(SDL_Renderer* const pRenderer);

			void SetDesiredState(GameState::Type newState);

			void QuitGame() { m_isPlaying = false; }
			bool IsPlaying() const { return m_isPlaying; }
			void SetPlaying(const bool set) { m_isPlaying = set; }

		};
	}
}