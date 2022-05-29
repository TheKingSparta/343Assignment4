#include "classic.h"

Classic::Classic(char movieCode, int stock, string director, string title, string actor, int monthReleased, int releaseYear)
{
    this->actor = actor;
    this->monthReleased = monthReleased;
}

Classic::~Classic()
{

}

int Classic::getReleaseMonth() const
{
    return monthReleased;
}

string Classic::getActor() const
{
    return actor;
}

bool Classic::operator==(const Movie &compare) const
{
    if (monthReleased == compare.getMonth() &&
        releaseYear == compare.getReleaseYear() && getActor() == compare.getActor())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Classic::operator>(const Movie &compare) const
{
    if (releaseYear > compare.getReleaseYear())
    {
        return true;
    }
    else if (releaseYear == compare.getReleaseYear())
    {
        if (monthReleased > compare.getMonth())
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool Classic::operator<(const Movie &compare) const
{
    if (releaseYear < compare.getReleaseYear())
    {
        return true;
    }
    else if (releaseYear == compare.getReleaseYear())
    {
        if (monthReleased < compare.getMonth())
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}