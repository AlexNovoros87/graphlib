#pragma once
#include "../graph/graph.h"
class Achiveabler
{
public:
    Achiveabler(const Graph &graph);
    /**
     * \brief Cделать матрицу достижимости за нужное количество шагов
     * \param moves количество шагов
     */
    const bool_matrix &GetAchiveableMatrix(int moves);

    /**
     * \brief Можно ли достичь точки to из точки from за moves шагов?
     * \param from ОТКУДА
     * \param to КУДА
     * \param moves Количество шагов
     */
    bool PossibleToReachForNMoves(const std::string &from, const std::string &to, int moves);

private:
    void BuildAchievebilityOne();
    /**
     * \brief Создает матрицу достижимости от 1 и до moves ходов
     * \param moves сколько ходов
     */
    void MakeAchievebility(int moves);

    /**
     * \brief Посчитать true или false добавлять в матрицу достижимости.
     * \param temp Текущая матрица достижимости которая строится
     * \param row Линия
     * \param col Столбец
     */
    bool CalculateDisjunction(const bool_matrix &temp, int row, int col);

    
    //! Кэш матриц достижимости на определенное кол-во шагов
    std::unordered_map<int, bool_matrix> achievability_list_;
    //! максмально большая построенная матрица достижимости
    int max_achivement = 1;

    const Graph& graph_;
   
};