# Enable testing and find GoogleTest:
enable_testing()
set(GoogleTest_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../CMake")
find_package(GoogleTest REQUIRED CONFIG)

# Add unit tests:
add_subdirectory(UnitTest)
add_test(MaiaUtilitiesTest MaiaUtilitiesUnitTest)
