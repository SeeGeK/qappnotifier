project(qappnotifier)

set(TARGET_NAME "${PROJECT_NAME}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE headers "*.h")

set(sources
   src/notifier.cpp
   src/notifierprivate.cpp
   src/notifyposeventfilter.cpp
   src/notifywidget.cpp
   )

add_library(${TARGET_NAME} STATIC
  ${sources}
  ${headers}
)

target_include_directories(${TARGET_NAME}
  PRIVATE
    src
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${TARGET_NAME} LINK_PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )
