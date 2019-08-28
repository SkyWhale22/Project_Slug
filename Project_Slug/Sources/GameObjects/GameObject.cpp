#include "GameObjects/GameObject.hpp"
#include "Core/Application.hpp"
#include <SDL_image.h>
namespace Slug
{
	namespace Objects
	{
		void GameObject::SetTexture(const char* pSpritePath)
		{
			if (!pSpritePath)
				return;

			//if (this->m_pTexture != nullptr)
				//SDL_DestroyTexture(m_pTexture);

			m_pTexture = IMG_LoadTexture(Core::Application::GetRenderer(), pSpritePath);
		}
	}
}
