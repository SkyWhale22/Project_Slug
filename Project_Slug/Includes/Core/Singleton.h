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
			static std::unique_ptr<Type> m_pInstance;
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
					m_pInstance.reset(new Type);
				}
			);

			return m_pInstance.get();
		}
	}
}

template<class Type>
std::unique_ptr<Type> Slug::Core::Singleton<Type>::m_pInstance = nullptr;

template<class Type>
std::once_flag Slug::Core::Singleton<Type>::m_onlyOnce;
