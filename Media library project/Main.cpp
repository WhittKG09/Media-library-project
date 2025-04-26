// Kedryn G Whittington, Media part 2, 4/24/2025  Class 201
// Program takes input of movies, books, and songs, and sorts them out. 
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Movie.h"
#include "Book.h"
#include "Song.h"

using namespace std;

bool isInt(const string& str) {
    try {
        stoi(str);
        return true;
    }
    catch (...) {
        return false;
    }
}

void processCommands(const string& cmdFile, vector<Media*>& mediaList, ofstream& out, ofstream& err) {
    ifstream cmdin(cmdFile);
    string cmdLine;

    while (getline(cmdin, cmdLine)) {
        if (cmdLine.empty()) continue;
        stringstream ss(cmdLine);
        string code, arg;
        getline(ss, code, ',');

        transform(code.begin(), code.end(), code.begin(), ::toupper);

        if (code == "A") {
            out << "\n--- All Media ---\n";
            for (auto* m : mediaList) m->print(out, mediaList);
        }
        else if (code == "T") {
            out << "\n--- Media By Type ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Movie*>(m)) {
                    m->print(out, mediaList);
                }
            }
            for (auto* m : mediaList) {
                if (dynamic_cast<Book*>(m)) {
                    m->print(out, mediaList);
                }
            }
            for (auto* m : mediaList) {
                if (dynamic_cast<Song*>(m)) {
                    m->print(out, mediaList);
                }
            }
        }
        else if (code == "M") {
            out << "\n--- Movies ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Movie*>(m)) {
                    m->print(out, mediaList);
                }
            }
        }
        else if (code == "B") {
            out << "\n--- Books ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Book*>(m)) {
                    m->print(out, mediaList);
                }
            }
        }
        else if (code == "S") {
            out << "\n--- Songs ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Song*>(m)) {
                    m->print(out, mediaList);
                }
            }
        }
        else if (code == "L") {
            getline(ss, arg);
            bool found = false;
            for (auto* m : mediaList) {
                if (auto* mov = dynamic_cast<Movie*>(m)) {
                    if (mov->getTitle() == arg) {
                        found = true;
                        out << "Stars in '" << arg << "': ";
                        const vector<string>& stars = mov->getStars();
                        for (size_t i = 0; i < stars.size(); ++i) {
                            out << stars[i];
                            if (i != stars.size() - 1) out << ", ";
                        }
                        out << "\n";
                        break;
                    }
                }
            }
            if (!found) err << "Title not found for L: " << arg << "\n";
        }
        else if (code == "F") {
            getline(ss, arg);
            bool found = false;
            out << "\n--- Movies featuring " << arg << " ---\n";
            for (auto* m : mediaList) {
                if (auto* mov = dynamic_cast<Movie*>(m)) {
                    const vector<string>& stars = mov->getStars();
                    if (find(stars.begin(), stars.end(), arg) != stars.end()) {
                        mov->print(out, mediaList);
                        found = true;
                    }
                }
            }
            if (!found) err << "Actor not found in any movie for F: " << arg << "\n";
        }
        else if (code == "K") {
            getline(ss, arg);
            bool found = false;
            out << "\n--- Media with key name '" << arg << "' ---\n";
            for (auto* m : mediaList) {
                if (m->getKeyName() == arg) {
                    m->print(out, mediaList);
                    found = true;
                }
            }
            if (!found) err << "Key name not found for K: " << arg << "\n";
        }
        else if (code == "N") {
            getline(ss, arg);
            vector<string> newTokens;
            stringstream newSS(arg);
            string token;
            while (getline(newSS, token, ',')) {
                newTokens.push_back(token);
            }

            if (newTokens.size() < 7) {
                err << "Invalid N command (insufficient tokens): " << arg << "\n";
                continue;
            }

            char newType = newTokens[0].empty() ? ' ' : toupper(newTokens[0][0]);
            string newTitle = newTokens[1];
            string newKeyName = newTokens[2];
            string newRatingStr = newTokens[3];
            string newGenre = newTokens[4];
            string newLengthStr = newTokens[5];
            string newYearStr = newTokens[6];

            if (!isInt(newRatingStr) || !isInt(newLengthStr) || !isInt(newYearStr)) {
                err << "Non-numeric field in N command: " << arg << "\n";
                continue;
            }

            int newRating = stoi(newRatingStr);
            int newLength = stoi(newLengthStr);
            int newYear = stoi(newYearStr);

            if (newRating <= 0 || newRating > 10 || newYear < 1920 || newYear >2024) {
                err << "Invalid integer value in N command: " << arg << "\n";
                continue;
            }

            if (newType == 'M') {
                vector<string> newStars(newTokens.begin() + 7, newTokens.end());
                newStars.erase(remove_if(newStars.begin(), newStars.end(), [](const string& s) { return s.empty(); }), newStars.end());
                mediaList.push_back(new Movie(newTitle, newKeyName, newRating, newGenre, newLength, newYear, newStars));
            }
            else if (newType == 'S') {
                if (newTokens.size() < 8) {
                    err << "Invalid N command for Song (insufficient tokens): " << arg << "\n";
                    continue;
                }
                string newTop40Str = newTokens[7];
                if (newTop40Str != "0" && newTop40Str != "1") {
                    err << "Invalid top40 value in N command: " << arg << "\n";
                    continue;
                }
                bool newTop40 = (newTop40Str == "1");
                mediaList.push_back(new Song(newTitle, newKeyName, newRating, newGenre, newLength, newYear, newTop40));
            }
            else if (newType == 'B') {
                if (newTokens.size() < 8) {
                    err << "Invalid N command for Book (insufficient tokens): " << arg << "\n";
                    continue;
                }
                string newWeeksNYTStr = newTokens[7];
                if (!isInt(newWeeksNYTStr)) {
                    err << "Non-numeric weeksNYT in N command: " << arg << "\n";
                    continue;
                }
                int newWeeksNYT = stoi(newWeeksNYTStr);
                if (newWeeksNYT < 0) {
                    err << "Invalid weeksNYT value in N command: " << arg << "\n";
                    continue;
                }
                mediaList.push_back(new Book(newTitle, newKeyName, newRating, newGenre, newLength, newYear, newWeeksNYT));
            }
            else {
                err << "Invalid media type in N command: " << arg << "\n";
                continue;
            }
        }
        else if (code == "Q") {
            out << "\n--- Quitting command processing ---\n";
            break;
        }
        else {
            err << "Unknown command: " << cmdLine << "\n";
        }
    }

    cmdin.close();
}
//pre: mediaCommands.txt, and medialist.txt
//post: using previous files, generate a report and error file
int main() {
    ifstream infile("mediaList.txt");
    ofstream outfile("mediaOutput.txt");
    ofstream errorfile("mediaError.txt");

    vector<Media*> mediaList;
    string line;

    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> tokens;
        string token;

        while (getline(ss, token, '\t')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 7) {
            errorfile << "Invalid record format: " << line << endl;
            continue;
        }

        char type = tokens[0].empty() ? ' ' : tokens[0][0];
        string title = tokens[1];
        string keyName = tokens[2];
        string ratingStr = tokens[3];
        string genre = tokens[4];
        string lengthStr = tokens[5];
        string yearStr = tokens[6];

        if ((type == 'B' || type == 'S') && tokens.size() < 8) {
            errorfile << "Invalid record format (missing fields): " << line << endl;
            continue;
        }

        if (!isInt(ratingStr) || !isInt(lengthStr) || !isInt(yearStr)) {
            errorfile << "Non-numeric field: " << line << endl;
            continue;
        }

        int rating = stoi(ratingStr);
        int length = stoi(lengthStr);
        int year = stoi(yearStr);

        if (rating <= 0 || rating > 10 || year < 1920 || year >2024) {
            errorfile << "Invalid integer value: " << line << endl;
            continue;
        }

        if (type == 'M') {
            vector<string> stars(tokens.begin() + 7, tokens.end());
            stars.erase(remove_if(stars.begin(), stars.end(), [](const string& s) { return s.empty(); }), stars.end());
            mediaList.push_back(new Movie(title, keyName, rating, genre, length, year, stars));
        }
        else if (type == 'S') {
            string top40Str = tokens[7];
            if (top40Str != "0" && top40Str != "1") {
                errorfile << "Invalid top40 value: " << line << endl;
                continue;
            }
            bool top40 = (top40Str == "1");
            mediaList.push_back(new Song(title, keyName, rating, genre, length, year, top40));
        }
        else if (type == 'B') {
            string weeksNYTStr = tokens[7];
            if (!isInt(weeksNYTStr)) {
                errorfile << "Non-numeric weeksNYT: " << line << endl;
                continue;
            }
            int weeksNYT = stoi(weeksNYTStr);
            if (weeksNYT < 0) {
                errorfile << "Invalid weeksNYT value: " << line << endl;
                continue;
            }
            mediaList.push_back(new Book(title, keyName, rating, genre, length, year, weeksNYT));
        }
        else {
            errorfile << "Invalid media type: " << line << endl;
            continue;
        }
    }

    processCommands("mediaCommands.txt", mediaList, outfile, errorfile);

    for (auto* m : mediaList) delete m;

    infile.close();
    outfile.close();
    errorfile.close();
    return 0;
}