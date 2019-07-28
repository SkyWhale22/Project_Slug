#pragma once
#include "Utils/Utils.hpp"

namespace Slug
{
	namespace Utils
	{
		class Transform
		{
		private:
			Vector2		m_position;
			Vector2		m_velocity;
			double		m_angle;

		public:
			Transform();
			Transform(const Transform& kInstance);
			Transform(float x, float y, double angle);
			Transform(const Vector2& pos, double angle);
			~Transform();

			void Update(double deltaSeconds);
			const Vector2 GetPosition();
			const Vector2& GetPositionRef();

			void SetPosition(const Vector2& kPos);
			void SetPosition(float x, float y);

			const float GetPositionX() const;
			const float GetPositionY() const;
			const double GetAngle() const;

			void SetPositionX(const float x);
			void SetPositionY(const float y);

			void SetVelocityX(float x);
			void SetVelocityY(float y);

			void Rotate(double angle);

			bool operator==(const Transform& kRhs);
			Transform operator+(const Transform& rhs);
			void operator=(const Transform& kRhs);
		};
	}
}

