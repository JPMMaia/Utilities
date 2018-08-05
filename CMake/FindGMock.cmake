#############
# Functions #
#############

function (_find_gmock_library _var _name)

    find_library (${_var} ${_name}
        HINTS
            "$ENV{GMOCK_ROOT}/lib"
            "${GMOCK_ROOT}/lib"
            "$ENV{GTEST_ROOT}/lib"
            "${GTEST_ROOT}/lib"
    )
    mark_as_advanced (${_var})

endfunction ()

function (_set_gmock_library_config_properties _target _imported_library _config)

    if (_config)
        set (_config_suffix "_${_config}")
    else ()
        set (_config_suffix "")
    endif ()

    if(_config)
        set_property(TARGET ${_target} APPEND PROPERTY
            IMPORTED_CONFIGURATIONS ${_config})
    endif()

    set_target_properties(${_target} PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES${_config_suffix} "CXX"
        IMPORTED_LOCATION${_config_suffix} "${_imported_library}"
    )

endfunction ()


###########
# Content #
###########

find_path (GMOCK_INCLUDE_DIR "gmock/gmock.h"
    HINTS
        "$ENV{GMOCK_ROOT}/include"
        "${GMOCK_ROOT}/include"
        "$ENV{GTEST_ROOT}/include"
        "${GTEST_ROOT}/include"
)
mark_as_advanced (GMOCK_INCLUDE_DIR)

_find_gmock_library (GMOCK_LIBRARY "gmock")
_find_gmock_library (GMOCK_DEBUG_LIBRARY "gmockd")
_find_gmock_library (GMOCK_MAIN_LIBRARY "gmock_main")
_find_gmock_library (GMOCK_MAIN_DEBUG_LIBRARY "gmock_maind")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GMOCK
    REQUIRED_VARS 
        GMOCK_LIBRARY
        GMOCK_MAIN_LIBRARY
        GMOCK_INCLUDE_DIR
)

if (GMOCK_FOUND)

    if (NOT TARGET GMock::GMock)

        add_library (GMock::GMock UNKNOWN IMPORTED)
        set_target_properties (GMock::GMock PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}"
        )

        _set_gmock_library_config_properties (GMock::GMock ${GMOCK_LIBRARY} "RELEASE")

        if (EXISTS "${GMOCK_DEBUG_LIBRARY}")
            _set_gmock_library_config_properties (GMock::GMock ${GMOCK_DEBUG_LIBRARY} "DEBUG")
        endif()

    endif ()

    if (NOT TARGET GMock::Main)

        add_library(GMock::Main UNKNOWN IMPORTED)
        set_target_properties (GMock::Main PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}"
        )

        _set_gmock_library_config_properties (GMock::Main ${GMOCK_MAIN_LIBRARY} "RELEASE")

        if (EXISTS "${GMOCK_DEBUG_LIBRARY}")
            _set_gmock_library_config_properties (GMock::Main ${GMOCK_MAIN_DEBUG_LIBRARY} "DEBUG")
        endif()
        
    endif ()

endif ()
