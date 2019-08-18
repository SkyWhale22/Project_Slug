#include "CharacterStates/SpartanStates/SpartanIdleState.hpp"
#include "CharacterStates/SpartanStates/SpartanWalkState.hpp"
#include "CharacterStates/CharacterStateMachineBase.hpp"
#include "Utils/Utils.hpp"
#include "GameObjects/Character.hpp"
#include <iostream>

namespace Slug
{
	namespace CharacterStates
	{
		SpartanIdleState::SpartanIdleState()
		{
		}
		
		SpartanIdleState::~SpartanIdleState()
		{
		}

		void SpartanIdleState::OnEnter(Character& obj)
		{
			obj.SetAnimation((int)AnimationType::kIdle);
			//std::cout << "Entered idle state\n";
		}

		void SpartanIdleState::OnUpdate(Character& obj, double deltaSeconds)
		{
		}
		
		CharacterStateBase* SpartanIdleState::OnHandleInput(Character& obj, const SDL_Event& event)
		{
			Movement* pMoveDir = obj.GetMovementPtr();

			// --- Key Down ---
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{

				case SDLK_w:
				{
					pMoveDir->m_up = true;
				}
				break;
				case SDLK_a:
				{
					pMoveDir->m_left = true;
				}
				break;
				case SDLK_s:
				{
					pMoveDir->m_down = true;
				}
				break;
				case SDLK_d:
				{
					pMoveDir->m_right = true;
				}
				break;
				}
			}

			if (pMoveDir->IsMoving())
			{
				//m_pStateMachine->SetDesiredState(StateType::kWalk);
				obj.SetAnimation((int)AnimationType::kWalk);
				return new SpartanWalkState();
			}

			return nullptr;
		}
	
		/*
		void SpartanIdleState::OnRender(SDL_Renderer* const pRenderer)
		{
			
		}
		*/
	}
}