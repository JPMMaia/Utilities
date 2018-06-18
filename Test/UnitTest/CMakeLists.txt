project(MaiaUtilitiesUnitTest LANGUAGES C CXX)

# Add test executable:
add_executable(MaiaUtilitiesUnitTest)
add_executable(Maia::Utilities::UnitTest ALIAS MaiaUtilitiesUnitTest)
gtest_discover_tests(MaiaUtilitiesUnitTest)

# Set compile features:
target_compile_features(MaiaUtilitiesUnitTest PRIVATE cxx_std_17)
target_compile_options(MaiaUtilitiesUnitTest 
	PUBLIC 
		$<$<COMPILE_LANGUAGE:CXX>:/permissive->
		$<$<COMPILE_LANGUAGE:CXX>:/Za>
		$<$<COMPILE_LANGUAGE:CXX>:/Zc:rvalueCast>
)

# Add includes directories:
target_include_directories(MaiaUtilitiesUnitTest 
	PRIVATE 
		${GOOGLE_TEST_INCLUDE_DIRECTORY}
		${CMAKE_SOURCE_DIR}
)

# Add test sources:
target_sources(MaiaUtilitiesUnitTest 
	
	PRIVATE

		Source/main.cpp

		# Allocators
		Source/Allocators/BuddyAllocatorTest.cpp
		Source/Allocators/ForwardAllocatorTest.cpp

		# Containers:
		Source/Containers/Pools/ContiguousMemoryPoolTest.cpp
		Source/Containers/Pools/MemoryPoolTest.cpp
		Source/Containers/Pools/PointedContiguousMemoryPoolTest.cpp

		# Math:
		Source/Math/MathHelpersTest.cpp

		# Threading:
		Source/Threading/ThreadPoolTest.cpp

)

# Link Google Test and Google Mock libraries:
target_link_libraries(MaiaUtilitiesUnitTest 
	debug ${GTEST_DEBUG_LIBRARY} optimized ${GTEST_RELEASE_LIBRARY}
	debug ${GTEST_MAIN_DEBUG_LIBRARY} optimized ${GTEST_MAIN_RELEASE_LIBRARY}
	debug ${GMOCK_DEBUG_LIBRARY} optimized ${GMOCK_RELEASE_LIBRARY}
	debug ${GMOCK_MAIN_DEBUG_LIBRARY} optimized ${GMOCK_MAIN_RELEASE_LIBRARY}
)

# Link libraries:
target_link_libraries(MaiaUtilitiesUnitTest Maia::Utilities)
