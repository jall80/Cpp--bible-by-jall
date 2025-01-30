#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <memory> // smart pointers (consider change some shared pointers to unique)
#include <filesystem> // For filesystem operations (No used yet, it could be used later)
#include <cstdint> // different int types
#include <optional>
#include <thread>
#include <atomic>  // variables used in different thereads (keep coherence between thereads)
#include <mutex>
#include <chrono>
#include <cstdlib> // Para rand() y srand()
#include <cmath>
#include <stdexcept> // For std::runtime_error
#include <condition_variable>
#include <functional>
#include "constants/constants.h" 



// Arrows icons control
enum class Arrow {
        None = 0,
        Up = 1,
        Down = 2,
        Both = 3,
        Error = -1
};



// Structure to represent a block of 30x30 pixels
struct Block {
    uint16_t x, y; // Coordinates of the block
    uint16_t width = BLOCK_SIZE; // Width of the block
    uint16_t height = BLOCK_SIZE; // Height of the block

    Block(uint16_t _x, uint16_t _y) : x(_x), y(_y) {}
};

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

auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

// Definitions for Screen and Texture Parameters

// Texture Object Definition
struct StructTextureObject {
    std::string name;
    std::string path;
    uint16_t width;
    uint16_t height;
    uint16_t x_position;
    uint16_t y_position;
    float velocity_x;
    float velocity_y;
};


// Screen Parameters Definition
struct ScreenParams {
    uint16_t width;
    uint16_t height;
    uint16_t leftMargin;
    uint16_t rightMargin;
    uint16_t topMargin;
    uint16_t bottomMargin;
};

// Generalscreen Initialization
ScreenParams generalScreen = {SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50, 50, 50};

// Screen Blocks Definition
struct ScreenBlocks_X {
    uint16_t blockX1;
    uint16_t blockX2;
    uint16_t blockX3;
    uint16_t blockX4;
};

// Calculate Block Size and Initialize Blocks
uint16_t FourblocksSize = (generalScreen.width - (generalScreen.leftMargin + generalScreen.rightMargin)) / 4;

ScreenBlocks_X general4BlocksX = {
    static_cast<uint16_t>(0), 
    static_cast<uint16_t>(FourblocksSize),
    static_cast<uint16_t>(FourblocksSize * 2),
    static_cast<uint16_t>(FourblocksSize * 3),
};

///////////////INITS//////////////////////////////////////////

std::vector<StructTextureObject> textureInfos = {
    {BACKGROUND_IMAGE_OBJ, IMAGES_PATH + BACKGROUND_IMAGE_FILE, generalScreen.width, generalScreen.height, 0, 0},
    {SOUND_ON_OBJ, ICONS_PATH + SOUND_ON_FILE, 50, 50, grid[122][1].x, grid[122][1].y},
    {SOUND_OFF_OBJ, ICONS_PATH + SOUND_OFF_FILE, 50, 50, grid[122][1].x, grid[122][1].y},
    {CPP100FILL_IMAGE_OBJ, ICONS_PATH + CPP100FILL_IMAGE_FILE, 50, 50, grid[122][8].x, grid[122][8].y},
    {X100_IMAGE_OBJ, ICONS_PATH + X100_IMAGE_FILE, 50, 50, grid[122][8].x, grid[122][8].y},
    {DOWN_ARROW_IMAGE_OBJ, ICONS_PATH + DOWN_ARROW_IMAGE_FILE, 64, 64, static_cast<uint16_t>(general4BlocksX.blockX2 - 200), static_cast<uint16_t>(generalScreen.height - generalScreen.bottomMargin - 50)},
    {UP_ARROW_IMAGE_OBJ, ICONS_PATH + UP_ARROW_IMAGE_FILE, 64, 64, static_cast<uint16_t>(general4BlocksX.blockX2 - 250), static_cast<uint16_t>(generalScreen.height - generalScreen.bottomMargin - 50)},
};

// Text Line Parameters Definition
struct LineTextParams {
    std::string name;
    uint16_t x_position;
    uint16_t y_position;
    std::array<uint16_t, 3> color;
    std::string text;
    std::string fontPath;
    uint16_t fontSize;
    bool centered;
    std::optional<std::vector<LineTextParams>> subtopics;
    int depth;
};

// Cpp icon Initialization
StructTextureObject iconCpp150 = {"iconCpp150", ICONS_PATH + CPP150_IMAGE_FILE, 150, 150, 0, 0, -1.0f, -2.0f};


