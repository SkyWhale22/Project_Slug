#pragma once
#include "CharacterStates/CharacterStateBase.hpp"

namespace Slug
{
	namespace CharacterStates
	{
		class SpartanWalkState : public CharacterStateBase
		{
		public:
			SpartanWalkState();
			~SpartanWalkState();

			// Inherited via CharacterStateBase
			virtual void OnEnter(Character& obj) override;
			virtual void OnUpdate(Character& obj, double deltaSeconds) override;
			virtual CharacterStateBase* OnHandleInput(Character& obj, const SDL_Event& event) override;
			
			//virtual void OnRender(SDL_Renderer* const pRenderer) override;
		};
	}
}

