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

set(QT_DEBUG_PLUGINS 1)

# Include sub-projects.
add_executable(game 
          src/main.cpp

        	src/core/game.h
        	src/core/game.cpp
        	src/core/vizualizer.h
        	src/core/vizualizer.cpp

        	src/helpers/core/factories.h
        	src/helpers/core/factories.cpp

          src/comp/velocity.h
          src/comp/acceleration.h
          src/comp/hp.h
          src/comp/sprite.h
          src/comp/position.h
          src/comp/spawner.h
          src/comp/life.h
          src/comp/player.h
          src/comp/entity.h
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
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
qt_standard_project_setup()
target_link_libraries(game PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game)
endif()

# solving cringe error
# thx https://stackoverflow.com/users/10185183/arsdever
if(WIN32)
    add_custom_command(
        TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${Qt6_DIR}/../../$<$<CONFIG:Debug>:debug/>Qt6/plugins/platforms/
            $<TARGET_FILE_DIR:game>/platforms/
    )
endif()