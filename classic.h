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

        int getReleaseMonth() const;
        std::string getActor() const;

    private:
        int monthReleased;
        std::string actor;
};

#endif //CLASSIC_H