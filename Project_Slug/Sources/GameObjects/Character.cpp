#include <SDL_image.h>

#include "Core/Application.hpp"
#include "GameObjects/Character.hpp"
#include "GameObjects/Weapon.hpp"
namespace Slug
{
	namespace Objects
	{
		//-------------------------------------
		// D'tor
		//-------------------------------------
		Character::~Character()
		{
		}

		void Character::UpdateAnim(double deltaSeconds)
		{
			Animation* pCurrentAnim = &m_animMap[m_currentAnim];
			m_frameTimer += (float)(deltaSeconds * pCurrentAnim->m_animationSpeed);

			if (m_frameTimer >= pCurrentAnim->m_frameDuration)
			{
				// GoTo Next Frame!
				m_frameTimer -= pCurrentAnim->m_frameDuration;
				++m_currentFrameIndex;

				if (pCurrentAnim->m_shouldLoop)
				{
					m_currentFrameIndex %= pCurrentAnim->m_frames.size();
				}
				else if (m_currentFrameIndex > pCurrentAnim->m_frames.size())
				{
					// At the end of the anim, and it's not supposed to loop
					m_currentFrameIndex = pCurrentAnim->m_frames.size() - 1;
				}
			}
		}

		void Character::SetWeapon(Weapon* pWeapon)
		{
			if (!pWeapon)
				return;

			m_pCurWeapon = pWeapon;
		} 
	}
}
