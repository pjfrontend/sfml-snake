#pragma once
#include <SFML/Graphics.hpp>
// text
static const std::string TXT_GAME_TITLE = "Snake";
static const std::string TXT_NEW_GAME = "New Game";
static const std::string TXT_PAUSE = "PAUSE";
static const std::string TXT_CONTINUE = "Resume";
static const std::string TXT_QUIT = "Quit";
static const std::string TXT_SCORE = "Score: ";
// states
static const std::string STATE_START = "StartState";
static const std::string STATE_PAUSE = "PauseState";
static const std::string STATE_SNAKE = "SnakeState";
// colors
static const sf::Color BG = sf::Color::Black;
static const sf::Color WHITE = sf::Color::White;
static const sf::Color APPLE = sf::Color::Green;
static const sf::Color HEAD = sf::Color::Yellow;
// assets
const static std::string FONT_NAME = "assets/Roboto-Regular.ttf";
// dimensions
const int TILE_SIZE = 64;
const int HEIGHT_IN_TILES = 9;
const int WIDTH_IN_TILES = 16;
const int TILES_PER_SCREEN = HEIGHT_IN_TILES * WIDTH_IN_TILES;
const int HEIGHT_IN_PIXELS = TILE_SIZE * HEIGHT_IN_TILES;
const int WIDTH_IN_PIXELS = TILE_SIZE * WIDTH_IN_TILES;
const int HALF_TILE = TILE_SIZE / 2;

enum Facing
{
    down,
    up,
    left,
    right,
};

const std::string threshold =
    "#version 120\n"
    "uniform sampler2D texture;\n"
    "void main()\n"
    "{\n"
    "    vec4 color = texture2D(texture, gl_TexCoord[0].xy);\n"
    "    float brightness = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));\n"
    "    if (brightness > 0.8)  // Adjust threshold as needed\n"
    "    {\n"
    "        gl_FragColor = color;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        gl_FragColor = vec4(0.0);\n"
    "    }\n"
    "}";

const std::string combine =
    "#version 120\n"
    "uniform sampler2D original;\n"
    "uniform sampler2D bloom;\n"
    "void main()\n"
    "{\n"
    "    vec4 sceneColor = texture2D(original, gl_TexCoord[0].xy);\n"
    "    vec4 bloomColor = texture2D(bloom, gl_TexCoord[0].xy);\n"
    "    gl_FragColor = sceneColor + bloomColor * 0.8;  // Adjust bloom intensity\n"
    "}";

const std::string blur =
    "#version 120\n"
    "uniform sampler2D texture;\n"
    "const float offset = 1.0 / 300.0;  // Adjust for screen resolution\n"
    "void main()\n"
    "{\n"
    "    vec4 color = vec4(0.0);\n"
    "    for (int x = -2; x <= 2; x++)\n"
    "    {\n"
    "        for (int y = -2; y <= 2; y++)\n"
    "        {\n"
    "            vec2 offsetCoords = vec2(x, y) * offset;\n"
    "            color += texture2D(texture, gl_TexCoord[0].xy + offsetCoords);\n"
    "        }\n"
    "    }\n"
    "    gl_FragColor = color / 25.0; // Average 5x5 kernel\n"
    "}";
