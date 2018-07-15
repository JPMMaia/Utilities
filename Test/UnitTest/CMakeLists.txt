project(MaiaUtilitiesUnitTest LANGUAGES C CXX)

add_executable(MaiaUtilitiesUnitTest)
add_executable(Maia::Utilities::UnitTest ALIAS MaiaUtilitiesUnitTest)
gtest_discover_tests(MaiaUtilitiesUnitTest)

target_compile_features(MaiaUtilitiesUnitTest PRIVATE cxx_std_17)
target_compile_options(MaiaUtilitiesUnitTest 
	PUBLIC 
		$<$<COMPILE_LANGUAGE:CXX>:/permissive->
		$<$<COMPILE_LANGUAGE:CXX>:/Za>
		$<$<COMPILE_LANGUAGE:CXX>:/Zc:rvalueCast>
)

target_include_directories(MaiaUtilitiesUnitTest 
	PRIVATE 
		"${GOOGLE_TEST_INCLUDE_DIRECTORY}"
		"${CMAKE_SOURCE_DIR}/Source"
)

target_sources(MaiaUtilitiesUnitTest 
	
	PRIVATE

		main.cpp

		Allocators/Buddy_allocator_test.cpp
		Allocators/Forward_allocator_test.cpp

		Containers/Pools/ContiguousMemoryPoolTest.cpp
		Containers/Pools/MemoryPoolTest.cpp
		Containers/Pools/PointedContiguousMemoryPoolTest.cpp

		Math/MathHelpersTest.cpp

		Threading/ThreadPoolTest.cpp

)

target_link_libraries(MaiaUtilitiesUnitTest 
	debug ${GTEST_DEBUG_LIBRARY} optimized ${GTEST_RELEASE_LIBRARY}
	debug ${GTEST_MAIN_DEBUG_LIBRARY} optimized ${GTEST_MAIN_RELEASE_LIBRARY}
	debug ${GMOCK_DEBUG_LIBRARY} optimized ${GMOCK_RELEASE_LIBRARY}
	debug ${GMOCK_MAIN_DEBUG_LIBRARY} optimized ${GMOCK_MAIN_RELEASE_LIBRARY}
)

target_link_libraries(MaiaUtilitiesUnitTest Maia::Utilities)
