#pragma once
#include "../free/freefoo.h"
#include <cassert>

class AStar;
/**
 *  \brief Перечисление направлений
 */
enum class Direction
{
    UP_LEFT,
    UP,
    UP_RIGHT,
    LEFT,
    RIGHT,
    DOWN_LEFT,
    DOWN,
    DOWN_RIGHT,
    STAY
};

/**
 *  \brief Хранит строку и столбец в матрице
 */
struct MatrixPosition
{
    int row = 0;
    int col = 0;
    MatrixPosition operator+(const MatrixPosition &rhs) const
    {
        return {row + rhs.row, col + rhs.col};
    }

    MatrixPosition operator-(const MatrixPosition &rhs) const
    {
        return {row - rhs.row, col - rhs.col};
    }

    bool operator==(const MatrixPosition &rhs) const
    {
        return ((row == rhs.row) && (col == rhs.col));
    }
};

/// @brief Наследник MatrixPosition
struct MatrixPositionHistory : public MatrixPosition
{
    // Возможно имеет точку откуда до нее пришли
    std::optional<MatrixPosition> parent;
};

/**
 * \brief Хешер
 * \details   Хешер, по которому будут храниться
 * объекты MatrixPositionHasher
 */
struct MatrixPositionHasher
{
    /**
     * \brief Непосредственно сама хеш-функция
     * \param pos Координата, для которой сделать хеш
     * \return Число, котоое будет являться хешем
     * \exception Нн выбрасывает исключений
     */
    size_t operator()(const MatrixPosition &pos) const
    {
        size_t h1 = std::hash<int>()(pos.row);
        size_t h2 = std::hash<int>()(pos.col);
        return h1 ^ (h2 << 1);
    };
};

/**
 * \brief Хешер
 * \details   Хешер, по которому будут храниться
 * объекты MatrixPositionHasher
 */
struct MatrixPositionHistoryHasher
{
    /**
     * \brief Непосредственно сама хеш-функция
     * \param pos Координата, для которой сделать хеш
     * \return Число, котоое будет являться хешем
     * \exception Нн выбрасывает исключений
     */
    size_t operator()(const MatrixPositionHistory &pos) const
    {
        size_t h1 = std::hash<int>()(pos.row);
        size_t h2 = std::hash<int>()(pos.col);
        return h1 ^ (h2 << 1);
    };
};

/**
 * @brief Лимиты минимум и максимум для двух пар параметров
 * @details  Оюычно используется для координат
 */
template <typename T>
struct Limits
{
    T minRW;
    T maxRW;
    T minCL;
    T maxCL;
};

/// @brief Модификаторы для использования
struct AStarTurnModificators
{
    // Разница между координатами(не путать с координатами)
    MatrixPosition difference;
    // Ортогональный или диагональный индекс
    int o_d_modificator;
    // Символ направления
    char waysymbol;
};

/**
 * @brief Текущие координаты и направление
 * @details  Текущие координаты и направление по которому шли
 * от исходной точки для того, чтобы достичь этой.
 */
struct Coordinates_Direction
{
    // Текущие координыты
    MatrixPosition current_coordinates;
    // Направление по которому шли с исходной точки
    Direction dir;
};

/// @brief описывает "элемент пути"
struct PathElement
{
    // Текущие координаты
    MatrixPosition current_pos;
    // Откуда ппришли
    MatrixPosition comed_from;
    // Ортогональное или диагональное расположение(индекс)
    int o_d;
    // Расстояние, вычисленное по "Индексу Манхеттена"
    int evristica;

    bool operator==(const PathElement &rhs) const
    {
        return ((current_pos == rhs.current_pos) |
                (comed_from == rhs.comed_from) |
                (o_d == rhs.o_d) | (evristica == rhs.evristica));
    }
};

/**
 * \brief Хешер
 * \details   Хешер, по которому будут храниться PathElementHasher
 */
struct PathElementHasher
{
    /**
     * \brief Непосредственно сама хеш-функция
     * \param el
     * \return Число, котоое будет являться хешем
     * \exception Нн выбрасывает исключений
     */
    size_t operator()(const PathElement &el) const
    {
        size_t h1 = std::hash<int>()(el.current_pos.row * 11);
        size_t h2 = std::hash<int>()(el.current_pos.col * 19);
        return h1 ^ (h2 << 1);
    };
};

/**
 * @brief Служебная вспомогательная структура
 */
struct AStarConsts
{
    /// @brief Судя по направлению может вернуть разницу между координатами, символ направления
    /// и индекс ортогонального или диагонального расположения
    const static std::map<Direction, AStarTurnModificators> different_chars;
    /**
     * @brief Возвращает две пары чимел минимально и максимально
     * возможных для данного типа Т
     */
    template <typename T>
    static Limits<T> GetTotalLimits()
    {
        T minRW = std::numeric_limits<T>::max();
        T minCL = minRW;
        T maxRW = std::numeric_limits<T>::min();
        T maxCL = maxRW;
        return {minRW, maxRW, minCL, maxCL};
    }

    const static int MINUSONE;
    const static int ONE;
    const static int ZERO;
    const static int ORTOGONAL_MOD;
    const static int DIAGONAL_MOD;
    const static int MANCHETTEN_MLTP;

    const static char UP_CH;
    const static char DN_CH;
    const static char LT_CH;
    const static char RT_CH;

    const static char DIAG_UL;
    const static char DIAG_DL;
    const static char DIAG_UR;
    const static char DIAG_DR;

    static int GetODByDirection(Direction dir)
    {
        return different_chars.at(dir).o_d_modificator;
    }

    static MatrixPosition GetCoordinatesDifference(Direction dir)
    {
        return different_chars.at(dir).difference;
    }

    static char GetSymbolics(Direction dir)
    {
        return different_chars.at(dir).waysymbol;
    }
};

/**
 * @brief Возвращает самые максимальные и минимальные координаты из коллекцции координат
 */
Limits<int> GetTurnLims(const std::vector<MatrixPosition> &way);
/**
 * @brief Считает Манхэттонскую разницу, игнорируя диагонали и препятствия
 */
int Evristica(MatrixPosition coords1, MatrixPosition coords2);
/**
 * @brief Реверсирует направление (UP --> DOWN)
 */
Direction InverseDirection(Direction dir);

/**
 * @brief Возращает конффициент расположения между точками (ортогональный или диагональный)
 */

int PosititionCoefficient(const MatrixPosition &child, const MatrixPosition par);

/////----------------------------------------------->>///
/**
 * @brief Печатает MatrixPosition
 */
std::ostream &operator<<(std::ostream &ofs, const MatrixPosition &mtrx);
/**
 * @brief Печатает Coordinates_Direction
 */
std::ostream &operator<<(std::ostream &ofs, const Coordinates_Direction &mtrx);
/**
 * @brief Печатает Direction
 */
std::ostream &operator<<(std::ostream &ofs, Direction dir);
/**
 * @brief Печатает PathElement
 */
std::ostream &operator<<(std::ostream &ofs, const PathElement &pth);
constexpr static char NON_AVAL_CH = '`';