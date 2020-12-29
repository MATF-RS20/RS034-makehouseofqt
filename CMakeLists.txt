cmake_minimum_required(VERSION 3.16)
project(makeHouseOfQt, VERSION 1.0.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)
find_package(Qt5 COMPONENTS OpenGL REQUIRED)
find_package(OpenGL)

add_executable(qt_project drawingarea.cpp inputdialog.cpp floor.cpp main.cpp mainwindow.cpp wall.cpp wallsmodelview.cpp window.cpp selectingform.cpp door.cpp house.cpp selectingform.ui inputdialog.ui)
qt5_use_modules(qt_project Widgets OpenGL)
target_link_libraries(qt_project Qt5::Widgets ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
