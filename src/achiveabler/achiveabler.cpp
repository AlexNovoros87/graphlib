#include "achiveabler.h"

Achiveabler::Achiveabler(const Graph &graph) : graph_(graph)
{

    BuildAchievebilityOne();
}

void Achiveabler::BuildAchievebilityOne()
{
    /*КОНСТРУИРЕМ СЫРУЮ МАТРИЦУ N X N ГДЕ N КОЛИЧЕСТВО
     ВЕРШИН ГРАФА*/
    bool_matrix achievability_ = GetCrowlBoolMatrix(graph_._Ways().size());
    for (const auto &pair : graph_._Graph())
    {
        // ВЫЧИСЛЯЕМ ПОРЯДКОВЫЙ НОМЕР ПУНКТА "ОТКУДА" ВО МНОЖЕСТВЕ
        int line = GetElementOrder(*pair.first, graph_._Ways());
        for (const auto &sec : pair.second)
        { // ВЫЧИСЛЯЕМ ПОРЯДКОВЫЙ НОМЕР ПУНКТА "ОТКУДА" ВО МНОЖЕСТВЕ
            int col = GetElementOrder(*sec.first, graph_._Ways());
            // ЕСЛИ ЕСТЬ ПУТЬ В ГРАФЕ ТО ЕСТЕВСТВЕННО МОЖЕМ ДОБРАТЬСЯ ЗА 1 ШАГ.
            achievability_[line][col] = true;
        }
    }
    // КЭШИРУЕМ МАТРИЦУ.
    achievability_list_[1] = std::move(achievability_);
}

void Achiveabler::MakeAchievebility(int moves)
{
    if (moves < 2)
    {
        return;
    }

    // МАТИЦА ДОСТИЖИСОСТИ ПОСТРОЕННАЯ ДЛЯ МАКСИМАЛЬНО БОЛЬШОГО
    // КОЛИЧЕСТВА ХОДОВ.
    auto temp_matrix = achievability_list_.at(max_achivement);
    // МАТРИЦА ДОСТИЖИМОСТИ ДЛИНОЙ 1 ДЛЯ НАЛОЖЕНИЕ ДЕЗЪЮНКЦИИ
    auto target_matrix = achievability_list_.at(1);
    // РАЗМЕР МАТРИЦЫ
    size_t size = achievability_list_.at(1).size();
    // КОЛИЧЕСТВО ПОВТОРЕНИЙ ЦИКЛА НАЛОЖЕНИЯ ДЕЗЪЮНКЦИИ
    int loop_repeats = moves - max_achivement;
    for (int lp = 0; lp < loop_repeats; ++lp)
    {
        // ПО КАЖДОЙ ЛИНИИ ЦЕЛЕВОЙ МАТРИЦЫ
        for (int line = 0; line < size; ++line)
        {
            // ПО КАЖДОМУ СТОЛБЦУ ЦЕЛЕВОЙ МАТРИЦЫ
            for (int col = 0; col < size; ++col)
            {
                // ПОСЧИТАТЬ ВОЗМОЖНОСТЬ ТЕКУЩЕЙ ДОСТИЖИМОСТИ
                bool res = CalculateDisjunction(temp_matrix, line, col);
                // РЕЗУЛЬТАТ ДОСТИЖИМОСТИ ПИШЕМ В МАТРИЦУ
                target_matrix[line][col] = res;
            }
        }
        /* СПИСОК МАТРИЦ ДОСТИЖИМОСТИ ОБНОВЛЯЕМ ДЛЯ (ТЕКУЩЕЙ МАКСИМАЛЬНО ПОСТРОЕНОЙ + 1)*/
        achievability_list_[++max_achivement] = target_matrix;
        /* ВРЕМЕННАЯ МАРИЦА РАВНА ТОЛЬКО ЧТО ПОСТРОЕННОЙ ДЛЯ ПОСТОЕНИЯ
        (ТЕКУЩЕЙ МАКСИМАЛЬНО ПОСТРОЕНОЙ + 1) */
        temp_matrix = target_matrix;
    }
}

bool Achiveabler::CalculateDisjunction(const bool_matrix &temp, int row, int col)
{
    // РАЗМЕР МАТРИЫ
    size_t size = achievability_list_.at(1).size();
    // НУЖНЫЙ РЯД - СТРОКА В ТЕКУЩЕЙ МАТРИЦЕ
    const auto &needed_row = temp[row];

    for (size_t i = 0; i < size; ++i)
    {
        /*ЕСЛИ ЭЛЕМЕНТ ТЕКУЩЕГО РЯДА ПО ИНДЕКСУ I == TRUE И ЭЛЕМЕТ ПО РЯДУ I И
        СТОЛБЦЕ СOL == TRUE ТО ОЗНАЧЕТ ЕСТЬ ВОЗМОЖНОСТЬ ДОСТИГНУТЬ*/
        if (needed_row[i] == true && achievability_list_.at(1)[i][col] == true)
        {
            return true;
        }
    }
    // НЕТ ВОЗМОЖНОСТИ ДОСТИГНУТЬ.
    return false;
}

/**
 * \brief Cделать матрицу достижимости за нужное количество шагов
 * \param moves количество шагов
 */
const bool_matrix &Achiveabler::GetAchiveableMatrix(int moves)
{
    if (moves < 1)
    {
        throw std::invalid_argument("GetAchiveableMatrix error");
    }
    if (achievability_list_.count(moves) == 0)
    {
        MakeAchievebility(moves);
    }
    return achievability_list_.at(moves);
}

bool Achiveabler::PossibleToReachForNMoves(const std::string &from, const std::string &to, int moves)
{
    if (!graph_.CheckInput(from) ||
        !graph_.CheckInput(to) ||
        (moves < 1))
    {
        return false;
    }

    MakeAchievebility(moves);
    int order_from = GetElementOrder(from, graph_._Ways());
    int order_to = GetElementOrder(to, graph_._Ways());
    return achievability_list_.at(moves)[order_from][order_to];
}
