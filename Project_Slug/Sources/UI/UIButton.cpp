#include "UI/UIButton.hpp"
#include <Managers/MouseManager.hpp>
#include <iostream>

namespace Slug
{
	namespace UI
	{
#pragma region None_Template
		UIButton::UIButton()
		{

		}

		UIButton::UIButton(SDL_Rect pos)
			: m_destRect(pos)
		{

		}

		UIButton::~UIButton()
		{
			SDL_DestroyTexture(m_pSelectedTexture);
			SDL_DestroyTexture(m_pUnselectedTextrue);
		}

		void UIButton::PostInit()
		{
		}

		void UIButton::Update(double deltaSeconds)
		{
		}

		void UIButton::Render(SDL_Renderer* const pRenderer)
		{
			// Change color to red
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);


			// Render button
			SDL_RenderFillRect(pRenderer, &m_destRect);
		}

		bool UIButton::CheckMousePosition(int x, int y)
		{
			SDL_Point p{ x, y };
			bool selectedNow = SDL_PointInRect(&p, &m_destRect);
			std::cout << selectedNow << std::endl;

			if (!m_isSelected && selectedNow)
			{
				m_isSelected = false;
				m_handleClickEnter();
			}
			else if (!m_isSelected && selectedNow)
			{
				m_isSelected = true;
			}

			return selectedNow;
		}
#pragma endregion None_Template

	}
}

#pragma region test
		//StartButton::StartButton(SDL_Rect pos)
		//{
		//	m_destRect = pos;
		//	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		//	std::cout << "Start Button created" << std::endl;
		//	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

		//	this->m_handleClickEnter = []()-> void
		//	{
		//		std::cout << "Start Button clikced!" << std::endl;
		//	};
		//}

		//StartButton::~StartButton()
		//{
		//	SDL_DestroyTexture(m_pSelectedTexture);
		//	SDL_DestroyTexture(m_pUnselectedTextrue);
		//}

		//void StartButton::PostInit()
		//{
		//}

		//void StartButton::Update(double deltaSeconds)
		//{	
		//}

		//void StartButton::Render(SDL_Renderer* const pRenderer)
		//{
		//	// Change color to red
		//	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

		//	// Render our "player"
		//	SDL_RenderFillRect(pRenderer, &m_destRect);
		//}
#pragma endregion test