std::vector<LineTextParams> TopicFloatingpointTypes = {
    {"Description", 0, 0, CRTGreen, "Description", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"Example", 0, 0, CRTGreen, "Example", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"Practice", 0, 0, CRTGreen, "Practice", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
};

std::vector<LineTextParams> TopicIntegralTypes = {
    {"1.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"2.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"3.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"4.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"5.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"6.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"7.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"8.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"9.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"10.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"11.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"12.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"13.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"14.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"15.Practice", 0, 0, CRTGreen, "GGPractice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"16.Description", 0, 0, CRTGreen, "GGDescription gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"17.Example", 0, 0, CRTGreen, "GGExample gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"18.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},

    {"19.Description", 0, 0, CRTGreen, "Description gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"20.Example", 0, 0, CRTGreen, "Example gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    {"21.Practice", 0, 0, CRTGreen, "Practice gg", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 3},
    
};


std::vector<LineTextParams> introductionTopics = {
    {"Topic1-1", 0, 0, CRTGreen, "History and Overview of C++", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic1-2", 0, 0, CRTGreen, "Setting Up the Development Environment", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic1-3", 0, 0, CRTGreen, "Basic Syntax and Structure", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2},
};


std::vector<LineTextParams> dataTypesTopics = {
    {"Topic2-1", 0, 0, CRTGreen, "Integral Types", RETRO_FONT_PATH, NORMAL_FONT, false, TopicIntegralTypes, 2},
    {"Topic2-2", 0, 0, CRTGreen, "Floating-point Types", RETRO_FONT_PATH, NORMAL_FONT, false, TopicFloatingpointTypes, 2},
    {"Topic2-3", 0, 0, CRTGreen, "Character Types", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic2-4", 0, 0, CRTGreen, "Boolean Type", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2},
    {"Topic2-5", 0, 0, CRTGreen, "Void Type", RETRO_FONT_PATH, NORMAL_FONT, false, std::nullopt, 2},
};

LineTextParams mainMenuParams = {"mainMenu", general4BlocksX.blockX3, generalScreen.topMargin, CRTGreen, "MAIN MENU", RETRO_FONT_PATH, MENU_FONT_SIZE, true};

std::vector<LineTextParams> generalTopics = {
    {"Topic1", 0, 0, CRTGreen, "Introduction to C++ Programming", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic2", 0, 0, CRTGreen, "Data Types in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1},
    {"Topic3", 0, 0, CRTGreen, "Control Structures in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic4", 0, 0, CRTGreen, "Functions and Parameters in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic5", 0, 0, CRTGreen, "Object-Oriented Programming Concepts", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic6", 0, 0, CRTGreen, "Memory Management", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic7", 0, 0, CRTGreen, "Standard Template Library (STL)", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic8", 0, 0, CRTGreen, "File Handling in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic9", 0, 0, CRTGreen, "Error Handling and Debugging", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic10", 0, 0, CRTGreen, "Advanced Topics in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},

    {"Topic11", 0, 0, CRTGreen, "GGG Introduction to C++ Programming", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic12", 0, 0, CRTGreen, "GGG Data Types in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1},
    {"Topic13", 0, 0, CRTGreen, "GGG Control Structures in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic14", 0, 0, CRTGreen, "GGG Functions and Parameters in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic15", 0, 0, CRTGreen, "GGGG Object-Oriented Programming Concepts", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic16", 0, 0, CRTGreen, "GGG Memory Management", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic17", 0, 0, CRTGreen, "GGG Standard Template Library (STL)", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic18", 0, 0, CRTGreen, "GGG File Handling in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic19", 0, 0, CRTGreen, "GGG Error Handling and Debugging", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic20", 0, 0, CRTGreen, "GGG Advanced Topics in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1},


    {"Topic11", 0, 0, CRTGreen, "GGG Introduction to C++ Programming", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic12", 0, 0, CRTGreen, "GGG Data Types in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1},
    {"Topic13", 0, 0, CRTGreen, "GGG Control Structures in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic14", 0, 0, CRTGreen, "GGG Functions and Parameters in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic15", 0, 0, CRTGreen, "GGGG Object-Oriented Programming Concepts", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic16", 0, 0, CRTGreen, "GGG Memory Management", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic17", 0, 0, CRTGreen, "GGG Standard Template Library (STL)", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic18", 0, 0, CRTGreen, "GGG File Handling in C++", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic19", 0, 0, CRTGreen, "GGG Error Handling and Debugging", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic20", 0, 0, CRTGreen, "GGG Advanced Topics in C++", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1},


    {"Topic18", 0, 0, CRTGreen, "XXXXXXXXXXXXXXXXXXX", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic19", 0, 0, CRTGreen, "yyyyyyyyyyyyyyyyyyy", RETRO_FONT_PATH, NORMAL_FONT, false, introductionTopics, 1},
    {"Topic20", 0, 0, CRTGreen, "fffffffffffffffff", RETRO_FONT_PATH, NORMAL_FONT, false, dataTypesTopics, 1}
};

///////////////TOOLS///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Función para verificar un solo campo
template <typename U>
bool verifyField(const U& field) {
    if constexpr (std::is_integral_v<std::decay_t<U>>) {
        return field > 0;
    } else if constexpr (std::is_floating_point_v<std::decay_t<U>>) {
        return field > 0.0;
    } else if constexpr (std::is_pointer_v<std::decay_t<U>>) {
        return field != nullptr;
    } else {
        // Otros tipos pueden requerir validaciones adicionales
        return true;
    }
}

// Plantilla para recorrer todos los miembros de una estructura
template <typename T, typename MemberType>
bool verifyStructMember(const T& s, MemberType T::*member) {
    return verifyField(s.*member);
}

// Función genérica para recorrer todos los miembros
template <typename T, typename... Members>
bool verifyStructValues(const T& s, Members T::*... members) {
    // Usamos un "fold expression" para aplicar la verificación a todos los miembros
    return (... && verifyStructMember(s, members));  // Aplica la verificación para cada miembro
}


/**
 * @brief Checks if a container is empty and throws an exception if it is.
 * 
 * @tparam Container The type of the container (e.g., std::vector, std::list, std::set).
 * @param container The container to check.
 * @param varName The name of the container variable as a string.
 * @throws std::invalid_argument if the container is empty.
 */
template <typename Container>
void validateNotEmpty(const Container& container, const std::string& varName, const std::string& funcName) {
    if (container.empty()) {
        throw std::invalid_argument("Validation failed in function \"" + funcName +
                            "\": The container \"" + varName + "\" cannot be empty.");
    }
}

// Macro to simplify calling the function with the variable name
#define VALIDATE_NOT_EMPTY(container, funcName) validateNotEmpty(container, #container, funcName)

/**
 * @brief Checks if a value is below a specified limit and throws an exception if it is.
 * 
 * @tparam T The type of the value (e.g., int, float, double).
 * @param value The value to check.
 * @param limit The lower limit the value must meet or exceed.
 * @param valueName The name of the variable being checked.
 * @param funcName The name of the function where the check is performed.
 * @throws std::invalid_argument if the value is below the specified limit.
 */
template <typename T>
void validateNotBelowLimit(const T& value, const T& limit, const std::string& valueName, const std::string& limitName, const std::string& funcName) {
    if (value < limit) {
    throw std::invalid_argument("Validation failed in function \"" + funcName +
                                "\": The parameter \"" + valueName + "\" -> " + std::to_string(value) +
                                " cannot be less than \"" + limitName  + "\" -> " + std::to_string(limit) + ".");
    }
}

// Macro to simplify calling the function with the variable name
#define VALIDATE_NOT_BELOW_LIMIT(value, limit) validateNotBelowLimit(value, limit, #value, #limit, __func__)


// Macro para obtener el nombre del vector
#define VALIDATE_VECTOR(vector, funcName) validateLineTextParams(vector, #vector, funcName)

/**
 * @brief Validates a vector of LineTextParams structures for correctness.
 * 
 * This function ensures that all fields in each `LineTextParams` structure
 * in the vector meet expected criteria (e.g., positive values, non-empty strings, valid ranges).
 * 
 * @param paramsList A vector of `LineTextParams` structures to validate.
 * @param vectorName The name of the vector for contextual error messages.
 * @param funcName The name of the function for contextual error messages.
 * @throws std::invalid_argument if any validation fails.
 */
void validateLineTextParams(const std::vector<LineTextParams>& paramsList, 
                            const std::string& vectorName, 
                            const std::string& funcName = "validateLineTextParams") {
    
    for (size_t idx = 0; idx < paramsList.size(); ++idx) {
        const auto& params = paramsList[idx];
        std::string errorMessage = funcName + " -> ( Vector: " + vectorName + ", index: " + std::to_string(idx + 1) + ")";

        // Validate non-empty string fields
        if (params.name.empty()) {
            throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                        "': 'name' field must not be empty.");
        }
        if (params.text.empty()) {
            throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                        "': 'text' field must not be empty.");
        }
        if (params.fontPath.empty()) {
            throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                        "': 'fontPath' field must not be empty.");
        }

        // Validate positive numeric fields
        if (params.x_position < 0 || params.y_position < 0) {
            throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                        "': x_position and y_position must not be negative.");
        }

        if (params.fontSize <= 0) {
            throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                        "': fontSize must be greater than 0.");
        }

        // Validate color array values (must be in the range [0, 255])
        for (size_t i = 0; i < params.color.size(); ++i) {
            if (params.color[i] > 255 || params.color[i] < 0) {
                throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                            "': color[" + std::to_string(i) + "] must be in the range [0, 255].");
            }
        }

        // Validate depth (must be non-negative)
        if (params.depth < 0) {
            throw std::invalid_argument(LINE_TEXT_ERROR + errorMessage +
                                        "': depth must be non-negative.");
        }

        // Validate subtopics recursively if present
        if (params.subtopics.has_value()) {
            VALIDATE_VECTOR(params.subtopics.value(), errorMessage);
        }
    }
}

void verifyScreenParams(const ScreenParams& screenParams) {
    // Validate that the struct values are not null or less than zero
    if (!verifyStructValues(screenParams, &ScreenParams::width, &ScreenParams::height,
                                      &ScreenParams::leftMargin, &ScreenParams::rightMargin,
                                      &ScreenParams::topMargin, &ScreenParams::bottomMargin)) {
        throw std::invalid_argument("Error: in " + std::string(__func__) + ", the 'screenParams' struct contains invalid values");
    }

    // Ensure all margins are at least 1/8 of the width and height
    if (screenParams.leftMargin > screenParams.width / 6 ||
        screenParams.rightMargin > screenParams.width / 6 ||
        screenParams.topMargin > screenParams.height / 6 ||
        screenParams.bottomMargin > screenParams.height / 6) {
        throw std::invalid_argument("Error: in " + std::string(__func__) + ", margins must be at least 1/6 of the width and height");
    }
}

/**
 * @brief Recursively enumerates topics and their subtopics, adding a numbered format based on depth.
 * 
 * @param topics A reference to a vector of LineTextParams objects representing the topics to be enumerated.
 *               Each LineTextParams contains a `text` field and an optional pointer to its subtopics.
 * @param depth (Optional) The current depth level of enumeration. Defaults to 0 for top-level topics.
 *              Determines the indentation of the numbering.
 */
void enumerateTopics(std::vector<LineTextParams>& topics, int depth = 0) {

    // Validate input: topics vector should not be empty
    VALIDATE_NOT_EMPTY(topics, std::string(__func__));
    // Validate input: depth should not be negative
    VALIDATE_NOT_BELOW_LIMIT(depth, 0);

    // Iterate through the list of topics
    for (size_t i = 0; i < topics.size(); ++i) {
        // Create a string stream to format the numbered text
        std::ostringstream numberedText;
        // Add indentation based on the current depth and number each topic
        numberedText << std::string(depth * 2, ' ') << (i + 1) << ". " << topics[i].text;
        // Update the topic's text with the formatted numbered string
        topics[i].text = numberedText.str();

        // Check if the current topic has subtopics
        if (topics[i].subtopics) {
            // Recursively enumerate subtopics with increased depth
            enumerateTopics(*topics[i].subtopics, depth + 1);
        }
    }
}



/**
 * @brief Filters topics based on their width, removing those that exceed the maximum width allowed for the screen.
 *        If a topic exceeds the allowed width, an error is thrown.
 * 
 * @param topics A reference to a vector of LineTextParams representing the topics to be checked.
 *               Each LineTextParams contains a `text` field and an optional pointer to its subtopics.
 * @param screenParams A reference to the ScreenParams structure, which contains information about the screen dimensions
 *                     and margins used to calculate the maximum allowed width for the topics.
 * 
 * @throws std::runtime_error If a topic exceeds the maximum width, an error is thrown with a descriptive message.
 */
void filterTopicsBySize(std::vector<LineTextParams>& topics, const ScreenParams& screenParams) {

    // Validate input: topics vector should not be empty
    VALIDATE_NOT_EMPTY(topics, std::string(__func__));

    // Calculate the maximum width available for a topic on the screen
    const uint16_t maxWidth = screenParams.width - general4BlocksX.blockX2 - screenParams.leftMargin;

    // Lambda function to check if a topic fits within the screen width
    auto fitsWithinScreen = [&](const LineTextParams& topic) {
        // Estimate the width of the topic text in pixels based on font size and font resize factor
        uint16_t estimatedWidth = topic.text.size() * (topic.fontSize * 0.9) * FONT_RESIZE;
        return estimatedWidth <= maxWidth;
    };

    // Iterate through the topics and validate their size
    topics.erase(std::remove_if(topics.begin(), topics.end(), [&](LineTextParams& topic) {
        // Recursively filter subtopics to ensure their size also fits within the screen
        if (topic.subtopics) {
            filterTopicsBySize(*topic.subtopics, screenParams);
        }

        // If the topic doesn't fit within the allowed width, throw an error
        if (!fitsWithinScreen(topic)) {
            throw std::runtime_error("Topic '" + topic.name + "' exceeds the maximum width of " + std::to_string(maxWidth) + " pixels.");
        }

        // No topics are deleted here, only validated for size
        return false;
    }), topics.end());
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TOOLS

/**
 * @class Stack
 * @brief A simple stack implementation using a vector to store int16_t values.
 *        The stack supports basic stack operations: push, pop, peek, and check if it's empty.
 */
class Stack {
private:
    std::vector<int16_t> stack;  ///< The internal vector that holds the stack elements.

public:
    /**
     * @brief Adds a value to the top of the stack.
     * 
     * @param value The value to be added to the stack.
     */
    void push(int16_t value) {
        stack.push_back(value);  ///< Adds the value to the stack (end of the vector).
    }

    /**
     * @brief Removes and returns the top value of the stack.
     * 
     * @return int16_t The value at the top of the stack. 
     *         Returns -1 if the stack is empty (error case).
     */
    int16_t pop() {
        if (!stack.empty()) {
            int16_t value = stack.back();  ///< Retrieve the top value.
            stack.pop_back();  ///< Remove the top value from the stack.
            return value;
        } else {
            std::cerr << "Error: Pila vacía." << std::endl;  ///< Error message if stack is empty.
            return -1;  ///< Return an error value (-1).
        }
    }

    /**
     * @brief Returns the top value of the stack without removing it.
     * 
     * @return int16_t The value at the top of the stack.
     *         Returns -1 if the stack is empty (error case).
     */
    int16_t peek() const {
        if (!stack.empty()) {
            return stack.back();  ///< Return the top value without removing it.
        } else {
            std::cerr << "Error: Pila vacía." << std::endl;  ///< Error message if stack is empty.
            return -1;  ///< Return an error value (-1).
        }
    }

    /**
     * @brief Checks if the stack is empty.
     * 
     * @return true If the stack is empty.
     * @return false If the stack contains one or more elements.
     */
    bool isEmpty() const {
        return stack.empty();  ///< Return whether the stack is empty.
    }
};


//TOOLS
/**
 * @class ThreadController
 * @brief A class that controls a thread, allowing it to be started, paused, resumed, and stopped.
 *        It provides thread management with synchronization mechanisms like mutexes and condition variables.
 */
class ThreadController {

private:
    std::thread controlledThread;           ///< The controlled thread.
    std::mutex controlMutex;                ///< Mutex used to synchronize access to control flags.
    std::condition_variable pauseCondition; ///< Condition variable to handle pausing and resuming the thread.
    std::atomic<bool> stopFlag;             ///< Atomic flag to indicate if the thread should stop.
    std::atomic<bool> pauseFlag;            ///< Atomic flag to indicate if the thread is paused.

public:
    /**
     * @brief Constructor that initializes the thread control flags.
     */
    ThreadController() : stopFlag(false), pauseFlag(false) {}

    /**
     * @brief Starts the thread, executing the given function.
     * 
     * @param func The function to be executed by the thread.
     */
    void start(std::function<void()> func) {
        stopFlag = false;  ///< Reset stop flag before starting the thread.
        pauseFlag = false; ///< Reset pause flag before starting the thread.

        // Start the thread with the given function
        controlledThread = std::thread([this, func]() {
            while (!stopFlag) {
                // Handle pause: wait if the thread is in a paused state
                {
                    std::unique_lock<std::mutex> lock(controlMutex);
                    pauseCondition.wait(lock, [this]() { return !pauseFlag || stopFlag; });
                }

                // If the stop flag is set, break the loop and stop the thread
                if (stopFlag) break;

                // Execute the provided function
                func();
            }
        });
    }

    /**
     * @brief Pauses the thread.
     */
    void pause() {
        {
            std::lock_guard<std::mutex> lock(controlMutex);
            pauseFlag = true; ///< Set the pause flag to true to pause the thread.
        }
        pauseCondition.notify_all();  ///< Notify the thread to check the pause condition.
    }

    /**
     * @brief Resumes the paused thread.
     */
    void resume() {
        {
            std::lock_guard<std::mutex> lock(controlMutex);
            pauseFlag = false; ///< Set the pause flag to false to resume the thread.
        }
        pauseCondition.notify_all();  ///< Notify the thread to check the resume condition.
    }

    /**
     * @brief Stops the thread, ensuring it completes its current execution.
     */
    void stop() {
        {
            std::lock_guard<std::mutex> lock(controlMutex);
            stopFlag = true;  ///< Set the stop flag to true to stop the thread.
            pauseFlag = false; ///< Ensure the thread is not paused when stopping.
        }
        pauseCondition.notify_all();  ///< Notify the thread to check the stop condition.
        
        if (controlledThread.joinable()) {
            controlledThread.join();  ///< Wait for the thread to finish execution.
        }
    }

    /**
     * @brief Checks if the thread is currently paused.
     * 
     * @return true if the thread is paused, false otherwise.
     */
    bool isPaused() const {
        return pauseFlag.load();  ///< Return the value of the pause flag.
    }

    /**
     * @brief Gets a reference to the pause flag.
     * 
     * @return A reference to the atomic pause flag.
     */
    std::atomic<bool>& getPauseFlag() {
        return pauseFlag;  ///< Return the reference to the pause flag.
    }

    /**
     * @brief Destructor that ensures the thread is stopped before the object is destroyed.
     */
    ~ThreadController() {
        stop();  ///< Ensure the thread is stopped when the object is destroyed.
    }
};


/**
 * @class BaseObject
 * @brief A base class representing an object with position, size, and velocity.
 *        It includes basic attributes such as name, width, height, position, and velocity.
 */
class BaseObject {
protected:
    uint16_t height;         ///< Height of the object.
    uint16_t width;          ///< Width of the object.
    uint16_t x_position;     ///< X-coordinate position of the object.
    uint16_t y_position;     ///< Y-coordinate position of the object.
    std::string name;        ///< Name of the object.
    float velocity_x;        ///< Velocity of the object in the X direction.
    float velocity_y;        ///< Velocity of the object in the Y direction.

public:
    /**
     * @brief Constructor to initialize the object without velocity.
     * 
     * @param _name The name of the object.
     * @param _width The width of the object.
     * @param _height The height of the object.
     * @param _x_position The X-coordinate position of the object.
     * @param _y_position The Y-coordinate position of the object.
     */
    BaseObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), velocity_x(0.0f), velocity_y(0.0f) {}

    /**
     * @brief Constructor to initialize the object with velocity.
     * 
     * @param _name The name of the object.
     * @param _width The width of the object.
     * @param _height The height of the object.
     * @param _x_position The X-coordinate position of the object.
     * @param _y_position The Y-coordinate position of the object.
     * @param _velocity_x The velocity of the object in the X direction.
     * @param _velocity_y The velocity of the object in the Y direction.
     */
    BaseObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position, float _velocity_x, float _velocity_y)
        : name(_name), width(_width), height(_height), x_position(_x_position), y_position(_y_position), velocity_x(_velocity_x), velocity_y(_velocity_y) {}

    /**
     * @brief Destructor.
     * The destructor is default as no special cleanup is needed for this class.
     */
    virtual ~BaseObject() = default;

    /**
     * @brief Getter for the object's name.
     * 
     * @return The name of the object.
     */
    std::string getName() const { return name; }

    /**
     * @brief Getter for the object's height.
     * 
     * @return The height of the object.
     */
    uint16_t getHeight() const { return height; }

    /**
     * @brief Getter for the object's width.
     * 
     * @return The width of the object.
     */
    uint16_t getWidth() const { return width; }

    /**
     * @brief Getter for the object's X-coordinate position.
     * 
     * @return The X-coordinate position of the object.
     */
    uint16_t getXPosition() const { return x_position; }

    /**
     * @brief Getter for the object's Y-coordinate position.
     * 
     * @return The Y-coordinate position of the object.
     */
    uint16_t getYPosition() const { return y_position; }

    /**
     * @brief Getter for the object's velocity in the X direction.
     * 
     * @return The velocity of the object in the X direction.
     */
    float getVelocityX() const { return velocity_x; }

    /**
     * @brief Getter for the object's velocity in the Y direction.
     * 
     * @return The velocity of the object in the Y direction.
     */
    float getVelocityY() const { return velocity_y; }

    /**
     * @brief Setter for the object's name.
     * 
     * @param _name The new name of the object.
     */
    void setName(const std::string& _name) { name = _name; }

    /**
     * @brief Setter for the object's height.
     * 
     * @param _height The new height of the object.
     */
    void setHeight(uint16_t _height) { height = _height; }

    /**
     * @brief Setter for the object's width.
     * 
     * @param _width The new width of the object.
     */
    void setWidth(uint16_t _width) { width = _width; }

    /**
     * @brief Setter for the object's X-coordinate position.
     * 
     * @param _x_position The new X-coordinate position of the object.
     */
    void setXPosition(uint16_t _x_position) { x_position = _x_position; }

    /**
     * @brief Setter for the object's Y-coordinate position.
     * 
     * @param _y_position The new Y-coordinate position of the object.
     */
    void setYPosition(uint16_t _y_position) { y_position = _y_position; }

    /**
     * @brief Setter for the object's velocity in the X direction.
     * 
     * @param _velocity_x The new velocity in the X direction.
     */
    void setVelocityX(float _velocity_x) { velocity_x = _velocity_x; }

    /**
     * @brief Setter for the object's velocity in the Y direction.
     * 
     * @param _velocity_y The new velocity in the Y direction.
     */
    void setVelocityY(float _velocity_y) { velocity_y = _velocity_y; }
};


