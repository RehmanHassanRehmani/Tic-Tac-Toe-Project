# Tic-Tac-Toe with Computer (C++ / SFML)
A Tic-Tac-Toe game where you play against the computer. It is written in C++ and uses SFML for the graphical interface and sound.
This is our Programming Fundamentals semester project at FAST-NUCES.

Team
1) Rehman Hassan (26L-0796)
2) Muhammad Asad (26L-0853)

GitHub: https://github.com/RehmanHassanRehmani/Tic-Tac-Toe-Project

## Features
Play against the computer with the mouse
Three difficulty levels: Easy, Medium and Hard
Enter your player name
Choose to play as X or O
Sound effects for click, win, lose and draw (can be turned ON or OFF)
A line is drawn over the winning row, column or diagonal
Scoreboard that saves games, wins, losses and draws for each player
Restart button and Main Menu button after every game

## Screenshots

### Main Menu
![Main Menu](PF%20semester%20project/docs/screenshots/main-menu.png)

### Game Setup (name, difficulty, mark and sound)
![Game Setup](PF%20semester%20project/docs/screenshots/difficulty.png)

### Winning a game
![Win Screen](PF%20semester%20project/docs/screenshots/win.png)

### Scoreboard
![Scoreboard](PF%20semester%20project/docs/screenshots/scoreboard.png)

## Requirements
Windows 10 or 11
Visual Studio 2022 or newer with the "Desktop development with C++" workload
  (make sure "C++ CMake tools for Windows" is ticked)
Git installed
 Internet connection for the first build, because SFML is downloaded automatically
## Libraries
The project uses "SFML 2.6.1" (graphics, window, audio and system modules).
You do not have to install it yourself. CMake downloads and builds it automatically.
More details are in `PF semester project/libraries/libraries.txt`.
## How to Set Up and Run
1. Clone the repository:
   ```
   git clone https://github.com/RehmanHassanRehmani/Tic-Tac-Toe-Project.git
   ```
2. Open Visual Studio and choose "File > Open > Folder".
3. Select the inner folder named `PF semester project` (the one that directly contains `CMakeLists.txt`, `src`, `assets` and `include`).
4. If a "CMake Integration" box appears, click "Enable".
5. Open the Output window and choose "Show output from: CMake". Wait until it says "CMake generation finished".
   The first time this takes about 2 to 5 minutes because SFML is downloaded and built.
6. In the toolbar, open the startup item dropdown and select "tic_tac_toe.exe".
7. Press "F5" to build and run the game.
## How to Play
1. Click "Play" in the main menu.
2. Type your name, choose a difficulty and choose X or O. Turn sound ON or OFF if you want.
3. Click "Start Game".
4. Click on any empty square to place your mark. The computer plays after you.
5. The first player to get three in a row wins. If the board fills up, the game is a draw.
6. Use "Scoreboard" in the main menu to see everyone's results.
## Project Structure
```
PF semester project/
    assets/          sound effects and font used by the game
    docs/screenshots/            screenshots used in this README
    include/         header files
    libraries/       libraries.txt (details of the library we use)
    src/
        main.cpp, game.cpp, difficulty.cpp, scoreboard.cpp   game logic
        gui/gui.cpp       SFML window and drawing code
        audio/audio.cpp   SFML sound code
    CMakeLists.txt
```
The game logic (board, difficulty, scoreboard) is plain C++. All SFML code is kept in the `gui` and `audio` folders.
## Troubleshooting
| Problem | Solution |
|---|---|
| "Project is unloaded" or ".vcxproj has been moved" | Do not open a `.sln` or `.slnx` file. Use "File > Open > Folder" and select the folder that contains `CMakeLists.txt`. |
| CMake error: SFML not found, or `git` / `fatal:` error | Install Git and check your internet connection. Then use "Project > Delete Cache and Reconfigure". |
| "Unable to start debugging" or `tic_tac_toe.exe` is not in the startup dropdown | Wait for "CMake generation finished" in the CMake output, then select `tic_tac_toe.exe` as the startup item. |
| `OpenAL32.dll was not found` | CMake copies it automatically. Reconfigure and rebuild. If it still fails, copy `openal32.dll` from `out\build\x64-Debug\_deps\sfml-src\extlibs\bin\x64` into the folder that has `tic_tac_toe.exe`. |
| Game opens but there is no sound | Check that the `assets/sounds` folder has `click.wav`, `win.wav`, `lose.wav` and `draw.wav`, and that Sound is set to ON in Game Setup. |
| Crash right when the game starts | Delete the `out` folder, reconfigure with "Project > Delete Cache and Reconfigure", then use "Build > Build All". |
| First build is very slow | This is normal. SFML is being downloaded and compiled. Later builds are fast. |