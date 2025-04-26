#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"
#include <vector>

class Movie : public Media {
    std::vector<std::string> stars;

public:
    Movie(const std::string& title,
        const std::string& keyName,
        int rating,
        const std::string& genre,
        int length,
        int year,
        const std::vector<std::string>& stars);

    void print(std::ostream& out, const std::vector<Media*>& mediaList) const override;
    std::string getKeyName() const override;
    const std::vector<std::string>& getStars() const { return stars; }
};

#endif