#pragma once
#include <SDL.h>

namespace Slug
{
	namespace Objects
	{
		class Character;
	}

	namespace CharacterStates
	{
		class CharacterStateMachineBase;

		class CharacterStateBase
		{
		// --- Member Variables ---
		private:
			friend class CharacterStateMachineBase;
			friend class SpartanStateMachine;
		
		protected:
			using Character = Objects::Character;
			CharacterStateMachineBase* m_pStateMachine;
			enum class StateType
			{
				kInvalid,
				kIdle,
				kWalk,
				kAttack,
				kDie
			};

		// --- Mebmer Functions ---
		public:
			/*CharacterStateBase();
			CharacterStateBase(const CharacterStateBase&);
			~CharacterStateBase();
			*/
			virtual void OnEnter(Character& obj) = 0;
			virtual void OnUpdate(Character& obj, double deltaSeconds) = 0;
			virtual CharacterStateBase* OnHandleInput(Character& obj, const SDL_Event& event) = 0;
			
			//virtual void OnRender(SDL_Renderer* const pRenderer) = 0;

		};
	}
}
