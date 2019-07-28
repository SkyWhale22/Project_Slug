#include "Utils/Transform.hpp"
#include "..//Camera.hpp"
#include <iostream>

using namespace Slug::Utils;
using Slug::Utils::Transform;

namespace Slug
{
	namespace Utils
	{
		Transform::Transform()
			: m_position({0, 0})
			, m_angle(0)
			, m_velocity({0, 0})
		{
		}

		Transform::Transform(const Transform& kInstance)
			: m_position(kInstance.m_position)
			, m_angle(kInstance.m_angle)
			, m_velocity({ 0, 0 })
		{
		}

		Transform::Transform(float x, float y, double angle)
			: m_position({x, y})
			, m_angle(angle)
			, m_velocity({ 0, 0 })
		{
		}

		Transform::Transform(const Vector2& pos, double angle)
			: m_position(pos)
			, m_angle(angle)
			, m_velocity({ 0, 0 })
		{
		}

		Transform::~Transform()
		{
		}

		void Transform::SetPosition(const Vector2& kPos)
		{
			m_position = kPos;
		}

		void Transform::SetPosition(float x, float y)
		{
			m_position = { x, y };
		}

		void Transform::Update(double deltaSeconds)
		{
			//m_position.m_x += (float)(m_velocity.m_x * kMovingSpeed);
			//m_position.m_y += (float)(m_velocity.m_y * kMovingSpeed);
		}

		const Vector2 Transform::GetPosition()
		{
			return m_position;
		}

		const Vector2& Transform::GetPositionRef()
		{
			return m_position;
		}

		const float Transform::GetPositionX() const
		{
			return m_position.m_x;
		}

		const float Transform::GetPositionY() const
		{
			return m_position.m_y;
		}

		const double Transform::GetAngle() const
		{
			return m_angle;
		}

		void Transform::SetPositionX(const float x)
		{
			m_position.m_x = x;
		}

		void Transform::SetPositionY(const float y)
		{
			m_position.m_y = y;
		}

		void Transform::SetVelocityX(float x)
		{
			m_velocity.m_x = x;
		}

		void Transform::SetVelocityY(float y)
		{
			m_velocity.m_y = y;
		}

		void Transform::Rotate(double angle)
		{
			m_angle = angle;
		}

		bool Transform::operator==(const Transform& kRhs)
		{
			return  m_angle == kRhs.m_angle && m_position.m_x == kRhs.m_position.m_x && m_position.m_y == kRhs.m_position.m_y;
		}

		Transform Transform::operator+(const Transform& rhs)
		{
			float posX = m_position.m_x + rhs.m_position.m_x;
			float posY = m_position.m_y + rhs.m_position.m_y;
			double angle = m_angle + rhs.m_angle;

			Transform transform(posX, posY, angle);

			return transform;
		}
		void Transform::operator=(const Transform& kRhs)
		{
			m_angle = kRhs.m_angle;
			m_position = kRhs.m_position;
		}
	}
}

