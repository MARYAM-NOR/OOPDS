/**********|**********|**********|
Program: main.cpp / Vector.h / Queue.h
Course: Data Structures and Algorithms
Trimester: 2410
Members:
Name: Maryam Binti Norazman
ID: 1211111809
Name: Mohanad Hassan Fathy Abdelatty
ID: 241UC240QH
Name: Nur Rafiqah Qurratu’aini binti Mohd Seman
ID: 241UC2415F
Name: Ayuub Yusuf Ibrahim
ID: 241UC2400K
Lecture Section: TC1L
Tutorial Section: TT1L
**********|**********|**********/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "Vector.h" // Custom data structure implementations assumed
#include "Queue.h"  // Custom data structure implementations assumed

using namespace std;

// Forward declaration of Battlefield class
class Battlefield;

// Base Ship class
// This class serves as the base class for all types of ships in the game.
// It contains common attributes and methods that all ships share.
class Ship
{
protected:
    int shipPositionX = -1; // X coordinate of the ship on the battlefield
    int shipPositionY = -1; // Y coordinate of the ship on the battlefield
    string id_ = "";        // Unique identifier for the ship
    string shipType_ = "";  // Type of the ship
    string shipName_ = "";  // Name of the ship
    int numOfLives_ = 3;    // Number of lives the ship has
    int numOfKills_ = 0;    // Number of kills the ship has made

public:
    // Constructor to initialize ship attributes
    Ship(string id = "", int x = -1, int y = -1) : id_(id), shipPositionX(x), shipPositionY(y) {}

    // Virtual destructor
    virtual ~Ship() {}

    // Getter and setter methods for ship's X coordinate
    int x() const { return shipPositionX; }
    void setX(int x) { shipPositionX = x; }

    // Getter and setter methods for ship's Y coordinate
    int y() const { return shipPositionY; }
    void setY(int y) { shipPositionY = y; }

    // Getter and setter methods for ship's ID
    string id() const { return id_; }
    void setId(string id) { id_ = id; }

    // Getter and setter methods for ship's type
    string shipType() const { return shipType_; }
    void setShipType(string shipType) { shipType_ = shipType; }

    // Getter and setter methods for ship's name
    string shipName() const { return shipName_; }
    void setShipName(string shipName) { shipName_ = shipName; }

    // Getter and setter methods for ship's number of lives
    int numOfLives() const { return numOfLives_; }
    void setNumOfLives(int numOfLives) { numOfLives_ = numOfLives; }

    // Getter method for ship's number of kills
    int getNumOfKills() const { return numOfKills_; }

    // Method to convert ship's attributes to a string
    string toString() const
    {
        return "Ship " + id_ + " has " + to_string(numOfKills_) + " kills.";
    }

    // Overloaded output operator to print ship's attributes
    friend ostream &operator<<(ostream &out, const Ship &s)
    {
        out << s.id_ << " at (" << s.shipPositionX << ", " << s.shipPositionY << ")";
        return out;
    }

    // Pure virtual functions to be implemented by derived classes
    virtual void setLocation(int x, int y) = 0;
    virtual void actions(Battlefield *battlefield) = 0;
    void checkForUpgrade(Battlefield *battlefield);
};

// Abstract classes for different ship actions
class SeeingShip : virtual public Ship
{
public:
    virtual ~SeeingShip() {}
    virtual void look(Battlefield *battlefield) = 0;
};

class MovingShip : virtual public Ship
{
public:
    virtual ~MovingShip() {}
    virtual void move(Battlefield *battlefield) = 0;
};

class ShootingShip : virtual public Ship
{
public:
    virtual ~ShootingShip() {}
    virtual void shoot(Battlefield *battlefield) = 0;
};

class RamShip : virtual public Ship
{
public:
    virtual ~RamShip() {}
    virtual void destroy(Battlefield *battlefield) = 0;
};

