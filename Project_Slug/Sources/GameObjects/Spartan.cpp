//-----------------------------------------------------------------
// Core
//-----------------------------------------------------------------
#include <iostream>
#include "Core/Application.hpp"
#include "Core/Camera.hpp"

//-----------------------------------------------------------------
// Objects
//-----------------------------------------------------------------
#include "GameObjects/Spartan.hpp"
#include "GameObjects/Weapons/AssaultRifle.hpp"
#include "GameObjects/Weapons/Magnum.hpp"
#include "GameObjects/Weapons/Bullet.hpp"

//-----------------------------------------------------------------
// Managers
//-----------------------------------------------------------------
#include "Managers/MouseManager.hpp"
#include "Managers/BulletPoolManager.hpp"

//-----------------------------------------------------------------
// States
//-----------------------------------------------------------------
#include "CharacterStates/CharacterStateBase.hpp"
#include "CharacterStates/SpartanStates/SpartanStateMachine.hpp"

//-----------------------------------------------------------------
// Utils
//-----------------------------------------------------------------
#include "Utils/ObjectPool.h"

//#include "CharacterStates/SpartanStates/SpartanIdleState.hpp"
//#include "CharacterStates/SpartanStates/SpartanWalkState.hpp"

std::string TestFunc()
{
	return "testestst";
}

namespace Slug
{
	namespace Objects
	{
		Spartan::Spartan()
			: m_pStateMachine(new CharacterStates::SpartanStateMachine())
			//, m_pCurrentState(new CharacterStates::SpartanIdleState())
		{
			m_transform = Utils::Transform(0, 0, 0);

			Initialize();
		}

		Spartan::Spartan(float posX, float posY)
			: m_pStateMachine(new CharacterStates::SpartanStateMachine())
			//, m_pCurrentState(new CharacterStates::SpartanIdleState())
		{
			m_transform = Utils::Transform(posX, posY, 0);

			Initialize();
		}

		Spartan::Spartan(const Vector2& initPos)
			: m_pStateMachine(new CharacterStates::SpartanStateMachine())
			//, m_pCurrentState(new CharacterStates::SpartanIdleState())
		{
			m_transform = Utils::Transform(initPos, 0);
			
			Initialize();
		}

		Spartan::~Spartan()
		{
			//delete m_pWeapon;
			//m_pWeapon = nullptr;

			delete m_pStateMachine;
			m_pStateMachine = nullptr;

			SDL_DestroyTexture(m_pTexture);
		}

		//--------------------------------------------------------------------
		// Initialization function.
		// This function contains common things that should be initialized
		// in constructors.
		//--------------------------------------------------------------------
		void Spartan::Initialize()
		{
			//- Dest to render
			m_destRect = { (int)(m_transform.GetPositionX() - (s_kSpriteWidth * 0.5)), (int)(m_transform.GetPositionY() - (s_kSpriteHeight * 0.5)), s_kSpriteWidth, s_kSpriteHeight };

			m_doc.LoadFile("Includes/Data/ObjectStatus.xml");
			m_pRoot = m_doc.RootElement();

			XMLElement* pSpartanStats = m_pRoot->FirstChildElement("Characters")->FirstChildElement("Spartan");

			//- Set status.
			this->GetStats().m_hp			= pSpartanStats->IntAttribute("Health");
			this->GetStats().m_shield		= pSpartanStats->IntAttribute("Shield");
			this->GetStats().m_movingSpeed	= pSpartanStats->IntAttribute("Speed");

			//- Set initial weapons;
			m_pWeapons[0] = std::make_unique<Magnum>(this->GetTransform().GetPosition());
			m_pWeapons[1] = std::make_unique<AssaultRifle>(this->GetTransform().GetPosition());
			this->SetWeapon(m_pWeapons[0].get());

			//- XML reader
			m_doc.LoadFile("Includes/Data/SpriteData.xml");
			m_pRoot = m_doc.RootElement();

			//- Initialized sprite, and animation
			InitAnimation();
		}

