#include "astarsupport.h"

AStarMap::AStarMap(const ConfigAStar &cfg, const std::filesystem::path &pth) : config_(cfg)
{
    BuildMap(pth);
}

void AStarMap::BuildMap(const std::filesystem::path &pth)
{

    std::ifstream ifs(pth);
    if (!ifs)
    {
        std::cout << "No stream Load Map" << std::endl;
        return;
    }
    std::string tmp;

    while (!ifs.eof())
    {
        // Читаем из файла
        std::getline(ifs, tmp);
        
        if(tmp == "Comments:"){
            break;
        }
        
        
        // Создаем вектор символов
        std::vector<char> mapline(tmp.size(), ' ');
        for (int i = 0; i < static_cast<int>(tmp.size()); ++i)
        {
            char sym = tmp[i];
            // Если корректный символ
            if (IsCorrectSym(sym))
            {
                // Помещаем в вектор
                mapline[i] = sym;
            }
            else
            {
                // Бросаем исключение
                std::ostringstream oss;
                oss << "The char: " << sym << " is incorrect";
                throw std::logic_error(oss.str());
            }
        };
        // Присоединяем строку к матрице
        map_.push_back(std::move(mapline));
    }
}

const char_matrix &AStarMap::GetMapMatrix() const
{
    return map_;
};

bool AStarMap::AcceptAllowNearBlock(MatrixPosition from, Direction dir) const
{

    if (dir == Direction::UP_LEFT)
    {
        auto cond1 = AStarConsts::GetCoordinatesDifference(Direction::UP);
        auto cond2 = AStarConsts::GetCoordinatesDifference(Direction::LEFT);
        return (IsPossibleToStandOn(from + cond1) && IsPossibleToStandOn(from + cond2));
    }

    if (dir == Direction::DOWN_LEFT)
    {
        auto cond1 = AStarConsts::GetCoordinatesDifference(Direction::DOWN);
        auto cond2 = AStarConsts::GetCoordinatesDifference(Direction::LEFT);
        return (IsPossibleToStandOn(from + cond1) && IsPossibleToStandOn(from + cond2));
    }

    if (dir == Direction::UP_RIGHT)
    {
        auto cond1 = AStarConsts::GetCoordinatesDifference(Direction::UP);
        auto cond2 = AStarConsts::GetCoordinatesDifference(Direction::RIGHT);
        return (IsPossibleToStandOn(from + cond1) && IsPossibleToStandOn(from + cond2));
    }
    
    if (dir == Direction::DOWN_RIGHT)
    {
        auto cond1 = AStarConsts::GetCoordinatesDifference(Direction::DOWN);
        auto cond2 = AStarConsts::GetCoordinatesDifference(Direction::RIGHT);
        return (IsPossibleToStandOn(from + cond1) && IsPossibleToStandOn(from + cond2));
    }
    return true;
};

std::vector<Coordinates_Direction> AStarMap::GetPossibleSteps(MatrixPosition pos) const
{
    std::vector<Coordinates_Direction> positions;
    if (!IsPossibleToStandOn(pos))
    {
        return positions;
    }

    for (auto &&direction_pair : AStarConsts::different_chars)
    {
        const MatrixPosition &mod = direction_pair.second.difference;
        MatrixPosition turn = pos + mod;
        if (IsPossibleToStandOn(turn))
        {
            if(!config_.AllowNearBlock()){
                if(!AcceptAllowNearBlock(pos, direction_pair.first)) {
                    continue;
                }
            }
            positions.push_back({turn, direction_pair.first});
        }
    }
    return positions;
}

std::vector<Coordinates_Direction> AStarMap::GetPossibleSteps(int row, int col) const
{
    return GetPossibleSteps({row, col});
};

/////////////////////////////////////////////////////////////////////////
//// CHECHKERS
/////////////////////////////////////////////////////////////////////////

bool AStarMap::IsCorrectSym(char ch) const
{
    // Символ проходимой клетки?
    bool condition1(CharIsTransparent(ch));
    bool condition2(ch == ' ');
    // Символ не проходимой клетки?
    bool condition3(CharIsNotTransparent(ch));
    return (condition1 | condition2 | condition3);
}

bool AStarMap::CharIsTransparent(char ch) const
{
    return (ch == config_.GetTranparentSym());
}

bool AStarMap::CharIsNotTransparent(char ch) const
{
    return (ch == config_.GetNoTranparent());
}

bool AStarMap::IsCorrectMapPosition(int row, int col) const
{
    if (row < 0 || row >= static_cast<int>(map_.size()))
    {
        return false;
    }
    if (col < 0)
    {
        return false;
    }
    if (map_[row].empty() || col >= static_cast<int>(map_[row].size()))
    {
        return false;
    }
    return true;
}

bool AStarMap::IsCorrectMapPosition(MatrixPosition pos) const
{
    return IsCorrectMapPosition(pos.row, pos.col);
}

bool AStarMap::IsMapElement(int row, int col) const
{
    if (!IsCorrectMapPosition(row, col))
    {
        return false;
    }
    char candidate = map_[row][col];
    bool condition1(CharIsTransparent(candidate));
    bool condition2(CharIsNotTransparent(candidate));
    return (condition1 || condition2);
}

bool AStarMap::IsMapElement(MatrixPosition pos) const
{
    return IsMapElement(pos.row, pos.col);
};

bool AStarMap::IsPossibleToStandOn(int row, int col) const
{
    if (!IsMapElement(row, col))
    {
        return false;
    }
    char symb = map_[row][col];
    return CharIsTransparent(symb);
};

bool AStarMap::IsPossibleToStandOn(MatrixPosition pos) const
{
    return IsPossibleToStandOn(pos.row, pos.col);
};
