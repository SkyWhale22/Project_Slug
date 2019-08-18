#pragma once
//---------------------------------------------------------------------------------------------------
// Core
//---------------------------------------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <tuple>

namespace Slug
{
	namespace Utils
	{
		template<class Type>
		class IPoolable
		{
		protected:
			int m_id;
			bool m_inUse;
			Type* m_pPrev;
			Type* m_pNext;

		public:
			virtual ~IPoolable() = 0 {}

			virtual void Reset() = 0;
			virtual void PrintStatus() = 0;

			virtual Type* GetNext() = 0;
			virtual Type* GetPrev() = 0;

			virtual void SetNext(Type* pObject) = 0;
			virtual void SetPrev(Type* pObject) = 0;

			void SetID(int id) { m_id = id; }
			bool IsUse() const { return m_inUse; }
			void SetInUse(bool set) { m_inUse = set; }
		};

		// Very very very very simple version of templated memory pool
		// TODO: 
		template <class Type>
		class TMemoryPool
		{
		private:
			constexpr static size_t s_kMaxSize = 100;
			int m_freeIndex;

			Type m_objects[s_kMaxSize];
			Type* m_freeListHead;
			Type* m_inUseListHead;

		public:
			TMemoryPool()
				: m_freeIndex(-1)
			{
				static_assert(std::is_base_of<IPoolable<Type>, Type>::value, "Must be poolable object");
				m_freeListHead = &m_objects[0];
			}

			~TMemoryPool()
			{
			}

			void Create()
			{
				m_freeListHead = &m_objects[0];
				for (int i = 0; i < s_kMaxSize - 1; ++i)
				{
					m_objects[i].SetID(i);
					m_objects[i].SetNext(&m_objects[i + 1]);
				}

				m_objects[s_kMaxSize - 1].SetID(s_kMaxSize - 1);
				m_objects[s_kMaxSize - 1].SetNext(nullptr);
			}

			inline void Print()
			{
				for (int index = 0; index < s_kMaxSize; ++index)
				{
					m_objects[index].PrintStatus();
				}
			}

			void PrintInUseList()
			{
				std::cout << "------------------------------------" << std::endl;
				std::cout << "               In Use               " << std::endl;
				std::cout << "------------------------------------" << std::endl;

				Type* pHead = m_inUseListHead;
				while (pHead)
				{
					pHead->PrintStatus();
					pHead = pHead->GetNext();
				}
			}

			void PrintFreeList()
			{
				std::cout << "------------------------------------" << std::endl;
				std::cout << "               Free                 " << std::endl;
				std::cout << "------------------------------------" << std::endl;

				Type* pHead = m_freeListHead;
				while (pHead)
				{
					pHead->PrintStatus();
					pHead = pHead->GetNext();
				}
			}

			void Update(float deltaSeconds)
			{
				for (int index = 0; index < s_kMaxSize; ++index)
				{
					if (!m_objects[index].IsUse())
					{
						// Remove dead object and move it to head of free list.
						m_objects[index].SetNext(m_freeListHead);
						m_freeListHead = &m_objects[index];
					}
				}
			}

			Type* Get()
			{
				if (m_freeListHead == nullptr)
				{
					return nullptr;
				}

				Type* pObject = m_freeListHead;
				m_freeListHead = m_freeListHead->GetNext();
				m_freeListHead->SetPrev(nullptr);
				pObject->SetNext(nullptr);

				if (m_inUseListHead == nullptr)
				{
					m_inUseListHead = pObject;
				}
				else
				{
					pObject->SetNext(m_inUseListHead);
					m_inUseListHead->SetPrev(pObject);
					m_inUseListHead = pObject;
				}

				pObject->SetInUse(true);
				return pObject;
			}

			void CollectUnusedObject()
			{
				// Get head node from in use list.
				Type* pCurrent = m_inUseListHead;
				Type* pNext = nullptr;

				while(pCurrent)
				{
					pNext = pCurrent->GetNext();

					if (!pCurrent->IsUse()) // When it isn't used.
						Return(pCurrent);

					pCurrent = pNext;
				}
			}

			void Return(Type* pObject)
			{
				pObject->SetInUse(false);

				// Case 1. When node was head of in use list.
				if (pObject == m_inUseListHead)
				{
					m_inUseListHead = m_inUseListHead->GetNext();

					if (m_inUseListHead)
						m_inUseListHead->SetPrev(nullptr);
				}

				// Case 2. When node was tail.
				else if (pObject->GetNext() == nullptr)
				{
					pObject->GetPrev()->SetNext(nullptr);
				}

				// Case 3. When the node was between two other nodes.
				else if (pObject->GetNext() && pObject->GetPrev())
				{
					pObject->GetPrev()->SetNext(pObject->GetNext());
					pObject->GetNext()->SetPrev(pObject->GetPrev());
				}

				// Common
				pObject->SetNext(m_freeListHead);
				pObject->SetPrev(nullptr);
				m_freeListHead->SetPrev(pObject);
				m_freeListHead = pObject;
			}

			Type* GetInUseListHead() { return m_inUseListHead; }
			Type* GetFreeListHead() { return m_freeListHead; }
		};

		
	}
}


namespace Test
{
	// The Object Pool
	template <typename Type, typename... Args>
	class ObjectPool
	{
		//--- Member Variables ---
	public:
		template <typename Type> using Deleter = std::function<void(Type*)>; // Deleter for unique_ptr
		template <typename Type> using PointerType = std::unique_ptr<Type, Deleter<Type>>;

	private:
		std::size_t m_maxSize; // Maximum size of object pool
		std::size_t m_available; // Currently available number of objects.
		std::size_t m_size;
		std::stack<PointerType<Type>> m_pool; // A stack of unique_ptr
		std::tuple<Args...> m_args;

		//--- Member functions ---
	private:
		// Adds a new object to the pool
		void Add(Type* pObject = nullptr)
		{
			if (pObject == nullptr)
			{
				pObject = CreateWithParams(std::index_sequence_for<Args...>());
				++m_size;
			}
			else
			{
				pObject->Reset();
				++m_available;
			}

			PointerType<Type> inst(pObject, [this](Type* ptr)
				{
					// This is the custom deleter of the unique_ptr.
					// When the object is deleted in the callers context, it will be
					// returned back to the pool by utilizing the Add function
					Add(ptr);
				});

			m_pool.push(std::move(inst));
		}

		template <std::size_t... Is>
		Type* CreateWithParams(const std::index_sequence<Is...>&)
		{
			return new Type(std::get<Is>(m_args)...);
		}

		// Initializes the pool
		void Initialize(std::size_t init_size)
		{
			for (std::size_t i = 0; i < init_size; ++i)
			{
				Add();
			}
		}
	public:
		ObjectPool(std::size_t init_size = 0, std::size_t max_size = 10, Args && ... args)
			: m_maxSize{ max_size }
			, m_available{ max_size }
			, m_size{ 0 }
			, m_args{ args... }
		{
			static_assert(std::is_base_of<Slug::Utils::IPoolable, Type>::value, "Must be poolable object");
			Initialize(init_size);
		}

		PointerType<Type> Get()
		{
			if (m_pool.empty())
			{
				if (m_available == 0)
				{
					return nullptr;
				}
				Add();
			}
			--m_available;
			auto inst = std::move(m_pool.top());
			m_pool.pop();
			return std::move(inst);
		}

		std::size_t Free() { return m_available; }
		std::size_t MaxSize() { return m_maxSize; }
		std::size_t Size() { return m_size; }
		bool Empty() { return m_pool.empty(); }
	};
}

