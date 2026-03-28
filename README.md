# 🚜 ROV-MAN | A Segfault Survivor

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Environment](https://img.shields.io/badge/Environment-Terminal-black.svg)

**ROV-MAN** is a fast-paced, terminal-based 2D maze navigation game written entirely in C for my 2nd-semester Computer Engineering project. 

Take control of a customizable rover, navigate a perilous grid, collect all the data points, and outsmart the dynamically tracking enemies. Do you have what it takes to survive the segfault?

---

## 📸 Gameplay Demo
*(Tip: Record a quick 5-second GIF of you playing the game and upload it to your repo, then replace this text with `![Gameplay](gameplay.gif)`)*

---

## 🎮 How to Play

### The Objective
Collect all **159 yellow dots** scattered across the map to win. If an enemy touches you, it's Game Over!

### The Elements
* 🟩 **The Rover:** You! Choose between *The Aerial*, *The Tanker*, or *The Digger*.
* 🟡 **Data Points (`.`):** Collect these to increase your score.
* 🟥 **Enemies (`X`):** Relentless hunters that track your movements.
* 🟦 **Walls (`#`):** Impassable boundaries.
* 🟪 **Obstacles (`=`):** Internal blocks you must navigate around.

### Controls
Real-time movement (No need to press Enter!)
* **[ W ]** - Move Up
* **[ S ]** - Move Down
* **[ A ]** - Move Left
* **[ D ]** - Move Right

---

## ⚙️ Under the Hood (Technical Details)

This project was built to explore core C programming concepts, memory management, and terminal manipulation. Here is how the engine works:

* **The Map Engine:** The game world is built on a `20x20` 2D `char` array. The grid updates dynamically based on player position and enemy coordinates.
* **Flicker-Free Rendering:** Instead of constantly clearing the screen with `system("cls")` (which causes terrible screen tearing), the game uses the ANSI escape code `\033[H` to instantly snap the cursor back to the top-left of the terminal. This redraws the map over the old frame instantly, providing smooth, flicker-free gameplay.
* **True RGB Coloring:** The game breaks away from standard 16-color terminal limits by utilizing **24-bit True RGB ANSI escape codes** (e.g., `\033[1;38;2;255;0;0m` for bright red enemies) to make the grid pop visually.
* **Real-Time Input:** Utilizes `<conio.h>` and `getch()` to capture keyboard strokes instantly, allowing for fluid character movement without pausing the game loop.
* **Smart Enemy Pathfinding:** The enemies use a "Manhattan Distance" algorithm to actively hunt the player. The AI compares the absolute X and Y distances between itself and the rover, prioritizing the longest axis while dynamically navigating around walls and obstacles.

---

## 🚀 How to Run the Game

### Requirements
Because this game utilizes `<conio.h>` for real-time input and `system("cls")` for initial screen clearing, it is designed to be compiled and run on **Windows**.

### Installation & Compilation
1. Clone this repository: `git clone https://github.com/k256505/ROV-MAN.git`
2. Navigate to the directory: `cd ROV-MAN`
3. Compile the C file: `gcc robo_navigator.c -o rov-man`
4. Run the executable: `rov-man.exe` (or `./rov-man.exe` depending on your terminal)

---

## 👨‍💻 Author
Created by **AYAAN** as a 2nd-Semester Computer Engineering Project.
