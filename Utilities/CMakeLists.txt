project(MaiaUtilities LANGUAGES C CXX)

# Add library to the project and define alias:
add_library(MaiaUtilities)
add_library(Maia::Utilities ALIAS MaiaUtilities)

# Add sources:
target_sources(MaiaUtilities 

	PRIVATE

		Utilities.cpp

		# Allocators:
		Allocators/BuddyAllocator.hpp
		Allocators/ForwardAllocator.hpp

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

# Set target linker language:
set_target_properties(MaiaUtilities PROPERTIES LINKER_LANGUAGE CXX)

# Set compile features:
target_compile_features(MaiaUtilities PRIVATE cxx_std_17)
target_compile_options(MaiaUtilities PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/permissive->)
