# Input variables:
set(GTEST_ROOT ENV{GTEST_ROOT} CACHE PATH "Path for Google Test")

# Output message:
message("Looking for Google Test in " ${GTEST_ROOT})

# Set include folder:
set(GOOGLE_TEST_INCLUDE_DIRECTORY ${GTEST_ROOT}/include)

# Find Google Test:
find_library(GTEST_DEBUG_LIBRARY gtestd PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)
find_library(GTEST_RELEASE_LIBRARY gtest PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)
find_library(GTEST_MAIN_DEBUG_LIBRARY gtest_maind PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)
find_library(GTEST_MAIN_RELEASE_LIBRARY gtest_main PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)

# Find Google Mock:
find_library(GMOCK_DEBUG_LIBRARY gmockd PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)
find_library(GMOCK_RELEASE_LIBRARY gmock PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)
find_library(GMOCK_MAIN_DEBUG_LIBRARY gmock_maind PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)
find_library(GMOCK_MAIN_RELEASE_LIBRARY gmock_main PATHS ${GTEST_ROOT} PATH_SUFFIXES lib)

# Include GoogleTest CMake package:
include(GoogleTest)