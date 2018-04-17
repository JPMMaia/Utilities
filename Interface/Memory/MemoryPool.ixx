export module Maia.Utilities.Memory;

import std.core;

namespace Maia
{
	namespace Utilities
	{
		export class MemoryPoolConstIterator
		{
		}

		export class MemoryPoolIterator
		{
		}

		template <class ValueT>
		export class MemoryPool
		{
		public:
			
			// Public member types:
			using ValueType = ValueT;
			using Reference = ValueT&;
			using Iterator = MemoryPoolIterator;
			using ConstIterator = MemoryPoolConstIterator;

			// Constructors:
			MemoryPool() = default;
			MemoryPool(std::size_t capacity)
			{
			}

			// Element access:


			// Iterators:
			Iterator Begin() noexcept
			{
				return {};
			}
			ConstIterator Begin() const noexcept
			{
				return {};
			}
			ConstIterator CBegin() const noexcept
			{
				return {};
			}
			Iterator End() noexcept
			{
				return {};
			}
			ConstIterator End() const noexcept
			{
				return {};
			}
			ConstIterator CEnd() const noexcept
			{
				return {};
			}

			// Capacity:
			bool Empty() const noexcept
			{
				return false;
			}
			std::size_t Size() const noexcept
			{
				return 0;
			}
			std::size_t MaxSize() const noexcept
			{
				return 0;
			}

			void Reserve(std::size_t capacity)
			{
			}

			// Modifiers:
			void Clear() noexcept
			{
			}
			template <class ...ArgumentsT>
			Reference Emplace(ArgumentsT&&... arguments)
			{
			}
			void Erase(ConstIterator position)
			{
			}
			void Erase(ConstIterator first, ConstIterator last)
			{
			}
			void Push(const ValueType& value)
			{
			}
			void Push(ValueType&& value)
			{
			}
			void Resize(std::size_t count)
			{
			}
			void Resize(std::size_t count, const ValueType& value)
			{
			}
			void Swap(MemoryPool<ValueType>& other) noexcept
			{
			}

		};
	}
}
