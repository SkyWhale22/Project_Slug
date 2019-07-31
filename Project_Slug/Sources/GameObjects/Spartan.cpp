#include <iostream>
#include <SDL_image.h>

#include "Core/Application.hpp"
#include "GameObjects/Spartan.hpp"
#include "GameObjects/Weapon.hpp"
#include "Managers/MouseManager.hpp"
#include "Core/Camera.hpp"


namespace Slug
{
	namespace Objects
	{
		Spartan::Spartan()
			: m_pWeapon(new Weapon(0, 0))
		{
			m_transform = Utils::Transform(0, 0, 0);

			Initialize();
		}

		Spartan::Spartan(float posX, float posY)
			: m_pWeapon(new Weapon(posX, posY))
		{
			m_transform = Utils::Transform(posX, posY, 0);

			Initialize();
		}

		Spartan::Spartan(const Vector2& initPos)
			: m_pWeapon(new Weapon(initPos))
		{
			m_transform = Utils::Transform(initPos, 0);
			
			Initialize();
		}

		Spartan::~Spartan()
		{
			delete m_pWeapon;
			m_pWeapon = nullptr;

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

			//- Set physical sprite path
			m_pSpritePath = "Resources/Sprites/Spartan.png";
			SetTexture(m_pSpritePath);

			//- XML reader
			m_doc.LoadFile("Includes/Datas/SpriteData.xml");
			m_pRoot = m_doc.RootElement();

			//- Init Animation and set its state to idle
			InitAnimation();
			SetAnimation((int)AnimationType::kIdle);
		}

		void Spartan::Update(double deltaSeconds)
		{
			if (m_moveDir.m_up)
			{
				if ((int)m_destRect.y > 0)
					m_transform.SetPositionY(m_transform.GetPositionY() - (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_down)
			{
				if ((int)m_destRect.y + m_destRect.h < s_kWindowHeight)
					m_transform.SetPositionY(m_transform.GetPositionY() + (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_right)
			{
				if ((int)m_destRect.x + m_destRect.w < s_kWindowWidth)
					m_transform.SetPositionX(m_transform.GetPositionX() + (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_left)
			{
				if ((int)m_destRect.x > 0)
					m_transform.SetPositionX(m_transform.GetPositionX() - (float)(s_kMovingSpeed * deltaSeconds));
			}

			if (m_moveDir.m_up || m_moveDir.m_down || m_moveDir.m_right || m_moveDir.m_left)
				SetAnimation((int)AnimationType::kWalk);
			else
				SetAnimation((int)AnimationType::kIdle);



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

			//m_transform.Update(deltaSeconds);

			//Vector2 test = { m_destRect.x, m_destRect.y };

			TestFunction(deltaSeconds);

			m_pWeapon->GetTransform().SetPosition(GetTransform().GetPosition());
			m_pWeapon->FindDegreesToCursor(Managers::MouseManager::GetInstance()->GetMousePosition());
			m_pWeapon->Update(deltaSeconds);

		}

		/**
		 * \brief 
		 * ---------------------------------------------------------------------------\n
		 * Renderring function\n
		 * ---------------------------------------------------------------------------\n
		 * \param pRenderer  SDL's renderer
		 **/
		void Spartan::Render(SDL_Renderer* const pRenderer)
		{
			// Render object
			
			Vector2 cameraPos = Core::Camera::GetInstance()->GetPosition();
#if DEBUG
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

#if DEBUG
			// --- Actual position ---
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
			SDL_Rect dest = { (int)m_transform.GetPositionX() - 5, (int)m_transform.GetPositionY() - 5, 10, 10 };
			SDL_RenderFillRect(pRenderer, &dest);
#endif	
			m_pWeapon->Render(pRenderer);
		}

		void Spartan::SetTexture(const char* pSpritePath)
		{
			if (m_pTexture)
				SDL_DestroyTexture(m_pTexture);

			m_pTexture = IMG_LoadTexture(Core::Application::GetRenderer(), "Resources/Sprites/Spartan.png");
		}

		void Spartan::InitAnimation()
		{
			XMLElement* pSpartanDataChunk = m_pRoot->FirstChildElement("Spartan");
			XMLElement* pAnimation = pSpartanDataChunk->FirstChildElement("Animation");
			
			//- XMLElement* pSpriteSize = m_pRoot->FirstChildElement("SpriteSize");
			const int spriteWidth	= pSpartanDataChunk->FirstChildElement("SpriteSize")->IntAttribute("width");
			const int spriteHeight	= pSpartanDataChunk->FirstChildElement("SpriteSize")->IntAttribute("height");

			for (int animIndex = 0; animIndex < s_kTotalAnimSpartan; ++animIndex)
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
				case AnimationType::kAttack:
				{
					pType = pAnimation->FirstChildElement("Attack");

					anim.m_animationSpeed = 1;
					anim.m_shouldLoop = false;
				}
				break;
				case AnimationType::kDie:
				{
					pType = pAnimation->FirstChildElement("Die");

					anim.m_animationSpeed = 1;
					anim.m_shouldLoop = false;
				}
				break;
				}

				// Get count of frame.
				maxFrame = pType->IntAttribute("frame");

				// Get where the sprite starts. 
				position.m_x = pType->IntAttribute("posX");
				position.m_y = pType->IntAttribute("posY");

				//? What are these for?
				//anim.m_center.m_x = pType->IntAttribute("centerX");
				//anim.m_center.m_y = pType->IntAttribute("centerY");
				//position.m_x *= (int)pSpriteSize->GetText();
				//position.m_y *= (int)pSpriteSize->GetText();


				for (int frameIndex = 0; frameIndex < maxFrame; ++frameIndex)
				{
					Frame frame;
					frame.m_sourcePosition = SDL_Rect{ (int)(position.m_x + (frameIndex * spriteWidth)), (int)(position.m_y), spriteWidth, spriteHeight };
					//frame.m_sourcePosition = SDL_Rect{ (int)(position.m_x + (frameIndex * SIZE_SPRITE)), (int)(position.m_y), SIZE_MARCO_WIDTH, SIZE_MARCO_HEIGHT };

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
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{

				case SDLK_w:
				{
					m_moveDir.m_up = true;
				}
				break;
				case SDLK_a:
				{
					m_moveDir.m_left = true;
				}
				break;
				case SDLK_s:
				{
					m_moveDir.m_down = true;
				}
				break;
				case SDLK_d:
				{
					m_moveDir.m_right = true;
				}
				break;
				}
			}

			if (event.type == SDL_KEYUP && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				{
					m_moveDir.m_up = false;
					//m_transform.SetVelocityY(0);
				}
				break;
				case SDLK_a:
				{
					m_moveDir.m_left = false;
					//m_transform.SetVelocityX(0);
				}
				break;
				case SDLK_s:
				{
					m_moveDir.m_down = false;
					//m_transform.SetVelocityY(0);
				}
				break;
				case SDLK_d:
				{
					m_moveDir.m_right = false;
					//m_transform.SetVelocityX(0);
				}
				break;
				}
			}
		}

		void Spartan::TestFunction(double deltaSeconds)
		{
			Animation* pCurrentAnim = &m_animMap[m_currentAnim];
			m_frameTimer += deltaSeconds * pCurrentAnim->m_animationSpeed;

			if (m_frameTimer >= pCurrentAnim->m_frameDuration)
			{
				// GoTo Next Frame!
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
			}

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
		}

	}
}
 