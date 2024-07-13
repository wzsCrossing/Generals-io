cmake_minimum_required(VERSION 3.5)

project(Generals-io VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    src
    src/common
    src/model
    src/viewmodel
    src/window
    src/app
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets WebSockets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets WebSockets Multimedia)

set(
    PROJECT_SOURCES

    res.rc

    src/main.cpp

    src/common/PlayerInfo.cpp
    src/common/PlayerInfo.h
    src/common/MapInfo.cpp
    src/common/MapInfo.h

    src/model/GeneralsGameModel.cpp
    src/model/GeneralsGameModel.h

    src/viewmodel/GeneralsViewModel.cpp
    src/viewmodel/GeneralsViewModel.h

    src/window/mainwindow.cpp
    src/window/mainwindow.h
    src/window/mainwindow.ui
    src/window/mappage.cpp
    src/window/mappage.h
    src/window/mappage.ui
    src/window/gamepage.cpp
    src/window/gamepage.h
    src/window/gamepage.ui

    src/app/GeneralsApp.cpp
    src/app/GeneralsApp.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 5)
    qt_add_executable(Generals-io
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        img/resources.qrc
        src/window/playbackpage.h src/window/playbackpage.cpp src/window/playbackpage.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Generals-io APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Generals-io SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Generals-io
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(
    Generals-io PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

target_include_directories(Generals-io PRIVATE "${CMAKE_BINARY_DIR}/Generals-io_autogen/include")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Generals-io)
endif()
set_target_properties(Generals-io PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Generals-io
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Generals-io)
endif()
