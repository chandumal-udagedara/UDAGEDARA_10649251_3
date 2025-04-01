#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Struct to store word information
struct Word {
    std::string name;      // The word in the dictionary
    std::string type;      // The word type (e.g., "n", "v", "adj")
    std::string definition; // The definition(s)
};

// Function declarations
void loadDictionary(std::vector<Word>& Dictionary);
void lookupWord(const std::vector<Word>& Dictionary);
void getRandomWord(const std::vector<Word>& Dictionary);
std::string getAbbreviatedType(const std::string& type);

// Function to display the menu
static void displayMenu() {
    std::cout << "\nDictionary Program Menu:\n";
    std::cout << "1. Load Dictionary\n";
    std::cout << "2. Lookup Word\n";
    std::cout << "3. Get Random Word\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice (1-4): ";
}

int main() {
    std::vector<Word> Dictionary;
    int choice;
    bool running = true;

    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (running) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline character

        switch (choice) {
        case 1:
            loadDictionary(Dictionary);
            break;
        case 2:
            lookupWord(Dictionary);
            break;
        case 3:
            getRandomWord(Dictionary);
            break;
        case 4:
            running = false;
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

//Converts word type to its abbreviated form
 
std::string getAbbreviatedType(const std::string& type) {
    if (type == "n") return "(n.)";
    if (type == "v") return "(v.)";
    if (type == "adv") return "(adv.)";
    if (type == "adj") return "(adj.)";
    if (type == "prep") return "(prep.)";
    if (type == "misc") return "(misc.)";
    if (type == "pn") return "(pn.)";
    if (type == "n v") return "(n. v.)";
    return type;
}

//Loads and parses the dictionary file, starting from the word "aa"
 
void loadDictionary(std::vector<Word>& Dictionary) {
    std::ifstream file("Dictionary/dictionary_2025S1.txt");
    if (!file.is_open()) {
        std::cout << "Error - Could not open dictionary file.\n";
        return;
    }

    Dictionary.clear(); // Clear existing dictionary
    std::string line;
    Word currentWord;
    bool startCounting = false; // Flag to track when we start counting words

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            if (!currentWord.name.empty()) {
                if (startCounting) {
                    Dictionary.push_back(currentWord);
                }
                currentWord = Word(); // Reset for next word
            }
            continue;
        }

        // Remove semicolon if present
        if (!line.empty() && line.back() == ';') {
            line.pop_back();
        }

        // Parse word information
        if (currentWord.name.empty()) {
            currentWord.name = line;
            // Check if we've reached "aa" or passed it
            if (line >= "aa") {
                startCounting = true;
            }
        }
        else if (currentWord.type.empty()) {
            currentWord.type = line;
        }
        else {
            if (!currentWord.definition.empty()) {
                currentWord.definition += "\n";
            }
            currentWord.definition += line;
        }
    }

    // Add the last word if exists and we're counting
    if (!currentWord.name.empty() && startCounting) {
        Dictionary.push_back(currentWord);
    }
    file.close();
    std::cout << "Dictionary loaded successfully with " << Dictionary.size() << " words.\n";
}

// Looks up a word in the dictionary
 
void lookupWord(const std::vector<Word>& Dictionary) {
    if (Dictionary.empty()) {
        std::cout << "Error - dictionary empty\n";
        return;
    }

    std::string searchWord;
    std::cout << "Enter word to lookup: ";
    std::getline(std::cin, searchWord);

    // Convert search word to lowercase for case-insensitive comparison
    std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);

    bool found = false;
    for (const auto& word : Dictionary) {
        std::string wordName = word.name;
        std::transform(wordName.begin(), wordName.end(), wordName.begin(), ::tolower);

        if (wordName == searchWord) {
            found = true;
            std::cout << "\nWord: " << word.name << "\n";
            std::cout << "Type: " << getAbbreviatedType(word.type) << "\n";
            std::cout << "Definition(s):\n" << word.definition << "\n\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Word not found.\n";
    }
}

// Retrieves and displays a random word from the dictionary
 
void getRandomWord(const std::vector<Word>& Dictionary) {
    if (Dictionary.empty()) {
        std::cout << "Error - dictionary empty\n";
        return;
    }

    // Generate random index
    int randomIndex = std::rand() % Dictionary.size();
    const Word& word = Dictionary[randomIndex];

    std::cout << "\nRandom Word:\n";
    std::cout << "Word: " << word.name << "\n";
    std::cout << "Type: " << getAbbreviatedType(word.type) << "\n";
    std::cout << "Definition(s):\n" << word.definition << "\n\n";
}