cmake_minimum_required(VERSION 3.20)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(game GameObject.h DynamicObject.h StaticObject.h Spawner.h Creature.h Hero.h NPC.h Boss.h Boiler.h Wall.h Map.h Constants.h AbstractController.h Controller.h LevelController.h View.h Model.h Util.h Points.h Colisions.h)
target_link_libraries(game
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
