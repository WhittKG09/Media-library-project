#include "Song.h"
#include <iostream>

Song::Song(const std::string& title,
    const std::string& keyName,
    int rating,
    const std::string& genre,
    int length,
    int year,
    bool top40)
    : Media(title, keyName, rating, genre, length, year), top40(top40) {
}

void Song::print(std::ostream& out, const std::vector<Media*>& mediaList) const {
    out << "Song: " << title
        << " (" << year << "), Rating: " << rating
        << "/10, Genre: " << genre
        << ", Duration: " << length << " seconds"
        << ", Top40: " << (top40 ? "Yes" : "No") << "\n";
}

std::string Song::getKeyName() const {
    return keyName;
}