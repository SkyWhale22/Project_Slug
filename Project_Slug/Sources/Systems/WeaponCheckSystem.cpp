//---------------------------------------------------------------
// Core
//---------------------------------------------------------------
#include "Utils/tinyxml2.h"
#include <string_view>

//---------------------------------------------------------------
// Systems
//---------------------------------------------------------------
#include "Systems/WeaponCheckSystem.hpp"

//---------------------------------------------------------------
// Game Objects
//---------------------------------------------------------------
#include "GameObjects/Weapon.hpp"
#include "GameObjects/Character.hpp"

using Slug::Systems::WeaponCheckSystem;
using Slug::Objects::Character;
using Slug::Objects::Weapon;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

WeaponCheckSystem::WeaponCheckSystem()
{
}

WeaponCheckSystem::~WeaponCheckSystem()
{
}

void WeaponCheckSystem::OnNotify(Character* pSubject)
{
	if (!pSubject)
		return;

	Weapon* pCurWeapon = pSubject->GetCurrentWeapon();

	if (!pCurWeapon)
		return;

	std::string_view type = pCurWeapon->ConvTypeToStr();

	XMLDocument doc;
	doc.LoadFile("Includes/Data/ObjectStatus.xml");
	
	XMLElement* pRoot = doc.RootElement();
	XMLElement* pWeaponStats = pRoot->FirstChildElement("Weapon")->FirstChildElement(type.data());

	size_t numClipMax = pWeaponStats->IntAttribute("Clip");
	size_t numToReload = numClipMax - pCurWeapon->GetRemainingBulletNum();
	
	// TODO: Complete reloading logic.
}
	