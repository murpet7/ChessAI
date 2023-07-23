#include "headers/boardRepresentation.hpp"

int Rank(int squareIndex)
{
    return squareIndex >> 3;
}

int File(int squareIndex)
{
    return squareIndex & 7;
}

int Square(int fileIndex, int rankIndex)
{
    return rankIndex * 8 + fileIndex;
}

std::string SquareName(int squareIndex)
{
    return SquareName(Rank(squareIndex), File(squareIndex));
}

std::string SquareName(int rankIndex, int fileIndex)
{
    std::string squareName = "";
    squareName += fileNames[fileIndex];
    squareName += rankNames[rankIndex];
    return squareName;
}
