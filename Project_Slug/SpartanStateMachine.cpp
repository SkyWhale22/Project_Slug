#include "CharacterStates/SpartanStates/SpartanStateMachine.hpp"

#include "CharacterStates/CharacterStateBase.hpp"
#include "CharacterStates/SpartanStates/SpartanIdleState.hpp"
#include "CharacterStates/SpartanStates/SpartanWalkState.hpp"

#include "GameObjects/Character.hpp"

namespace Slug
{
	namespace CharacterStates
	{
		SpartanStateMachine::SpartanStateMachine()
		{
			m_pCurrent = { nullptr };
			//m_desiredState = { CharacterStateBase::StateType::kIdle };
			//m_currentState = { CharacterStateBase::StateType::kInvalid };
		}

		SpartanStateMachine::~SpartanStateMachine()
		{
		}

		void SpartanStateMachine::Update(Objects::Character& obj, double deltaSeconds)
		{
			m_pCurrent->OnUpdate(obj, deltaSeconds);
		}
		void SpartanStateMachine::Render(SDL_Renderer* const pRenderer)
		{
			//m_pCurrent->OnRender(pRenderer);
		}

		//void SpartanStateMachine::CheckState()
		//{
		//}

		void SpartanStateMachine::Input(Objects::Character& obj, const SDL_Event& event)
		{
			CharacterStateBase* pState = m_pCurrent->OnHandleInput(obj, event);

			if (pState != nullptr)
			{
				delete m_pCurrent;
				m_pCurrent = pState;
			}
			
			m_pCurrent->OnEnter(obj);
			/*
			if (m_currentState == m_desiredState)
				return;
			
			switch (m_desiredState)
			{
			case CharacterStateBase::StateType::kIdle:
			{
				m_pCurrent = new SpartanIdleState(this);
			}
			break;
			
			case CharacterStateBase::StateType::kWalk:
			{
				m_pCurrent = new SpartanWalkState(this);
			}
			break;

			case CharacterStateBase::StateType::kAttack:
			{
				// TODO: Change to attack state
				//m_pCurrent = new SpartanWalkState();
			}
			break;

			case CharacterStateBase::StateType::kDie:
			{
				// TODO: Change to die state
				//m_pCurrent = new SpartanWalkState();
			}
			break;
			}
			*/
			

			//m_currentState = m_desiredState;
			//m_pCurrent->OnEnter(this);
		}
	}
}