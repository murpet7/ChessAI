#pragma once

#include <string>

#define fileNames "abcdefgh"
#define rankNames "12345678"

int RankIndex(int squareIndex);
int FileIndex(int squareIndex);
int SquareIndex(int rankIndex, int fileIndex);
std::string SquareName(int squareIndex);
std::string SquareName(int rankIndex, int fileIndex);
