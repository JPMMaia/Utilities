project(MaiaUtilitiesUnitTest VERSION 0.1.0 LANGUAGES C CXX)

# Add test executable:
add_executable(MaiaUtilitiesUnitTest Source/main.cpp)
add_executable(Maia::Utilities::UnitTest ALIAS MaiaUtilitiesUnitTest)
gtest_discover_tests(MaiaUtilitiesUnitTest)

# Set compile features:
target_compile_features(MaiaUtilitiesUnitTest PRIVATE cxx_std_17)

# Add includes directories:
target_include_directories(MaiaUtilitiesUnitTest PRIVATE ${GOOGLE_TEST_INCLUDE_DIRECTORY})

# Add test sources:
target_sources(MaiaUtilitiesUnitTest PRIVATE

	# Math:
	Source/Math/MathHelpersTest.cpp

	# Memory:
	Source/Memory/MemoryPoolTest.cpp

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
