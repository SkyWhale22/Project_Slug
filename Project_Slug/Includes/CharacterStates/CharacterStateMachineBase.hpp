#pragma once
#include <SDL.h>
#include "CharacterStates/CharacterStateBase.hpp"

namespace Slug
{
	namespace Objects
	{
		class Character;
	}

	namespace CharacterStates
	{
		//using StateType = enum class CharacterStateBase::StateType;

		class CharacterStateMachineBase
		{

		protected:
			CharacterStateBase* m_pCurrent;
			//CharacterStateBase::StateType m_currentState;
			//CharacterStateBase::StateType m_desiredState;

			//--- Mebmer Functions ---
		public:
			virtual ~CharacterStateMachineBase() = 0 {}

			//virtual void CheckState() = 0;
			virtual void Update(Objects::Character& obj, double deltaSeconds) = 0;
			virtual void Render(SDL_Renderer* const pRenderer) = 0;
			virtual void Input(Objects::Character& obj, const SDL_Event& event) = 0;
			virtual void SetDesiredState(CharacterStateBase::StateType newState) = 0;
		};


	}
}
