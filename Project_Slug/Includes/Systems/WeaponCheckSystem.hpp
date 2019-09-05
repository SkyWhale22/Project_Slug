#pragma once
#include <Systems/SystemBase.hpp>

namespace Slug::Systems
{
	class WeaponCheckSystem : public SystemBase
	{
	public:
		WeaponCheckSystem();
		virtual ~WeaponCheckSystem() override;
		
		// Inherited via SystemBase
		virtual void OnNotify(Slug::Objects::Character* pSubject);
	};
}

