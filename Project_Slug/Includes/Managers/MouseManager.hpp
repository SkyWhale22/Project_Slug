#pragma once
#include "Utils/Utils.hpp"
#include "Core/Singleton.hpp"
#include <memory>

namespace Slug
{
	namespace Managers
	{
		class MouseManager : public Core::Singleton<MouseManager>
		{

		private:
			Vector2 m_mousePosition;
			bool m_isClicked;


		public:
			MouseManager();
			~MouseManager();

			// Templated function for setting mouse's current coordinate.
			template<typename type>
			void SetPosition(type x, type y);
			void SetPosition(Vector2 pos);

			bool IsClicked() const { return m_isClicked; }
			void SetClicked(bool set) { m_isClicked = set; }
			void PrintClikedPos();
			Vector2 GetMousePosition() const { return m_mousePosition; }
		};
		template<typename type>
		void MouseManager::SetPosition(type x, type y)
		{
			m_mousePosition.m_x = (float)x;
			m_mousePosition.m_y = (float)y;
		}
	}
}

