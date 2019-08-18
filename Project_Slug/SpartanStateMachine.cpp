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
			m_pCurrent = new SpartanIdleState();
		}

		SpartanStateMachine::~SpartanStateMachine()
		{
			delete m_pCurrent;
			m_pCurrent = nullptr;
		}

		void SpartanStateMachine::Update(Objects::Character& obj, double deltaSeconds)
		{
			m_pCurrent->OnUpdate(obj, deltaSeconds);
		}

		void SpartanStateMachine::Input(Objects::Character& obj, const SDL_Event& event)
		{
			CharacterStateBase* pState = m_pCurrent->OnHandleInput(obj, event);

			if (pState != nullptr)
			{
				delete m_pCurrent;
				m_pCurrent = pState;
			}
			
			m_pCurrent->OnEnter(obj);		
		}
	}
}