/**
 * @class TextureObject
 * @brief A derived class from BaseObject that adds texture handling functionality to the object.
 *        This class uses the SFML library to load and display textures for graphical representation.
 */
class TextureObject : public BaseObject {
private:
    sf::Texture texture;         ///< Texture for the object (SFML Texture).
    sf::Sprite textureSprite;    ///< Sprite to render the texture on screen (SFML Sprite).

public:
    /**
     * @brief Constructor to initialize the texture object without velocity.
     *        Inherits from BaseObject and initializes the texture object.
     * 
     * @param _name The name of the object.
     * @param _width The width of the object.
     * @param _height The height of the object.
     * @param _x_position The X-coordinate position of the object.
     * @param _y_position The Y-coordinate position of the object.
     */
    TextureObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position)
        : BaseObject(_name, _width, _height, _x_position, _y_position) {}

    /**
     * @brief Constructor to initialize the texture object with velocity.
     *        Inherits from BaseObject and initializes the texture object with velocity.
     * 
     * @param _name The name of the object.
     * @param _width The width of the object.
     * @param _height The height of the object.
     * @param _x_position The X-coordinate position of the object.
     * @param _y_position The Y-coordinate position of the object.
     * @param _velocity_x The velocity of the object in the X direction.
     * @param _velocity_y The velocity of the object in the Y direction.
     */
    TextureObject(const std::string& _name, uint16_t _width, uint16_t _height, uint16_t _x_position, uint16_t _y_position, float _velocity_x, float _velocity_y)
        : BaseObject(_name, _width, _height, _x_position, _y_position, _velocity_x, _velocity_y) {}

    /**
     * @brief Destructor for the TextureObject class.
     *        Prints a message when destroying the object, useful for debugging.
     */
    virtual ~TextureObject() {
        std::cout << "Destroying TextureObject: " << name << std::endl;
    }

    /**
     * @brief Loads the texture from a file and sets up the texture sprite.
     *        Adjusts the sprite's position and scale based on the object dimensions.
     * 
     * @param path The file path to the texture image.
     * @return true if the texture was successfully loaded, false otherwise.
     */
    bool loadTexture(const std::string& path) {
        if (!texture.loadFromFile(path)) {   // Attempt to load the texture from file.
            std::cerr << "Error loading texture from file: " << path << std::endl;
            return false; // Return false if texture load fails.
        }
        textureSprite.setTexture(texture);  // Set the texture to the sprite.
        textureSprite.setPosition(static_cast<float>(x_position), static_cast<float>(y_position));  // Set sprite position.
        textureSprite.setScale(
            static_cast<float>(width) / texture.getSize().x,   // Scale sprite to fit object width.
            static_cast<float>(height) / texture.getSize().y   // Scale sprite to fit object height.
        );
        return true;   // Return true if texture loading and sprite setup are successful.
    }

    /**
     * @brief Getter for the texture.
     * 
     * @return A reference to the texture object.
     */
    sf::Texture& getTexture() {
        return texture;  // Return the texture object.
    }

    /**
     * @brief Getter for the texture (const version).
     * 
     * @return A constant reference to the texture object.
     */
    const sf::Texture& getTexture() const {
        return texture;  // Return the texture object as a constant reference.
    }

    /**
     * @brief Getter for the texture sprite.
     * 
     * @return A reference to the texture sprite.
     */
    sf::Sprite& getTextureSprite() {
        return textureSprite;  // Return the texture sprite object.
    }

    /**
     * @brief Getter for the texture sprite (const version).
     * 
     * @return A constant reference to the texture sprite.
     */
    const sf::Sprite& getTextureSprite() const {
        return textureSprite;  // Return the texture sprite object as a constant reference.
    }

    /**
     * @brief Updates the position of the sprite based on the object's position.
     *        This ensures the sprite follows the object's position.
     */
    void updatePosition() {
        textureSprite.setPosition(static_cast<float>(x_position), static_cast<float>(y_position));  // Set the sprite's position.
    }

    /**
     * @brief Draws the object (sprite) to the screen.
     *        This method will render the sprite to the given render window.
     * 
     * @param window The SFML render window where the sprite will be drawn.
     */
    void draw(sf::RenderWindow& window) {
        window.draw(textureSprite);  // Draw the texture sprite onto the window.
    }
};


