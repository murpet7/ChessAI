#include "headers/evaluator.hpp"

float Evaluator::EvaluatePosition(Board &board, int maximizingPlayer)
{
    int gameEndState = GetGameEndState(board);
    if (gameEndState == CHECKMATE)
    {
        return -1000000;
    }
    if (gameEndState == DRAW)
    {
        return 0;
    }

    float materialScore = EvaluateMaterial(board, maximizingPlayer);
    float positionalScore = EvaluatePositional(board, maximizingPlayer);
    return materialScore + positionalScore;
}

float Evaluator::EvaluateMaterial(Board &board, int maximizingPlayer)
{
    int opponent = maximizingPlayer == WHITE ? BLACK : WHITE;
    int numGoodPawns = board.pieceSquaresOfType[PAWN | maximizingPlayer].size();
    int numBadPawns = board.pieceSquaresOfType[PAWN | opponent].size();
    int numGoodKnights = board.pieceSquaresOfType[KNIGHT | maximizingPlayer].size();
    int numBadKnights = board.pieceSquaresOfType[KNIGHT | opponent].size();
    int numGoodBishops = board.pieceSquaresOfType[BISHOP | maximizingPlayer].size();
    int numBadBishops = board.pieceSquaresOfType[BISHOP | opponent].size();
    int numGoodRooks = board.pieceSquaresOfType[ROOK | maximizingPlayer].size();
    int numBadRooks = board.pieceSquaresOfType[ROOK | opponent].size();
    int numGoodQueens = board.pieceSquaresOfType[QUEEN | maximizingPlayer].size();
    int numBadQueens = board.pieceSquaresOfType[QUEEN | opponent].size();

    return -((PAWN_VALUE * (numGoodPawns - numBadPawns)) +
             (KNIGHT_VALUE * (numGoodKnights - numBadKnights)) +
             (BISHOP_VALUE * (numGoodBishops - numBadBishops)) +
             (ROOK_VALUE * (numGoodRooks - numBadRooks)) +
             (QUEEN_VALUE * (numGoodQueens - numBadQueens)));
}

float Evaluator::EvaluatePositional(Board &board, int maximizingPlayer)
{
    // test ook het meegeven van de table ipv map
    int opponent = maximizingPlayer == WHITE ? BLACK : WHITE;
    float positionalScore = 0;
    positionalScore += EvaluatePositionalForPiece(board, PAWN, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, KNIGHT, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, BISHOP, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, ROOK, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, QUEEN, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, KING, maximizingPlayer);
    return -positionalScore;
}

float Evaluator::EvaluatePositionalForPiece(Board &board, int pieceType, int maximizingPlayer)
{
    int positionalScore = 0;
    int multiplier = maximizingPlayer == WHITE ? 1 : -1;

    std::array<int, 64> piecePositionTable = Evaluator::piecePositionTables.at(pieceType);
    for (int piece : board.pieceSquaresOfType[pieceType | WHITE])
    {
        positionalScore += piecePositionTable[piece];
    }
    for (int piece : board.pieceSquaresOfType[pieceType | BLACK])
    {
        positionalScore -= piecePositionTable[63 - piece];
    }
    return positionalScore * multiplier;
}

const std::map<int, std::array<int, 64>> Evaluator::piecePositionTables = {
    {PAWN, pawnPositionTable},
    {KNIGHT, knightPositionTable},
    {BISHOP, bishopPositionTable},
    {ROOK, rookPositionTable},
    {QUEEN, queenPositionTable},
    {KING, kingPositionTable}};

const std::array<int, 64> Evaluator::pawnPositionTable = {
    0, 0, 0, 0, 0, 0, 0, 0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5, 5, 10, 25, 25, 10, 5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, -5, -10, 0, 0, -10, -5, 5,
    5, 10, 10, -20, -20, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0};

const std::array<int, 64> Evaluator::knightPositionTable = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50};

const std::array<int, 64> Evaluator::bishopPositionTable = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -20, -10, -10, -10, -10, -10, -10, -20};

const std::array<int, 64> Evaluator::rookPositionTable = {
    0, 0, 0, 5, 5, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    5, 10, 10, 10, 10, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0};

const std::array<int, 64> Evaluator::queenPositionTable = {
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -5, 0, 5, 5, 5, 5, 0, -5,
    0, 0, 5, 5, 5, 5, 0, -5,
    -10, 5, 5, 5, 5, 5, 0, -10,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20};

const std::array<int, 64> Evaluator::kingPositionTable = {
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    20, 20, 0, 0, 0, 0, 20, 20,
    20, 30, 10, 0, 0, 10, 30, 20};
