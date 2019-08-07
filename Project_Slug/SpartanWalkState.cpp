#include <iostream>
#include "CharacterStates/CharacterStateMachineBase.hpp"

#include "CharacterStates/SpartanStates/SpartanWalkState.hpp"
#include "CharacterStates/SpartanStates/SpartanIdleState.hpp"

#include "GameObjects/Character.hpp"
#include "Utils/Utils.hpp"


namespace Slug
{
	namespace CharacterStates
	{
		SpartanWalkState::SpartanWalkState()
		{
		}

		SpartanWalkState::~SpartanWalkState()
		{
		}

		void SpartanWalkState::OnEnter(Character& obj)
		{
			obj.SetAnimation((int)AnimationType::kWalk);
		}

		void SpartanWalkState::OnUpdate(Character& obj, double deltaSeconds)
		{
			Utils::Transform& transform = obj.GetTransform();
			SDL_Rect destRect = obj.GetDestRect();
			Movement moveDir = obj.GetMovement();

			if (moveDir.m_up)
			{
				if ((int)destRect.y > 0)
					transform.SetPositionY(transform.GetPositionY() - (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (moveDir.m_down)
			{
				if ((int)destRect.y + destRect.h < s_kWindowHeight)
					transform.SetPositionY(transform.GetPositionY() + (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (moveDir.m_right)
			{
				if ((int)destRect.x + destRect.w < s_kWindowWidth)
					transform.SetPositionX(transform.GetPositionX() + (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (moveDir.m_left)
			{
				if ((int)destRect.x > 0)
					transform.SetPositionX(transform.GetPositionX() - (float)(s_kMovingSpeed * deltaSeconds));
			}
		}

		CharacterStateBase* SpartanWalkState::OnHandleInput(Character& obj, const SDL_Event& event)
		{
			Movement* pMoveDir = obj.GetMovementPtr();

			// --- Key Up ---
			if (event.type == SDL_KEYUP && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				{
					pMoveDir->m_up = false;
				}
				break;
				case SDLK_a:
				{
					pMoveDir->m_left = false;
				}
				break;
				case SDLK_s:
				{
					pMoveDir->m_down = false;
				}
				break;
				case SDLK_d:
				{
					pMoveDir->m_right = false;
				}
				break;
				}
			}

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

			// If player character isn't moving 
			if (!pMoveDir->IsMoving())
			{
				//m_pStateMachine->SetDesiredState(StateType::kIdle);
				
				obj.SetAnimation((int)AnimationType::kIdle);
				return new SpartanIdleState();
			}

			return nullptr;
		}


		//void SpartanWalkState::OnRender(SDL_Renderer* const pRenderer)
		//{
		//}
	}
}