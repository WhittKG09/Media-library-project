// Kedryn G Whittington, Media part 2, 4/24/2025  Class 201
// Program takes input of movies, books, and songs, and sorts them out. 

#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>       
#include "Media.h"    
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
            // Print Movies first
            for (auto* m : mediaList) {
                if (dynamic_cast<Movie*>(m)) m->print(out, mediaList);
            }
            // Then Books
            for (auto* m : mediaList) {
                if (dynamic_cast<Book*>(m)) m->print(out, mediaList);
            }
            // Then Songs
            for (auto* m : mediaList) {
                if (dynamic_cast<Song*>(m)) m->print(out, mediaList);
            }
        }
        else if (code == "M") {
            out << "\n--- Movies ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Movie*>(m)) m->print(out, mediaList);
            }
        }
        else if (code == "B") {
            out << "\n--- Books ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Book*>(m)) m->print(out, mediaList);
            }
        }
        else if (code == "S") {
            out << "\n--- Songs ---\n";
            for (auto* m : mediaList) {
                if (dynamic_cast<Song*>(m)) m->print(out, mediaList);
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
            if (!found) err << "Unable to process command. The movie: '" << arg << "' is not found in your list\n";
        }
        else if (code == "F") {
            getline(ss, arg);
            bool found = false;
            vector<string> movieTitles;

            for (auto* m : mediaList) {
                if (auto* mov = dynamic_cast<Movie*>(m)) {
                    const vector<string>& stars = mov->getStars();
                    if (find(stars.begin(), stars.end(), arg) != stars.end()) {
                        movieTitles.push_back(mov->getTitle());
                        found = true;
                    }
                }
            }

            if (found) {
                out << "\n" << arg << " appears in the following movie(s):\n";
                for (const auto& title : movieTitles) out << title << "\n";
            }
            else {
                err << "Unable to process command. The star: " << arg << " is not found in any movies in your list\n";
            }
        }
        else if (code == "K") {
            getline(ss, arg);
            bool found = false;
            out << "\n" << arg << " appears in the following media item(s):\n";
            out << "TYPE TITLE RATING\n";

            for (auto* m : mediaList) {
                if (m->getKeyName() == arg) {
                    out << m->getType() << " " << m->getTitle() << " " << m->getRating() << "\n";
                    found = true;
                }
            }

            if (!found) err << "Unable to process command. The name: " << arg << " was not found in your list\n";
        }
        else if (code == "N") {
            // ... (keep N command logic unchanged)
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

        while (getline(ss, token, '\t')) tokens.push_back(token);

        if (tokens.size() < 7) {
            errorfile << "Invalid record format: " << line << endl;
            continue;
        }

        char type = !tokens[0].empty() ? toupper(tokens[0][0]) : ' ';
        string title = tokens[1];
        string keyName = tokens[2];
        string ratingStr = tokens[3];
        string genre = tokens[4];
        string lengthStr = tokens[5];
        string yearStr = tokens[6];

        if (!isInt(ratingStr) || !isInt(lengthStr) || !isInt(yearStr)) {
            errorfile << "Non-numeric field: " << line << endl;
            continue;
        }

        int rating = stoi(ratingStr);
        int length = stoi(lengthStr);
        int year = stoi(yearStr);

        if (rating < 1 || rating > 10 || year < 1920 || year > 2024) {
            errorfile << "Invalid integer value: " << line << endl;
            continue;
        }

        try {
            if (type == 'M') {
                vector<string> stars(tokens.begin() + 7, tokens.end());
                mediaList.push_back(new Movie(title, keyName, rating, genre, length, year, stars));
            }
            else if (type == 'B') {
                if (tokens.size() < 8) throw invalid_argument("Missing weeksNYT");
                int weeksNYT = stoi(tokens[7]);
                mediaList.push_back(new Book(title, keyName, rating, genre, length, year, weeksNYT));
            }
            else if (type == 'S') {
                if (tokens.size() < 8) throw invalid_argument("Missing top40");
                bool top40 = (tokens[7] == "1");
                mediaList.push_back(new Song(title, keyName, rating, genre, length, year, top40));
            }
            else {
                errorfile << "Invalid media type: " << line << endl;
            }
        }
        catch (const exception& e) {
            errorfile << "Error processing record: " << line << " - " << e.what() << endl;
        }
    }

    processCommands("mediaCommands.txt", mediaList, outfile, errorfile);

    for (auto* m : mediaList) delete m;

    infile.close();
    outfile.close();
    errorfile.close();
    return 0;
}