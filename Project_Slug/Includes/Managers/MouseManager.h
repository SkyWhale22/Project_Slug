#pragma once
#include "Includes/Utils/Utils.h"
#include <memory>

namespace Slug
{
	namespace Managers
	{
		class MouseManager
		{

		private:
			Vector2 m_mousePosition;
			static std::shared_ptr<MouseManager> m_pInstance;
			bool m_isClicked;

			MouseManager();
			~MouseManager();

		public:
			static std::shared_ptr<MouseManager> GetInstance();

			// Templated function for setting mouse's current coordinate.
			template<typename type>
			void SetPosition(type x, type y);

			bool IsClicked() const { return m_isClicked; }
			void SetClicked(bool set) { m_isClicked = set; }

			// Destory Instance.
			void Destroy();
		};
	}
}

