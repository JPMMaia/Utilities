#############
# Functions #
#############

function (_find_gmock_library _var _name)

    find_library (${_var} ${_name}
        HINTS
            "$ENV{GMock_ROOT}/lib"
            "${GMock_ROOT}/lib"
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

find_path (GMock_INCLUDE_DIR "gmock/gmock.h"
    HINTS
        "$ENV{GMock_ROOT}/include"
        "${GMock_ROOT}/include"
        "$ENV{GTEST_ROOT}/include"
        "${GTEST_ROOT}/include"
)
mark_as_advanced (GMock_INCLUDE_DIR)

_find_gmock_library (GMock_LIBRARY "gmock")
_find_gmock_library (GMock_DEBUG_LIBRARY "gmockd")
_find_gmock_library (GMock_MAIN_LIBRARY "gmock_main")
_find_gmock_library (GMock_MAIN_DEBUG_LIBRARY "gmock_maind")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GMock
    REQUIRED_VARS 
        GMock_LIBRARY
        GMock_MAIN_LIBRARY
        GMock_INCLUDE_DIR
)

if (GMock_FOUND)

    if (NOT TARGET GMock::GMock)

        add_library (GMock::GMock UNKNOWN IMPORTED)
        set_target_properties (GMock::GMock PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIR}"
        )

        _set_gmock_library_config_properties (GMock::GMock ${GMock_LIBRARY} "RELEASE")

        if (EXISTS "${GMock_DEBUG_LIBRARY}")
            _set_gmock_library_config_properties (GMock::GMock ${GMock_DEBUG_LIBRARY} "DEBUG")
        endif()

    endif ()

    if (NOT TARGET GMock::Main)

        add_library(GMock::Main UNKNOWN IMPORTED)
        set_target_properties (GMock::Main PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIR}"
        )

        _set_gmock_library_config_properties (GMock::Main ${GMock_MAIN_LIBRARY} "RELEASE")

        if (EXISTS "${GMock_DEBUG_LIBRARY}")
            _set_gmock_library_config_properties (GMock::Main ${GMock_MAIN_DEBUG_LIBRARY} "DEBUG")
        endif()
        
    endif ()

endif ()
