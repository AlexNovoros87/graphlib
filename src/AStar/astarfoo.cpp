#include "astarsupport.h"

std::ostream &operator<<(std::ostream &ofs, const MatrixPosition &mtrx)
{
    ofs << "ROW: " << mtrx.row << " COL: " << mtrx.col;
    return ofs;
};

const std::unordered_map<MatrixPosition, char, MatrixPositionHasher> AStarConsts::different_chars{
    {{-1, -1}, '*'}, {{-1, 0}, '^'}, {{-1, 1}, '*'}, {{0, -1}, '<'}, {{0, 1}, '>'}, {{1, -1}, '*'}, {{1, 0}, 'v'}, {{1, 1}, '*'}};
const std::vector<MatrixPosition> AStarConsts::turns_modificators_{
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};



Limits<int> GetTurnLims(const std::vector<MatrixPosition> &way)
{
    Limits<int> limits = AStarConsts::GetTotalLimits<int>();
    for (auto &&coord : way)
    {
        limits.minRW = std::min(limits.minRW, coord.row);
        limits.maxRW = std::min(limits.maxRW, coord.row);
        limits.minCL = std::min(limits.minCL, coord.col);
        limits.maxRW = std::min(limits.maxCL, coord.col);
    }
    return limits;
}
