cmake_minimum_required(VERSION 3.16)

project(keyboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# X11 라이브러리 및 XTest 라이브러리 찾기
find_package(X11 REQUIRED)
find_library(XTEST_LIB Xtst REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    keyboard.cpp
    keyboard.h
    keyboard.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(keyboard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(keyboard SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(keyboard
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# X11 및 XTest 라이브러리 링크
if(X11_FOUND AND XTEST_LIB)
    target_link_libraries(keyboard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${X11_LIBRARIES} ${XTEST_LIB})
    include_directories(${X11_INCLUDE_DIR})
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.keyboard)
endif()
set_target_properties(keyboard PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS keyboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(keyboard)
endif()
