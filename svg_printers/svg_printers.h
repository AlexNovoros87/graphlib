#pragma once
#include "../graphics/drawable_shapes.h"
#include "../routers/routers.h"
#include "shape_modificators.h"

using PointPositionsMap = std::unordered_map<const std::string *, Point, Hasher>;

template <template <typename, typename> class Container, typename Drawable>
void PrintDrawable(const Container<Drawable, std::allocator<Drawable>> &container, std::ostream &os)
{
    for (const auto &item : container)
    {
        item->Draw(os);
    }
}

class PrinterSVGbase
{
public:
    PrinterSVGbase(Graph &source_graph);
    virtual ~PrinterSVGbase() {};

protected:
    Graph &source_graph_; //ГРАФ
    double square_width_; //СТОРОНА КВАДРАТА ДЛЯ ПЕЧАТИ
    const double diff = 60.;//ПОГРЕШНОСТЬ ОТСТУПА ПЕЧАТИ
    PointPositionsMap point_positions_; //ИМЯ ВЕРШИНЫ - КООРДИНАТА НА КРУГЕ
    auto &_Graph() const; //ПОКАЗАТЬ ГРАФ
    bool IsEdge(const std::string *from, const std::string *to) const; //ДУГА ИЛИ РЕБРО
    //НАРИСОВАТЬ ДУГИ И РЕБРА
    virtual void DrawEdgesAndArcs(std::ostream &os, std::vector<std::shared_ptr<Text>> &texts) const;
    //НАРИСОВАТЬ ДУГИ И РЕБРА
    void DrawEA(std::ostream &os, BoolGraph &visited, std::vector<std::shared_ptr<Text>> &texts) const;
    void Init();
};

class PrinterSVGGraph : public PrinterSVGbase
{
public:
    void Draw(std::ofstream &os);
};

class DeikstraRoutePrinter : public PrinterSVGbase
{
private:
    std::shared_ptr<DeikstraRouter> router_; //РОУТЕР
    std::vector<NamedArrow> GetWayAndUpdateVisited(const std::string &from,
                                                   const std::string &to, BoolGraph &visited) const;
    //НАРИСОВАТЬ ДУГИ И РЕБРА(С МАРШРУТАМИ)
    void DrawEdgesAndArcs(std::ostream &os, const std::string &from, const std::string &to,
                          std::vector<std::shared_ptr<Text>> &texts) const;
public:
    //НАРИСОВАТЬ МАРШРУТ НА ГРАФЕ
    void DrawWithGraph(std::ostream &os, const std::string &from, const std::string &to) const;
    //НАРИСОВАТЬ ТОЛЬКО МАРШУТ
    void DrawOnlyWay(std::ostream &os, const std::string &from, const std::string &to) const;
    DeikstraRoutePrinter(Graph &source_graph);
};
