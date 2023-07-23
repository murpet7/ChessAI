#pragma once

#include <string>

#define fileNames "abcdefgh"
#define rankNames "12345678"

int Rank(int squareIndex);
int File(int squareIndex);
int Square(int rankIndex, int fileIndex);
std::string SquareName(int squareIndex);
std::string SquareName(int rankIndex, int fileIndex);
