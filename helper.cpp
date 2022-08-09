#include <iostream>
#include <string>
#include "helper.h"
using namespace std;

int fConv(string const& coord)
{
    return coord[FI] - 'A';
}

int rConv(string const& coord)
{
    return (coord[RA] - '1');
}