// BattleShip class inherits from multiple action classes
// This class represents a BattleShip ship which can see, move, and shoot.
class Battleship : public SeeingShip, public MovingShip, public ShootingShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Battleship instances
public:
    // Constructor to initialize Battleship attributes
    Battleship(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipIncrement++;
        shipType_ = "Battleship";
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Battleship() {}

    // Set the location of the Battleship
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Look around the battlefield
    virtual void look(Battlefield *battlefield);

    // Move to a new location on the battlefield
    virtual void move(Battlefield *battlefield);

    // Fire at targets on the battlefield
    virtual void shoot(Battlefield *battlefield);

    // Perform all actions (look, move, fire) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Battleship::shipIncrement = 0;

// Cruiser class inherits from SeeingShip and RamShip
// This class represents a Cruiser ship which can see and step on other ships to terminate them.
class Cruiser : public SeeingShip, public RamShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Cruiser instances
public:
    // Constructor to initialize Cruiser attributes
    Cruiser(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipIncrement++;
        shipType_ = "Cruiser";
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Cruiser() {}

    // Set the location of the Cruiser
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Look around the battlefield
    virtual void look(Battlefield *battlefield);

    // Step to a new location on the battlefield
    virtual void destroy(Battlefield *battlefield);

    // Perform all actions (look, step) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Cruiser::shipIncrement = 0;

// Destroyer class inherits from multiple action classes
// This class represents a hybrid ship that can see, shoot, and step on other ships.
class Destroyer : public SeeingShip, public ShootingShip, public RamShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Destroyer instances
public:
    // Constructor to initialize Destroyer attributes
    Destroyer(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipType_ = "Destroyer";
        shipIncrement++;
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Destroyer() {}

    // Set the location of the Destroyer
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Look around the battlefield
    virtual void look(Battlefield *battlefield);

    // Fire at targets on the battlefield
    virtual void shoot(Battlefield *battlefield);

    // Step to a new location on the battlefield
    virtual void destroy(Battlefield *battlefield);

    // Perform all actions (look, fire, step) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Destroyer::shipIncrement = 0;

// Frigate class inherits from ShootingShip
// This class represents a Frigate ship which can only shoot.
class Frigate : public ShootingShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Frigate instances
    int fireDirection_ = 0;   // Direction in which the ship fires
public:
    // Constructor to initialize Frigate attributes
    Frigate(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipIncrement++;
        shipType_ = "Frigate";
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Frigate() {}

    // Set the location of the Frigate
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Fire at targets on the battlefield
    virtual void shoot(Battlefield *battlefield);

    // Perform all actions (fire) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Frigate::shipIncrement = 0;

// Corvette class inherits from ShootingShip
// This class represents a Corvette ship which can only shoot.
class Corvette : public ShootingShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Corvette instances
public:
    // Constructor to initialize Corvette attributes
    Corvette(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipIncrement++;
        shipType_ = "Corvette";
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Corvette() {}

    // Set the location of the Corvette
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Fire at targets on the battlefield
    virtual void shoot(Battlefield *battlefield);

    // Perform all actions (fire) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Corvette::shipIncrement = 0;

// Amphibious class inherits from ShootingShip
// This class represents a Amphibious ship which can only shoot.
class Amphibious : public ShootingShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Amphibious instances
public:
    // Constructor to initialize Amphibious attributes
    Amphibious(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipIncrement++;
        shipType_ = "Amphibious";
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Amphibious() {}

    // Set the location of the Amphibious
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Fire at targets on the battlefield
    virtual void shoot(Battlefield *battlefield);

    // Perform all actions (fire) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Amphibious::shipIncrement = 0;

// Supership class inherits from multiple action classes
// This class represents an Supership which can see, move, shoot, and step on other ships.
class Supership : public SeeingShip, public ShootingShip, public RamShip, public MovingShip
{
private:
    static int shipIncrement; // Static counter to generate unique IDs for Supership instances
public:
    // Constructor to initialize Supership attributes
    Supership(string id = "", int x = -1, int y = -1)
    {
        id_ = id;
        shipPositionX = x;
        shipPositionY = y;
        shipIncrement++;
        shipType_ = "Supership";
    }
    static int shipIncrement_() { return shipIncrement; }
    virtual ~Supership() {}

    // Set the location of the Supership
    virtual void setLocation(int x, int y)
    {
        shipPositionX = x;
        shipPositionY = y;
    }

    // Look around the battlefield
    virtual void look(Battlefield *battlefield);

    // Move to a new location on the battlefield
    virtual void move(Battlefield *battlefield);

    // Fire at targets on the battlefield
    virtual void shoot(Battlefield *battlefield);

    // Step to a new location on the battlefield
    virtual void destroy(Battlefield *battlefield);

    // Perform all actions (look, move, fire, step) on the battlefield
    virtual void actions(Battlefield *battlefield);
};
int Supership::shipIncrement = 0;

// Battlefield class definition
// This class represents the battlefield where ships perform their actions.
class Battlefield
{
private:
    int BTF_NUM_OF_COLS_ = -1;     // Number of columns on the battlefield
    int BTF_NUM_OF_ROWS_ = -1;     // Number of rows on the battlefield
    int turns_ = -1;               // Number of turns in the game
    int numOfShips_ = -1;          // Number of ships on the battlefield
    Vector<Ship *> ships_;         // Custom Vector class to store ships
    Vector<Vector<string>> btf_;   // Custom 2D Vector class to represent the battlefield grid
    Queue<Ship *> revivalQueue_;   // Custom Queue class to store ships to be revived
    static Battlefield *instance_; // Singleton instance of the Battlefield class

    Battlefield(const Battlefield &) = delete;
    Battlefield &operator=(const Battlefield &) = delete;

public:
    // Counters for each type of ship
    int battleshipCount_ = 0;
    int cruiserCount_ = 0;
    int destroyerCount_ = 0;
    int frigateCount_ = 0;
    int corvetteCount_ = 0;
    int amphibiousCount_ = 0;
    int supershipCount_ = 0;

    // Getter for ships vector
    Vector<Ship *> getShips() { return ships_; }

    // Constructor
    Battlefield() {}

    // Singleton instance getter
    static Battlefield *getInstance()
    {
        if (!instance_)
        {
            instance_ = new Battlefield();
        }
        return instance_;
    }

    // Destructor to clean up dynamically allocated ships
    ~Battlefield()
    {
        for (auto ship : ships_)
        {
            delete ship;
        }
    }

    // Getter methods for battlefield dimensions and game attributes
    int BTF_NUM_OF_COLS() { return BTF_NUM_OF_COLS_; }
    int BTF_NUM_OF_ROWS() { return BTF_NUM_OF_ROWS_; }
    int turns() { return turns_; }
    int numOfShips() { return numOfShips_; }
    Vector<Ship *> ships() { return ships_; }
    Vector<Vector<string>> btf() { return btf_; }

    // Read input file to initialize battlefield and ships
    void readFile(string filename)
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cout << "Cannot open the file: " << filename << endl;
            exit(1);
        }

        string key;
        int value;

        // Read iterations
        inFile >> key >> value;
        if (key == "iterations")
        {
            turns_ = value;
        }
        else
        {
            cout << "Error: Expected 'iterations', found '" << key << "'" << endl;
            exit(1);
        }

        // Read battlefield width
        inFile >> key >> value;
        if (key == "width")
        {
            BTF_NUM_OF_COLS_ = value;
        }
        else
        {
            cout << "Error: Expected 'width', found '" << key << "'" << endl;
            exit(1);
        }

        // Read battlefield height
        inFile >> key >> value;
        if (key == "height")
        {
            BTF_NUM_OF_ROWS_ = value;
        }
        else
        {
            cout << "Error: Expected 'height', found '" << key << "'" << endl;
            exit(1);
        }

        cout << "----------------------------------------------------------------------" << endl;
        cout << "|                  Game Start! Data Initialization ...               |" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "\nBattlefield Size: " << BTF_NUM_OF_COLS_ << " x " << BTF_NUM_OF_ROWS_ << "\n";
        cout << "Max Turns: " << turns_ << endl;

        // Resize battlefield
        btf_.resize(BTF_NUM_OF_ROWS_, Vector<string>(BTF_NUM_OF_COLS_, ""));

        // Read the rest of the file (teams, ships, grid)
        string line;
        while (getline(inFile, line))
        {
            if (line.find("Team") != string::npos)
            {
                string teamName;
                int numShips;
                istringstream iss(line);
                iss >> key >> teamName >> numShips;
                cout << "Team " << teamName << " has " << numShips << " ships." << endl;

                for (int i = 0; i < numShips; ++i)
                {
                    string shipType, shipSymbol;
                    int shipCount;
                    inFile >> shipType >> shipSymbol >> shipCount;

                    for (int j = 0; j < shipCount; ++j)
                    {
                        int x = rand() % BTF_NUM_OF_COLS_;
                        int y = rand() % BTF_NUM_OF_ROWS_;
                        string shipId = shipType.substr(0, 2) + to_string(j + 1);

                        if (shipType == "Battleship")
                        {
                            ships_.push_back(new Battleship(shipId, x, y));
                        }
                        else if (shipType == "Cruiser")
                        {
                            ships_.push_back(new Cruiser(shipId, x, y));
                        }
                        else if (shipType == "Destroyer")
                        {
                            ships_.push_back(new Destroyer(shipId, x, y));
                        }
                        else if (shipType == "Frigate")
                        {
                            ships_.push_back(new Frigate(shipId, x, y));
                        }
                        cout << "Added " << shipType << " (" << shipSymbol << ") at (" << x << ", " << y << ")" << endl;
                    }
                }
            }
        }

        // Read the battlefield grid
        for (int i = 0; i < BTF_NUM_OF_ROWS_; ++i)
        {
            for (int j = 0; j < BTF_NUM_OF_COLS_; ++j)
            {
                string cell;
                inFile >> cell;
                cout << "[" << btf_[i][j] << "] "; // Helps check empty spaces
                if (cell == "1" || cell == "0")
                {
                    btf_[i][j] = cell; // Store island (1) or sea (0)
                }
                else
                {
                    btf_[i][j] = cell; // Store ship symbols (e.g., "UR04", "TR03")
                }
            }
        }

        inFile.close();
        placeShips();
    }

    // Place ships on the battlefield
    void placeShips()
    {
        for (int i = 0; i < btf_.size(); ++i)
        {
            for (int j = 0; j < btf_[i].size(); ++j)
            {
                btf_[i][j] = "";
            }
        }
        for (int i = 0; i < ships_.size(); ++i)
        {
            if (ships_[i]->y() < btf_.size() && ships_[i]->x() < btf_[0].size())
            {
                btf_[ships_[i]->y()][ships_[i]->x()] = ships_[i]->id();
            }
            else
            {
                cout << "Error message: Invalid location for the ship " << ships_[i]->id() << endl;
                exit(1);
            }
        }
    }

    // Remove ship by ID from the battlefield
    void eraseShipById(string id)
    {
        for (int i = 0; i < ships_.size(); ++i)
        {
            if (ships_[i]->id() == id)
            {
                cout << "Killed ship " << *ships_[i] << endl;
                ships_.erase(ships_.begin() + i);
                break;
            }
        }
        placeShips();
    }

    // Add a ship back to the battlefield
    void pushBackShip(Ship *ship)
    {
        cout << "Push back ship " << *ship << "\n"
             << endl;
        ships_.push_back(ship);
        placeShips();
    }

    // Display the battlefield grid
    void displayBTF() const
    {
        cout << "\nCurrent Battlefield State:\n\n";

        for (int i = 0; i < BTF_NUM_OF_ROWS_; ++i)
        {
            for (int j = 0; j < BTF_NUM_OF_COLS_; ++j)
            {
                if (btf_[i][j] == "1")
                {
                    cout << "1 "; // Island
                }
                else if (btf_[i][j] == "0" || btf_[i][j].empty())
                {
                    cout << "0 "; // Sea
                }
                else
                {
                    cout << btf_[i][j] << " "; // Ship's symbol & number (e.g., "*1", "$2")
                }
            }
            cout << endl;
        }

        cout << endl;
    }

    // Run ship actions for each turn
    void runShipActions()
    {
        int turn = 1;
        int revive_CD = 3; // Cooldown for reviving ships
        while (turn <= turns_)
        {
            // Check if there's only one ship left standing
            if (ships_.size() == 1)
            {
                cout << "----------------------------------------------------------------------" << endl;
                cout << "|               Only one ship left standing. Game over!             |" << endl;
                cout << "----------------------------------------------------------------------\n"
                     << endl;
                displayBTF(); // Print final grid when the game ends
                return;
            }

            for (int i = 0; i < ships_.size(); ++i)
            {
                // Execute actions for each ship
                cout << "------------------------------- iteration " << turn << " -------------------------------" << endl;
                cout << *ships_[i] << endl;
                cout << "Num of lives: " << ships_[i]->numOfLives() << endl;
                cout << "------------------------ " << *ships_[i] << " Action" << " ------------------------ \n"
                     << endl;

                ships_[i]->actions(this);
                cout << "\n";
                displayBTF();
                cout << "\n"
                     << endl;

                // Increment the turn counter after each ship's turn
                turn++;
                if (!revivalQueue_.empty())
                {
                    revive_CD--;
                    if (revive_CD == 0)
                    {
                        // Revive ships after each round
                        reviveShips();

                        // Reset cooldown
                        revive_CD = revivalQueue_.empty() ? 3 : 2;
                    }
                }

                // Check if the turn reaches the maximum number of turns
                if (turn == turns_ + 1)
                {
                    cout << "----------------------------------------------------------------------" << endl;
                    cout << "|                  Maximum turns reached. Game over!                 |" << endl;
                    cout << "----------------------------------------------------------------------\n\n"
                         << endl;
                    displayBTF(); // Print final grid when the game ends
                    cout << "\n"
                         << "------------------------- Finale Battle Report -----------------------\n"
                         << endl;
                    return;
                }
            }
        }
    }

    // Print the area around a specific location
    void printLookArea(int x, int y) const
    {
        cout << "Look area centered at (" << x << ", " << y << "):\n\n";

        // Print the column indices
        cout << "     ";
        for (int j = x - 1; j <= x + 1; ++j)
        {
            if (j >= 0 && j < BTF_NUM_OF_COLS_)
            {
                cout << right << setfill('0') << setw(2) << j << "   ";
            }
            else
            {
                cout << "     ";
            }
        }
        cout << endl;

        // Print the top border
        cout << "   ";
        for (int j = x - 1; j <= x + 1; ++j)
        {
            cout << "+----";
        }
        cout << "+" << endl;

        for (int i = y - 1; i <= y + 1; ++i)
        {
            // Print the row index
            if (i >= 0 && i < BTF_NUM_OF_ROWS_)
            {
                cout << right << setfill('0') << setw(2) << i << " ";
            }
            else
            {
                cout << "   ";
            }

            for (int j = x - 1; j <= x + 1; ++j)
            {
                if (i >= 0 && i < BTF_NUM_OF_ROWS_ && j >= 0 && j < BTF_NUM_OF_COLS_)
                {
                    if (btf_[i][j] == "")
                    {
                        cout << "|    ";
                    }
                    else
                    {
                        cout << "|" << setw(4) << left << setfill(' ') << btf_[i][j];
                    }
                }
                else
                {
                    cout << "|####";
                }
            }
            cout << "|\n";

            // Print the row border
            cout << "   ";
            for (int j = x - 1; j <= x + 1; ++j)
            {
                cout << "+----";
            }
            cout << "+" << endl;
        }

        // Spacing
        cout << " " << endl;
    }

    // Check if a position is occupied by a ship
    bool isOccupied(int x, int y) const
    {
        for (auto ship : ships_)
        {
            if (ship->x() == x && ship->y() == y)
            {
                return true;
            }
        }
        return false;
    }

    // Move a ship to a new position
    void moveShip(Ship *ship, int newX, int newY)
    {
        if (!isOccupied(newX, newY) && newX >= 0 && newX < BTF_NUM_OF_COLS() && newY >= 0 && newY < BTF_NUM_OF_ROWS())
        {
            ship->setX(newX);
            ship->setY(newY);
            placeShips();
        }
    }

    // Attack a position on the battlefield
    bool attackPosition(int x, int y, const string &attackerId)
    {
        for (auto ship : ships_)
        {
            if (ship->x() == x && ship->y() == y)
            {
                cout << attackerId << " kills " << ship->id() << " at (" << x << ", " << y << ")" << endl;
                queueForRevival(ship);
                eraseShipById(ship->id());
                return true;
            }
        }
        return false;
    }

    // Queue a ship for revival
    void queueForRevival(Ship *ship)
    {
        if (ship->numOfLives() > 1)
        {
            ship->setNumOfLives(ship->numOfLives() - 1);
            revivalQueue_.enqueue(ship);
        }
    }

    // Revive ships from the queue
    void reviveShips()
    {
        if (!revivalQueue_.empty())
        {
            Ship *ship = revivalQueue_.front();
            revivalQueue_.dequeue();
            cout << ship->id() << " Lives left :" << ship->numOfLives() << endl;
            int x = ship->x();
            int y = ship->y();
            if (isOccupied(x, y))
            {
                do
                {
                    x = rand() % BTF_NUM_OF_COLS_;
                    y = rand() % BTF_NUM_OF_ROWS_;
                } while (isOccupied(x, y));
            }
            ship->setX(x);
            ship->setY(y);
            pushBackShip(ship);
        }
    }
};

Battlefield *Battlefield::instance_ = nullptr;

// Battleship action methods
void Battleship::look(Battlefield *battlefield)
{
    cout << "Battleship " << id_ << " looking around:\n";
    battlefield->printLookArea(shipPositionX, shipPositionY);
}

void Battleship::move(Battlefield *battlefield)
{
    while (true)
    {
        // Generate a random direction
        int direction = rand() % 8;

        // Define possible directions (pairs of x, y offsets)
        static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

        // Calculate new position based on the random direction
        int newX = shipPositionX + directions[direction].first;
        int newY = shipPositionY + directions[direction].second;

        // Check if the new position is within the grid boundaries and unoccupied
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() &&
            newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS() &&
            !battlefield->isOccupied(newX, newY) &&
            (newX != shipPositionX || newY != shipPositionY))
        {

            // Move the ship to the new position
            battlefield->moveShip(this, newX, newY);

            // Output the new position
            cout << "Battleship " << id_ << " moved to (" << newX << ", " << newY << ")\n";
            break; // Exit the loop after successful move
        }
    }
}

void Battleship::shoot(Battlefield *battlefield)
{
    int shots = 3;              // Number of shots Battleship can fire
    const int maxDistance = 10; // Maximum distance Battleship can fire
    int tempX, tempY;

    for (int i = 0; i < shots; ++i)
    {
        int distance = 0;
        int distanceX = 0;
        int distanceY = 0;

        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            distance = abs(distanceX) + abs(distanceY);
            tempX = distanceX + shipPositionX;
            tempY = distanceY + shipPositionY;
        } while (
            distance < 1 || distance > maxDistance ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_) == true)
        {
            numOfKills_++;
            cout << "Number of kills: " << numOfKills_ << '\n';
        }
        else
        {
            cout << "Number of kills: " << numOfKills_ << '\n';
        }
    }
}

void Battleship::actions(Battlefield *battlefield)
{
    look(battlefield);
    move(battlefield);
    shoot(battlefield);
    checkForUpgrade(battlefield);
}

// Cruiser action methods
void Cruiser::look(Battlefield *battlefield)
{
    cout << "Cruiser " << id_ << " looking around:\n";
    battlefield->printLookArea(shipPositionX, shipPositionY);
}

void Cruiser::destroy(Battlefield *battlefield)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a ship
    for (auto dir : directions)
    {
        int newX = shipPositionX + dir.first;
        int newY = shipPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                cout << "Cruiser " << id_ << " stepped ship at (" << newX << ", " << newY << ")\n";
                battlefield->attackPosition(newX, newY, id_);
                numOfKills_++;
                cout << "Number of kills: " << numOfKills_ << '\n';
                attacked = true;
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = shipPositionX + directions[index].first;
            int newY = shipPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveShip(this, newX, newY);
                cout << "Cruiser " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

void Cruiser::actions(Battlefield *battlefield)
{
    look(battlefield);
    destroy(battlefield);
    checkForUpgrade(battlefield);
}

// Destroyer action methods
void Destroyer::look(Battlefield *battlefield)
{
    cout << "Destroyer " << id_ << " looking around:\n";
    battlefield->printLookArea(shipPositionX, shipPositionY);
}

void Destroyer::shoot(Battlefield *battlefield)
{
    int shots = 3;              // Number of shots Destroyer can fire
    const int maxDistance = 10; // Maximum distance Destroyer can fire
    int tempX, tempY;

    for (int i = 0; i < shots; ++i)
    {
        int distance = 0;
        int distanceX = 0;
        int distanceY = 0;

        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            distance = abs(distanceX) + abs(distanceY);
            tempX = distanceX + shipPositionX;
            tempY = distanceY + shipPositionY;
        } while (
            distance < 1 || distance > maxDistance ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_) == true)
        {
            numOfKills_++;
            cout << "Number of kills: " << numOfKills_ << '\n';
        }
        else
        {
            cout << "Number of kills: " << numOfKills_ << '\n';
        }
    }
}

