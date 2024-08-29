cmake_minimum_required(VERSION 3.5)

project(MyBroker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)


# Specify the path to the MongoDB C++ drivers relative to the project directory
# Assuming you have MongoDB C++ drivers installed, set their paths here.
# For instance:
#set(MONGOCXX_INCLUDE_DIRS "C:/path/to/mongocxx/include")
#set(MONGOCXX_LIBRARIES "C:/path/to/mongocxx/lib/mongocxx.lib" "C:/path/to/bsoncxx/lib/bsoncxx.lib")

# Include directories for MongoDB C++ drivers
#include_directories(${MONGOCXX_INCLUDE_DIRS})

add_definitions(-DBSONCXX_POLY_USE_IMPLS=ON)
add_definitions(-DBSONCXX_POLY_USE_MNMLSTC=1)

set(PROJECT_SOURCES
    main.cpp



    signup.cpp
    signup.h
    signup.ui
    login.cpp
    login.h
    login.ui
    database.cpp
    database.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)


qt_add_executable(MyBroker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        datahandler.h datahandler.cpp
        homepage.h homepage.cpp homepage.ui
        functions.h functions.cpp
        uimanager.h uimanager.cpp

        mybroker.ui
        mybroker.h mybroker.cpp mybroker.ui
        investment.h investment.cpp


        loadenv.h loadenv.cpp
        info.env
        .gitignore




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

# Link MongoDB C++ driver libraries if needed
# target_link_libraries(MyBroker PRIVATE ${MONGOCXX_LIBRARIES})

# Link Qt Widgets and Sql
target_link_libraries(MyBroker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql cpr::cpr nlohmann_json::nlohmann_json)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MyBroker)
endif()
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.10.5)
FetchContent_MakeAvailable(cpr)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(json)

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

