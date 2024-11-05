#pragma once
#include "../free/freefoo.h"
//////////////////////////////////////////////////////////////
class Graph
{
private:
    friend class GraphPrinterAndStrPerfomance;
    WaysCollection graph_;
    std::set<std::string> waypoints_;
    std::unordered_map<int, std::vector<std::vector<bool>>> achievability_list_;
    std::vector<std::vector<double>> border_matrix_;
    int max_achivement = 1;
    // construction
    // ЗАГРУЖАЕТ В ГРАФ НАПРАВЛЕНИЯ ИЗ ФАЙЛА
    void LoadDirections(const std::filesystem::path &path);
    void LoadDirections();
    // СТРОИТ МАТРИЦУ ДОСТИЖИМОСТИ ДЛИНОЙ 1
    void BuildAchievebilityOne();
    // СТРОИТ МАТРИЦУ СМЕЖНОСТИ
    void BuildBorderMatrix();
    // privatecalculators
    // СЧИТАЕТ ДЕЗЪЮНКЦИЮ ПРИ УМНОЖЕНИИ МАТРИЦ
    bool CalculateDisjunction(const std::vector<std::vector<bool>> &temp, int row, int col);
    // СТРОИТ МАТРИЦУ ДОСТИЖИМОСТИ ДЛИНОЙ LENGHT И ВСЕ ДО ДЛИНЫ LENGTH
    void MakeAchievebility(int length);
    

public:
    Graph(const std::string& way_to_file);
    // ВЕРНУТЬ АССОЦИАЦИЮ НОМЕР - ИМЯ ВЕРШИНЫ ГРАФА
    const std::string *Number_matrix_assotiation(int num) const;
    // МАТРИЦА ДОСТИЖИМОСТИ
    // представление в булевой таблице
    const std::vector<std::vector<bool>> &GetAchiveableMatrix(int lenght);
    double GetDistance(const std::string &from, const std::string &to) const;
    const auto& _Graph() const {return graph_;}
    const std::set<std::string>& _Ways() const {return waypoints_;}
    const auto& _BorderMatrix() const {return border_matrix_;}
    bool CheckInputs(const std::string &from, const std::string &to) const;

    // ПОКАЗЫВАЕТ ЕСТЬ ЛИ РЕБРО ГРАФА
    bool AlreadyHasDirection(const GraphDirection &gr) const;
    bool AlreadyHasDirection(const std::string &from, const std::string &to) const;
    // ВОЗВРАЩАЕТ ПОРЯДКОВЫЙ НОМЕР СТРОКИ В УПОРЯДОЧЕННОМ СПИСКЕ ВЕРРШИН ГРАФА
    int GetOrderNumWaypoint(const std::string *wp) const;

private:
    int max_len_word = 5;
    int max_len_double = 8;
};

class GraphPrinterAndStrPerfomance
{
    Graph &graph_lnk_;
    std::vector<std::string> string_border_matrix_;
public:
    GraphPrinterAndStrPerfomance(Graph &gr) : graph_lnk_(gr) {}
    void PrintDirections(std::ostream &ost) const;
    void PrintDirectionsToFile(std::filesystem::path pth, bool trunc) const;
    void PrintAchiveableMatrix(int lenght, std::ostream &ofs);
    void PrintBorderMatrix(std::ostream &ofs = std::cout);
    void PrintAchiveableMatrixToFile(int lenght, std::filesystem::path pth, bool trunc = true);
    void PrintBorderMatrixToFile(std::filesystem::path pth, bool trunc = true);

    // представление в string таблице удобной для чтения
    std::vector<std::string> StringPerfomanceAchiveableMatrix(int lenght);
    // представление в string таблице удобной для чтения
    const std::vector<std::string> &StringPerfomanceBorderMatrix();
private:
    // ПОМОЩНИКИ ДЛЯ СОЗДАНИЯ СТРОКОВОГО ПРЕДСТАЛЕНИЯ ГРАФА
    std::string HeaderStrPerfomance(int max) const;
    std::vector<std::string> ContentStrPerfomanceAchiveable(int lenght);
    std::vector<std::string> ContentStrPerfomanceBorder();
};
