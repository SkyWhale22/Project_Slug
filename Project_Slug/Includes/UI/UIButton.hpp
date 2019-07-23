#pragma once
#include <functional>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

namespace Slug
{
	namespace UI
	{
		//=====================================================
		// Interface of base UIButton
		//=====================================================
		class UIButton
		{
		// ----- Member Variables -----
		private:
			using OnMouseEnter	= std::function<void()>;
			using OnMouseExit	= std::function<void()>;
			using OnClickEnter	= std::function<void()>;
			using OnClickExit	= std::function<void()>;

			OnMouseEnter	m_handleMouseEnter;
			OnMouseExit		m_handleMouseExit;
			OnClickEnter	m_handleClickEnter;
			OnClickExit		m_handleClickExit;

			SDL_Rect		m_destRect;
			SDL_Texture*	m_pSelectedTexture;
			SDL_Texture*	m_pUnselectedTextrue;

			bool			m_isSelected;
			const char*		m_pButtonName;

		// ----- Member Functions ----
		public:
			UIButton();
			UIButton(SDL_Rect pos);
			~UIButton();

			void PostInit();
			void Update(double deltaSeconds);
			void Render(SDL_Renderer* const pRenderer);

			bool CheckMousePosition(int x, int y);

			void SetMouseEnter(std::function<void()> func)	{ m_handleMouseEnter = func;	}
			void SetMouseExit(std::function<void()> func)	{ m_handleMouseExit = func;		}
			void SetClickEnter(std::function<void()> func)	{ m_handleClickEnter = func;	}
			void SetClickExit(std::function<void()> func)	{ m_handleClickExit = func;		}
		};
	}
}

