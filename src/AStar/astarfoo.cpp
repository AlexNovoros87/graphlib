#include "structs.h"

std::ostream &operator<<(std::ostream &ofs, const MatrixPosition &mtrx)
{
    ofs << "ROW: " << mtrx.row << " COL: " << mtrx.col;
    return ofs;
};

std::ostream &operator<<(std::ostream &ofs, const Coordinates_Direction &val)
{
    ofs << val.current_coordinates << " " << val.dir;
    return ofs;
};

std::ostream &operator<<(std::ostream &ofs, Direction dir)
{

    ofs << "Direction: ";
    switch (dir)
    {
    case Direction::UP:
        ofs << "UP ^";
        break;
    case Direction::DOWN:
        ofs << "DOWN v";
        break;
    case Direction::LEFT:
        ofs << "LEFT <";
        break;
    case Direction::RIGHT:
        ofs << "RIGHT >";
        break;
    case Direction::UP_LEFT:
        ofs << "UP_LEFT ^<";
        break;
    case Direction::UP_RIGHT:
        ofs << "UP_RIGHT ^>";
        break;
    case Direction::DOWN_LEFT:
        ofs << "DOWN_LEFT v<";
        break;
    case Direction::DOWN_RIGHT:
        ofs << "DOWN_RIGHT v>";
        break;
    }
    return ofs;
};

std::ostream &operator<<(std::ostream &ofs, const PathElement &pth)
{
    ofs << "Current: " << pth.current_pos << std::endl;
    ofs << "Parent: " << pth.comed_from << std::endl;
    ofs << "O_D Status: " << pth.o_d << std::endl;
    ofs << "Manhattan to target: " << pth.evristica << std::endl;
    return ofs;
};

constexpr int AStarConsts::MINUSONE = -1;
constexpr int AStarConsts::ONE = 1;
constexpr int AStarConsts::ZERO = 0;
constexpr int AStarConsts::ORTOGONAL_MOD = 10;
constexpr int AStarConsts::DIAGONAL_MOD = 14;
constexpr int AStarConsts::MANCHETTEN_MLTP = 10;

constexpr char AStarConsts::UP_CH = '^';
constexpr char AStarConsts::DN_CH = 'v';
constexpr char AStarConsts::LT_CH = '<';
constexpr char AStarConsts::RT_CH = '>';

constexpr char AStarConsts::DIAG_UL = 'q';
constexpr char AStarConsts::DIAG_DL = 'e';
constexpr char AStarConsts::DIAG_UR = 'z';
constexpr char AStarConsts::DIAG_DR = 'c';

const std::map<Direction, AStarTurnModificators> AStarConsts::different_chars{
    {/*UP-LEFT*/
     Direction::UP_LEFT,
     {{AStarConsts::MINUSONE, AStarConsts::MINUSONE},
      AStarConsts::DIAGONAL_MOD,
      AStarConsts::DIAG_UL}},
    {/*UP*/
     Direction::UP,
     {{AStarConsts::MINUSONE, AStarConsts::ZERO},
      AStarConsts::ORTOGONAL_MOD,
      AStarConsts::UP_CH}},
    {/*UP-RIGHT*/
     Direction::UP_RIGHT,
     {{AStarConsts::MINUSONE, AStarConsts::ONE},
      AStarConsts::DIAGONAL_MOD,
      AStarConsts::DIAG_UR}},
    {/*LEFT*/
     Direction::LEFT,
     {{AStarConsts::ZERO, AStarConsts::MINUSONE},
      AStarConsts::ORTOGONAL_MOD,
      AStarConsts::LT_CH}},
    {/*RIGHT*/
     Direction::RIGHT,
     {{AStarConsts::ZERO, AStarConsts::ONE},
      AStarConsts::ORTOGONAL_MOD,
      AStarConsts::RT_CH}},
    {/*DOWN-LEFT*/ Direction::DOWN_LEFT,
     {{AStarConsts::ONE, AStarConsts::MINUSONE},
      AStarConsts::DIAGONAL_MOD,
      AStarConsts::DIAG_DL}},
    {/*DOWN*/
     Direction::DOWN,
     {{AStarConsts::ONE, AStarConsts::ZERO},
      AStarConsts::ORTOGONAL_MOD,
      AStarConsts::DN_CH}},
    {/*DOWN-RIGHT*/
     Direction::DOWN_RIGHT,
     {{AStarConsts::ONE, AStarConsts::ONE},
      AStarConsts::DIAGONAL_MOD,
      AStarConsts::DIAG_DR}}};

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

int Evristica(MatrixPosition coords1, MatrixPosition coords2)
{
    return (std::abs(coords1.row - coords2.row) + std::abs(coords1.col - coords2.col)) * 10;
};

Direction InverseDirection(Direction dir)
{
    switch (dir)
    {
    case Direction::UP:
        return Direction::DOWN;
        break;
    case Direction::DOWN:
        return Direction::UP;
        break;
    case Direction::LEFT:
        return Direction::RIGHT;
        break;
    case Direction::RIGHT:
        return Direction::LEFT;
        break;
    case Direction::UP_LEFT:
        return Direction::DOWN_RIGHT;
        break;
    case Direction::UP_RIGHT:
        return Direction::DOWN_LEFT;
        break;
    case Direction::DOWN_LEFT:
        return Direction::UP_RIGHT;
        break;
    case Direction::DOWN_RIGHT:
        return Direction::UP_LEFT;
        break;
    }
    return Direction::STAY;
};

int PosititionCoefficient(const MatrixPosition &child, const MatrixPosition par)
{
    if(child == par){return 0;}
    // Проверяем что клетки дейсвительно соседние
    assert(std::abs(par.col - child.col) >= 0 && std::abs(par.col - child.col) <= 1);
    assert(std::abs(par.row - child.row) >= 0 && std::abs(par.row - child.row) <= 1);
    // Еслм столбец или ряд равны - расположение ортогональное
    if (child.row == par.row || child.col == par.col)
    {
        return AStarConsts::ORTOGONAL_MOD;
    }
    // иначе диагональное
    return AStarConsts::DIAGONAL_MOD;
};
