#include "Book.h"
#include <iostream>

Book::Book(const std::string& title,
    const std::string& keyName,
    int rating,
    const std::string& genre,
    int length,
    int year,
    int weeksNYT)
    : Media(title, keyName, rating, genre, length, year), weeksNYT(weeksNYT) {
}

void Book::print(std::ostream& out, const std::vector<Media*>& mediaList) const {
    out << "Book: " << title
        << " (" << year << "), Rating: " << rating
        << "/10, Genre: " << genre
        << ", Pages: " << length
        << ", Weeks on NYT Best Seller: " << weeksNYT << "\n";
}

std::string Book::getKeyName() const {
    return keyName;
}