/**
 * @class TextObject
 * @brief Represents a text object for rendering text on a screen with potential child and parent relationships.
 *        This class supports text alignment, color, font management, and hierarchical rendering.
 *
 * @param _name       The name of the object.
 * @param _x_position X-coordinate of the object's position.
 * @param _y_position Y-coordinate of the object's position.
 * @param _color      The RGB color of the text (array of 3 uint16_t values).
 * @param _text       The text string to display.
 * @param _fontPath   Path to the font file.
 * @param _text_size  The size of the text.
 * @param _centerText Boolean flag to specify if the text should be center-aligned.
 *
 * @return None
 */
class TextObject : public BaseObject {
private:
    std::array<uint16_t, 3> color;   // RGB color of the text
    sf::Font font;                  // SFML Font for the text
    sf::Text textObj;               // SFML Text object to hold and display the text
    bool centerText;                // Flag indicating if the text should be center-aligned
    std::string fontPath;           // Path to the font file
    std::vector<std::shared_ptr<TextObject>> children; // List of child text objects
    std::weak_ptr<TextObject> parent; // Weak pointer to the parent text object

public:
    /**
     * @brief Constructor for initializing a TextObject with a specified position, color, text, font, and size.
     * 
     * @param _name       Name of the text object.
     * @param _x_position X-coordinate of the text object's position.
     * @param _y_position Y-coordinate of the text object's position.
     * @param _color      The RGB color of the text.
     * @param _text       The text string to display.
     * @param _fontPath   Path to the font file.
     * @param _text_size  Size of the text.
     * @param _centerText Whether the text should be center-aligned.
     * 
     * @throw std::runtime_error If the font cannot be loaded from the given font path.
     * @return None
     */
    TextObject(const std::string& _name, uint16_t _x_position, uint16_t _y_position, 
               std::array<uint16_t, 3> _color, const std::string& _text, const std::string& _fontPath, 
               uint16_t _text_size, bool _centerText)
        : BaseObject(_name, 0, 0, _x_position, _y_position), color(_color), fontPath(_fontPath), centerText(_centerText) {

        if (!font.loadFromFile(fontPath)) {
            throw std::runtime_error("Failed to load font: " + fontPath);
        }

        textObj.setFont(font);
        textObj.setString(_text);
        textObj.setCharacterSize(_text_size);
        textObj.setFillColor(sf::Color(color[0], color[1], color[2]));

        sf::FloatRect textBounds = textObj.getLocalBounds();
        if (centerText) {
            textObj.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        } else {
            textObj.setOrigin(0, textBounds.top + textBounds.height / 2);
        }

        textObj.setPosition(static_cast<float>(_x_position), static_cast<float>(_y_position));
    }

    /**
     * @brief Destructor for the TextObject.
     *
     * Prints a message to the console when the object is destroyed.
     * 
     * @return None
     */
    virtual ~TextObject() {
        std::cout << "Destroying TextObject: " << name << std::endl;
    }

    /**
     * @brief Sets the parent of the TextObject.
     * 
     * @param _parent A shared pointer to the parent TextObject.
     * @return None
     */
    void setParent(const std::shared_ptr<TextObject>& _parent) {
        parent = _parent;
    }

    /**
     * @brief Returns the parent of the TextObject.
     * 
     * @return A shared pointer to the parent TextObject, or an empty shared pointer if no parent exists.
     */
    std::shared_ptr<TextObject> getParent() const {
        return parent.lock(); // Converts the weak_ptr to shared_ptr if valid
    }

    /**
     * @brief Adds a child TextObject to the current object.
     * 
     * @param child A shared pointer to the child TextObject.
     * @return None
     */
    void addChild(std::shared_ptr<TextObject> child) {
        children.push_back(child);
    }

    /**
     * @brief Returns the list of child TextObjects.
     * 
     * @return A reference to a vector containing shared pointers to child TextObjects.
     */
    const std::vector<std::shared_ptr<TextObject>>& getChildren() const {
        return children;
    }

    /**
     * @brief Draws the text object on the window.
     * 
     * @param window The SFML render window to draw the text object on.
     * 
     * @return None
     */
    void draw(sf::RenderWindow& window) {
        window.draw(textObj);
    }

    /**
     * @brief Prints the hierarchy of the TextObject and its children for debugging purposes.
     * 
     * @param level The current indentation level for printing.
     * 
     * @return None
     */
    void printHierarchy(int level = 0) const {
        std::string indentation(level * 2, ' ');
        std::cout << indentation << "- " << name << std::endl;
        for (const auto& child : children) {
            child->printHierarchy(level + 1);
        }
    }

    /**
     * @brief Updates the position of the text based on the object's coordinates.
     * 
     * @return None
     */
    void updateTextPosition() {
        textObj.setPosition(static_cast<float>(x_position), static_cast<float>(y_position));
    }

    /**
     * @brief Sets the font size of the text object and optionally applies it to all children.
     * 
     * @param newFontSize The new font size to set.
     * @param applyToChildren Whether to apply the new font size to all child TextObjects.
     * 
     * @return None
     */
    void setFontSize(uint16_t newFontSize, bool applyToChildren = false) {
        textObj.setCharacterSize(newFontSize);
        if (applyToChildren) {
            for (auto& child : children) {
                child->setFontSize(newFontSize, applyToChildren);
            }
        }
    }

    /**
     * @brief Returns the color of the text.
     * 
     * @return A 3-element array representing the RGB color.
     */
    std::array<uint16_t, 3> getColor() const {
        return color;
    }

    /**
     * @brief Returns the text string displayed by the object.
     * 
     * @return The text string.
     */
    std::string getText() const {
        return textObj.getString();
    }

    /**
     * @brief Returns the path of the font file.
     * 
     * @return The font file path as a string.
     */
    std::string getFontPath() const {
        return fontPath;
    }

    /**
     * @brief Returns the current size of the text.
     * 
     * @return The font size as an unsigned 16-bit integer.
     */
    uint16_t getTextSize() const {
        return textObj.getCharacterSize();
    }

    /**
     * @brief Returns whether the text is centered.
     * 
     * @return True if the text is centered, false otherwise.
     */
    bool isCentered() const {
        return centerText;
    }

    /**
     * @brief Checks if the text object is a leaf node (has no children).
     * 
     * @return True if the text object has no children, false otherwise.
     */
    bool isLeaf() const {
        return children.empty();
    }

    /**
     * @brief Returns the width of the text.
     * 
     * @return The width of the text as a float.
     */
    float getTextWidth() const {
        return textObj.getLocalBounds().width;
    }

    /**
     * @brief Returns the height of the text.
     * 
     * @return The height of the text as a float.
     */
    float getTextHeight() const {
        return textObj.getLocalBounds().height;
    }

    /**
     * @brief Removes all children from the current TextObject.
     * 
     * @return None
     */
    void removeAllChildren() {
        for (auto& child : children) {
            // Break the parent-child relationship
            if (auto sharedChild = child->getParent()) {
                if (sharedChild.get() == this) {
                    child->setParent(nullptr);
                }
            }
        }
        children.clear(); // Clear the children vector
    }
};



/**
 * @brief Recursively calculates the maximum depth of the tree.
 * 
 * This function traverses the tree starting from the given node, calculating 
 * the depth of each branch. It finds the deepest branch by checking all 
 * children nodes recursively. The maximum depth is the longest path from 
 * the root node to any leaf node.
 * 
 * A leaf node is considered to have a depth of 1, and the depth increases 
 * by 1 for each level deeper into the tree. The function returns the 
 * maximum depth in the tree.
 * 
 * @param node A shared pointer to the TextObject node from which the depth 
 *             calculation starts.
 * @return The maximum depth of the tree. If the node is nullptr (empty tree), 
 *         the function returns 0.
 */
int getMaxDepth(const std::shared_ptr<TextObject>& node) {
    if (!node) {
        return 0; // Tree is empty, depth is 0
    }

    int maxDepth = 0;
    // Recursively calculate the depth for each child node
    for (const auto& child : node->getChildren()) {
        maxDepth = std::max(maxDepth, getMaxDepth(child));
    }
    return maxDepth + 1; // Add 1 to the current node's depth
}

