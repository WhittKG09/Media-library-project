#pragma once
#ifndef BOOK_H
#define BOOK_H

#include "Media.h"

class Book : public Media {
private:
    int weeksNYT;

public:
    Book(const std::string& ti, const std::string& k, int r, const std::string& g, int l, int y, int w)
        : Media('B', ti, k, r, g, l, y), weeksNYT(w) {
    }

    int getWeeks() const { return weeksNYT; }
    void setWeeks(int w) { weeksNYT = w; }

    void print(std::ostream& os, const std::vector<Media*>&) const override {
        os << "Book: " << title << " (" << yearReleased << ")\n";
        os << "Weeks on NYT Bestseller: " << weeksNYT << "\n";
    }
};

#endif
