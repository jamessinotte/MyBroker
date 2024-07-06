cmake_minimum_required(VERSION 3.5)

project(MyBroker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


# Specify the path to the MongoDB C++ drivers relative to the project directory


# Include directories for MongoDB C++ drivers

add_definitions(-DBSONCXX_POLY_USE_IMPLS=ON)
add_definitions(-DBSONCXX_POLY_USE_MNMLSTC=1.)
set(PROJECT_SOURCES
    main.cpp
    mybroker.cpp
    mybroker.h
    mybroker.ui
    signup.cpp
    signup.h
    signup.ui
    login.cpp
    login.h
    login.ui
    
)
set(ENABLE_BSONCXX_POLY_USE_IMPLS ON)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MyBroker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        database.h database.cpp

    )
else()
    if(ANDROID)
        add_library(MyBroker SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MyBroker
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link MongoDB C++ driver libraries
target_link_libraries(MyBroker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MyBroker)
endif()
set_target_properties(MyBroker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MyBroker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyBroker)
endif()
