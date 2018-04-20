export module Maia.Utilities.Memory;

namespace Maia
{
	namespace Utilities
	{
		export class MemoryPoolConstIterator
		{
		};

		export class MemoryPoolIterator : public MemoryPoolConstIterator
		{
		};

		export template <class ValueT>
		class MemoryPool
		{
		public:
			
			// Public member types:
			using SizeType = std::size_t;
			using ValueType = ValueT;
			using Reference = ValueT&;
			using ConstReference = const Reference;
			using Iterator = MemoryPoolIterator;
			using ConstIterator = MemoryPoolConstIterator;

			// Constructors:
			MemoryPool() = default;
			MemoryPool(SizeType count, const ValueType& value = ValueType())
			{
			}

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
			SizeType Size() const noexcept
			{
				return 0;
			}
			SizeType MaxSize() const noexcept
			{
				return 0;
			}
			void Reserve(SizeType capacity)
			{
			}

			// Modifiers:
			void Clear() noexcept
			{
			}
			template <class ...ArgumentsT>
			Reference Emplace(ArgumentsT&&... arguments)
			{
				static ValueType v;
				return &v;
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
			void Resize(SizeType count)
			{
			}
			void Resize(SizeType count, const ValueType& value)
			{
			}
			void Swap(MemoryPool<ValueType>& other) noexcept
			{
			}

		};
	}
}
