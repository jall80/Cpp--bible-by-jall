#include "../constants/constants.h"
#include <string>
#include <cstdint>
#include <array>

// Paths
const std::string AUDIOS_PATH = "audios/";
const std::string IMAGES_PATH = "images/";
const std::string FONTS_PATH = "fonts/";
const std::string ICONS_PATH = "images/icons/";

// Fonts
const std::string RETRO_FONT_PATH = FONTS_PATH + "retro_computer.ttf";

// Audio
const std::string MUSIC_FILE = "MASTER_BOOT_RECORD_INTERRUPT_REQUEST.mp3";

// Window Configuration
const std::string WINDOW_TITLE = "C++ Bible by JALL";

// Background Images
const std::string BACKGROUND_IMAGE_OBJ = "BackgroundImage";
const std::string BACKGROUND_IMAGE_FILE = "realCRT.jpeg";

// Sound Icons
const std::string SOUND_ON_OBJ = "soundON";
const std::string SOUND_ON_FILE = "soundON.png";
const std::string SOUND_OFF_OBJ = "soundOFF";
const std::string SOUND_OFF_FILE = "soundOFF.png";

// Miscellaneous Icons
const std::string CPP150_IMAGE_OBJ = "cpp150";
const std::string CPP150_IMAGE_FILE = "cpp150.png";

const std::string CPP100FILL_IMAGE_OBJ = "cpp100filled";
const std::string CPP100FILL_IMAGE_FILE = "cpp100filled.png";

const std::string X100_IMAGE_OBJ = "Xicon100";
const std::string X100_IMAGE_FILE = "Xicon100.png";

const std::string UP_ARROW_IMAGE_OBJ = "upArrow";
const std::string UP_ARROW_IMAGE_FILE = "upArrow.png";

const std::string DOWN_ARROW_IMAGE_OBJ = "downArrow";
const std::string DOWN_ARROW_IMAGE_FILE = "downArrow.png";

// Colors
const std::array<uint16_t, 3> CRTGreen = {0, 255, 128};

// For moving object

const int EXTRA_MARGING = 5;
const int MAX_VELOCITY = EXTRA_MARGING - 1;  //This in order to avoid a segmentation fault, when the object meets the margin
const float OVERLAP_PERCENTAGE = 0.8; // 0.5 - 1  1 -> no overlap
const int MIN_SIZE = 50;
const int MAX_MOVING_OBJS = 10;

//For matrix

const uint16_t SCREEN_WIDTH = 1920;
const uint16_t SCREEN_HEIGHT = 1080;
const uint16_t BLOCK_SIZE = 15;

//Font sizes

const uint16_t NORMAL_FONT = 30;
const float FONT_RESIZE = 1.27;
const int BIG_FONT = int(NORMAL_FONT * FONT_RESIZE);
const uint16_t MENU_FONT_SIZE = 40;
const int LINE_SPACING = 40;

// Calculate the number of rows and columns
const int rows = SCREEN_HEIGHT / BLOCK_SIZE;
const int cols = SCREEN_WIDTH / BLOCK_SIZE;

// Validation

const std::string LINE_TEXT_ERROR = "Validation LineTextParams vector failed in function: '";
