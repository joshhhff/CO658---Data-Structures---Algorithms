#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

// item class - represents a single item in the player's inventory
class Item {
public:
    int id;       // unique identifier for the item
    string name;  // name of the item

    // initialises the item with a given ID and name
    Item(int itemId, string itemName) {
        id = itemId;     
        name = itemName;
    }
};

// quest class - represents a single quest with a name, reward, and urgency level
class Quest {
public:
    string name;  // the name/title of the quest
    int reward;   // gold or XP reward granted on completion
    int urgency;  // priority level (higher = more urgent); used to order the priority queue

    // initialises the quest with the given values
    Quest(string qName, int qReward, int qUrgency) {
        name = qName;
        reward = qReward;
        urgency = qUrgency;
    }

    // Overloads the < operator so the priority_queue can compare quests by urgency
    // Returns true if this quest has lower urgency than the other (max-heap behaviour)
    bool operator<(const Quest& other) const {
        return urgency < other.urgency;    // Lower urgency = lower priority in the queue
    }
};

// player class - manages the player's inventory and quests using three data structures
class Player {
private:
    vector<Item> inventory;                // dynamic array storing all carried items; O(1) access by index
    list<Quest> activeQuests;              // doubly linked list of active quests; O(1) insert/erase at any position
    priority_queue<Quest> urgentQuests;    // max-heap of quests ordered by urgency; O(log n) insert, O(1) top access

    // helper - reads a validated integer from within the class
    static int readInt(const string& prompt) {
        string line;   // buffer to hold the raw input line
        int value;     // variable to store the parsed integer
        while (true) { // loops until valid input is received
            cout << prompt;     // displays the prompt to the user
            getline(cin, line);    // reads the entire line to avoid leftover newline issues
            stringstream ss(line);    // wraps the line in a stream for safe parsing
            if (ss >> value && ss.eof()) { // checks that exactly one integer was entered and nothing else
                return value;    // returns the valid integer to the caller
            }
            cout << "Invalid input. Please enter a whole number.\n";    // prompts the user to try again
        }
    }

public:
    // adds a new item to the inventory vector
    void addItem(int id, const string& name) {
        inventory.push_back(Item(id, name));    // constructs an Item and appends it to the end of the vector
        cout << "[LOG] Item added: " << name << "\n";    // confirms the addition to the user
    }

    // displays all items with a numbered list, then asks the user to pick one to remove
    void promptRemoveItem() {
        if (inventory.empty()) { // checks whether the inventory vector contains any items
            cout << "\nInventory is empty. Nothing to remove.\n";
            return;
        }
        cout << "\n--- SELECT ITEM TO REMOVE ---\n";
        for (int i = 0; i < (int)inventory.size(); ++i) { // iterates over each item by index
            cout << "  " << (i + 1) << ". " << inventory[i].name << "\n"; 
        }
        int choice = readInt("Enter number of item to remove: "); // reads the user's numeric selection
        if (choice < 1 || choice > (int)inventory.size()) { // validates that the number is within the valid range
            cout << "[LOG] Invalid selection.\n";
            return;
        }
        auto it = inventory.begin() + (choice - 1); //  calculates iterator to the chosen item (converts to 0-based)
        cout << "[LOG] Item removed: " << it->name << "\n"; 
        inventory.erase(it); // removes the element at that iterator position from the vector
    }

    // displays all items in the inventory (used for the Show Inventory menu option)
    void showInventory() {
        if (inventory.empty()) {    // checks whether the inventory vector contains any items
            cout << "\nInventory is empty.\n";
            return;
        }
        cout << "\n--- INVENTORY ---\n";
        for (int i = 0; i < (int)inventory.size(); ++i) { // iterates over each item by index
            cout << "  " << (i + 1) << ". " << inventory[i].name << "\n";
        }
    }

    // adds a new quest to both the linked list and the priority queue
    void addQuest(const string& name, int reward, int urgency) {
        Quest q(name, reward, urgency); // constructs a Quest object with the given values
        activeQuests.push_back(q);      // appends the quest to the end of the doubly linked list
        urgentQuests.push(q);           // inserts the quest into the max-heap (reorders by urgency automatically)
        cout << "[LOG] Quest added: " << name << "\n";
    }

    // rebuilds the priority queue from the current state of activeQuests
    // necessary because priority_queue does not support direct deletion of arbitrary elements
    void rebuildQueue() {
        priority_queue<Quest> newQueue;    // creates a fresh empty priority queue
        for (const auto& q : activeQuests) { // iterates over every quest still in the linked list
            newQueue.push(q); // re-inserts each quest into the new heap, restoring correct order
        }
        urgentQuests = newQueue; // replaces the old queue with the fully rebuilt one
    }