void Destroyer::destroy(Battlefield *battlefield)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a ship
    for (auto dir : directions)
    {
        int newX = shipPositionX + dir.first;
        int newY = shipPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                cout << "Destroyer " << id_ << " stepped ship at (" << newX << ", " << newY << ")\n";
                battlefield->attackPosition(newX, newY, id_);
                numOfKills_++;
                cout << "Number of kills: " << numOfKills_ << '\n';
                attacked = true;
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = shipPositionX + directions[index].first;
            int newY = shipPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveShip(this, newX, newY);
                cout << "Destroyer " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

void Destroyer::actions(Battlefield *battlefield)
{
    look(battlefield);
    shoot(battlefield);
    destroy(battlefield);
    checkForUpgrade(battlefield);
}

// Frigate action methods
void Frigate::shoot(Battlefield *battlefield)
{
    int x = shipPositionX;
    int y = shipPositionY;
    static const pair<int, int> directions[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int targetX = x + directions[fireDirection_].first;
    int targetY = y + directions[fireDirection_].second;
    cout << id_ << " fires at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(targetX, targetY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
    }
    fireDirection_ = (fireDirection_ + 1) % 8;
}

void Frigate::actions(Battlefield *battlefield)
{
    shoot(battlefield);
}

// Corvette action methods
void Corvette::shoot(Battlefield *battlefield)
{
    int x = shipPositionX;
    int y = shipPositionY;
    int dir = rand() % 8;
    static const pair<int, int> directions[] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int targetX = x + directions[dir].first;
    int targetY = y + directions[dir].second;
    cout << id_ << " randomly fires at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(targetX, targetY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
    }
}

