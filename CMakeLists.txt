cmake_minimum_required(VERSION 3.25)
project(Sudoku)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (QT_QUICK_CONTROLS_IGNORE_CUSTOMIZATION_WARNINGS TRUE)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)

qt_add_executable(Sudoku src/main.cpp)

qt_add_qml_module(Sudoku
        VERSION 1.0
        URI SudokuModule
        RESOURCE_PREFIX /
        SOURCES
        src/game/SudokuSolver.cpp
        src/game/SudokuSolver.hpp
        src/game/Sudoku.cpp
        src/game/Sudoku.hpp
        src/game/SudokuGrid.cpp
        src/game/SudokuGrid.hpp
        src/game/SudokuGridStyle.cpp
        src/game/SudokuGridStyle.hpp
        src/records/RecordStorage.cpp
        src/records/RecordStorage.hpp
        src/records/constants.hpp
        src/LabelStorage.cpp
        src/LabelStorage.hpp
        QML_FILES
        src/main.qml
        src/mainMenu.qml
        src/languages.qml
        src/game/game.qml
        src/game/difficultyChoice.qml
        src/records/records.qml
)

target_link_libraries(Sudoku PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Qml)
target_include_directories(Sudoku PUBLIC src src/game src/records)

qt_add_resources(Sudoku "resources"
        PREFIX "/"
        FILES ./resources/language.png
        ./resources/languages.json
)

 if (ANDROID)
     set_target_properties(Sudoku PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../android"
     )
 endif ()

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()
    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()
    add_custom_command(TARGET Sudoku POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Sudoku> $<TARGET_FILE_DIR:Sudoku>
            COMMAND_EXPAND_LISTS
            )
    add_custom_command(TARGET Sudoku POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${QT_INSTALL_PATH}/qml $<TARGET_FILE_DIR:Sudoku>/qml
            COMMAND_EXPAND_LISTS
            )
endif()