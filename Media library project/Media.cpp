#include "Media.h"

Media::Media(const std::string& title,
    const std::string& keyName,
    int rating,
    const std::string& genre,
    int length,
    int year)
    : title(title),
    keyName(keyName),
    rating(rating),
    genre(genre),
    length(length),
    year(year) {
}