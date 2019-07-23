#pragma once

#include <GameStates/GameState.hpp>

namespace Slug
{
	namespace UI
	{
		class UIButton;
	}

	namespace Objects
	{
		class Spartan;
	}

	namespace GameStates
	{
		class MainTitleScene : public GameState
		{
			// ----- Member Variables -----
		private:
			// ==== Buttons ====
			UI::UIButton* m_pStart;
			UI::UIButton* m_pSetting;
			UI::UIButton* m_pQuit;

			// ==== Objects ====

			// ----- Member Functions -----
		public:
			MainTitleScene();
			virtual ~MainTitleScene() override;

			// Inherited via GameState
			virtual void OnEnter(GameStateMachine* pStateMachine)	override;
			virtual void OnExit()									override;
			virtual void OnUpdate(double deltaSeconds)				override;
			virtual void OnHandleInput(const SDL_Event& event)		override;
			virtual void OnRender(SDL_Renderer* const pRenderer)	override;
		};

	}
}

