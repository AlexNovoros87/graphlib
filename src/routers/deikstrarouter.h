#pragma once
#include "../graph/graph.h"

/** 
 * \file Описание Маршрутизатора на основе алгоритма Дейкстры и класса печати маршрута
*/

/**
 * \brief Маршрутизатор алгоритма Дейкстры
 */
class DeikstraRouter
{
private:
    // СДЕЛАТЬ ЗАГОТОВКУ ДЛЯ ТАБЛИЦЫ КРАТЧАЙШИХ РАССТОЯНИЙ
    DeikstraTable MakeCrowTableToDeikstra(const std::string &start) const;
    // ПРОВЕРИТЬ ВАЛИДНОСТЬ ТОЧЕК FROM И TO И ВЕРНУТЬ НАЧАЛЬНУЮ РАССМАТРИВАЕМУЮ ВЕРШИНУ
    const std::string *CheckValidWayPointsAndLookingNowPointer(const std::string &from, const std::string &to) const;

    // ВЫБРАТЬ НОВУЮ РАССМАТРИВАЕМУЮ ВЕРШИНУ
    const std::string *NewNowLooking(const std::unordered_set<const std::string *, Hasher> &visited,
                                     const DeikstraTable &table) const;

    const Graph &source_grph_;
    //! Сделать таблицу кратчайших расстояний расстояний при поиске
    DeikstraTable ConstructShortestRoutesTable(const std::string &from, const std::string &to) const;

    //! Ecли отключен режим экономии памяти - хранит граф в виде таблицы
    std::optional<double_matrix> border_matrix_;
    //! Режим экономии памяти
    bool economy_memory_ = false;

public:
    /**
     * \brief Конструктор
     * \param graph Граф, с которого будет строится маршрут
     * \param  economy_memory Режим экономии памяти
     */
    DeikstraRouter(const Graph &graph,bool economy_memory);
    DeikstraRouter(const Graph &graph);
    
    /**
     * \brief Конструктор
     * \param from Начальная точка маршрута
     * \param to Конечная точка маршрута
     * \returns Путь в виде std::vector<const std::string *>
     */
    std::vector<const std::string *> DeikstraWayString(const std::string &from, const std::string &to) const;
    /**
     * \brief Кратчайший путь
     * \param from Начальная точка маршрута
     * \param to Конечная точка маршрута
     * \returns Путь в виде std::vector<GraphDirection>
     */
    std::vector<GraphDirection> DeikstraWayGraphDirection(const std::string &from, const std::string &to) const;

    /**
     * \brief Граф
     */
    const auto &_Graph() { return source_grph_; }
};


