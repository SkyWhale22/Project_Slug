#pragma once
#include <memory>
#include <mutex>

namespace Slug
{
	namespace Core
	{
		template <class Type>
		class Singleton
		{
		//----- Member Variables -----
		private:
			static std::shared_ptr<Type> s_pInstance;
			static std::once_flag m_onlyOnce;

		public:

		//----- Member Functions -----
		private:
		protected:
			Singleton() {};
			Singleton(const Singleton&) = delete;

			//Singleton& operator= (const Singleton& rhs);

		public:
			static Type* GetInstance();
		};
			   		 
		template<class Type>
		inline Type* Singleton<Type>::GetInstance()
		{
			std::call_once(m_onlyOnce, []
				{
					s_pInstance.reset(new Type);
				}
			);

			return s_pInstance.get();
		}
	}
}

template<class Type>
std::shared_ptr<Type> Slug::Core::Singleton<Type>::s_pInstance = nullptr;

template<class Type>
std::once_flag Slug::Core::Singleton<Type>::m_onlyOnce;
