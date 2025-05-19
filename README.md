# OOPDS### 
**Warship Battle Simulator – Object-Oriented Programming Project**  
**CCP6124 Object-Oriented Programming and Data Structures | Trimester 2510**  

#### **Project Overview**  
Developed a **turn-based naval battle simulator** in C++ to model warfare between two teams of ships with distinct capabilities (e.g., Battleships, Cruisers). The simulator reads battlefield configurations from a text file, implements inheritance-driven ship behaviors, and adheres to strict OOP principles (polymorphism, operator overloading) while avoiding STL containers.  

#### **Key Features**  
1. **Core Game Mechanics**:  
   - **Turn-Based Simulation**: Ships perform actions (look, move, shoot, destroy) sequentially per turn.  
   - **Battlefield Grid**: 10x10 matrix with islands (`1`) and navigable water (`0`). Ships spawn randomly on `0` cells.  
   - **Ship Classes**:  
     - **Battleship**: Moves once, shoots twice per turn; upgrades to **Destroyer** after 4 kills.  
     - **Cruiser**: Moves to enemy-occupied cells; upgrades to **Destroyer** after 3 kills.  
     - **Frigate**: Static, fires clockwise; upgrades to **Corvette** after 3 kills.  
     - **SuperShip** (upgraded): Moves like Cruiser, shoots 3 random locations per turn.  

2. **OOP Implementation**:  
   - **Inheritance Hierarchy**: Abstract base class `Ship` with derived classes (`MovingShip`, `ShootingShip`, etc.).  
   - **Polymorphism**: Dynamic action execution (e.g., `shoot()` behavior varies by ship type).  
   - **Custom Data Structures**: Self-built linked lists/queues for tracking active/destroyed ships (STL prohibited).  

3. **Rules & Edge Cases**:  
   - **Preemptive Actions**: Ships avoid suicide/team damage.  
   - **Upgrades**: Kills trigger ship transformations (e.g., Cruiser → Destroyer).  
   - **Respawns**: Destroyed ships re-enter battle twice from a queue.  

#### **Technical Implementation**  
- **Language**: C++ (ISO C++17).  
- **Key Challenges**:  
  - Implementing move semantics for efficient ship state transfers.  
  - Designing collision detection for ship movements/shots.  
- **Output**:  
  - **Console Display**: Battlefield grid with ship symbols (e.g., `*A1`, `>B2`).  
  - **Log File**: Records turn-by-turn actions (e.g., "*A1 shoots at (5,3)").  

#### **Outcome**  
- Simulated 100+ turns with team annihilation as win condition.  
- Demonstrated OOP mastery through clean class hierarchies and runtime polymorphism.  

#### **Skills Demonstrated**  
- **OOP Principles**: Inheritance, polymorphism, operator overloading.  
- **Low-Level C++**: Manual memory management, custom data structures.  
- **Problem-Solving**: Handling edge cases (e.g., respawns, upgrades).  

---  
**Note**: This project emphasized algorithmic logic and visualization but focused on OOP rigor and game mechanics. Both required parsing input files, simulating dynamic systems, and delivering clear outputs.
