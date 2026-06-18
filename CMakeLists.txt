cmake_minimum_required(VERSION 3.16)

project(BioAnalyzerApp VERSION 0.1 LANGUAGES CXX)

# Enable Qt meta-object compiler and UI compiler
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

<<<<<<< Updated upstream
# Find Qt (supports Qt5 and Qt6)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Charts)
=======
# Find Qt6 (only Qt6, no Qt5 fallback)
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts LinguistTools)
>>>>>>> Stashed changes

# Add the DLL subproject
add_subdirectory(BioAnalyzerDLL)

# Translation files
set(TS_FILES BioAnalyzerApp_pl_PL.ts)
qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})

# Qt app sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${QM_FILES}
)

# Create the Qt executable
qt_add_executable(BioAnalyzerApp MANUAL_FINALIZATION ${PROJECT_SOURCES})
qt_finalize_executable(BioAnalyzerApp)

<<<<<<< Updated upstream
# Link Qt libraries
target_link_libraries(BioAnalyzerApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)
=======
# Link Qt libraries (including Charts)
target_link_libraries(BioAnalyzerApp PRIVATE Qt6::Widgets Qt6::Charts)
>>>>>>> Stashed changes

# Copy the DLL to the output directory (Windows only)
if(WIN32)
    add_custom_command(TARGET BioAnalyzerApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:BioAnalyzerDLL>"
            "$<TARGET_FILE_DIR:BioAnalyzerApp>/BioAnalyzer.dll"
    )
endif()

# macOS/iOS bundle settings (optional)
set_target_properties(BioAnalyzerApp PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BioAnalyzerApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    WIN32_EXECUTABLE TRUE
<<<<<<< Updated upstream
)

# --- Installation (optional) ---
include(GNUInstallDirs)
install(TARGETS BioAnalyzerApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize Qt6 executable
if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(BioAnalyzerApp)
endif()
=======
)
>>>>>>> Stashed changes