    // displays all active quests with a numbered list, then asks the user to pick one to complete
    void promptCompleteQuest() {
        if (activeQuests.empty()) {    // checks whether the linked list has any quests
            cout << "\nNo active quests to complete.\n";
            return;
        }
        cout << "\n--- SELECT QUEST TO COMPLETE ---\n";
        int i = 1;    // counter used to display 1-based numbering alongside each quest
        for (const auto& q : activeQuests) {    // iterates over each quest node in the linked list
            cout << "  " << i++ << ". " << q.name
                 << " | Reward: " << q.reward
                 << " | Urgency: " << q.urgency << "\n";
        }
        int choice = readInt("Enter number of quest to complete: "); // reads the user's numeric selection
        if (choice < 1 || choice > (int)activeQuests.size()) {    // validates the selection is within range
            cout << "[LOG] Invalid selection.\n";
            return;
        }
        auto it = activeQuests.begin(); // gets an iterator pointing to the first quest in the list
        advance(it, choice - 1);        // advances the iterator to the chosen quest (converts to 0-based)
        cout << "[LOG] Quest completed: " << it->name << "\n"; // confirms which quest is being marked complete
        activeQuests.erase(it); // removes the quest node from the linked list in O(1)
        rebuildQueue();          // synchronises the priority queue to reflect the removal
    }

    // displays all active quests (used for the Show Quests menu option)
    void showQuests() {
        if (activeQuests.empty()) {    // checks whether the linked list has any quests
            cout << "\nNo active quests.\n";
            return;
        }
        cout << "\n--- ACTIVE QUESTS ---\n"; // prints the section header
        int i = 1; // counter for 1-based numbering
        for (const auto& q : activeQuests) { // iterates over each quest node in the linked list
            cout << "  " << i++ << ". " << q.name
                 << " | Reward: " << q.reward
                 << " | Urgency: " << q.urgency << "\n";
        }
    }

    // displays the highest-urgency quest from the priority queue without removing it
    void showTopQuest() {
        if (urgentQuests.empty()) {    // checks whether the priority queue is empty
            cout << "\nNo quests available.\n";
            return;
        }
        const Quest& q = urgentQuests.top();    // peeks at the root of the max-heap (highest urgency) in O(1)
        cout << "\nTop Priority Quest: " << q.name
             << " (Urgency: " << q.urgency
             << ", Reward: " << q.reward << ")\n";
    }
};

// reads a validated integer from the user (free function used in main)
int getIntInput(const string& prompt) {
    string line;   // Buffer to hold the raw input line
    int value;     // Variable to store the parsed integer
    while (true) { // Loops until valid input is received
        cout << prompt; // displays the prompt to the user
        getline(cin, line); // reads the full line to prevent stray newlines breaking subsequent reads
        stringstream ss(line); // wraps the line in a stringstream for safe integer extraction
        if (ss >> value && ss.eof()) { // succeeds only if the entire input is a valid integer
            return value; // returns the validated integer
        }
        cout << "Invalid input. Please enter a whole number.\n"; // asks the user to retry
    }
}

// reads a non-empty string from the user, supporting spaces in names
string getStringInput(const string& prompt) {
    string line; // buffer to hold the input
    while (true) { // loops until a non-empty string is entered
        cout << prompt; // displays the prompt
        getline(cin, line); // reads the full line including any spaces
        if (!line.empty()) return line; // returns the input if it contains at least one character
        cout << "Input cannot be empty. Please try again.\n"; // asks the user to retry
    }
}

// prints the main menu options to the console
void displayMenu() {
    cout << "\n=================================\n";
    cout << "       RPG PLAYER MANAGER\n";
    cout << "=================================\n";
    cout << "  1. Show Inventory\n";
    cout << "  2. Add Item\n";
    cout << "  3. Remove Item\n";
    cout << "  4. Show Quests\n";
    cout << "  5. Add Quest\n";
    cout << "  6. Complete Quest\n";
    cout << "  7. Show Top Priority Quest\n";
    cout << "  0. Exit\n";
    cout << "=================================\n";
}

// program entry point
int main() {
    Player player; // creates the player object which owns all three data structures

    // pre-populate some items and quests for demo purposes
    player.addItem(1, "Sword");
    player.addItem(2, "Shield");
    player.addQuest("Save the Village", 100, 5);
    player.addQuest("Defeat the Dragon", 500, 10);

    int choice; // stores the user's menu selection each iteration

    do {
        displayMenu(); // renders the menu options before each input prompt
        choice = getIntInput("Choose option: "); // reads and validates the menu choice

        switch (choice) {
            case 1:
                player.showInventory(); // displays all items currently in the inventory vector
                break;

            case 2: {
                int id = getIntInput("Enter item ID: ");
                string name = getStringInput("Enter item name: ");
                player.addItem(id, name);    // adds the new item to the inventory vector
                break;
            }

            case 3:
                player.promptRemoveItem(); // lists inventory with numbers; user picks which to remove
                break;

            case 4:
                player.showQuests();    // displays all active quests from the linked list
                break;

            case 5: {
                string name    = getStringInput("Quest name: ");     // reads the quest title
                int reward     = getIntInput("Reward: ");            // reads the reward value
                int urgency    = getIntInput("Urgency (1-10): ");    // reads the urgency/priority level
                if (urgency < 1 || urgency > 10) {    // warns if urgency is outside the expected range
                    cout << "Warning: Urgency is outside 1-10 range, but quest will still be added.\n";
                }
                player.addQuest(name, reward, urgency);    // adds the quest to both the list and the heap
                break;
            }

            case 6:
                player.promptCompleteQuest();    // lists quests with number - user picks which to complete
                break;

            case 7:
                player.showTopQuest();    // returns the highest-urgency quest from the priority queue
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid option. Please choose 0-7.\n"; // handles any number outside the valid range
        }

    } while (choice != 0);    // continues looping until the user selects Exit (0)

    return EXIT_SUCCESS;
}