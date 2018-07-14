#ifndef MAIA_UTILITIES_FORWARDALLOCATOR_H_INCLUDED
#define MAIA_UTILITIES_FORWARDALLOCATOR_H_INCLUDED

#include <cstddef>
#include <memory>

namespace Maia::Utilities
{
	class Memory_arena;

	template <class T>
	class Forward_allocator
	{
	public:

		template <typename U> friend class Forward_allocator;

		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using is_always_equal = std::false_type;

		using propagate_on_container_copy_assignment = std::true_type;
		using propagate_on_container_move_assignment = std::true_type;
		using propagate_on_container_swap = std::true_type;

		Forward_allocator(Memory_arena& memory_arena) noexcept
			: m_memory_arena(memory_arena)
		{
		}

		template <class U>
		constexpr Forward_allocator(Forward_allocator<U> const& other) noexcept
		{
		}

		//[[nodiscard]]
		T* allocate(std::size_t numElements)
		{
			return nullptr;
		}

		void deallocate(T* ptr, std::size_t numElements) noexcept
		{
		}

		template <class U>
		bool operator==(Forward_allocator<U> const& rhs) const noexcept
		{
			return m_memory_arena == rhs.m_memory_arena;
		}

	private:

		Memory_arena& m_memory_arena;

	};

	template <class T, class U>
	bool operator!=(Forward_allocator<T> const& lhs, Forward_allocator<U> const& rhs) noexcept
	{
		return !(lhs == rhs);
	}
}

#endif
