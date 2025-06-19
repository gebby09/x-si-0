# Tic-Tac-Toe in C++ with Threads

This project is an implementation of the classic Tic-Tac-Toe (X and 0) game in C++, using threads to simulate each player's turn.

## Features

- Each player runs on a separate thread.
- Safe synchronization with mutex and condition_variable.
- Automatic validation of moves and detection of wins or draws.
- C++20 required (for `std::jthread` support, if used).

## Project Structure

- `main.cpp` – Entry point of the application
- `Incercare.cpp`, `Incercare.h` – Player classes (Player, PlayerX, PlayerO), game logic, utility functions
- `.gitignore` – Excludes generated or editor-specific files
- `.vscode/` – Local VS Code configuration files

## How to Compile

### Using MSVC (cl.exe):

```sh
cl /std:c++20 /EHsc main.cpp Incercare.cpp
