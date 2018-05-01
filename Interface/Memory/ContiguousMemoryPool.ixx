#include <vector>

import Maia.Utilities.Memory.MemoryPool;

export module Maia.Utilities.Memory.ContiguousMemoryPool;

namespace Maia
{
	namespace Utilities
	{
		export template <class ValueT>
		class ContiguousMemoryPool
		{
		public:
			
			// Public member types:
			using SizeType = std::size_t;
			using ValueType = ValueT;
			using Reference = ValueT&;
			using ConstReference = const ValueT&;
			using Iterator = typename std::vector<ValueT>::iterator;
			using ConstIterator = typename std::vector<ValueT>::const_iterator;			

			// Constructors:
			ContiguousMemoryPool() noexcept = default;
			ContiguousMemoryPool(const ContiguousMemoryPool& other) = delete;
			ContiguousMemoryPool(ContiguousMemoryPool&& other) noexcept :
				m_elements(std::move(other.m_elements))
			{
			}
			ContiguousMemoryPool(SizeType capacity) :
				m_elements()
			{
				Reserve(capacity);
			}

			// Copy/move assignment:
			ContiguousMemoryPool& operator=(const ContiguousMemoryPool& other) = delete;
			ContiguousMemoryPool& operator=(ContiguousMemoryPool&& other) noexcept
			{
				m_elements = std::move(other.m_elements);
			}

			// Iterators:
			Iterator Begin()
			{
				return m_elements.begin();
			}
			Iterator End()
			{
				return m_elements.end();
			}

			// Capacity:
			bool Empty() const noexcept
			{
				return m_elements.empty();
			}
			SizeType Size() const noexcept
			{
				return m_elements.size();
			}
			SizeType MaxSize() const noexcept
			{
				return m_elements.max_size();
			}
			void Reserve(SizeType capacity)
			{
				m_elements.reserve(capacity);
			}
			SizeType Capacity() const noexcept
			{
				return m_elements.capacity();
			}

			// Modifiers:
			void Clear() noexcept
			{
				m_elements.clear();
			}
			template <class ...ArgumentsT>
			Reference EmplaceBack(ArgumentsT&&... arguments)
			{
				if (Size() == Capacity())
					throw std::out_of_range("Memory pool is full! Use the reserve method to reserve a block of memory!");

				return m_elements.emplace_back(std::forward<ArgumentsT>(arguments)...);
			}
			void SwapWithBackAndPopBack(Iterator position)
			{
				// Overwrite element at given position by moving the element at the back:
				*position = std::move(m_elements[m_elements.size() - 1]);
				
				// Remove element at the back:
				m_elements.pop_back();
			}
			void Swap(ContiguousMemoryPool& other) noexcept
			{
				std::swap(m_elements, other.m_elements);
			}

		private:

			// Members:
			std::vector<ValueType> m_elements;

		};
	}
}
