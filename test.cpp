#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string dictionaryFile = "dictionary.txt";

void generateDictionary() {
    ofstream file(dictionaryFile);
    file << "Word\tMeaning\n";
    file.close();
    cout << "Dictionary file generated successfully." << endl;
}

void addWordMeaning(const string& word, const string& meaning) {
    ofstream file(dictionaryFile, ios::app);
    file << word << "\t" << meaning << "\n";
    file.close();
    cout << "Word and meaning added successfully." << endl;
}

void searchMeaning(const string& word) {
    ifstream file(dictionaryFile);
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos = line.find("\t");
        if (pos != string::npos) {
            string storedWord = line.substr(0, pos);
            if (storedWord == word) {
                cout << "Meaning of '" << word << "': " << line.substr(pos + 1) << endl;
                found = true;
                break;
            }
        }
    }
    if (!found)
        cout << "Meaning not found." << endl;
    file.close();
}

void removeWord(const string& word) {
    ifstream file(dictionaryFile);
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find("\t");
        if (pos != string::npos) {
            string storedWord = line.substr(0, pos);
            if (storedWord != word)
                lines.push_back(line);
        }
    }
    file.close();

    ofstream outFile(dictionaryFile);
    for (const string& l : lines)
        outFile << l << "\n";
    outFile.close();

    cout << "'" << word << "' and its meaning removed successfully." << endl;
}

int main() {
    while (true) {
        cout << "\nDictionary Tool" << endl;
        cout << "1. Generate Dictionary" << endl;
        cout << "2. Add Word and Meaning" << endl;
        cout << "3. Search for Meaning" << endl;
        cout << "4. Remove Word and Meaning" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                generateDictionary();
                break;
            case 2: {
                string word, meaning;
                cout << "Enter the word: ";
                cin.ignore();
                getline(cin, word);
                cout << "Enter the meaning: ";
                getline(cin, meaning);
                addWordMeaning(word, meaning);
                break;
            }
            case 3: {
                string word;
                cout << "Enter the word to search: ";
                cin.ignore();
                getline(cin, word);
                searchMeaning(word);
                break;
            }
            case 4: {
                string word;
                cout << "Enter the word to remove: ";
                cin.ignore();
                getline(cin, word);
                removeWord(word);
                break;
            }
            case 5:
                cout << "Exiting Dictionary Tool." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
