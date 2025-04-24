#pragma once
#ifndef SONG_H
#define SONG_H

#include "Media.h"

class Song : public Media {
private:
    bool top40;

public:
    Song(const std::string& ti, const std::string& k, int r, const std::string& g, int l, int y, bool t)
        : Media('S', ti, k, r, g, l, y), top40(t) {
    }

    bool getTop40() const { return top40; }
    void setTop40(bool t) { top40 = t; }

    void print(std::ostream& os, const std::vector<Media*>&) const override {
        os << "Song: " << title << " (" << yearReleased << ")\n";
        os << "Top 40: " << (top40 ? "Yes" : "No") << "\n";
    }
};

#endif