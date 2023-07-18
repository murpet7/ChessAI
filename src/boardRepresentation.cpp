#include "headers/boardRepresentation.hpp"

int RankIndex(int squareIndex)
{
    return squareIndex >> 3;
}

int FileIndex(int squareIndex)
{
    return squareIndex & 7;
}

int SquareIndex(int fileIndex, int rankIndex)
{
    return rankIndex * 8 + fileIndex;
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
