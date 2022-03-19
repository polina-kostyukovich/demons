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
        Model/constants.cpp
        Model/constants.h
        Controller/abstract_controller.cpp
        Controller/abstract_controller.h
        Controller/controller.h
        Controller/controller.cpp
        Controller/level_controller.cpp
        Controller/level_controller.h
        GameObject/boss.cpp
        GameObject/boss.h
        GameObject/сreature.cpp
        GameObject/сreature.h
        GameObject/dynamic_object.cpp
        GameObject/dynamic_object.h
        GameObject/game_object.cpp
        GameObject/game_object.h
        GameObject/hero.cpp
        GameObject/hero.h
        GameObject/npc.cpp
        GameObject/npc.h
        GameObject/spawner.cpp
        GameObject/spawner.h
        GameObject/static_object.cpp
        GameObject/static_object.h
        GameObject/wall.cpp
        GameObject/wall.h
        Map/map.cpp
        Map/map.h
        Model/model.cpp
        Model/model.h
        Util/util.cpp
        Util/util.h
        Util/points.cpp
        Util/points.h
        Util/collisions.cpp
        Util/collisions.h
        View/view.cpp
        View/view.h)
target_link_libraries(demons
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
