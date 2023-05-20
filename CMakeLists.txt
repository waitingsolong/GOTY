# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("game")

# Include sub-projects.
add_executable(game src/core/main.cpp
        	src/core/game.h
        	src/core/game.cpp
        	src/core/vizualizer.h
        	src/core/vizualizer.cpp
        	src/core/factories.h
        	src/core/factories.cpp
)

# entt
find_package(EnTT CONFIG REQUIRED)
target_link_libraries(game PUBLIC EnTT::EnTT)

# gtest
enable_testing()
find_package(GTest CONFIG REQUIRED)
target_link_libraries(game PUBLIC GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
#add_test(AllTestsInMain main)

# qt 
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()
target_link_libraries(game PUBLIC Qt6::Core)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game)
endif()