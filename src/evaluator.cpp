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
    int numGoodPawns = board.GetPieceSquares(PAWN | maximizingPlayer).size();
    int numGoodKnights = board.GetPieceSquares(KNIGHT | maximizingPlayer).size();
    int numGoodBishops = board.GetPieceSquares(BISHOP | maximizingPlayer).size();
    int numGoodRooks = board.GetPieceSquares(ROOK | maximizingPlayer).size();
    int numGoodQueens = board.GetPieceSquares(QUEEN | maximizingPlayer).size();
    int numBadPawns = board.GetPieceSquares(PAWN | opponent).size();
    int numBadKnights = board.GetPieceSquares(KNIGHT | opponent).size();
    int numBadBishops = board.GetPieceSquares(BISHOP | opponent).size();
    int numBadRooks = board.GetPieceSquares(ROOK | opponent).size();
    int numBadQueens = board.GetPieceSquares(QUEEN | opponent).size();

    return ((PAWN_VALUE * (numGoodPawns - numBadPawns)) +
            (KNIGHT_VALUE * (numGoodKnights - numBadKnights)) +
            (BISHOP_VALUE * (numGoodBishops - numBadBishops)) +
            (ROOK_VALUE * (numGoodRooks - numBadRooks)) +
            (QUEEN_VALUE * (numGoodQueens - numBadQueens)));
}

float Evaluator::EvaluatePositional(Board &board, int maximizingPlayer)
{
    int opponent = maximizingPlayer == WHITE ? BLACK : WHITE;
    float positionalScore = 0;
    positionalScore += EvaluatePositionalForPiece(board, PAWN, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, KNIGHT, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, BISHOP, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, ROOK, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, QUEEN, maximizingPlayer);
    positionalScore += EvaluatePositionalForPiece(board, KING, maximizingPlayer);
    return positionalScore;
}

float Evaluator::EvaluatePositionalForPiece(Board &board, int pieceType, int maximizingPlayer)
{
    int positionalScore = 0;
    int multiplier = maximizingPlayer == WHITE ? 1 : -1;

    std::array<int, 64> piecePositionTable = Evaluator::piecePositionTables.at(pieceType);
    for (int piece : board.GetPieceSquares(pieceType | WHITE))
    {
        positionalScore += piecePositionTable[piece];
    }
    for (int piece : board.GetPieceSquares(pieceType | BLACK))
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
