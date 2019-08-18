#pragma once
#include "CharacterStates/CharacterStateMachineBase.hpp"
#include <SDL.h>

namespace Slug
{
	namespace CharacterStates
	{
		class SpartanStateMachine : public CharacterStateMachineBase
		{
		//using SpartanState = CharacterStateBase;

		//--- Member Variables ---
		private:

		//--- Mebmer Functions ---
		public:
			SpartanStateMachine();
			~SpartanStateMachine();

			virtual void Update(Objects::Character& obj, double deltaSeconds) override;
			virtual void Input(Objects::Character& obj, const SDL_Event& event) override;
		};
	}
}





