# Game_CreaturePlayerMonster
# Console Game in C++

## Project Overview

This project is a simple console-based text RPG written in C++. The player explores a world, fights randomly generated monsters, collects gold, levels up, and encounters magical potions with different effects.

The project was created for educational purposes to practice object-oriented programming, standard library usage, and basic game logic implementation in C++.

---

## Features

- Object-oriented design with inheritance and encapsulation
- Random enemy generation
- Turn-based combat system
- Level progression system
- Random events (potions)
- Simple console-based interaction

---

## Architecture

### Core Classes

**Creature**
- Base class representing any living entity in the game
- Stores common attributes: name, health, damage, gold

**Player**
- Derived from `Creature`
- Includes level system and progression mechanics
- Can level up and increase damage

**Monster**
- Derived from `Creature`
- Multiple predefined monster types
- Randomized enemy selection

---

## Game Mechanics

### Combat System
- Player can choose to fight or attempt to flee
- Monsters deal damage each turn
- Player attacks until one side is defeated

### Progression
- Killing monsters grants gold and experience (levels)
- Leveling up increases player damage
- Game ends when player reaches level 20 or dies

### Random Events
- After defeating a monster, the player may find a potion:
  - Health potion (restores HP)
  - Strength potion (increases damage)
  - Poison potion (reduces HP)

---

## Random System

The game uses `<random>` for:
- Monster selection
- Flee success chance
- Potion effects

---

## Controls

All interactions are text-based:

- `R` / `F` — Run or Fight
- `Y` / `N` — Drink potion or ignore
- Player name input at game start

---

## Build and Run

### Requirements
- C++17 or higher
- Any modern compiler (GCC, Clang, MSVC)

### Compilation
```bash
g++ main.cpp -o game
