#pragma once

/**
 * \file structs.h
 * \brief Описание классов и структур
 * \details Описывает структуры нужные для работы графов,
 * содержит псевдонимы типов ,
 */

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <set>
#include <algorithm>
#include <optional>
#include <sstream>

#define endl__ std::cout << std::endl;

/**
 * \struct GraphDirection
 * \brief Стуктура "Направление"
 * \details Описывает путь из from в to в условных
 * еденицах измерения.
 */
struct GraphDirection
{
    //! ОТКУДА
    std::string from;
    //! КУДА
    std::string to;
    //! СКОЛЬКО
    double how_much;
};

/**
 * \brief Хешер
 * \details   Хешер, по которому будут храниться
 * объекты string* в unordered_map и unordered_set
 */
struct Hasher
{
    /**
     * \brief Непосредственно сама хеш-функция
     * \param str Указатель для которого будет вычислена
     * хеш-функция
     * \return Число, котоое будет являться хешем
     * \exception Нн выбрасывает исключений
     */
    size_t operator()(const std::string *str) const
    {
        return std::hash<std::string>{}(*str);
    };
};

/**
 *  \brief Строковые Константы
 */
struct Constants
{
    //! "true"
    static const std::string tr;
    //! "false"
    static const std::string fls;
    //! "infinity"
    static const std::string inf;
    //! ' '
    static const char gap;
    //! '|'
    static const char delim;
    //! '-'
    static const char ln;
    //! "NO WAYS"
    static const std::string no_ways;
    //! " --> "
    static const std::string arrow;
};

/**
 *  \brief Хранит все вершины маршрута(указатели) и длину маршрута
 */
struct RoutePair
{
    //! Весь маршрут A->B->C
    std::vector<const std::string *> way_points_;
    //! Длмна маршрута
    double now_distance = std::numeric_limits<double>::infinity();
};

using UnorderedTable = std::unordered_map<const std::string *, double, Hasher>;
using WaysCollection = std::unordered_map<const std::string *, UnorderedTable, Hasher>;
using DeikstraTable = std::unordered_map<const std::string *, RoutePair, Hasher>;

using UnorderedBoolTable = std::unordered_map<const std::string *, bool, Hasher>;
using BoolGraph = std::unordered_map<const std::string *, UnorderedBoolTable, Hasher>;

using bool_matrix = std::vector<std::vector<bool>>;
using double_matrix = std::vector<std::vector<double>>;
using const_str_ptr_matrix = std::vector<std::vector<const std::string *>>;
using char_matrix = std::vector<std::vector<char>>;