project (MaiaUtilitiesUnitTest)

add_executable (MaiaUtilitiesUnitTest)
add_executable (Maia::Utilities::UnitTest ALIAS MaiaUtilitiesUnitTest)

target_compile_features (MaiaUtilitiesUnitTest PRIVATE cxx_std_17)

if (MSVC)
	target_compile_options(MaiaUtilitiesUnitTest
		PRIVATE
			/permissive-
			/Za
			/Zc:rvalueCast
	)
endif ()

target_include_directories(MaiaUtilitiesUnitTest 
	PRIVATE
		"${CMAKE_SOURCE_DIR}/Source"
)

target_link_libraries (MaiaUtilitiesUnitTest PRIVATE Maia::Utilities)

find_package (GTest REQUIRED)
target_link_libraries (MaiaUtilitiesUnitTest PRIVATE GTest::GTest GTest::Main)

find_package (GMock REQUIRED)
target_link_libraries (MaiaUtilitiesUnitTest PRIVATE GMock::GMock GMock::Main)

target_sources (MaiaUtilitiesUnitTest 
	PRIVATE

		"main.cpp"

		"Allocators/Buddy_allocator_test.cpp"
		"Allocators/Forward_allocator_test.cpp"

		"Containers/Pools/ContiguousMemoryPoolTest.cpp"
		"Containers/Pools/MemoryPoolTest.cpp"
		"Containers/Pools/PointedContiguousMemoryPoolTest.cpp"

		"Math/MathHelpersTest.cpp"

		"Threading/ThreadPoolTest.cpp"

)

gtest_discover_tests (MaiaUtilitiesUnitTest)