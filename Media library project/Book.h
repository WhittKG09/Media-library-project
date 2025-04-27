#ifndef BOOK_H
#define BOOK_H

#include "Media.h"
#include <vector>
class Book : public Media {
    int weeksNYT;

public:
    Book(const std::string& title,
        const std::string& keyName,
        int rating,
        const std::string& genre,
        int length,
        int year,
        int weeksNYT);  

    void print(std::ostream& out, const std::vector<Media*>& mediaList) const override;
    std::string getKeyName() const override;
    char getType() const override { return 'B'; }
};

#endif  