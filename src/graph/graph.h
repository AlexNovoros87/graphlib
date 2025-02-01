#pragma once
#include "../free/freefoo.h"
//////////////////////////////////////////////////////////////
/**
 * \file Хранит Граф
 */

/**
 * \brief Хранит граф как в виде unordered_map<string*, unordered_map<string, int>> так и в виде таблицы
 */
class Graph
{
private:
    friend class GraphPrinterAndStrPerfomance;
    //! Представленин графа в виде std::unordered_map<const std::string *, UnorderedTable, Hasher>
    WaysCollection graph_;
    //! Названия вершин графа
    std::set<std::string> waypoints_;
    //! ЗАГРУЖАЕТ В ГРАФ НАПРАВЛЕНИЯ ИЗ ФАЙЛА
    void LoadDirections(const std::filesystem::path &path);

public:
    //! Конструктор
    Graph(const std::string &way_to_file);
    /**
     * \brief Дистанция между точками
     * \param from
     * \param to
     * \returns Если расстояние есть - вернет расстояние, нет - бесконечность.
     */

    double GetDistance(const std::string &from, const std::string &to) const;
    /**
     * \brief Вернуть представление графа
     */
    const auto &_Graph() const { return graph_; }

    /**
     * \brief Вернуть коллекцию путей графа
     */
    const std::set<std::string> &_Ways() const { return waypoints_; }

    /**
     * \brief Проверить существование вершины
     * \param way проверяемая вершина
     */
    bool CheckInput(const std::string &way) const { return (waypoints_.count(way) > 0); };
    /**
     * \brief ПРОВЕРЯЕТ ЕСТЬ ЛИ ДАННОЕ НАПРАВЛЕНИЕ
     * \param gr СТРУКТУРА ОПИСЫВАЮЩЕЕ ОДНО НАПРАВЛЕНИЕ И ЕГО "СТОИМОСТЬ"
     */
    bool AlreadyHasDirection(const GraphDirection &gr) const;
    /**
     * \brief ПРОВЕРЯЕТ ЕСТЬ ЛИ ДАННОЕ НАПРАВЛЕНИЕ
     * \param from ОТКУДА
     * \param to КУДА
     */
    bool AlreadyHasDirection(const std::string &from, const std::string &to) const;
};

/**
 * \brief Строит представление граафа в таблице
 * \param graph Граф
 * \returns Матрицу расстояний графа
 */
double_matrix BuildBorderMatrix(const Graph &graph);

 /**
     * \brief Строит таблицу расстояний от вершины from до всех других вершин.
     * \param from От какой точки строить путь
     * \param graph Граф
     * \returns Матрицу расстояний графа
     */
std::vector<double> BuildMatrixLine(const std::string &from, const Graph &graph);