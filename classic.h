#ifndef CLASSIC_H
#define CLASSIC_H

#include "movie.h"
#include <string>

class Classic : public Movie
{
    public:
        // constructor
        Classic(char movieCode, int stock, std::string director, std::string title, std::string actor, int monthReleased, int releaseYear);

        // destructor
        ~Classic();

        // accessors
        int getMonth() const;
        std::string getActor() const;
        string toString() const;

        // operator overloads
        bool operator==(const Movie &compare) const;
        bool operator>(const Movie &compare) const;
        bool operator<(const Movie &compare) const;

    private:
        int monthReleased;
        std::string actor;
};

#endif //CLASSIC_H
