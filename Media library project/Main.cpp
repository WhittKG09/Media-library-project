/*Kedryn G Whittington, Media part 2, 4/24/2025  Class 201
Program takes input of movies, books, and songs, and sorts them out. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include "Media.h"
#include "Movie.h"
#include "Book.h"
#include "Song.h"

void processCommands(const std::string& commandFile, const std::vector<std::unique_ptr<Media>>& mediaList) {
    std::ifstream file(commandFile);
    std::string line;

    while (std::getline(file, line)) {
        if (line == "A") {
            for (const auto& media : mediaList) {
                media->print(std::cout, {});
            }
        }
    }
}

int main() {
    std::vector<std::unique_ptr<Media>> mediaList;
    std::ifstream file("mediaList.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string typeStr;
        std::getline(iss, typeStr, '\t');
        char type = typeStr[0];

        std::string title, key, genre, extra;
        int rating, length, year;

        if (type == 'M') {
            std::getline(iss, title, '\t');
            std::getline(iss, key, '\t');
            iss >> rating;
            iss.ignore(1);
            std::getline(iss, genre, '\t');
            iss >> length;
            iss.ignore(1);
            iss >> year;
            iss.ignore(1);
            std::getline(iss, extra); // Get actor names
            std::istringstream ss(extra);
            std::vector<std::string> stars;
            std::string star;
            while (std::getline(ss, star, ',')) {
                stars.push_back(star);
            }
            mediaList.push_back(std::make_unique<Movie>(title, key, rating, genre, length, year, stars));
        }
        else if (type == 'B') {
            int weeks;
            std::getline(iss, title, '\t');
            std::getline(iss, key, '\t');
            iss >> rating;
            iss.ignore(1);
            std::getline(iss, genre, '\t');
            iss >> length;
            iss.ignore(1);
            iss >> year;
            iss.ignore(1);
            iss >> weeks;
            mediaList.push_back(std::make_unique<Book>(title, key, rating, genre, length, year, weeks));
        }
        else if (type == 'S') {
            std::getline(iss, title, '\t');
            std::getline(iss, key, '\t');
            iss >> rating;
            iss.ignore(1);
            std::getline(iss, genre, '\t');
            iss >> length;
            iss.ignore(1);
            iss >> year;
            iss.ignore(1);
            std::getline(iss, extra);
            bool top40 = (extra == "1" || extra == "true" || extra == "True");
            mediaList.push_back(std::make_unique<Song>(title, key, rating, genre, length, year, top40));
        }
    }

    processCommands("mediaCommands.txt", mediaList);
    return 0;
}
