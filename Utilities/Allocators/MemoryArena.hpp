#ifndef MAIA_UTILITIES_MEMORYARENA_H_INCLUDED
#define MAIA_UTILITIES_MEMORYARENA_H_INCLUDED

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace Maia::Utilities
{
	class Memory_arena
	{
	public:

		explicit Memory_arena(std::size_t size_in_bytes) :
			m_data{ std::make_unique<std::byte[]>(size_in_bytes) },
			m_size_in_bytes{ size_in_bytes },
			m_offset_in_bytes{ 0 }
		{
		}
		Memory_arena(const Memory_arena&) = delete;
		Memory_arena(Memory_arena&& other) = delete;

		Memory_arena& operator=(const Memory_arena&) = delete;
		Memory_arena& operator=(Memory_arena&&) = delete;

		void* allocate(std::size_t size_in_bytes, std::size_t alignment_in_bytes)
		{
			void* data = m_data.get() + m_offset_in_bytes;
			
			auto const original_space = m_size_in_bytes - m_offset_in_bytes;
			auto new_space = original_space;

			if (!std::align(alignment_in_bytes, size_in_bytes, data, new_space))
			{
				throw std::bad_alloc();
			}

			auto const offset = original_space - new_space;
			m_offset_in_bytes += offset;

			return data;
		}
		void deallocate(void* data, std::size_t size_in_bytes)
		{
		}

	private:

		std::unique_ptr<std::byte[]> const m_data;
		std::size_t const m_size_in_bytes;
		std::size_t m_offset_in_bytes;

	};
}

#endif
