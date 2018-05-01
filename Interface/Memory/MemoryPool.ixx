#include <numeric>
#include <stdexcept>
#include <vector>

export module Maia.Utilities.Memory.MemoryPool;

namespace Maia
{
	namespace Utilities
	{
		template <class ValueT>
		class MemoryPool;

		export template <class ValueT>
		class MemoryPoolConstIterator
		{
		public:

			// Public member types:
			using ValueType = ValueT;
			using Reference = ValueT&;
			using ConstReference = const ValueT&;
			using Pointer = ValueType*;

			// Constructors:
			MemoryPoolConstIterator(Pointer element) :
				m_element(element)
			{	
			}

			// Element access:
			ConstReference operator*() const
			{
				return *m_element;
			}

		protected:

			// Friends:
			friend MemoryPool<ValueType>;

			// Members:
			Pointer m_element;

		};

		export template <class ValueT>
		class MemoryPoolIterator : public MemoryPoolConstIterator<ValueT>
		{
		public:

			// Constructors:
			MemoryPoolIterator(Pointer element) :
				MemoryPoolConstIterator(element)
			{	
			}

			// Element access:
			Reference operator*() const
			{
				return *m_element;
			}

		};

		export template <class ValueT>
		class MemoryPool
		{
		public:
			
			// Public member types:
			using SizeType = std::size_t;
			using ValueType = ValueT;
			using Reference = ValueT&;
			using ConstReference = const ValueT&;
			using Iterator = MemoryPoolIterator<ValueT>;
			using ConstIterator = MemoryPoolConstIterator<ValueT>;

			// Constructors:
			MemoryPool() noexcept = default;
			MemoryPool(const MemoryPool& other) = delete;
			MemoryPool(MemoryPool&& other) noexcept :
				m_elements(std::move(other.m_elements)),
				m_inactiveElements(std::move(other.m_inactiveElements)),
				m_numActiveElements(other.m_numActiveElements)
			{
			}
			MemoryPool(SizeType capacity) :
				m_elements(),
				m_inactiveElements(),
				m_numActiveElements(0)
			{
				Reserve(capacity);
			}

			// Copy/move assignment:
			MemoryPool& operator=(const MemoryPool& other) = delete;
			MemoryPool& operator=(MemoryPool&& other) noexcept
			{
				m_elements = std::move(other.m_elements);
				m_inactiveElements = std::move(other.m_inactiveElements);
				m_numActiveElements = std::move(other.m_numActiveElements);
			}

			// Iterators:
			Iterator Begin()
			{
				return Iterator(m_elements.data());
			}
			Iterator End()
			{
				return Iterator(m_elements.data() + Size());
			}

			// Capacity:
			bool Empty() const noexcept
			{
				return Size() == 0;
			}
			SizeType Size() const noexcept
			{
				return m_numActiveElements;
			}
			SizeType MaxSize() const noexcept
			{
				return m_elements.max_size();
			}
			void Reserve(SizeType capacity)
			{
				m_elements.reserve(capacity);
				
				m_inactiveElements.resize(capacity);
				std::iota(m_inactiveElements.begin(), m_inactiveElements.end(), 0);
			}
			SizeType Capacity() const noexcept
			{
				return m_elements.capacity();
			}

			// Modifiers:
			void Clear() noexcept
			{
				m_elements.clear();
				m_inactiveElements.clear();
				m_numActiveElements = 0;
			}
			template <class ...ArgumentsT>
			Iterator Emplace(ArgumentsT&&... arguments)
			{
				if (m_inactiveElements.empty())
				{
					throw std::out_of_range("Memory pool is full! Use the reserve method to reserve a block of memory!");
				}

				auto index = m_inactiveElements.back();
				m_inactiveElements.pop_back();
				++m_numActiveElements;

				m_elements[index] = ValueType(std::forward<ArgumentsT>(arguments)...);

				return Iterator(m_elements.data() + index);
			}
			void Erase(ConstIterator position)
			{
				--m_numActiveElements;
				m_inactiveElements.emplace_back(position.m_element - m_elements.data());

			}
			void Swap(MemoryPool<ValueType>& other) noexcept
			{
				std::swap(m_elements, other.m_elements);
				std::swap(m_inactiveElements, other.m_inactiveElements);
				std::swap(m_numActiveElements, other.m_numActiveElements);
			}

		private:

			// Friends:
			friend class ConstIterator;
			friend class Iterator;

			// Members:
			std::vector<ValueType> m_elements;
			std::vector<SizeType> m_inactiveElements;
			std::size_t m_numActiveElements = 0;

		};
	}
}
