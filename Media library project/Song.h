#ifndef SONG_H
#define SONG_H

#include "Media.h"

class Song : public Media {
    bool top40;

public:
    Song(const std::string& title,
        const std::string& keyName,
        int rating,
        const std::string& genre,
        int length,
        int year,
        bool top40);

    void print(std::ostream& out, const std::vector<Media*>& mediaList) const override;
    std::string getKeyName() const override;
    char getType() const override { return 'S'; }  
};

#endif  