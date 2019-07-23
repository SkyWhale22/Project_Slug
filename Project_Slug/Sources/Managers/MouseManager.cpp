#include "Managers/MouseManager.hpp"
#include <iostream>

namespace Slug
{
	namespace Managers
	{
		MouseManager::MouseManager()
			: m_isClicked(false)
		{
		}

		MouseManager::~MouseManager()
		{
		}

		void MouseManager::SetPosition(Vector2 pos)
		{
			m_mousePosition = pos;
		}

		void MouseManager::PrintClikedPos()
		{
			std::cout << "Cliked on x: " << m_mousePosition.m_x << ", y: " << m_mousePosition.m_y << "." << std::endl;
		}


	}
}