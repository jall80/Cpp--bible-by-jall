#include <vector>
#include <string>
#include <cstdint>
#include <array>
#include <optional>
#include "../constants/constants.h"
#include "../structures/structures.h"

// Generalscreen Initialization
ScreenParams generalScreen(SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50, 50, 50);

/**
 * @brief Creates and initializes a 2D grid (matrix) of blocks with dimensions based on the given width, height, and block size.
 * 
 * @param width The total width of the grid area in pixels.
 * @param height The total height of the grid area in pixels.
 * @param blockSize The size (both width and height) of each block in pixels.
 * @return std::vector<std::vector<Block>> A 2D vector representing the grid, where each element is a Block.
 *         The grid is organized in a (columns, rows) layout.
 */
std::vector<std::vector<Block>> createGrid(int width, int height, int blockSize) {

    /*
    // Validate input: blockSize shouldn't be zero nor less
    VALIDATE_NOT_BELOW_LIMIT(blockSize, 1);

    // Validate input: width shouldn't be less than blockSize * 2
    VALIDATE_NOT_BELOW_LIMIT(width, blockSize * 2);

    // Validate input: height shouldn't be less than blockSize * 2
    VALIDATE_NOT_BELOW_LIMIT(height, blockSize * 2);

    */

    // Calculate the number of columns and rows based on the width, height, and block size
    uint16_t cols = width / blockSize;
    uint16_t rows = height / blockSize;

    // Create a 2D matrix with 'cols' columns, each initially empty
    std::vector<std::vector<Block>> grid(cols, std::vector<Block>());

    // Populate the grid with blocks
    // Iterate over columns (outer loop) and rows (inner loop)
    for (uint16_t j = 0; j < cols; ++j) {
        for (uint16_t i = 0; i < rows; ++i) {
            // Add a new Block at the calculated position (j * blockSize, i * blockSize)
            grid[j].emplace_back(j * blockSize, i * blockSize);
        }
    }

    // Return the fully initialized grid
    return grid;
}

std::vector<std::vector<Block>> grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);


// Calculate Block Size and Initialize Blocks
uint16_t FourblocksSize = (generalScreen.width - (generalScreen.leftMargin + generalScreen.rightMargin)) / 4;

ScreenBlocks_X general4BlocksX(
    static_cast<uint16_t>(0), 
    static_cast<uint16_t>(FourblocksSize),
    static_cast<uint16_t>(FourblocksSize * 2),
    static_cast<uint16_t>(FourblocksSize * 3)
);

// Cpp icon Initialization using constructor
StructTextureObject iconCpp150("iconCpp150", ICONS_PATH + CPP150_IMAGE_FILE, 150, 150, 0, 0, -1.0f, -2.0f);

std::vector<StructTextureObject> textureInfos = {
    StructTextureObject(BACKGROUND_IMAGE_OBJ, IMAGES_PATH + BACKGROUND_IMAGE_FILE, generalScreen.width, generalScreen.height, 0, 0),
    StructTextureObject(SOUND_ON_OBJ, ICONS_PATH + SOUND_ON_FILE, 50, 50, grid[122][1].x, grid[122][1].y),
    StructTextureObject(SOUND_OFF_OBJ, ICONS_PATH + SOUND_OFF_FILE, 50, 50, grid[122][1].x, grid[122][1].y),
    StructTextureObject(CPP100FILL_IMAGE_OBJ, ICONS_PATH + CPP100FILL_IMAGE_FILE, 50, 50, grid[122][8].x, grid[122][8].y),
    StructTextureObject(X100_IMAGE_OBJ, ICONS_PATH + X100_IMAGE_FILE, 50, 50, grid[122][8].x, grid[122][8].y),
    StructTextureObject(DOWN_ARROW_IMAGE_OBJ, ICONS_PATH + DOWN_ARROW_IMAGE_FILE, 64, 64, static_cast<uint16_t>(general4BlocksX.blockX2 - 200), static_cast<uint16_t>(generalScreen.height - generalScreen.bottomMargin - 50)),
    StructTextureObject(UP_ARROW_IMAGE_OBJ, ICONS_PATH + UP_ARROW_IMAGE_FILE, 64, 64, static_cast<uint16_t>(general4BlocksX.blockX2 - 250), static_cast<uint16_t>(generalScreen.height - generalScreen.bottomMargin - 50)),
};

