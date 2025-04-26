#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <vector>

class Media {
protected:
    std::string title;
    std::string keyName;
    int rating;
    std::string genre;
    int length;
    int year;

public:
    Media(const std::string& title,
        const std::string& keyName,
        int rating,
        const std::string& genre,
        int length,
        int year);
    virtual ~Media() = default;

    virtual void print(std::ostream& out, const std::vector<Media*>& mediaList) const = 0;
    virtual std::string getKeyName() const = 0;

    // Common getters
    std::string getTitle() const { return title; }
    int getRating() const { return rating; }
    int getYear() const { return year; }
};

#endif