# SFML Snake

A classic Snake game implemented in C++ using the [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library). This project serves as a hands-on exercise to explore game development concepts and the SFML framework.

## Features

* Classic Snake gameplay mechanics
* Modular code structure with separate game states (e.g., Start Menu, Pause, Gameplay)
* Utilizes SFML for graphics rendering and input handling
* Simple batch scripts (`comp.bat`, `debug.bat`) for building and debugging

## Getting Started

### Prerequisites

* C++ compiler supporting C++17 or later
* [SFML 2.5.1](https://www.sfml-dev.org/download.php) or newer installed on your system
* Windows environment (batch scripts provided for Windows)

### Building the Game

1. Clone the repository:

   ```bash
   git clone https://github.com/pjfrontend/sfml-snake.git
   cd sfml-snake
   ```

2. Compile the project:

   * For release build:

     ```bash
     comp.bat
     ```

   * For debug build:

     ```bash
     debug.bat
     ```

   Ensure that the SFML libraries are correctly linked in your development environment.

## Controls

* **Arrow Keys**: Navigate the snake
* **P**: Pause/Resume the game
* **Esc**: Exit the game

## Project Structure

* `Main.cpp`: Entry point of the application
* `Engine.*`: Core game engine managing the game loop and state transitions
* `GameStartMenu.*`: Implementation of the start menu state
* `GameSnake.*`: Main gameplay logic
* `GamePause.*`: Pause state management
* `Constants.hpp`: Configuration constants
* `utils/`: Utility functions and classes
* `output/`: Directory for compiled binaries and assets

## Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests to enhance the game or fix issues.

## License

This project is open-source and available under the [MIT License](LICENSE).
