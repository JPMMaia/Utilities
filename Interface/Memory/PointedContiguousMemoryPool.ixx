#include <vector>

import Maia.Utilities.Memory.ContiguousMemoryPool;
import Maia.Utilities.Memory.MemoryPool;

export module Maia.Utilities.Memory.PointedContiguousMemoryPool;

namespace Maia
{
	namespace Utilities
	{
		template <class ValueT>
		class PointedContiguousMemoryPool;

		export template <class ValueT>
		class PointedContiguousMemoryPoolPointer
		{
		public:

			// Public member types:
			using ValueType = ValueT;
			using SizeType = std::size_t;

			// Element Access:
			ValueType& operator->() const
			{
				return *m_pointer;
			}
			ValueType& operator*() const
			{
				return *m_pointer;
			}

		private:

			// Friends:
			friend PointedContiguousMemoryPool<ValueT>;

			// Members:
			ValueType* m_pointer;

		};

		export template <class ValueT>
		class PointedContiguousMemoryPool
		{
		public:
			
			// Public member types:
			using SizeType = std::size_t;
			using ValueType = ValueT;
			using Reference = ValueT&;
			using ConstReference = const ValueT&;
			using Iterator = typename std::vector<ValueT>::iterator;
			using ConstIterator = typename std::vector<ValueT>::const_iterator;
			using Pointer = PointedContiguousMemoryPoolPointer<ValueT>;

			// Constructors:
			PointedContiguousMemoryPool() noexcept = default;
			PointedContiguousMemoryPool(const PointedContiguousMemoryPool& other) = delete;
			PointedContiguousMemoryPool(PointedContiguousMemoryPool&& other) noexcept :
				m_elements(std::move(other.m_elements)),
				m_pointers(std::move(other.m_pointers))
			{
			}
			PointedContiguousMemoryPool(SizeType capacity) :
				m_elements(),
				m_pointers()
			{
				Reserve(capacity);
			}

			// Copy/move assignment:
			PointedContiguousMemoryPool& operator=(const PointedContiguousMemoryPool& other) = delete;
			PointedContiguousMemoryPool& operator=(PointedContiguousMemoryPool&& other) noexcept
			{
				m_elements = std::move(other.m_elements);
				m_pointers = std::move(other.m_pointers);
			}

			// Element Access:
			// TODO

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
				m_pointers.reserve(capacity);
			}
			SizeType Capacity() const noexcept
			{
				return m_elements.capacity();
			}

			// Modifiers:
			void Clear() noexcept
			{
				m_elements.clear();
				m_pointers.clear();
			}
			template <class ...ArgumentsT>
			Pointer EmplaceBack(ArgumentsT&&... arguments)
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
			ContiguousMemoryPool<ValueType> m_elements;
			MemoryPool<Pointer> m_pointers;

		};
	}
}