//GGG
/**
 * @brief Finds nested subtopics based on the provided indices.
 * 
 * This function traverses through the levels of topics and subtopics, starting
 * from a general list of topics. It uses a vector of indices to navigate 
 * through each level of the tree-like structure. The function checks if each 
 * topic has subtopics, and if it does, it continues to the next level. If a 
 * leaf node (a topic without subtopics) is encountered, the function returns 
 * an empty vector. If the indices are valid and all levels have subtopics, 
 * the function will return the list of subtopics at the deepest level.
 * 
 * @param generalTopics A vector containing the general topics at the first level.
 * @param indices A vector of indices used to traverse through the levels of subtopics.
 * 
 * @return A vector of `LineTextParams` containing the subtopics at the deepest level
 *         of the hierarchy. If any level doesn't have subtopics or the indices are 
 *         invalid, the function returns an empty vector.
 * 
 * @throws std::out_of_range If an index is out of bounds at any level.
 */
std::vector<LineTextParams> findNestedSubtopics(
    const std::vector<LineTextParams>& generalTopics,
    const std::vector<uint16_t>& indices
) {

    // Validate input: generalTopics vector should not be empty
    VALIDATE_NOT_EMPTY(generalTopics, std::string(__func__));

    // Validate input: indices vector should not be empty
    VALIDATE_NOT_EMPTY(indices, std::string(__func__));

    const std::vector<LineTextParams>* currentLevel = &generalTopics;

    // Traverse through each level of subtopics using the indices
    for (int index : indices) {
        // Check if the index is valid for the current level
        if (index < 0 || index >= currentLevel->size()) {
            throw std::out_of_range("Index out of range in generalTopics or subtopics.");
        }

        // Get the selected topic at the current index
        const LineTextParams& selectedTopic = (*currentLevel)[index];

        // If no subtopics exist at this level, return an empty vector (leaf node)
        if (!selectedTopic.subtopics.has_value()) {
            std::cerr << "Leaf node found. No more submenus.\n";
            return {};  // No more subtopics to explore
        }

        // Move to the next level of subtopics
        currentLevel = &selectedTopic.subtopics.value();
    }

    // Return the subtopics at the deepest level
    return *currentLevel;
}


/**
 * @brief Checks if a point is far enough from a list of objects.
 * 
 * This function checks whether a given point, specified by its coordinates
 * (`x`, `y`), is at least a certain distance away from all objects in a list.
 * It calculates the Euclidean distance between the point and each object, 
 * and if the distance is smaller than the specified minimum distance (`minDistance`),
 * it returns `false`, indicating that the point is too close to one of the objects.
 * If the point is far enough from all objects, the function returns `true`.
 * 
 * @param objects A vector of pointers to `TextureObject` instances representing
 *                the objects to check against.
 * @param x The x-coordinate of the point to check (must be positive).
 * @param y The y-coordinate of the point to check (must be positive).
 * @param minDistance The minimum required distance between the point and each object (must be positive).
 * 
 * @return `true` if the point is at least `minDistance` away from all objects, 
 *         otherwise `false` if any object is too close.
 * 
 * @throws std::invalid_argument if `x`, `y`, or `minDistance` is not positive.
 */
bool isFarEnough(const std::vector<TextureObject*>& objects, float x, float y, float minDistance) {
    // Validate that x, y, and minDistance are positive
    if (x <= 0 || y <= 0 || minDistance <= 0) {
        throw std::invalid_argument("x, y, and minDistance must be positive values.");
    }

    // Iterate over each object in the list
    for (const auto& obj : objects) {
        // Calculate the difference in x and y coordinates between the point and the object
        float dx = obj->getXPosition() - x;
        float dy = obj->getYPosition() - y;

        // Calculate the Euclidean distance between the point and the object (Pitagoras)
        if (std::sqrt(dx * dx + dy * dy) < minDistance) {
            // Return false if the distance is smaller than the minimum required
            return false;
        }
    }

    // Return true if the point is far enough from all objects
    return true;
}



/**
 * @brief Creates a list of moving objects with random positions.
 * 
 * This function creates a specified number (`n`) of moving objects with random sizes 
 * and positions within a given grid. It ensures that the objects are placed far enough 
 * from each other to avoid overlap. The size of each object is chosen randomly within a 
 * specified range, and the object positions are checked to ensure they do not violate 
 * the minimum distance requirement from other objects.
 * 
 * @param n The number of moving objects to create. Must be between 0 and 10.
 * @param grid A 2D grid represented as a vector of vectors of `Block` objects, used 
 *             to define the area in which the objects can be placed.
 * @param object The `StructTextureObject` containing the properties of the object to 
 *               be created, such as its size, velocity, and texture path.
 * 
 * @return A vector of pointers to dynamically allocated `TextureObject` instances.
 *         If the creation fails at any point, an empty vector is returned.
 * 
 * @throws std::runtime_error If the number of objects is greater than 10, or if the 
 *         size of the object does not meet the minimum size requirements.
 */
std::vector<TextureObject*> createMovingObjects(int n, std::vector<std::vector<Block>> grid, StructTextureObject object) {
    // Check if the number of objects is valid
    if (n <= 0) return {};  // Return an empty vector if n is less than or equal to 0

    if (n > MAX_MOVING_OBJS) {
        throw std::invalid_argument("Max num of moving objects is " + std::to_string(MAX_MOVING_OBJS) + ". Got: " + std::to_string(n));
    }

    // Ensure the object size meets the minimum size requirement
    if (MIN_SIZE * 2 > object.width) {
        throw std::invalid_argument(
            "The size of the square object must be at least double the minimum size. "
            "Got: " + std::to_string(object.width) + ", required: " + std::to_string(MIN_SIZE * 2));
    }

    // Use current time as a seed for random number generation
    auto now = std::chrono::high_resolution_clock::now();
    auto seed = static_cast<unsigned>(now.time_since_epoch().count());
    std::srand(seed);

    std::vector<TextureObject*> movingObjectPointer;  // Vector to store pointers to moving objects
    const float minDistance = object.width;  // Minimum distance between objects

    // Loop to create the specified number of moving objects
    for (int i = 0; i < n; ++i) {
        // Randomly determine the size of the object within the specified range
        int size = MIN_SIZE + (std::rand() % (object.width - (MIN_SIZE - 1)));  // Random size between MIN_SIZE and object.width
        float posX, posY;
        bool validPosition = false;

        // Try to find a valid position for the object
        while (!validPosition) {
            // Randomly select a position within the grid
            posX = grid[8][16].x + (std::rand() % (grid[100][60].x - grid[8][16].x + 1));
            posY = grid[8][16].y + (std::rand() % (grid[100][60].y - grid[8][16].y + 1));

            // Check if the position is far enough from other objects
            if (isFarEnough(movingObjectPointer, posX, posY, minDistance)) {
                validPosition = true;
            }
        }

        // Create a new TextureObject with the selected size and position
        std::unique_ptr<TextureObject> texture = std::make_unique<TextureObject>(
            object.name, size, size, posX, posY, object.velocity_x, object.velocity_y);

        // Attempt to load the texture for the object
        if (!texture->loadTexture(object.path)) {
            // Clean up previously created objects if loading the texture fails
            for (auto obj : movingObjectPointer) {
                delete obj;
            }
            return {};  // Return an empty vector if texture loading fails
        }

        // Add the created object to the list of moving objects
        movingObjectPointer.push_back(texture.release());
    }

    // Return the list of created moving objects
    return movingObjectPointer;
}


/**
 * @brief Draws a list of objects onto a render window.
 * 
 * This function iterates through a list of `TextureObject` pointers and draws each 
 * valid object onto the provided `sf::RenderWindow`. If an object pointer is `nullptr`, 
 * it skips that object to avoid any potential errors.
 * 
 * @param objects A vector of pointers to `TextureObject` instances, which represent 
 *                the objects to be drawn on the window.
 * @param window The `sf::RenderWindow` instance where the objects will be drawn.
 * 
 * @return void
 */
void drawObjects(const std::vector<TextureObject*>& objects, sf::RenderWindow& window) {
    // Iterate through the list of objects
    for (auto* obj : objects) {
        // Check if the object pointer is valid (non-null)
        if (obj) {
            // Call the draw method of each valid object to render it to the window
            obj->draw(window);
        }
    }
}


/**
 * @brief Handles the sound button interaction to toggle music on or off.
 * 
 * This function checks if the sound button is clicked. If the button is clicked and music 
 * is currently playing, it pauses the music and changes the button's texture to the 
 * "sound-off" icon. If the music is paused, it starts the music and changes the button's 
 * texture to the "sound-on" icon. The function also uses atomic operations to handle 
 * the `isMusicPlaying` state safely in a multi-threaded environment.
 * 
 * @param soundButton A reference to the `sf::Sprite` that represents the sound button.
 * @param soundOnTexture A reference to the `sf::Texture` that represents the sound-on icon.
 * @param soundOffTexture A reference to the `sf::Texture` that represents the sound-off icon.
 * @param music A reference to the `sf::Music` object that controls the background music.
 * @param isMusicPlaying An atomic boolean to track whether the music is currently playing.
 * @param window A constant reference to the `sf::RenderWindow` where the button is located.
 * 
 * @return void
 */
void handleSoundButton(sf::Sprite& soundButton, 
                       sf::Texture& soundOnTexture, 
                       sf::Texture& soundOffTexture, 
                       sf::Music& music, 
                       std::atomic<bool>& isMusicPlaying, 
                       const sf::RenderWindow& window) 
{
    // Get the mouse position relative to the window
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Check if the mouse is over the button
    if (soundButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        // Toggle music playback based on its current state
        if (isMusicPlaying.load()) {
            music.pause();                         // Pause music
            soundButton.setTexture(soundOffTexture); // Set sound-off icon
            isMusicPlaying.store(false);            // Update state to not playing
        } else {
            music.play();                          // Play music
            soundButton.setTexture(soundOnTexture); // Set sound-on icon
            isMusicPlaying.store(true);             // Update state to playing
        }
    }
}