		void Spartan::Update(double deltaSeconds)
		{
			m_pStateMachine->Update(*this, deltaSeconds);
					   			 		  
			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();

			m_destRect.x = (int)(m_transform.GetPositionX() - (s_kSpriteWidth / 2)) - (int)cameraPos.m_x;
			m_destRect.y = (int)(m_transform.GetPositionY() - (s_kSpriteHeight / 2)) - (int)cameraPos.m_y;

			if (m_destRect.x < 0)
				m_destRect.x = 0;
			if (m_destRect.y < 0)
				m_destRect.y = 0;

			if (m_destRect.x > s_kWindowWidth)
				m_destRect.x = s_kWindowWidth - m_destRect.w;
			if (m_destRect.y > s_kWindowHeight)
				m_destRect.y = s_kWindowHeight - m_destRect.h;

			UpdateAnim(deltaSeconds);

			Weapon* pCurWeapon = this->GetCurrentWeapon();
			pCurWeapon->GetTransform().SetPosition(GetTransform().GetPosition());

			// Update weapon data
			Vector2 mousePosition = Managers::MouseManager::GetInstance()->GetMousePosition();
			SDL_Rect destRect = pCurWeapon->GetDestRect();
		
			pCurWeapon->GetTransform().Rotate(Utils::FindDegreesToCursor(mousePosition, destRect));
			pCurWeapon->Update(deltaSeconds);
		}

		 //---------------------------------------------------------------------------
		 // Renderring function
		 //---------------------------------------------------------------------------
		 // pRenderer : SDL's renderer
		 //---------------------------------------------------------------------------
		void Spartan::Render(SDL_Renderer* const pRenderer)
		{
			// Render object
			
			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();
#if DEBUG_COLLIDER
			// --- Position to render ---
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(pRenderer, &m_destRect);
#endif
			const float transformX	= GetTransform().GetPositionX() - cameraPos.m_x;
			const float mouseX = Managers::MouseManager::GetInstance()->GetMousePosition().m_x;

			SDL_Rect* pSrc = &m_animMap[m_currentAnim].m_frames[m_currentFrameIndex].m_sourcePosition;
			m_resourceRect = *pSrc;

			SDL_RendererFlip renderFlip = (transformX < mouseX) ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

			// --- Render Sprite ---
			SDL_RenderCopyEx(pRenderer, m_pTexture, &m_resourceRect, &m_destRect, 0, 0, renderFlip); 

#if DEBUG_POSITION
			// --- Actual position ---
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
			SDL_Rect dest = { (int)m_transform.GetPositionX() - 5, (int)m_transform.GetPositionY() - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);
#endif	
			this->GetCurrentWeapon()->Render(pRenderer);
		}

		void Spartan::InitAnimation()
		{
			XMLElement* pSpartanDataChunk = m_pRoot->FirstChildElement("Spartan");
			XMLElement* pAnimation = pSpartanDataChunk->FirstChildElement("Animation");
			
			//- Set physical sprite path
			m_pSpritePath = pSpartanDataChunk->FirstChildElement("SpritePath")->GetText();
			//m_pSpritePath = "Resources/Sprites/Spartan.png";
			SetTexture(m_pSpritePath);

			//- XMLElement* pSpriteSize = m_pRoot->FirstChildElement("SpriteSize");
			const int spriteWidth	= pSpartanDataChunk->FirstChildElement("SpriteSize")->IntAttribute("width");
			const int spriteHeight	= pSpartanDataChunk->FirstChildElement("SpriteSize")->IntAttribute("height");

			for (int animIndex = 0; animIndex < (int)AnimationType::kTotal; ++animIndex)
			{
				Animation anim;
				int maxFrame;
				Vector2 position;

				XMLElement* pType = nullptr;

				switch ((AnimationType)animIndex)
				{
				case AnimationType::kIdle:
				{
					pType = pAnimation->FirstChildElement("Idle");

					anim.m_animationSpeed = 1;
					anim.m_shouldLoop = true;
					anim.m_frameDuration = 0.1f;
				}
				break;
				case AnimationType::kWalk:
				{
					pType = pAnimation->FirstChildElement("Walk");

					anim.m_animationSpeed = 0.99f;
					anim.m_shouldLoop = true;
					anim.m_frameDuration = 0.1f;
				}
				break;
				case AnimationType::kDie:
				{
					pType = pAnimation->FirstChildElement("Die");

					anim.m_animationSpeed = 0.0f;
					anim.m_shouldLoop = false;
					anim.m_animationSpeed = 1;
				}
				break;
				}

				// Get count of frame.
				maxFrame = pType->IntAttribute("frame");

				// Get where the sprite starts. 
				position.m_x = pType->IntAttribute("posX");
				position.m_y = pType->IntAttribute("posY");

				for (int frameIndex = 0; frameIndex < maxFrame; ++frameIndex)
				{
					Frame frame;
					frame.m_sourcePosition = SDL_Rect{ (int)(position.m_x + (frameIndex * spriteWidth)), (int)(position.m_y), spriteWidth, spriteHeight };
					anim.m_frames.push_back(frame);
				}

 				m_animMap.emplace((AnimationType)animIndex, anim);
			}
		}

