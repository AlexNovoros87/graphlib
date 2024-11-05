#pragma once
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

#define endl__ std::cout << std::endl;

class GraphPrinterAndStrPerfomance;
class DeikstraRouter;

struct GraphDirection
{
    std::string from;
    std::string to;
    double how_much;
};

struct Hasher
{
    size_t operator()(const std::string *str) const
    {
        return std::hash<std::string>{}(*str);
    };
};

struct Constants
{
    static const std::string tr;
    static const std::string fls;
    static const std::string inf;
    static const char gap;
    static const char delim;
    static const char ln;
    static const std::string no_ways;
    static const std::string arrow;
};

struct DeikstraPair
{
    std::vector<const std::string *> way_points_;
    double now_distance = std::numeric_limits<double>::infinity();
};

using UnorderedTable = std::unordered_map<const std::string *, double, Hasher>;
using WaysCollection = std::unordered_map<const std::string *, UnorderedTable, Hasher>;
using DeikstraTable = std::unordered_map<const std::string *, DeikstraPair, Hasher>;

using UnorderedBoolTable = std::unordered_map<const std::string *, bool, Hasher>;
using BoolGraph = std::unordered_map<const std::string *, UnorderedBoolTable , Hasher>;
