#pragma once
#include "../graph/graph.h"

class FloydWarshallRouter
{
public:
    /**
     * \brief Конструктор
     * \param graph Граф, с которого будет строится маршрут
     */
    FloydWarshallRouter(const Graph &gr);
    /**
     * \brief Матрица истории ходов (Лекция Володи Мозженкова)
     */
    const const_str_ptr_matrix &GetHistoryMathrix() const;
    /**
     * \brief Возвращает матицу самых коротких путей.
     */
    const double_matrix &GetShortestWayTable() const;

    /**
     * \brief Возвращает длину самого короткого пути от from до to.
     * \param from Начальная точка маршрута
     * \param to Конечная точка маршрута
     */
    double GetShortestWayLength(const std::string &from, const std::string &to) const;

    /**
     * \brief Возвращает путь от from до to в виде std::vector<std::string *>
     * \param from Начальная точка маршрута
     * \param to Конечная точка маршрута
     */
    std::vector<const std::string *> ShortestWay(const std::string &from, const std::string &to) const;

private:
    //! Запускает работу алгоритма по нахождению всех возможных кратчайших путей.
    void SetupShortestDistanses(const Graph &gr);
    //! Возвращет заготовку матрицы истории.
    const_str_ptr_matrix GetHistoryMatrixByWeightMatrix(const double_matrix &wm) const;
    //! Граф.
    const Graph &graph_; 
    //! Матрица истории.
    const_str_ptr_matrix history_mtrx_;
    //! Матрица самых коротких путей.
    double_matrix shortest_matrix_;
    //! Было ли предупреждение о том что есть знаачения меньше 0
    bool warned_ = false;
};