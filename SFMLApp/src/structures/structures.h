#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <optional>
#include "../constants/constants.h"

// Structure to represent a block of 30x30 pixels
struct Block {
    uint16_t x, y; // Coordinates of the block
    uint16_t width = BLOCK_SIZE; // Width of the block
    uint16_t height = BLOCK_SIZE; // Height of the block

    // Constructor
    Block(uint16_t _x, uint16_t _y) : x(_x), y(_y) {}
};

extern std::vector<std::vector<Block>> grid;


// Definición de la estructura para objetos de textura
struct StructTextureObject {
    std::string name;
    std::string path;
    uint16_t width;
    uint16_t height;
    uint16_t x_position;
    uint16_t y_position;
    float velocity_x;  // Optional velocity on x-axis
    float velocity_y;  // Optional velocity on y-axis

    // Constructor
    StructTextureObject(std::string name, std::string path, uint16_t width, uint16_t height, 
                        uint16_t x, uint16_t y, float vx, float vy)
        : name(std::move(name)), path(std::move(path)), width(width), height(height), 
          x_position(x), y_position(y), velocity_x(vx), velocity_y(vy) {}

    // Constructor
    StructTextureObject(std::string name, std::string path, uint16_t width, uint16_t height, 
                        uint16_t x, uint16_t y)
        : name(std::move(name)), path(std::move(path)), width(width), height(height), 
          x_position(x), y_position(y) {}
};

extern StructTextureObject iconCpp150;
extern std::vector<StructTextureObject> textureInfos;


// Definición de la estructura para parámetros de pantalla
struct ScreenParams {
    uint16_t width;
    uint16_t height;
    uint16_t leftMargin;
    uint16_t rightMargin;
    uint16_t topMargin;
    uint16_t bottomMargin;

    // Constructor
    ScreenParams(uint16_t w, uint16_t h, uint16_t left, uint16_t right, uint16_t top, uint16_t bottom)
        : width(w), height(h), leftMargin(left), rightMargin(right), topMargin(top), bottomMargin(bottom) {}
};

extern ScreenParams generalScreen;

// Definición de la estructura para bloques de pantalla
struct ScreenBlocks_X {
    uint16_t blockX1;
    uint16_t blockX2;
    uint16_t blockX3;
    uint16_t blockX4;

    // Constructor
    ScreenBlocks_X(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4)
        : blockX1(x1), blockX2(x2), blockX3(x3), blockX4(x4) {}
};

extern ScreenBlocks_X general4BlocksX;

// Definición de la estructura para parámetros de texto en pantalla
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

    // Constructor
    LineTextParams(std::string name, uint16_t x, uint16_t y, std::array<uint16_t, 3> color, 
                   std::string text, std::string fontPath, uint16_t fontSize, bool centered, 
                   std::optional<std::vector<LineTextParams>> subtopics, int depth)
        : name(std::move(name)), x_position(x), y_position(y), color(color),
          text(std::move(text)), fontPath(std::move(fontPath)), fontSize(fontSize),
          centered(centered), subtopics(std::move(subtopics)), depth(depth) {}
};

extern std::vector<LineTextParams> TopicFloatingpointTypes;
extern std::vector<LineTextParams> TopicIntegralTypes;
extern std::vector<LineTextParams> introductionTopics;
extern std::vector<LineTextParams> dataTypesTopics;
extern std::vector<LineTextParams> generalTopics;
extern LineTextParams mainMenuParams;


#endif // STRUCTURES_H
