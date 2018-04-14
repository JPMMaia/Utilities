cmake_minimum_required(VERSION 3.10)
project(MaiaUtilities VERSION 0.1.0 LANGUAGES C CXX)

# Add library to the project and define alias:
add_library(MaiaUtilities)
add_library(Maia::Utilities ALIAS MaiaUtilities)

# Add sources:
target_sources(MaiaUtilities PRIVATE
	
	# Root:
	Interface/Utilities.ixx

	# Events:
	Interface/Events/Events.ixx
	Interface/Events/Event.ixx
	Interface/Events/InternalEvent.ixx
	Interface/Events/InternalEventsComponent.ixx

	# Exceptions:
	Interface/Exceptions/EngineException.ixx

	# Helpers:
	Interface/Helpers/Helpers.ixx

	# Math:
	Interface/Math/MathHelpers.ixx

	# Memory:
	Interface/Memory/MemoryPool.ixx

	# Threading:
	Interface/Threading/Threading.ixx
	Interface/Threading/Task.ixx
	Interface/Threading/TasksComponent.ixx

	# Timers:
	Interface/Timers/PerformanceTimer.ixx
	Interface/Timers/Timer.ixx
)

# Set target linker language:
set_target_properties(MaiaUtilities PROPERTIES LINKER_LANGUAGE CXX)

# Set compile features:
target_compile_features(MaiaUtilities PRIVATE cxx_std_17)

# Define headers:
target_include_directories(MaiaUtilities PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interface>
    $<INSTALL_INTERFACE:Interface>
    PRIVATE Source
)

# Specify rules to run at install time:
install(TARGETS MaiaUtilities
	EXPORT MaiaUtilitiesConfig
	RUNTIME DESTINATION Binaries
	LIBRARY DESTINATION Libraries
	ARCHIVE DESTINATION Libraries/Static
)
install(
	DIRECTORY ${CMAKE_BINARY_DIR}/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/Interface
	FILES_MATCHING PATTERN "*.ifc"
)

# Make the library importable from the install directory:
install(EXPORT MaiaUtilitiesConfig DESTINATION CMake)

# Make the project importable from the build directory:
export(TARGETS MaiaUtilities FILE MaiaUtilitiesConfig.cmake)

# Add tests:
add_subdirectory(Test)