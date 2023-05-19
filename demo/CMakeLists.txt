cmake_minimum_required(VERSION 3.5)

project(demo)

set(TARGET_NAME "${PROJECT_NAME}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES main.cpp )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
   qt_add_executable(demo MANUAL_FINALIZATION ${PROJECT_SOURCES} )
else()
   add_executable(${TARGET_NAME} ${PROJECT_SOURCES})
endif()

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets qappnotifier)


if(QT_VERSION_MAJOR EQUAL 6)
   qt_finalize_executable(notify_test)
endif()