void Corvette::actions(Battlefield *battlefield)
{
    shoot(battlefield);
    checkForUpgrade(battlefield);
}

// Amphibious action methods
void Amphibious::shoot(Battlefield *battlefield)
{
    int targetX = rand() % battlefield->BTF_NUM_OF_COLS();
    int targetY = rand() % battlefield->BTF_NUM_OF_ROWS();

    // Add logic to not shoot itself
    cout << id_ << " fires across the battlefield at (" << targetX << ", " << targetY << ")" << endl;
    if (battlefield->attackPosition(targetX, targetY, id_) == true)
    {
        numOfKills_++;
        cout << "Number of kills: " << numOfKills_ << '\n';
    }
    else
    {
        cout << "Number of kills: " << numOfKills_ << '\n';
    }
}

void Amphibious::actions(Battlefield *battlefield)
{
    shoot(battlefield);
    checkForUpgrade(battlefield);
}

// Supership action methods
void Supership::look(Battlefield *battlefield)
{
    cout << "Supership " << id_ << " looking around:\n";
    battlefield->printLookArea(shipPositionX, shipPositionY);
}

void Supership::move(Battlefield *battlefield)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a ship
    for (auto dir : directions)
    {
        int newX = shipPositionX + dir.first;
        int newY = shipPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                battlefield->attackPosition(newX, newY, id_);
                cout << "Supership " << id_ << " stepped ship at (" << newX << ", " << newY << ")\n";
                numOfKills_++;
                attacked = true;
                cout << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {
        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = shipPositionX + directions[index].first;
            int newY = shipPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveShip(this, newX, newY);
                cout << "Supership " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

void Supership::shoot(Battlefield *battlefield)
{
    int shots = 3; // Number of shots Supership can fire
    int tempX, tempY;

    for (int i = 0; i < shots; ++i)
    {
        int distanceX = 0;
        int distanceY = 0;

        do
        {
            distanceX = rand() % 21 - 10;
            distanceY = rand() % 21 - 10;
            tempX = distanceX + shipPositionX;
            tempY = distanceY + shipPositionY;
        } while (
            abs(distanceX) + abs(distanceY) < 1 ||
            tempX < 0 || tempX >= battlefield->BTF_NUM_OF_COLS() ||
            tempY < 0 || tempY >= battlefield->BTF_NUM_OF_ROWS());

        cout << id_ << " fires at (" << tempX << ", " << tempY << ")" << endl;
        if (battlefield->attackPosition(tempX, tempY, id_) == true)
        {
            numOfKills_++;
            cout << "Number of kills: " << numOfKills_ << '\n';
        }
        else
        {
            cout << "Number of kills: " << numOfKills_ << '\n';
        }
    }
}

void Supership::destroy(Battlefield *battlefield)
{
    static const pair<int, int> directions[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    bool attacked = false;

    // First loop to detect and attack if any adjacent cell contains a ship
    for (auto dir : directions)
    {
        int newX = shipPositionX + dir.first;
        int newY = shipPositionY + dir.second;
        if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
        {
            if (battlefield->isOccupied(newX, newY))
            {
                cout << "Supership " << id_ << " stepped ship at (" << newX << ", " << newY << ")\n";
                battlefield->attackPosition(newX, newY, id_);
                numOfKills_++;
                cout << "Number of kills: " << numOfKills_ << '\n';
                attacked = true;
                break;
            }
        }
    }

    // If no attack was made, move to a random adjacent position
    if (!attacked)
    {

        int randomIndex = rand() % 8;
        for (int i = 0; i < 8; ++i)
        {
            int index = (randomIndex + i) % 8;
            int newX = shipPositionX + directions[index].first;
            int newY = shipPositionY + directions[index].second;
            if (newX >= 0 && newX < battlefield->BTF_NUM_OF_COLS() && newY >= 0 && newY < battlefield->BTF_NUM_OF_ROWS())
            {
                battlefield->moveShip(this, newX, newY);
                cout << "Supership " << id_ << " stepped to (" << newX << ", " << newY << ")\n";
                cout << "Number of kills: " << numOfKills_ << '\n';
                break;
            }
        }
    }
}

// Perform all actions (look, move, fire, step) on the battlefield
void Supership::actions(Battlefield *battlefield)
{
    look(battlefield);    // Supership looks around
    move(battlefield);    // Supership moves to a new position
    shoot(battlefield);   // Supership fires at targets
    destroy(battlefield); // Supership steps to adjacent cells
}

// Implementing checkForUpgrade method for the Ship class
void Ship::checkForUpgrade(Battlefield *battlefield)
{
    if (numOfKills_ == 3)
    {
        string newType, newId;

        // Determine the new type and ID for the upgraded ship
        if (shipType_ == "Battleship")
        {
            newType = "Destroyer";
            int count = ++battlefield->destroyerCount_;
            newId = (count < 10) ? "#" + to_string(count) : "#" + to_string(count);
        }
        else if (shipType_ == "Cruiser")
        {
            newType = "Destroyer";
            int count = ++battlefield->destroyerCount_;
            newId = (count < 10) ? "#" + to_string(count) : "#" + to_string(count);
        }
        else if (shipType_ == "Frigate")
        {
            newType = "Corvette";
            int count = ++battlefield->corvetteCount_;
            newId = (count < 10) ? "^" + to_string(count) : "^" + to_string(count);
        }
        else if (shipType_ == "Corvette")
        {
            newType = "Amphibious";
            int count = ++battlefield->amphibiousCount_;
            newId = (count < 10) ? "%" + to_string(count) : "%" + to_string(count);
        }
        else if (shipType_ == "Amphibious")
        {
            newType = "Supership";
            int count = ++battlefield->supershipCount_;
            newId = (count < 10) ? "!" + to_string(count) : "!" + to_string(count);
        }
        else if (shipType_ == "Destroyer")
        {
            newType = "Supership";
            int count = ++battlefield->supershipCount_;
            newId = (count < 10) ? "!" + to_string(count) : "!" + to_string(count);
        }
        else
        {
            return;
        }

        // Remove the old ship and add the upgraded ship
        battlefield->eraseShipById(id_);

        Ship *upgradedShip = nullptr;
        if (newType == "Destroyer")
        {
            upgradedShip = new Destroyer(newId, shipPositionX, shipPositionY);
        }
        else if (newType == "Corvette")
        {
            upgradedShip = new Corvette(newId, shipPositionX, shipPositionY);
        }
        else if (newType == "Amphibious")
        {
            upgradedShip = new Amphibious(newId, shipPositionX, shipPositionY);
        }
        else if (newType == "Supership")
        {
            upgradedShip = new Supership(newId, shipPositionX, shipPositionY);
        }

        battlefield->pushBackShip(upgradedShip);

        cout << shipType_ << " upgraded to " << newType << " with ID " << newId << endl;
        numOfKills_ = 0; // reset kill counter
    }
}

// Main function to start the simulation
int main()
{
    Battlefield *battlefield = Battlefield::getInstance();

    string filename = "game.txt";
    cout << "Read " << filename << ":\n";
    battlefield->readFile(filename); // Initialize battlefield from input file
    cout << endl;

    cout << "------------------------ Display starting grid ------------------------\n"
         << endl;
    battlefield->displayBTF(); // Display the initial state of the battlefield

    cout << "\n";
    battlefield->runShipActions(); // Run the simulation
    for (auto ship : battlefield->getShips())
    {
        cout << "Ship " << ship->id() << " has " << ship->getNumOfKills() << " kills." << endl;
    }

    return 0;
}
