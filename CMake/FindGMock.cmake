find_path (GMOCK_INCLUDE_DIR "gmock/gmock.h"
    HINTS
        "$ENV{GMOCK_ROOT}/include"
        "${GMOCK_ROOT}/include"
        "$ENV{GTEST_ROOT}/include"
        "${GTEST_ROOT}/include"
)
mark_as_advanced (GMOCK_INCLUDE_DIR)

find_library (GMOCK_LIBRARY "gmock"
    HINTS
        "$ENV{GMOCK_ROOT}/lib"
        "${GMOCK_ROOT}/lib"
        "$ENV{GTEST_ROOT}/lib"
        "${GTEST_ROOT}/lib"
)
mark_as_advanced (GMOCK_LIBRARY)

find_library (GMOCK_MAIN_LIBRARY "gmock_main"
    HINTS
        "$ENV{GMOCK_ROOT}/lib"
        "${GMOCK_ROOT}/lib"
        "$ENV{GTEST_ROOT}/lib"
        "${GTEST_ROOT}/lib"
)
mark_as_advanced (GMOCK_MAIN_LIBRARY)

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GMOCK
    REQUIRED_VARS 
        GMOCK_INCLUDE_DIR
        GMOCK_LIBRARY
        GMOCK_MAIN_LIBRARY
)

if (GMOCK_FOUND)

    if (NOT TARGET GMock::GMock)
        add_library(GMock::GMock UNKNOWN IMPORTED)
        set_target_properties(GMock::GMock PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
            IMPORTED_LOCATION "${GMOCK_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}"
        )
    endif ()

    if (NOT TARGET GMock::Main)
        add_library(GMock::Main UNKNOWN IMPORTED)
        set_target_properties(GMock::Main PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
            IMPORTED_LOCATION "${GMOCK_MAIN_LIBRARY}"
            INTERFACE_LINK_LIBRARIES "GMock::GMock"
        )
    endif ()

endif ()