/**
 * @brief Handles the interaction with the moving button to toggle object movement.
 * 
 * This function checks if the moving button is clicked. If the button is clicked and the 
 * thread controller is paused, it clears the current moving objects, creates new ones 
 * using the `createMovingObjects` function, and resumes the thread. If the thread is not paused, 
 * it clears the current moving objects, sets the button to the "off" texture, and pauses the thread.
 * This ensures that the objects' movement can be controlled by the button.
 * 
 * @param movingButton A reference to the `sf::Sprite` that represents the moving button.
 * @param movingONTexture A reference to the `sf::Texture` representing the "moving-on" button texture.
 * @param movingOffTexture A reference to the `sf::Texture` representing the "moving-off" button texture.
 * @param window A constant reference to the `sf::RenderWindow` used to check the mouse position.
 * @param threadController A reference to the `ThreadController` responsible for pausing and resuming the thread.
 * @param movingObjectPointer A reference to the vector of `TextureObject*` containing the moving objects.
 * @param grid A reference to the 2D grid used to place the moving objects.
 * @param object A reference to the `StructTextureObject` containing the properties of the moving objects.
 * 
 * @return void
 */
void handleMovingButton(sf::Sprite& movingButton,
                        sf::Texture& movingONTexture,  
                        sf::Texture& movingOffTexture, 
                        const sf::RenderWindow& window,
                        ThreadController& threadController,
                        std::vector<TextureObject*>& movingObjectPointer,
                        std::vector<std::vector<Block>>& grid,           
                        StructTextureObject& object)                  
{
    // Get the mouse position relative to the window
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Check if the mouse is over the moving button
    if (movingButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        // If the thread is paused, resume and create new moving objects
        if (threadController.isPaused()) {
            // Clear the current moving objects and free memory
            for (auto* obj : movingObjectPointer) {
                delete obj; // Deallocate memory for each object
            }
            movingObjectPointer.clear(); // Clear the pointer vector

            // Create new moving objects and update the vector
            movingObjectPointer = createMovingObjects(8, grid, object);
            movingButton.setTexture(movingONTexture); // Set the "on" texture for the button
            threadController.resume(); // Resume the thread if it's paused
        } else {
            // If the thread is running, stop the movement and clear objects
            for (auto* obj : movingObjectPointer) {
                delete obj; // Deallocate memory for each object
            }
            movingObjectPointer.clear(); // Clear the pointer vector

            movingButton.setTexture(movingOffTexture); // Set the "off" texture for the button
            threadController.pause(); // Pause the thread if it's running
        }
    }
}



/**
 * @brief Loads and plays music from a file.
 * 
 * This function attempts to load music from a file located at the provided `music_path`. 
 * If the music file is successfully loaded, it is played and set to loop. 
 * If the loading fails, an error message is displayed and `nullptr` is returned to indicate failure.
 * 
 * @param music_path The relative path to the music file in AUDIOS_PATH.
 * 
 * @return A `std::shared_ptr<sf::Music>` pointing to the loaded and playing music, 
 *         or `nullptr` if the loading failed.
 */
std::shared_ptr<sf::Music> loadAndPlayMusic(std::string music_path) {
    // Create a shared pointer for the music object
    auto music = std::make_shared<sf::Music>();

    // Attempt to load the music file from the specified path
    if (!music->openFromFile(AUDIOS_PATH + music_path)) {
        // If loading fails, display an error message and return nullptr
        std::cerr << "Error loading music.\n";
        return nullptr; // Indicate failure by returning nullptr
    }

    // If loading is successful, play the music and set it to loop
    music->play();
    music->setLoop(true);

    // Return the shared pointer to the music object
    return music;
}

//TOOLS
/**
 * @brief Finds a number in a list of integer arrays.
 * 
 * This function iterates over a vector of integer pointers, where each pointer points to an array. 
 * It searches for a specified `number` in each array, stopping when the number is found or the end of the array is reached (indicated by `-1`).
 * If the number is found, the function returns the first element of the array where the number is located.
 * If the number is not found in any array, the function returns `-1`.
 * 
 * @param vec The vector containing pointers to integer arrays.
 * @param number The number to search for in the arrays.
 * 
 * @return The first element of the array where the number is found, or `-1` if the number is not found in any array.
 */
int findFirstArrayWithNumber(const std::vector<int*>& vec, int number) {
    // Iterate through each array in the vector of arrays
    for (size_t i = 0; i < vec.size(); i++) {
        int* array = vec[i];  // Get the current array

        // Search for the number in the array, stopping when the end (-1) is reached
        for (size_t j = 0; array[j] != -1; j++) {
            if (array[j] == number) {
                return array[0];  // Return the first element of the array where the number is found
            }
        }
    }

    // Return -1 if the number is not found in any array
    return -1;
}



/**
 * @brief Determines the relative position of an array containing a specific number in a vector of arrays.
 * 
 * This function searches through a vector of integer arrays for a given number. 
 * Upon finding the number, it checks if the array has a preceding (up) or succeeding (down) array 
 * in the vector. The function returns an `Arrow` value that indicates the relation between the found array 
 * and its surrounding arrays:
 * - `Arrow::Up` if there is a preceding array.
 * - `Arrow::Down` if there is a succeeding array.
 * - `Arrow::Both` if both preceding and succeeding arrays exist.
 * - `Arrow::Error` if the number is not found in any array.
 * 
 * @param vec The vector of integer arrays to search through.
 * @param number The number to find in the arrays.
 * @return Arrow Enumeration value indicating the relation (Up, Down, Both, or Error).
 */
Arrow findArraySurroundingRelation(const std::vector<int*>& vec, int number) {
    // Iterate through each array in the vector
    for (size_t i = 0; i < vec.size(); i++) {
        int* array = vec[i];  // Get the current array

        // Search for the number in the array, stopping at the end marker (-1)
        for (size_t j = 0; array[j] != -1; j++) {
            if (array[j] == number) {
                // Check if the current array has previous or next arrays in the vector
                bool hasPrevious = (i > 0);  // There is a previous array if i > 0
                bool hasNext = (i < vec.size() - 1);  // There is a next array if i < vec.size() - 1

                // Return the appropriate Arrow value based on the surrounding arrays
                if (hasPrevious && hasNext) {
                    return Arrow::Both;  // Both previous and next arrays exist
                } else if (hasPrevious) {
                    return Arrow::Up;  // Only a previous array exists
                } else if (hasNext) {
                    return Arrow::Down;  // Only a next array exists
                }
                else {
                    return Arrow::None;  // Nor next nor previous array exists
                }
            }
        }
    }

    return Arrow::Error;  // Return Error if the number is not found in any array
}


/**
 * @brief Draws arrows on the screen based on the relation result.
 * 
 * This function takes the relation result returned by `findArraySurroundingRelation` and draws arrows accordingly. 
 * It uses the `Arrow` enumeration to determine which arrows to display:
 * - `Arrow::Up`: Draws the upward arrow.
 * - `Arrow::Down`: Draws the downward arrow.
 * - `Arrow::Both`: Draws both the upward and downward arrows.
 * - `Arrow::Error`: Logs an error message if the relation result is invalid.
 * 
 * @param relationResult The result of the relation check (from `findArraySurroundingRelation`).
 * @param window The `sf::RenderWindow` object used for drawing the arrows.
 * @param upArrow A unique pointer to the texture object for the up arrow.
 * @param downArrow A unique pointer to the texture object for the down arrow.
 */
void drawArrowsBasedOnRelation(Arrow relationResult, sf::RenderWindow& window, const std::unique_ptr<TextureObject>& upArrow, const std::unique_ptr<TextureObject>& downArrow) {
    // Draw arrows based on the result of the relation
    if (relationResult == Arrow::Up) {
        upArrow->draw(window);  // Only draw the up arrow
    } else if (relationResult == Arrow::Down) {
        downArrow->draw(window);  // Only draw the down arrow
    } else if (relationResult == Arrow::Both) {
        // Draw both the up and down arrows
        downArrow->draw(window);
        upArrow->draw(window);
    } else if (relationResult == Arrow::None) {
        return; // Nothing to print
    } else if (relationResult == Arrow::Error) {
        // Log an error if the relation result is invalid
        std::cerr << "Error: Invalid relationResult value. findArraySurroundingRelation() returned error. Value: " 
                  << static_cast<int>(relationResult) << std::endl;
    }
}


/**
 * @brief Creates a dynamic array from a vector of indices.
 * 
 * This function takes a `std::vector<int>` of indices and creates a dynamic array of integers to hold the same values. 
 * The size of the dynamic array matches the size of the input vector, and the values from the vector are copied into the array.
 * 
 * @param indices The vector of integers that will be copied into the dynamic array.
 * @return A pointer to the dynamically allocated array of integers, or nullptr if allocation fails.
 */
int* createIndexArray(const std::vector<int>& indices) {
    // Create a dynamic array to store the indices
    int* indexArray = new int[indices.size()];  // Dynamically allocate memory for the array
    
    // Copy the values from the vector into the dynamic array
    std::copy(indices.begin(), indices.end(), indexArray);  // Copy elements from the vector to the array
    
    // Return the pointer to the dynamic array
    return indexArray;
}


/**
 * @brief Predicts overflow of text objects based on screen size and layout.
 * 
 * This function calculates whether the text objects exceed the available screen space (taking margins into account). 
 * If the next line of text exceeds the screen's bottom margin, a new array of indices is created and stored in the result vector.
 * It also handles cases where the remaining elements fit within the screen.
 * 
 * @param rootNode The root text object from which child objects are processed.
 * @param screen The screen parameters, including height and margin values.
 * @param window The render window used to draw and calculate text layout.
 * @return A vector of dynamically allocated arrays containing indices of text objects in different screen segments.
 */
std::vector<int*> predictTextOverflow(
    const std::shared_ptr<TextObject>& rootNode,
    const ScreenParams& screen,
    sf::RenderWindow& window
) {
    const auto& children = rootNode->getChildren();  // Get the child text objects of the root node
    std::vector<int*> overflowIndices;  // Vector to store arrays of indices for overflow segments
    std::vector<int> currentIndices;  // Temporary list of indices before overflow occurs
    int next_line = LINE_SPACING * 2 + screen.topMargin + 50;  // Initialize the position for the next line

    // Loop through all child nodes to check if they cause overflow
    for (size_t i = 0; i < children.size(); i++) {
        // Check if the next line exceeds the available screen space
        if (next_line > screen.height - screen.bottomMargin) {
            currentIndices.push_back(-1);  // Sentinel value to mark the overflow point

            // Save the array of indices up until the first overflow
            int* indexArray = createIndexArray(currentIndices);
            overflowIndices.push_back(indexArray);

            // Reset the list of indices and position for the next line
            currentIndices.clear();
            next_line = LINE_SPACING * 2 + screen.topMargin + 50;  // Reset the next line position
        }

        // Add the current node's index to the list
        currentIndices.push_back(i);

        // Update the next line position based on the height of the current text node
        next_line += children[i]->getTextHeight() + LINE_SPACING;
    }

    // Handle any remaining elements that didn't cause overflow (final segment without overflow)
    if (!currentIndices.empty()) {
        int* indexArray = createIndexArray(currentIndices);
        overflowIndices.push_back(indexArray);
    }

    // Return the vector of arrays containing indices of text objects
    return overflowIndices;
}


