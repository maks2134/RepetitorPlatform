cmake_minimum_required(VERSION 3.28)
project(RepetitorPlatform)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(RepetitorPlatform src/main.cpp
        src/auth/auth.ui
        src/auth/auth.h
        src/auth/auth.cpp
        src/register/register.cpp
        src/register/register.h
        src/register/register.ui
        src/sha256/sha256.cpp
        src/sha256/sha256.h
        src/authbase/authbase.cpp
        src/authbase/authbase.h
        src/test/testbase.ui
        src/main/mainwin.cpp
        src/main/mainwin.h
        src/main/mainwin.ui
        src/test/QuestionManager.cpp
        src/test/QuestionManager.h
        src/test/NavigationManager.cpp
        src/test/NavigationManager.h
        src/test/TestBase.cpp
        src/test/TestBase.h
        src/account/account.cpp
        src/account/account.h
        src/account/account.ui
        src/basewin/basewin.cpp
        src/basewin/basewin.h
        src/finder/BinarySearchTree.h
        src/repetitors/Repetitor.h
)
target_link_libraries(RepetitorPlatform
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)

endif ()
