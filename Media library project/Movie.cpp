#include "Movie.h"
#include <iostream>

Movie::Movie(const std::string& title,
    const std::string& keyName,
    int rating,
    const std::string& genre,
    int length,
    int year,
    const std::vector<std::string>& stars)
    : Media(title, keyName, rating, genre, length, year), stars(stars) {
}

void Movie::print(std::ostream& out, const std::vector<Media*>& mediaList) const {
    out << "Movie: " << title
        << " (" << year << "), Rating: " << rating
        << "/10, Genre: " << genre
        << ", Length: " << length << " minutes\n";
    out << "Stars: ";
    for (size_t i = 0; i < stars.size(); ++i) {
        out << stars[i];
        if (i != stars.size() - 1) out << ", ";
    }
    out << "\n";
}

std::string Movie::getKeyName() const {
    return keyName;
}