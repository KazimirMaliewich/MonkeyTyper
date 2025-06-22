# MonkeyTyper

A fast-paced typing game built with C++ and SFML where players must type words before they reach the right edge of the screen.

## 🎮 Game Description

MonkeyTyper is a typing game that challenges players to type words as they move across the screen from left to right. The goal is to type each word correctly before it reaches the right edge of the window. The game features customizable settings, multiple fonts, and a scoring system.

## 🛠️ Technical Details

### Built With
- **C++20**: Modern C++ features and syntax
- **SFML 2.5.1**: Graphics and window management library
- **CMake**: Cross-platform build system

### Project Structure
```
MonkeyTyper/
├── main.cpp          # Entry point and window management
├── game.cpp/h        # Core game logic and rendering
├── menu.cpp/h        # Settings menu system
├── word.cpp/h        # Word object and movement logic
├── CMakeLists.txt    # Build configuration
├── base.txt          # Word dictionary (101 words)
├── save.txt          # Score persistence
└── README.md         # This file
```

### Dependencies
- **SFML 2.5.1**: Graphics, Window, and System modules
- **C++20 Standard Library**: STL containers and algorithms
- **Windows Fonts**: Arial, Times New Roman, Comic Sans (system fonts)

## 🚀 Installation & Build

### Prerequisites
- **CMake 3.25+**
- **C++20 compatible compiler** (GCC, Clang, or MSVC)
- **SFML 2.5.1** (automatically fetched by CMake)

### Building the Project

1. **Clone or download the project**
   ```bash
   git clone https://github.com/KazimirMaliewich/MonkeyTyper.git
   cd MonkeyTyper
   ```

   ```sh
   git clone git@github.com:KazimirMaliewich/MonkeyTyper.git
   cd MonkeyTyper
   ```

2. **Create build directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure and build**
   ```bash
   cmake ..
   cmake --build .
   ```

4. **Run the game**
   ```bash
   ./MonkeyTyper  # Linux/macOS
   MonkeyTyper.exe  # Windows
   ```

### Windows-Specific Notes
- The project uses Windows system fonts located at `C:/Windows/Fonts/`
- Save file is stored at `C:/Users/username/CLionProjects/MonkeyTyper/save.txt`
- Word dictionary is loaded from `C:/Users/username/CLionProjects/MonkeyTyper/base.txt`

## 🎯 How to Play

### Menu Controls
- **Enter**: Start the game with current settings
- **Left/Right Arrow**: Change font selection
- **Up/Down Arrow**: Change window size
- **Page Up/Page Down**: Adjust font size
- **+/- Keys**: Adjust word speed
- **Delete**: Reset high score

### In-Game Controls
- **Type**: Enter words as they appear on screen
- **Backspace**: Delete incorrect characters
- **F1**: Restart game (when game over)
- **F2**: Switch font during gameplay
- **F5**: Toggle text highlighting

### Game Rules
1. Words spawn from the left side of the screen
2. Type each word completely before it reaches the right edge
3. Correctly typed words disappear and award points
4. If any word reaches the right edge, the game ends
5. Your score is saved automatically

## 🎨 Customization

### Adding New Words
Edit `base.txt` to add or modify the word dictionary. Each word should be on a separate line.

### Modifying Game Settings
Adjust the following in `game.h`:
- `spawnInterval`: Time between word spawns (default: 1.5s)
- `minSpeed`/`maxSpeed`: Word movement speed range
- `fontFiles`: Paths to additional fonts

### Changing Save Location
Modify `SAVE_PATH` in `game.h` to change where scores are saved.

## 🔧 Troubleshooting

### Common Issues
- **Font Loading Error**: Ensure Windows fonts are available at the specified paths
- **Build Errors**: Verify CMake version and C++20 compiler support
- **SFML Issues**: The project automatically fetches SFML, but ensure internet connection during first build

## 📝 Development Notes

### Code Architecture
- **Object-Oriented Design**: Clean separation between Game, Menu, and Word classes
- **Event-Driven**: SFML event system for input handling
- **Resource Management**: Automatic font and texture loading
- **State Management**: Clear game states (menu, playing, game over)

### Future Enhancements
- Multiplayer support
- Different game modes (time attack, survival)
- Custom word categories
- Sound effects and music
- Online leaderboards
- Mobile/tablet support


**Happy Typing!** 🐒⌨️
