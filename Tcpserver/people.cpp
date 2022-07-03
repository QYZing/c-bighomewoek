#include "people.h"

people::people()
{
    name="";
    ID="";
    pin="";
}

people::people(const people &p)
{
    name=p.name;
    ID=p.ID;
    pin=p.pin;
}

people people::operator=(people &p)
{
    name=p.name;
    ID=p.ID;
    pin=p.pin;
    return *this;
}
