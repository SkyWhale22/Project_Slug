#pragma once
///--------------------------------------------------------------------------
/// File description
///
/// TODO: Add description here.
///--------------------------------------------------------------------------

//---------------------------------------------------------------
// Core
//---------------------------------------------------------------
#include <vector>

namespace Slug
{
	namespace Objects
	{
		class Character;
	}

	namespace Systems
	{
		class SystemBase
		{
		private:
		public:
			virtual ~SystemBase() = 0 {}

			virtual void OnNotify(Objects::Character* pSubject) = 0;
		};
	}
}