/**
 * @brief Draws the nodes starting from the root node, handling overflow and screen layout.
 * 
 * This function iterates through the root node and its children, positioning them on the screen. 
 * It starts by drawing the root node, then draws each child node below it, taking into account 
 * the screen's height and margin. If the screen's space is insufficient (overflow), the drawing stops.
 * 
 * @param rootNode A shared pointer to the root node of the text object tree.
 * @param screen The screen parameters, including height and margins.
 * @param window The render window used to draw the nodes.
 * @param overflow The index to start drawing children from, used for handling overflow.
 */
void drawMenuFromRoot(
    const std::shared_ptr<TextObject>& rootNode,
    const ScreenParams& screen,
    sf::RenderWindow& window,
    int overflow
) {
    // Check if the root node is null
    if (!rootNode) {
        std::cerr << "Error: Root node is null." << std::endl;
        return;  // Exit if the root node is invalid
    }

    uint16_t next_line = screen.topMargin + 50; // Start drawing from the top margin

    // Draw the root node centered on the screen
    uint16_t root_x_position = general4BlocksX.blockX2; // Adjust to center on screen
    rootNode->setXPosition(root_x_position);  // Set the X position of the root node
    rootNode->setYPosition(next_line);       // Set the Y position of the root node
    rootNode->updateTextPosition();          // Update the text position for correct rendering
    rootNode->draw(window);                  // Draw the root node

    next_line += LINE_SPACING * 2; // Add space below the root node for children

    uint16_t child_x_position = general4BlocksX.blockX2;  // Set the X position for child nodes
    const auto& children = rootNode->getChildren(); // Get the list of child nodes

    // Iterate through the child nodes, starting from the overflow index
    for (size_t i = overflow; i < children.size(); ++i) {

        // Check if the next line exceeds the screen height minus the bottom margin
        if (next_line > screen.height - screen.bottomMargin) {
            break; // Exit the loop if we reach the bottom of the screen
        }

        // Draw the current child node at the new position
        children[i]->setYPosition(next_line);      // Set the Y position for the child node
        children[i]->setXPosition(child_x_position); // Set the X position for the child node
        children[i]->updateTextPosition();         // Update the text position for correct rendering
        children[i]->draw(window);                 // Draw the child node

        // Update the position for the next line
        next_line += children[i]->getTextHeight() + LINE_SPACING;
    }
}


/**
 * @brief Populates the root node with its subtopics.
 * 
 * This function adds a list of subtopics to the root node by associating each subtopic as a child of the root node. 
 * It also sets the root node as the parent of each subtopic, establishing the parent-child relationship.
 * 
 * @param root A shared pointer to the root node, which will be populated with subtopics.
 * @param subTopics A vector of shared pointers to subtopics to be added to the root node.
 */
void populateRootWithSubtopics(
    const std::shared_ptr<TextObject>& root,
    std::vector<std::shared_ptr<TextObject>> subTopics
)
{
    // Iterate through the list of subtopics
    for (const auto& child : subTopics) {
        root->addChild(child);  // Add the subtopic as a child to the root node
        child->setParent(root); // Set the root node as the parent of the subtopic
    }
}


/**
 * @brief Creates a list of `TextObject` instances based on the provided topic data.
 * 
 * This function takes a vector of `LineTextParams` (referred to as `topics`) and creates a corresponding 
 * list of `TextObject` instances. Each `TextObject` is initialized using the properties 
 * from the `LineTextParams` and added to the vector to be returned.
 * 
 * @param topics A vector of `LineTextParams` structures, each containing parameters 
 *               for creating a `TextObject`.
 * 
 * @return A vector of shared pointers to the created `TextObject` instances.
 */
std::vector<std::shared_ptr<TextObject>> createTextObjects(const std::vector<LineTextParams>& topics) {
    std::vector<std::shared_ptr<TextObject>> textObjects;  // Vector to store the created text objects

    // Iterate over each set of parameters in the input vector
    for (const auto& topic : topics) {
        // Create a new TextObject with the parameters from the current element
        auto textObject = std::make_shared<TextObject>(
            topic.name,         // Set the name of the text object
            topic.x_position,   // Set the X position
            topic.y_position,   // Set the Y position
            topic.color,        // Set the color
            topic.text,         // Set the text content
            topic.fontPath,     // Set the font path
            topic.fontSize,     // Set the font size
            topic.centered      // Set the centered alignment flag
        );

        // Add the newly created TextObject to the vector
        textObjects.push_back(textObject);
    }

    // Return the vector containing all created TextObjects
    return textObjects;
}

/**
 * @brief Recursively creates a tree structure of `TextObject` nodes from provided text parameters.
 * 
 * This function builds a hierarchical tree of `TextObject` nodes starting from a root node, with each node
 * potentially having child nodes (subtopics). It stops the recursion either when the maximum depth is reached
 * or when there are no more subtopics to process.
 * 
 * @param root A shared pointer to the root `TextObject`, which will act as the starting point of the tree.
 * @param nodes A vector of `LineTextParams`, each representing the parameters for creating a `TextObject`.
 * @param maxDepth The maximum depth of the tree. The function will stop recursively creating nodes if this depth is reached.
 * @param currentDepth The current depth of the tree during recursion. Defaults to 1.
 */
void createTree(
    const std::shared_ptr<TextObject>& root,                // Root node to start creating the tree
    const std::vector<LineTextParams>& nodes,               // List of nodes (with parameters) to create from
    int maxDepth,                                          // Maximum depth for the recursion
    int currentDepth = 1                                    // Current depth of the recursion (default to 1)
) {
    // Base case: If the root is null or the maximum depth is reached, stop the recursion.
    if (!root || currentDepth > maxDepth) {
        return;
    }

    // Step 1: Create child nodes from the current level of LineTextParams (nodes).
    auto subTopics = createTextObjects(nodes);  // Create a vector of TextObjects from the node parameters.
    
    // Step 2: Populate the root node with these created children (subtopics).
    populateRootWithSubtopics(root, subTopics);  // Add the child nodes (subTopics) to the root node.

    // Step 3: Recursively process each node's subtopics if they exist and the maximum depth is not exceeded.
    for (size_t i = 0; i < nodes.size(); ++i) {
        const auto& node = nodes[i];
        
        // Check if the current node has subtopics (children). If so, process them recursively.
        if (node.subtopics.has_value()) {
            // Recursively create a tree of subtopics for the current node.
            createTree(subTopics[i], node.subtopics.value(), maxDepth, currentDepth + 1);
        }
    }
}

/**
 * @brief Determines if two `TextureObject` instances are colliding based on their positions and dimensions.
 * 
 * This function checks whether the bounding boxes of two objects overlap, indicating a collision.
 * The overlap detection can be fine-tuned using the `OVERLAP_PERCENTAGE` factor, which adjusts
 * the effective size of the bounding boxes considered during the collision check.
 * 
 * @param obj1 The first `TextureObject` to check for collision.
 * @param obj2 The second `TextureObject` to check for collision.
 * @return `true` if the objects are colliding, `false` otherwise.
 */
bool isColliding(const TextureObject* obj1, const TextureObject* obj2) {
    // Validate that both objects exist
    if (obj1 == nullptr || obj2 == nullptr) {
        return false; // If either object is null, they cannot collide
    }

    // Check if the bounding boxes of obj1 and obj2 overlap.
    // The conditions check for cases where the bounding boxes are NOT colliding:
    // 1. The right side of obj1 is to the left of the left side of obj2.
    // 2. The left side of obj1 is to the right of the right side of obj2.
    // 3. The bottom side of obj1 is above the top side of obj2.
    // 4. The top side of obj1 is below the bottom side of obj2.
    return !(obj1->getXPosition() + obj1->getWidth() * OVERLAP_PERCENTAGE < obj2->getXPosition() || 
             obj1->getXPosition() > obj2->getXPosition() + obj2->getWidth() * OVERLAP_PERCENTAGE || 
             obj1->getYPosition() + obj1->getHeight() * OVERLAP_PERCENTAGE < obj2->getYPosition() || 
             obj1->getYPosition() > obj2->getYPosition() + obj2->getHeight() * OVERLAP_PERCENTAGE);
}

/**
 * @brief Moves multiple `TextureObject` instances within a window, managing velocity, boundary collisions, and inter-object collisions.
 * 
 * This function operates in a loop to continuously update the positions of objects, check for collisions
 * with the window boundaries and other objects, and adjust their velocities accordingly. It supports pause functionality
 * through an atomic flag and signals when a redraw is needed.
 * 
 * @param objects A vector of pointers to `TextureObject` instances to be moved.
 * @param window The SFML render window representing the screen boundaries.
 * @param needsRedraw An atomic flag to signal that the objects need to be redrawn.
 * @param isPaused An atomic flag indicating whether the movement is paused.
 */
