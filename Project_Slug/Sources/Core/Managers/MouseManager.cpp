#include "Includes/Managers/MouseManager.h"

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

		std::shared_ptr<MouseManager> MouseManager::GetInstance()
		{
			// Check does application isn't initialized
			if (m_pInstance == nullptr)
			{
				m_pInstance = std::make_shared<MouseManager>();
			}

			return m_pInstance;
		}
	}
}