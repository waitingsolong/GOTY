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

# qt 
set(QT_DEBUG_PLUGINS 1)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include sub-projects.
add_executable(game 
          src/main.cpp
          src/constants.h

        	src/core/game.h
          src/core/game.cpp

          src/sys/physics.h 
          src/sys/physics.cpp

        	src/helpers/core/factories.h
        	src/helpers/core/factories.cpp
           
          src/helpers/core/setupplayer.cpp
          src/helpers/factories/weaponFactory.h 
          src/helpers/factories/weaponFactory.cpp

          src/comp/velocity.h
          src/comp/acceleration.h
          src/comp/hp.h
          src/comp/sprite.h
          src/comp/position.h
          src/comp/spawner.h
          src/comp/life.h
          src/comp/player.h
          src/comp/enemy.h
          src/comp/gore.h
          src/comp/shootpattern.h
          src/comp/label.h
          src/comp/spritevector.h 
          src/comp/weapon.h 
           
          src/comp/damage.h   "src/comp/timer.h" "src/sys/combat.h" "src/sys/combat.cpp" "src/helpers/factories/bulletFactory.cpp" "src/helpers/factories/bulletFactory.h" 
           "src/comp/bullet.h")

# entt
find_package(EnTT CONFIG REQUIRED)
target_link_libraries(game PUBLIC EnTT::EnTT)

# gtest
enable_testing()
find_package(GTest CONFIG REQUIRED)
target_link_libraries(game PUBLIC GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
#add_test(AllTestsInMain game)

# qtbase

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
qt_standard_project_setup()
target_link_libraries(game PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# add resources 

qt_add_resources(game "resources"
    PREFIX "/"
    BASE "resources/img/"
    FILES
        resources/img/player/fly_fly.png
        resources/img/weapon/deagle.png
)

# qtmultimedia

find_package(Qt6BundledResonanceAudio CONFIG REQUIRED)
target_link_libraries(game PRIVATE Qt::BundledResonanceAudio Qt6::BundledResonanceAudio)

find_package(Qt6Multimedia CONFIG REQUIRED)
target_link_libraries(game PRIVATE Qt::Multimedia Qt6::Multimedia Qt::MultimediaPrivate Qt6::MultimediaPrivate)

find_package(Qt6MultimediaWidgets CONFIG REQUIRED)
target_link_libraries(game PRIVATE Qt::MultimediaWidgets Qt6::MultimediaWidgets Qt::MultimediaWidgetsPrivate Qt6::MultimediaWidgetsPrivate)

find_package(Qt6SpatialAudio CONFIG REQUIRED)
target_link_libraries(game PRIVATE Qt::SpatialAudio Qt6::SpatialAudio Qt::SpatialAudioPrivate Qt6::SpatialAudioPrivate)

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
