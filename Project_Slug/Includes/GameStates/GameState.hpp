#pragma once

//-----------------------------------------------------------------
// Cores
//-----------------------------------------------------------------
#include <SDL_events.h>
#include <time.h>
#include <functional>
#include <iostream>
#include <SDL.h>

namespace Slug
{
	namespace GameStates
	{
		class GameStateMachine;

		class GameState
		{
			// ----- Member Variables -----
		protected:
			GameStateMachine* m_pStateMachine;

		public:
			enum class Type
			{
				kInvalid,
				kMenu,
				kGamePlay,
				kCredits,
			};

			// ----- Member Functions -----
		public:
			virtual ~GameState() {};

			virtual void OnEnter(GameStateMachine* pStateMachine) { m_pStateMachine = pStateMachine; }
			virtual void OnUpdate(double deltaSeconds) {};
			virtual void OnExit() = 0;
			virtual void OnHandleInput(const SDL_Event& event) {};
			virtual void OnRender(SDL_Renderer* const pRenderer) = 0;
		};
	}
}