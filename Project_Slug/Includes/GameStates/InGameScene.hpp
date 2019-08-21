#pragma once

//-----------------------------------------------------------------
// Cores
//-----------------------------------------------------------------
#include <SDL_events.h>
#include "GameStates/GameState.hpp"

namespace Slug
{
	namespace Objects
	{
		class GameObject;
		class Spartan;
		class Bullet;
	}

	namespace GameStates
	{
		class InGameScene : public GameState
		{
			// ----- Member Variables -----
		private:
			Objects::Spartan* m_pPlayer;

			// ----- Member Functions -----
		public:
			InGameScene();
			virtual ~InGameScene() override;

			// Inherited via GameState
			virtual void OnEnter(GameStateMachine* pStateMachine)	override;
			virtual void OnExit()									override;
			virtual void OnUpdate(double deltaSeconds)				override;
			virtual void OnHandleInput(const SDL_Event& event)		override;
			virtual void OnRender(SDL_Renderer* const pRenderer)	override;
		};

	}
}