std::vector<LineTextParams> TopicFloatingpointTypes = {
    LineTextParams("Description", 0, 0, CRTGreen, "Description", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("Example", 0, 0, CRTGreen, "Example", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("Practice", 0, 0, CRTGreen, "Practice", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
};

std::vector<LineTextParams> TopicIntegralTypes = {
    LineTextParams("1.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("2.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("3.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("4.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("5.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("6.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("7.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("8.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("9.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("10.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("11.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("12.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("13.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("14.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("15.Practice", 0, 0, CRTGreen, "GGPractice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("16.Description", 0, 0, CRTGreen, "GGDescription gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("17.Example", 0, 0, CRTGreen, "GGExample gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("18.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("19.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("20.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
    LineTextParams("21.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3),
};

std::vector<LineTextParams> introductionTopics = {
    LineTextParams("Topic1-1", 0, 0, CRTGreen, "History and Overview of C++", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2),
    LineTextParams("Topic1-2", 0, 0, CRTGreen, "Setting Up the Development Environment", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2),
    LineTextParams("Topic1-3", 0, 0, CRTGreen, "Basic Syntax and Structure", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2),
};

std::vector<LineTextParams> dataTypesTopics = {
    LineTextParams("Topic2-1", 0, 0, CRTGreen, "Integral Types", RETRO_FONT_PATH, NORMAL_FONT, false, TopicIntegralTypes, 2),
    LineTextParams("Topic2-2", 0, 0, CRTGreen, "Floating-point Types", RETRO_FONT_PATH, NORMAL_FONT, false, TopicFloatingpointTypes, 2),
    LineTextParams("Topic2-3", 0, 0, CRTGreen, "Character Types", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2),
    LineTextParams("Topic2-4", 0, 0, CRTGreen, "Boolean Type", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2),
    LineTextParams("Topic2-5", 0, 0, CRTGreen, "Void Type", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2),
};

LineTextParams mainMenuParams("mainMenu", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "MAIN MENU", RETRO_FONT_PATH, MENU_FONT_SIZE, true, std::nullopt, 0);

std::vector<LineTextParams> generalTopics = {
    LineTextParams("Topic1", 0, 0, CRTGreen, "Introduction to C++ Programming", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic2", 0, 0, CRTGreen, "Data Types in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1),
    LineTextParams("Topic3", 0, 0, CRTGreen, "Control Structures in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic4", 0, 0, CRTGreen, "Functions and Parameters in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic5", 0, 0, CRTGreen, "Object-Oriented Programming Concepts", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic6", 0, 0, CRTGreen, "Memory Management", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic7", 0, 0, CRTGreen, "Standard Template Library (STL)", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic8", 0, 0, CRTGreen, "File Handling in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic9", 0, 0, CRTGreen, "Error Handling and Debugging", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic10", 0, 0, CRTGreen, "Advanced Topics in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),

    LineTextParams("Topic11", 0, 0, CRTGreen, "GGG Introduction to C++ Programming", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic12", 0, 0, CRTGreen, "GGG Data Types in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1),
    LineTextParams("Topic13", 0, 0, CRTGreen, "GGG Control Structures in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic14", 0, 0, CRTGreen, "GGG Functions and Parameters in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic15", 0, 0, CRTGreen, "GGGG Object-Oriented Programming Concepts", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic16", 0, 0, CRTGreen, "GGG Memory Management", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic17", 0, 0, CRTGreen, "GGG Standard Template Library (STL)", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic18", 0, 0, CRTGreen, "GGG File Handling in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic19", 0, 0, CRTGreen, "GGG Error Handling and Debugging", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic20", 0, 0, CRTGreen, "GGG Advanced Topics in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),

    LineTextParams("Topic21", 0, 0, CRTGreen, "GGG Introduction to C++ Programming", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic22", 0, 0, CRTGreen, "GGG Data Types in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1),
    LineTextParams("Topic23", 0, 0, CRTGreen, "GGG Control Structures in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic24", 0, 0, CRTGreen, "GGG Functions and Parameters in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic25", 0, 0, CRTGreen, "GGGG Object-Oriented Programming Concepts", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic26", 0, 0, CRTGreen, "GGG Memory Management", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic27", 0, 0, CRTGreen, "GGG Standard Template Library (STL)", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic28", 0, 0, CRTGreen, "GGG File Handling in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic29", 0, 0, CRTGreen, "GGG Error Handling and Debugging", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1),
    LineTextParams("Topic30", 0, 0, CRTGreen, "GGG Advanced Topics in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1),
};
