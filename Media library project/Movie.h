#pragma once
#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"

class Movie : public Media {
private:
    std::vector<std::string> stars;

public:
    Movie(const std::string& ti, const std::string& k, int r, const std::string& g, int l, int y, const std::vector<std::string>& s)
        : Media('M', ti, k, r, g, l, y), stars(s) {
    }

    std::vector<std::string> getStars() const { return stars; }
    void setStars(const std::vector<std::string>& s) { stars = s; }

    void print(std::ostream& os, const std::vector<Media*>&) const override {
        os << "Movie: " << title << " (" << yearReleased << ")\n";
        os << "Stars: ";
        for (const auto& star : stars) {
            os << star << ", ";
        }
        os << "\n";
    }
};

#endif