#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <cstdint>
#include <array>


// Paths
extern const std::string AUDIOS_PATH;
extern const std::string IMAGES_PATH;
extern const std::string FONTS_PATH;
extern const std::string ICONS_PATH;

// Fonts
extern const std::string RETRO_FONT_PATH;  // Posible corrección

// Audio
extern const std::string MUSIC_FILE;

// Window Configuration
extern const std::string WINDOW_TITLE;

// Background Images
extern const std::string BACKGROUND_IMAGE_OBJ;
extern const std::string BACKGROUND_IMAGE_FILE;

// Sound Icons
extern const std::string SOUND_ON_OBJ;
extern const std::string SOUND_ON_FILE;
extern const std::string SOUND_OFF_OBJ;
extern const std::string SOUND_OFF_FILE;

// Miscellaneous Icons
extern const std::string CPP150_IMAGE_OBJ;
extern const std::string CPP150_IMAGE_FILE;
extern const std::string CPP100FILL_IMAGE_OBJ;
extern const std::string CPP100FILL_IMAGE_FILE;
extern const std::string X100_IMAGE_OBJ;
extern const std::string X100_IMAGE_FILE;
extern const std::string UP_ARROW_IMAGE_OBJ;
extern const std::string UP_ARROW_IMAGE_FILE;
extern const std::string DOWN_ARROW_IMAGE_OBJ;
extern const std::string DOWN_ARROW_IMAGE_FILE;

// Colors
extern const std::array<uint16_t, 3> CRTGreen;

// For moving object

extern const int EXTRA_MARGING;
extern const int MAX_VELOCITY;  //This in order to avoid a segmentation fault, when the object meets the margin
extern const float OVERLAP_PERCENTAGE ; // 0.5 - 1  1 -> no overlap
extern const int MIN_SIZE;
extern const int MAX_MOVING_OBJS;

//For matrix

extern const uint16_t SCREEN_WIDTH;
extern const uint16_t SCREEN_HEIGHT;
extern const uint16_t BLOCK_SIZE;

//Font sizes

extern const uint16_t NORMAL_FONT;
extern const float FONT_RESIZE;
extern const int BIG_FONT;
extern const uint16_t MENU_FONT_SIZE;
extern const int LINE_SPACING;

// Calculate the number of rows and columns
extern const int rows;
extern const int cols;

// Validation

extern const std::string LINE_TEXT_ERROR;


#endif  // CONSTANTS_H
