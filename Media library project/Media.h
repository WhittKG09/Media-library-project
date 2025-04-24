#pragma once
#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <vector>
#include <iostream>

class Media {
protected:
    char type;
    std::string title;
    std::string keyName;
    int rating;
    std::string genre;
    int length;
    int yearReleased;

public:
    Media(char t, const std::string& ti, const std::string& k, int r, const std::string& g, int l, int y)
        : type(t), title(ti), keyName(k), rating(r), genre(g), length(l), yearReleased(y) {
    }

    virtual void print(std::ostream& os, const std::vector<class Media*>& mediaList) const = 0;
    virtual ~Media() {}
};

#endif