/* Created by Gavin Atkin
 * Date: 4/23/2016
 * Homework 8 Data Structures
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

istream& getWord(istream& fin, string& w)
{
    char c;

    w = ""; // clear the string of characters

    while (fin.get(c) && !isalpha(c)); // do nothing. just ignore c

    // return on end-of-file
    if (fin.eof())
        return fin;

    // record first letter of the word
    w += tolower(c);

    // collect letters and digits
    while (fin.get(c) && (isalpha(c) || isdigit(c)))
        w += tolower(c);

    return fin;
}

void spellCheck(string filename) {
    unordered_map<int, string> words;           // User list of words
    unordered_map<int, string> dictionary;      // Dictionary to check against
    int keyGen = 0;

    ifstream file;
    file.open(filename);

    if (file) {
        // file is open
        // this is the user defined file

        while (!file.eof()) {
            string line;
            getline(file, line);
            stringstream ss(line);
            string word;
            getWord(ss, word);

            // Add word into user list of words
            words[keyGen] = word;
            keyGen++;
        }
    }
    else {
        cout << "Filename: " << filename << " does not exist!" << endl;
        return;
    }

    file.close();

    file.open("dict.dat");
    keyGen = 0;

    if (file) {
        // file is open
        // this is the user defined file

        while (!file.eof()) {
            string line;
            getline(file, line);
            stringstream ss(line);
            string word;
            getWord(ss, word);

            // Add word into dictionary
            dictionary[keyGen] = word;
            keyGen++;
        }
    }
    else {
        cout << "Filename: " << "dict.dat" << " does not exist!" << endl;
        return;
    }

    file.close();

    // Print out misspelled words.
    for (auto &x: words) {
        bool correct = false;
        for (auto &m: dictionary) {
            if (x.second == m.second) { // Word is a match in dictionary file
                correct = true;
            }
        }
        if (!correct) {
            cout << x.second << " is misspelled" << endl;
        }
    }
}

int main() {
    string f;
    cout << "Please enter a file with words to spell check:" << endl;
    cin >> f;

    spellCheck(f);
}