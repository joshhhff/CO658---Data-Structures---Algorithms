#include <iostream>
#include <vector>       // For dynamic inventory
#include <list>         // For linked list of active quests
#include <queue>        // For priority queue of urgent quests
#include <string>       // For string item/quest names
using namespace std;

// Item class
class Item {
public:
    int id;           // Unique identifier for the item
    string name;      // Human-readable name of the item

    // Constructor initializes item ID and name
    Item(int id, string name) : id(id), name(name) {}
};

// Quest class
class Quest {
public:
    string name;      // Quest name
    int reward;       // Reward value for completing the quest
    int urgency;      // Priority level (higher = more urgent)

    // Constructor initializes quest attributes
    Quest(string name, int reward, int urgency)
        : name(name), reward(reward), urgency(validateUrgency(urgency)) {}

    // Overload operator< for priority queue
    // Priority queue keeps the quest with highest urgency on top
    bool operator<(const Quest& other) const {
        return urgency < other.urgency; // lower urgency is "less than"
    }

    int validateUrgency(int u) const {
        if (u < 1 || u > 10) {
            throw invalid_argument("Urgency must be between 1 and 10.");
        }
        return u;
    }
};

// Player class managing inventory and quests
class Player {
public:
    vector<Item> inventory;          // Dynamic array storing items
    list<Quest> activeQuests;        // Linked list for active quests
    priority_queue<Quest> urgentQuests; // Priority queue for urgent quests

    // Add item to player's inventory
    void addItem(const Item& item) {
        inventory.push_back(item);   // Vector push_back adds to end
    }

    // Remove item from inventory by ID
    void removeItem(int id) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->id == id) {
                inventory.erase(it); // Remove the item from vector
                break;
            }
        }
    }

    // Display all items in inventory
    void showInventory() {
        cout << "Inventory:\n";
        for (const auto& item : inventory) {
            cout << "- " << item.name << " (ID: " << item.id << ")\n";
        }
    }

    // Add a quest to both linked list and priority queue
    void addQuest(const Quest& quest) {
        activeQuests.push_back(quest); // Add to linked list
        urgentQuests.push(quest);      // Add to priority queue
    }

    // Complete a quest by name
    void completeQuest(const string& questName) {
        // Remove from linked list
        for (auto it = activeQuests.begin(); it != activeQuests.end(); ++it) {
            if (it->name == questName) {
                activeQuests.erase(it);
                break;
            }
        }

        // Priority queue removal is tricky, normally would rebuild
        // For demonstration, just display top urgent quest next
    }

    // Show top urgent quest
    void showTopUrgentQuest() {
        if (!urgentQuests.empty()) {
            Quest top = urgentQuests.top();
            cout << "Top urgent quest: " << top.name
                 << " (Urgency: " << top.urgency
                 << ", Reward: " << top.reward << ")\n";
        } else {
            cout << "No urgent quests.\n";
        }
    }

    // Display all active quests
    void showActiveQuests() {
        cout << "Active Quests:\n";
        for (const auto& quest : activeQuests) {
            cout << "- " << quest.name
                 << " (Urgency: " << quest.urgency
                 << ", Reward: " << quest.reward << ")\n";
        }
    }
};

// Main function demonstrating the inventory system
int main() {
    // Create a player object
    Player player;

    // Add items to inventory
    player.addItem(Item(1, "Sword"));      // Add sword
    player.addItem(Item(2, "Shield"));     // Add shield
    player.addItem(Item(3, "Health Potion")); // Add potion

    // Display inventory
    player.showInventory();

    // Add quests to player
    player.addQuest(Quest("Find the Gem", 500, 3));      // Moderate urgency
    player.addQuest(Quest("Defeat the Dragon", 1000, 10)); // Very urgent
    player.addQuest(Quest("Collect Herbs", 200, 1));    // Low urgency
    player.addQuest(Quest("Rescue Villager", 800, 7));  // High urgency

    // Display all active quests
    player.showActiveQuests();

    // Show top urgent quest
    player.showTopUrgentQuest();

    // Complete a quest
    cout << "\nCompleting quest: Collect Herbs\n";
    player.completeQuest("Collect Herbs");

    // Show updated active quests
    player.showActiveQuests();

    // Remove an item from inventory
    cout << "\nUsing item: Health Potion\n";
    player.removeItem(3); // Remove Health Potion by ID

    // Show updated inventory
    player.showInventory();

    return EXIT_SUCCESS;
}