cmake_minimum_required(VERSION 3.20)
project(demons)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(demons
        main.cpp
        App/app.cpp
        Controller/abstract_controller.cpp
        Controller/controller.cpp
        Controller/level_controller.cpp
        Controller/npc_controller.cpp
        GameObject/boss.cpp
        GameObject/creature.cpp
        GameObject/dynamic_object.cpp
        GameObject/game_object.cpp
        GameObject/hero.cpp
        GameObject/npc.cpp
        GameObject/spawner.cpp
        GameObject/static_object.cpp
        GameObject/wall.cpp
        Map/map.cpp
        Model/constants.cpp
        Model/model.cpp
        Util/collisions.cpp
        Util/point.cpp
        Util/structs.h
        Util/vector.cpp
        View/menu.cpp
        View/view.cpp
        resources.qrc)

target_link_libraries(demons
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
