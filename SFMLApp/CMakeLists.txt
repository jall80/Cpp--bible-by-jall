cmake_minimum_required(VERSION 3.10)

# Project name
project(SFMLApp)

# Define C++ version and compilation flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML directories (adjust according to your path)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIB_DIR "${SFML_DIR}/lib")
set(SFML_BIN_DIR "${SFML_DIR}/bin")
set(FONTS_DIR "${CMAKE_SOURCE_DIR}/fonts")
set(AUDIOS_DIR "${CMAKE_SOURCE_DIR}/audios")
set(IMAGES_DIR "${CMAKE_SOURCE_DIR}/images")
set(CONSTANTS_DIR "${CMAKE_SOURCE_DIR}/src/constants")

# Include necessary directories
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})
include_directories(${CONSTANTS_DIR})

# Add the source file
add_executable(SFMLApp 
    src/main.cpp
    src/constants/constants.cpp
)

# Link SFML with the executable
target_link_libraries(SFMLApp sfml-graphics sfml-audio sfml-window sfml-system)

# Copy SFML DLLs to the output directory
file(GLOB SFML_DLLS "${SFML_BIN_DIR}/*.dll")
foreach(DLL ${SFML_DLLS})
    add_custom_command(TARGET SFMLApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL} $<TARGET_FILE_DIR:SFMLApp>)
endforeach()

# Copy audio files to the output directory
add_custom_command(TARGET SFMLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${AUDIOS_DIR} $<TARGET_FILE_DIR:SFMLApp>/audios)

# Copy fonts to the output directory
add_custom_command(TARGET SFMLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${FONTS_DIR} $<TARGET_FILE_DIR:SFMLApp>/fonts)

# Copy fonts to the output directory
add_custom_command(TARGET SFMLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${IMAGES_DIR} $<TARGET_FILE_DIR:SFMLApp>/images)
