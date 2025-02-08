#pragma once
#include "../free/freefoo.h"

class AStar;
/**
 *  \brief Хранит строку и столбец в матрице
 */
struct MatrixPosition
{
    int row;
    int col;

    MatrixPosition operator+(const MatrixPosition &rhs)
    {
        return {row + rhs.row, col + rhs.col};
    }

    MatrixPosition operator-(const MatrixPosition &rhs)
    {
        return {row - rhs.row, col - rhs.col};
    }

    bool operator==(const MatrixPosition &rhs) const
    {
        return ((row == rhs.row) && (col == rhs.col));
    }
};

//! ВЫВОДИТ СТУКТУРУ MatrixPosition В НУЖНЫЙ ПОТОК
std::ostream &operator<<(std::ostream &ofs, const MatrixPosition &mtrx);

/**
 * \brief Хешер
 * \details   Хешер, по которому будут храниться
 * объекты string* в unordered_map и unordered_set
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

/**
 * @brief Служебная вспомогательная структура
 */
struct AStarConsts
{
    /**
     * @brief
     */
    const static std::unordered_map<MatrixPosition, char, MatrixPositionHasher> different_chars;
    /**
     * @brief Модификаторы ходов для поиска возможных ходов
     */
    const static std::vector<MatrixPosition> turns_modificators_;
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
};

/**
 * @brief Возвращает самые максимальные и минимальные координаты из коллекцции координат
 */
Limits<int> GetTurnLims(const std::vector<MatrixPosition> &way);

constexpr static char NON_AVAL_CH = '`';
/**
 * \brief Класс, хранящий в себе параметры , необходимые для А*
 * \details Хранит в себе:
 * 1. Символ для представления проходимого объекта.
 * 2. Символ для представления непроходимого объекта.
 */
class ConfigAStar
{
public:
    /**
     * \brief Получить символ для представления проходимого объекта.
     */
    char GetTranparentSym() const;
    /**
     * \brief Получить символ для представления непроходимого объекта.
     */
    char GetNoTranparent() const;
    /**
     * \brief Печать содержимого объекта
     */
    void PrintParametrs() const;

private:
    std::unordered_map<std::string, std::function<void(const std::string &str)>> params_setter_;
    char is_transparent_ = 'Y';
    char no_transparent_ = 'N';

    ConfigAStar operator=(const ConfigAStar &rhs) = delete;
    ConfigAStar operator=(ConfigAStar &&rhs) = delete;
    ConfigAStar(const ConfigAStar &rhs) = delete;
    ConfigAStar(ConfigAStar &&rhs) = delete;
    /**
     * \brief Конструктор
     * \details принимает на вход файл с конфигурациями и файл с
     */
    explicit ConfigAStar(std::filesystem::path configs_way);
    /**
     * \brief Загружает конфигураации из файла
     */
    void LoadConfigs(const std::filesystem::path &pth);
    /**
     * \brief Выполняет команду, если это возможно
     */
    void TryToExecuteCommand(std::vector<std::string> &&command);
    /**
     * \brief Настраивает исполнитель команд.
     */
    void LoadParamsSetter();
    friend class AStar;
};

/**
 * \brief Класс, хранящий в себе карту.
 * \details Хранит в себе карту для А* загруженную с файла и методы для
 * работы с ней.
 */
class AStarMap
{
public:
    /**
     * @brief Являются ли координаты элементом карты?
     * @param row Ряд
     * @param col Столбец
     */
    bool IsMapElement(int row, int col) const;
    /**
     * @brief Являются ли координаты элементом карты?
     * @param pos Координаты
     */
    bool IsMapElement(MatrixPosition pos) const;
    /**
     * @brief Получить матрицу-карту
     */
    const char_matrix &GetMapMatrix() const;
    /**
     * @brief Можно ли идти на эти координаты?
     * @param row Ряд
     * @param col Столбец
     */
    bool IsPossibleToStandOn(int row, int col) const;
    /**
     * @brief Можно ли идти на эти координаты?
     * @param pos Координаты
     */
    bool IsPossibleToStandOn(MatrixPosition pos) const;

    /**
     * @brief Получить все возможные ходы с жанной клетки
     * @param pos Координаты
     * @return Все возможные ходы с данных координат
     */
    std::vector<MatrixPosition> GetPossibleSteps(MatrixPosition pos) const;
    /**
     * @brief Получить все возможные ходы с жанной клетки
     * @param row Ряд
     * @param col Столбец
     * @return Все возможные ходы с данных координат
     */
    std::vector<MatrixPosition> GetPossibleSteps(int row, int col) const;

private:
    friend class AStar;
    AStarMap(const std::filesystem::path &pth, char tr, char ntr);
    AStarMap &operator=(const AStarMap &rhs) = delete;
    AStarMap operator=(AStarMap &&rhs) = delete;
    AStarMap(const AStarMap &rhs) = delete;
    AStarMap(AStarMap &&rhs) = delete;

    ///! Является ли символ корректным при создании строки матрицы
    bool IsCorrectSym(char ch) const;
    ///! Символ проходимой точки??
    bool CharIsTransparent(char ch) const;
    ///! Символ непроходимой точки??
    bool CharIsNotTransparent(char ch) const;

    ///! Коректна ли позиция матрицы??
    bool IsCorrectMapPosition(int row, int col) const;
    bool IsCorrectMapPosition(MatrixPosition pos) const;
    /*Построить карту из файла:
       ...........................
            .....ооооо........
       ооо........................
    */
    void BuildMap(const std::filesystem::path &pth);

    ///! Карта
    char_matrix map_;
    char is_tranparent_;
    char no_tranparent_;
};