void moveObjects(std::vector<TextureObject*>& objects, 
                 const sf::RenderWindow& window, 
                 std::atomic<bool>& needsRedraw, 
                 std::atomic<bool>& isPaused) {
    try { //Using try logic because this isn't critical
        // Validate input: objects vector should not be empty
        VALIDATE_NOT_EMPTY(objects, std::string(__func__));

        while (!isPaused.load() && window.isOpen()) {
            // Pause handling: wait if the movement is paused
            if (isPaused.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue; // Skip to the next iteration
            }

            // Step 1: Update positions and handle boundary collisions
            for (size_t i = 0; i < objects.size(); ++i) {
                auto* obj = objects[i];

                // Retrieve current velocity and position
                float velocity_x = obj->getVelocityX();
                float velocity_y = obj->getVelocityY();
                float posX = obj->getXPosition();
                float posY = obj->getYPosition();

                // Apply velocities to calculate the new position
                posX += velocity_x;
                posY += velocity_y;

                // Check for collisions with window boundaries
                if (posX <= EXTRA_MARGING || posX + obj->getWidth() >= window.getSize().x - EXTRA_MARGING) {
                    obj->setVelocityX(-velocity_x); // Reverse X velocity
                }
                if (posY <= EXTRA_MARGING || posY + obj->getHeight() >= window.getSize().y - EXTRA_MARGING) {
                    obj->setVelocityY(-velocity_y); // Reverse Y velocity
                }

                // Update the object's position
                obj->setXPosition(posX);
                obj->setYPosition(posY);
                obj->updatePosition(); // Synchronize the position with the sprite

                // Step 2: Check for collisions with other objects
                for (size_t j = i + 1; j < objects.size(); ++j) {
                    auto* otherObj = objects[j];

                    if (isColliding(obj, otherObj)) {
                        // Reverse velocities for both objects upon collision
                        obj->setVelocityX(-velocity_x);
                        obj->setVelocityY(-velocity_y);
                        otherObj->setVelocityX(-otherObj->getVelocityX());
                        otherObj->setVelocityY(-otherObj->getVelocityY());
                    }
                }
            }

            // Step 3: Indicate that the objects need to be redrawn
            needsRedraw.store(true);

            // Pause to control the movement loop
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch (const std::exception& e) {
        // Log any exceptions that occur in the movement thread
        std::cerr << "Error in the movement thread: " << e.what() << std::endl;
    }
}

/**
 * @brief Retrieves a const reference to a unique_ptr<TextureObject> from the vector based on its name.
 * 
 * This function iterates through a vector of TextureObject instances managed by unique_ptr.
 * It compares the name of each object with the provided name and returns a const reference to 
 * the matching unique_ptr if found. If no match is found, it throws an exception or can return a null reference.
 * 
 * @param textureObjects A vector of unique_ptr<TextureObject> containing the objects to search through.
 * @param name The name of the TextureObject to retrieve.
 * @return const std::unique_ptr<TextureObject>& A const reference to the matching unique_ptr, or throws an exception if not found.
 */
const std::unique_ptr<TextureObject>& getTextureObjectByName(const std::vector<std::unique_ptr<TextureObject>>& textureObjects, const std::string& name) {
    // Iterate through the vector of unique_ptrs
    for (const auto& textureObject : textureObjects) {
        // Check if the object exists and its name matches the given name
        if (textureObject && textureObject->getName() == name) {
            return textureObject; // Return a const reference to the matching unique_ptr
        }
    }
    throw std::runtime_error("TextureObject not found: " + name); // Handle not found case (optional)
}


/**
 * @brief Loads textures into a vector of unique_ptr<TextureObject>.
 * 
 * This function iterates through a vector of texture information structures (StructTextureObject),
 * creates TextureObject instances for each, attempts to load the associated texture, and stores 
 * the successfully created TextureObjects into a provided vector.
 * 
 * @param textureObjects A vector of unique_ptr<TextureObject> to store loaded textures.
 * @param textureInfos A vector of StructTextureObject containing texture metadata.
 * @return int Returns 0 if all textures are loaded successfully, or -1 if any texture fails to load.
 */

int loadTextures(
    std::vector<std::unique_ptr<TextureObject>>& textureObjects, 
    const std::vector<StructTextureObject>& textureInfos
) {
    for (const auto& info : textureInfos) {
        // Create a unique_ptr for the TextureObject
        auto textureObject = std::make_unique<TextureObject>(
            info.name, info.width, info.height, info.x_position, info.y_position
        );

        // Attempt to load the texture using the provided path
        if (!textureObject->loadTexture(info.path)) {
            return -1; // Return -1 if texture loading fails
        }

        // Move the unique_ptr into the textureObjects vector
        textureObjects.push_back(std::move(textureObject));
    }

    return 0; // Return 0 if all textures are successfully loaded
}


uint16_t initAndStartMainWindowLoop() {
    // Initialize the grid once
    auto grid = createGrid(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE);

    verifyScreenParams(generalScreen);
    VALIDATE_VECTOR(generalTopics, std::string(__func__));

    filterTopicsBySize(generalTopics, generalScreen);
    enumerateTopics(generalTopics);

    // Create the main application window
    sf::RenderWindow window(sf::VideoMode(generalScreen.width, generalScreen.height), WINDOW_TITLE);

    std::vector<std::unique_ptr<TextureObject>> textureObjects;

    if (loadTextures(textureObjects, textureInfos) == -1) {
        std::cerr << "Error: Failed to load textures!" << std::endl;
        return -1;
    }

    // Initialize menu and hierarchical tree
    auto mainMenu = std::make_shared<TextObject>(
        mainMenuParams.name, mainMenuParams.x_position, mainMenuParams.y_position, mainMenuParams.color,
        mainMenuParams.text, mainMenuParams.fontPath, mainMenuParams.fontSize, mainMenuParams.centered
    );
    createTree(mainMenu, generalTopics, 1);

    std::vector<uint16_t> indices;
    std::shared_ptr<sf::Music> music = loadAndPlayMusic(MUSIC_FILE);
    std::atomic<bool> isMusicPlaying = true;

    auto selectedMenu = mainMenu;
    auto selectedMenuChildren = selectedMenu->getChildren();
    int8_t types = 0;

    Stack last_types;


    std::vector<int*> overflow_list = predictTextOverflow(selectedMenu, generalScreen, window);

    std::atomic<bool> needsRedraw(true);

    // puedo destruirlos y volverlos a contruir
    std::vector<TextureObject*> movingObjectPointer = createMovingObjects(8, grid, iconCpp150);


    ThreadController movementThread;
    
    movementThread.start([&]() {
    moveObjects(std::ref(movingObjectPointer), std::cref(window), std::ref(needsRedraw), std::ref(movementThread.getPauseFlag()));
    });



    // Main event loop
    while (window.isOpen()) {
        sf::Event event;
        selectedMenuChildren[types]->setFontSize(BIG_FONT);
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    needsRedraw = true;
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    } else if (event.key.code == sf::Keyboard::Up) {
                        selectedMenuChildren[types]->setFontSize(NORMAL_FONT);
                        types = (types - 1 + selectedMenuChildren.size()) % selectedMenuChildren.size();
                        selectedMenuChildren[types]->setFontSize(BIG_FONT);
                    } else if (event.key.code == sf::Keyboard::Down) {
                        selectedMenuChildren[types]->setFontSize(NORMAL_FONT);
                        types = (types + 1) % selectedMenuChildren.size();
                        selectedMenuChildren[types]->setFontSize(BIG_FONT);
                    } else if (event.key.code == sf::Keyboard::Enter && !selectedMenu->isLeaf()) {
                        selectedMenuChildren[types]->setFontSize(NORMAL_FONT);
                        indices.push_back(types);
                        auto subtopics = findNestedSubtopics(generalTopics, indices);
                        if (!subtopics.empty()) {
                            createTree(selectedMenu->getChildren()[types], subtopics, 1);
                            selectedMenu = selectedMenu->getChildren()[types];
                            selectedMenuChildren = selectedMenu->getChildren();
                            last_types.push(types); // save last position in a stack to come back later
                            types = 0; // Bringing back user to first element of the new deployed list
                            selectedMenuChildren[types]->setFontSize(BIG_FONT);
                            overflow_list = predictTextOverflow(selectedMenu, generalScreen, window);
                        } else {
                            indices.pop_back();
                        }
                    } else if (event.key.code == sf::Keyboard::Left && selectedMenu != mainMenu) {
                        selectedMenu->removeAllChildren();
                        selectedMenu = selectedMenu->getParent();
                        selectedMenuChildren = selectedMenu->getChildren();
                        indices.pop_back();
                        types = last_types.pop(); // Bringing back user to the last position
                        selectedMenuChildren[types]->setFontSize(BIG_FONT);
                        overflow_list = predictTextOverflow(selectedMenu, generalScreen, window);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        handleSoundButton(getTextureObjectByName(textureObjects, SOUND_ON_OBJ)->getTextureSprite(), getTextureObjectByName(textureObjects, SOUND_ON_OBJ)->getTexture(), getTextureObjectByName(textureObjects, SOUND_OFF_OBJ)->getTexture(), *music, isMusicPlaying, window);
                        handleMovingButton(getTextureObjectByName(textureObjects, CPP100FILL_IMAGE_OBJ)->getTextureSprite(), getTextureObjectByName(textureObjects, CPP100FILL_IMAGE_OBJ)->getTexture(), getTextureObjectByName(textureObjects, X100_IMAGE_OBJ)->getTexture(), window, movementThread, movingObjectPointer, grid, iconCpp150);
                        needsRedraw = true;
                    }
                    break;

                default:
                    break;
            }
        }

        // Redraw only if necessary
        //needsRedraw
        //types
        //window
        //overflow_list
        //movementThread
        //movingObjectPointer
        //selectedMenu
        if (needsRedraw) {
            window.clear();
            getTextureObjectByName(textureObjects, BACKGROUND_IMAGE_OBJ)->draw(window);
            if (!movementThread.isPaused()){
                drawObjects(movingObjectPointer, window);
            }
            getTextureObjectByName(textureObjects, SOUND_ON_OBJ)->draw(window);
            getTextureObjectByName(textureObjects, CPP100FILL_IMAGE_OBJ)->draw(window);
            drawMenuFromRoot(selectedMenu, generalScreen, window, findFirstArrayWithNumber(overflow_list, types));
            Arrow temp = findArraySurroundingRelation(overflow_list, types);
            drawArrowsBasedOnRelation(temp, window, getTextureObjectByName(textureObjects, UP_ARROW_IMAGE_OBJ), getTextureObjectByName(textureObjects, DOWN_ARROW_IMAGE_OBJ));
            window.display();
            needsRedraw = false;
        } else {
            // Reduce CPU usage when idle
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    movementThread.stop();

    return 0;
}


int main() {

    return initAndStartMainWindowLoop();

    //return 0;
}