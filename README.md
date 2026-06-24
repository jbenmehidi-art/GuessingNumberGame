# 🎯 Guessing Number Game (v2.0)

A polished, interactive, and animated command-line interface (CLI) game written in **C**. Players register their names, choose a difficulty level, and try to guess a randomly generated secret number within 10 attempts. The game features local persistent leaderboard tracking using binary file storage.

---

## ✨ Features

- **Interactive Menu:** Smooth keyboard navigation using Up/Down arrow keys and Enter (powered by `conio.h`).
- **Dynamic UI & Animations:** Custom loading bars, spinners, typewriter text effects, and flashy win/loss animations with synchronized audio beeps.
- **Three Difficulty Levels:**
  - **Easy:** Range 0 - 50 (Baseline score)
  - **Medium:** Range 0 - 100 (Score multiplied x2)
  - **Hard:** Range 0 - 1000 (Score multiplied x3)
- **Persistent Leaderboard:** Saves player records, automatically sorts them descendingly, and displays a Top Players board featuring rank medals (🥇, 🥈, 🥉).
- **Cross-Platform UTF-8 Support:** Configured to correctly render emojis and structural borders in Windows Console.

---

## 📂 Project Structure

- `main.c`: The entry point of the program, initializes console setups and boots the main game loop.
- `fun.c`: Contains the core game mechanics, difficulty routing, and leaderboard file management (I/O).
- `ui.c`: Handles all low-level terminal rendering, text color manipulations, animations, and menu interactions.
- `header.h`: Holds data structures (like `Player`) and global core function prototypes.
- `ui.h`: Definitions for standard Windows console color macros and layout helper prototypes.

---

## 🛠️ Requirements & Setup

### Prerequisites
- **Operating System:** Windows (uses Windows-specific APIs like `<windows.h>` and `<conio.h>`).
- **Compiler:** GCC (MinGW or any C compiler supporting standard Windows libraries).

### Compilation
Open your terminal/command prompt inside the project folder and run the following command to compile all modules together:

```bash
gcc main.c fun.c ui.c -o GuessingGame