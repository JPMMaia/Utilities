project (MaiaUtilities)

add_library (MaiaUtilities INTERFACE)
add_library (Maia::Utilities ALIAS MaiaUtilities)

target_compile_features (MaiaUtilities 
	INTERFACE
		cxx_std_17
)

target_include_directories (MaiaUtilities INTERFACE "${CMAKE_CURRENT_LIST_DIR}/../..")

target_sources(MaiaUtilities 
	INTERFACE

		"${CMAKE_CURRENT_LIST_DIR}/Allocators/Buddy_allocator.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/Allocators/Forward_allocator.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/Allocators/Memory_arena.hpp"
		
		"${CMAKE_CURRENT_LIST_DIR}/Containers/Pools/ContiguousMemoryPool.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/Containers/Pools/MemoryPool.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/Containers/Pools/PointedContiguousMemoryPool.hpp"

		"${CMAKE_CURRENT_LIST_DIR}/Helpers/Helpers.hpp"

		"${CMAKE_CURRENT_LIST_DIR}/Math/MathHelpers.hpp"

		"${CMAKE_CURRENT_LIST_DIR}/Threading/ThreadPool.hpp"

		"${CMAKE_CURRENT_LIST_DIR}/Timers/PerformanceTimer.hpp"
		"${CMAKE_CURRENT_LIST_DIR}/Timers/Timer.hpp"
)
