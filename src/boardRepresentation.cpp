#include "headers/boardRepresentation.hpp"

int RankIndex(int squareIndex)
{
    return squareIndex >> 3;
}

int FileIndex(int squareIndex)
{
    return squareIndex & 7;
}

int SquareIndex(int rankIndex, int fileIndex)
{
    return (rankIndex << 3) | fileIndex;
}

std::string SquareName(int squareIndex)
{
    return SquareName(RankIndex(squareIndex), FileIndex(squareIndex));
}

std::string SquareName(int rankIndex, int fileIndex)
{
    std::string squareName = "";
    squareName += fileNames[fileIndex];
    squareName += rankNames[rankIndex];
    return squareName;
}