		void Spartan::SetAnimation(int type)
		{
			if(m_currentAnim != (AnimationType)type)
			{
				m_currentFrameIndex = 0;
				m_currentAnim = (AnimationType)type;
				m_frameTimer = 0;
			}
		}

		void Spartan::Input(const SDL_Event& event)
		{
			m_pStateMachine->Input(*this, event);

#if DEBUG_WEAPON_SWAP
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
				{
					//m_pWeapon = new Magnum(this->GetTransform().GetPosition());
					this->SetWeapon(m_pWeapons[0].get());
				}
				break;
				case SDLK_2:
				{
					//m_pWeapon = new AssaultRifle(this->GetTransform().GetPosition());
					this->SetWeapon(m_pWeapons[1].get());
				}
				break;
				case SDLK_e:
				{
					
				}
				break;

				}
			}

 			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();

				SDL_Point point = this->GetCurrentWeapon()->GetMuzzelPoint();
				Vector2 muzzel = { point.x + (int)cameraPos.m_x, point.y + (int)cameraPos.m_y };

				int adjust = 90;
				double angle = this->GetCurrentWeapon()->GetTransform().GetAngle() + adjust;

				//const std::string_view& test = m_pWeapon->ConvTypeToStr();
				//std::string test = m_pWeapon->ConvTypeToStr();
				Managers::BulletPoolManager::GetInstance()->GetBullet(muzzel, angle)
 														  ->SetBulletData(this->GetCurrentWeapon()->ConvTypeToStr());
			}
#endif
		}
	}
}

//=====================================================================================================================================================================================================================
			/*
			Animation* pCurrentAnim = &m_animMap[m_currentAnim];
			m_frameTimer += deltaSeconds * pCurrentAnim->m_animationSpeed;

			if (m_frameTimer >= pCurrentAnim->m_frameDuration)
			{
				// GoTo Next frame!
				m_frameTimer -= pCurrentAnim->m_frameDuration;

				++m_currentFrameIndex;

				if (pCurrentAnim->m_shouldLoop)
				{
					m_currentFrameIndex %= pCurrentAnim->m_frames.size();
				}
				else if (m_currentFrameIndex >= pCurrentAnim->m_frames.size())
				{
					// At the end of the anim, and it's not supposed to loop
					m_currentFrameIndex = pCurrentAnim->m_frames.size() - 1;
				}
			}*/

			// ===== Code Before State Machine ========================================================================================
			
			// Update()
			//if (m_moveDir.m_up)
			//{
			//	if ((int)m_destRect.y > 0)
			//		m_transform.SetPositionY(m_transform.GetPositionY() - (float)(s_kMovingSpeed * deltaSeconds));
			//}

			//if (m_moveDir.m_down)
			//{
			//	if ((int)m_destRect.y + m_destRect.h < s_kWindowHeight)
			//		m_transform.SetPositionY(m_transform.GetPositionY() + (float)(s_kMovingSpeed * deltaSeconds));
			//}

			//if (m_moveDir.m_right)
			//{
			//	if ((int)m_destRect.x + m_destRect.w < s_kWindowWidth)
			//		m_transform.SetPositionX(m_transform.GetPositionX() + (float)(s_kMovingSpeed * deltaSeconds));
			//}

			//if (m_moveDir.m_left)
			//{
			//	if ((int)m_destRect.x > 0)
			//		m_transform.SetPositionX(m_transform.GetPositionX() - (float)(s_kMovingSpeed * deltaSeconds));
			//}

			//if (m_moveDir.m_up || m_moveDir.m_down || m_moveDir.m_right || m_moveDir.m_left)
			//{
			//	m_pStateMachine->SetDesiredState(CharacterStates::StateType::kWalk);
			//	SetAnimation((int)AnimationType::kWalk);
			//}
			//else
			//{
			//	m_pStateMachine->SetDesiredState(CharacterStates::StateType::kIdle);
			//	SetAnimation((int)AnimationType::kIdle);
			//}
			// ========================================================================================================================
