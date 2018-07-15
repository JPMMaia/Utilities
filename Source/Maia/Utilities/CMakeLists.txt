project(MaiaUtilities LANGUAGES C CXX)

add_library(MaiaUtilities)
add_library(Maia::Utilities ALIAS MaiaUtilities)

target_include_directories(MaiaUtilities PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../..")

target_sources(MaiaUtilities 

	PRIVATE

		Utilities.cpp

		# Allocators:
		Allocators/BuddyAllocator.hpp
		Allocators/ForwardAllocator.hpp
		Allocators/MemoryArena.hpp

		# Containers:
		Containers/Pools/ContiguousMemoryPool.hpp
		Containers/Pools/MemoryPool.hpp
		Containers/Pools/PointedContiguousMemoryPool.hpp

		# Helpers:
		Helpers/Helpers.hpp

		# Math:
		Math/MathHelpers.hpp

		# Threading:
		Threading/ThreadPool.hpp

		# Timers:
		Timers/PerformanceTimer.hpp
		Timers/Timer.hpp
		
)

set_target_properties(MaiaUtilities PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(MaiaUtilities PRIVATE cxx_std_17)
target_compile_options(MaiaUtilities PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/permissive->)
