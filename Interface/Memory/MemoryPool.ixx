export module Maia.Utilities.Memory;

namespace Maia
{
	namespace Utilities
	{
		export template <class ValueT>
		class MemoryPoolConstIterator
		{
		public:

			// Public member types:
			using ValueType = ValueT;
			using Reference = ValueT&;
			using ConstReference = const ValueT&;

			// Element access:
			ConstReference operator*()
			{
				static ValueType value;
				return &value;
			}

		};

		export template <class ValueT>
		class MemoryPoolIterator : public MemoryPoolConstIterator<ValueT>
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
			using ConstReference = const ValueT&;
			using Iterator = MemoryPoolIterator<ValueT>;
			using ConstIterator = MemoryPoolConstIterator<ValueT>;

			// Constructors:
			MemoryPool() noexcept = default;
			MemoryPool(const MemoryPool& other) = delete;
			MemoryPool(MemoryPool&& other) noexcept
			{
			}
			MemoryPool(SizeType count, const ValueType& value = ValueType())
			{
			}

			// Copy/move assignment:
			MemoryPool& operator=(const MemoryPool& other) = delete;
			MemoryPool& operator=(MemoryPool&& other) noexcept
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
			SizeType Capacity() const noexcept
			{
				return 0;
			}

			// Modifiers:
			void Clear() noexcept
			{
			}
			template <class ...ArgumentsT>
			Iterator Emplace(ArgumentsT&&... arguments)
			{
				return {};
			}
			void Erase(ConstIterator position)
			{
			}
			void Erase(ConstIterator first, ConstIterator last)
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
