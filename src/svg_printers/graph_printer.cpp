#include "svg_printers.h"
// СЧИТАЕТ РАДИУС ПО КОЛИЧЕСТВУ ВЕРШИН
double CalculateNeededRadius(size_t vertexes)
{
    int n_v = static_cast<int>(vertexes);
    double number_vertices = static_cast<double>(n_v);
    double rad = number_vertices <= 10 ? 300. : std::pow(number_vertices, 2);
    return rad;
}

// ВОЗВРАЩАЕТ СТРУКТУРУ "ИМЯ ТОЧКИ - ЕЕ КООРДИНАТЫ НА ОКРУЖНОСТИ"
std::unordered_map<const std::string *, Point, Hasher>
CreateWaypoinsCoordinates(const std::set<std::string> &waypoints, Point center, double radius)
{
    std::unordered_map<const std::string *, Point, Hasher> point_coords;
    // РАСПОЛОЖИТЬ ТОЧКИ РАВНОМЕРНО ПО ОКРУЖНОСТИ
    std::vector<Point> coords_pack = DistributePointsOnCircle(center, radius, static_cast<int>(waypoints.size()));
    int coord_num = 0;
    for (auto &&waypoint : waypoints)
    {
        // КАЖДОМУ ИМЕНИ ТОЧКИ - КООРДИНАТЫ
        point_coords[&waypoint] = std::move(coords_pack[coord_num++]);
    }
    return point_coords;
}

// ПЕЧАТАЕТ ИМЕНОВАННЫЕ КРУГИ, ЗАПОМИНАЯ ТЕКСТЫ , ТЕКСТЫ В КРАЙНЮЮ ОЧЕРЕДЬ ЧТОБ НЕ ПЕРЕКРЫВАЛСЯ ЛИНИЯМИ
void DrawNamedCirclesWithoutTexts(std::ostream &os, std::vector<std::shared_ptr<Text>> &texts,
                                  const PointPositionsMap &point_positions)
{
    for (auto &&[point_name, point] : point_positions)
    {

        NamedCircle cr(point, 10, *point_name);     // СОЗДАЕМ МЕНОВАННЫЙ КРУГ
        ModifyNamedCircle(cr, GCP::graph_tops_pr_); ////ЗАДАЕМ ЕМУ СТИЛЬ
        cr.GetCircle()->Draw(os);                   // ПЕЧАТЬ КРУГА
        texts.push_back(std::move(cr.GetText()));   // ТЕКСТЫ В ОТЛОЖЕННУЮ ОЧЕРЕДЬ НА ПЕЧАТЬ
    }
}

// ПЕЧАТАЕТ ДУГИ , ЗАПОМИНАЯ ТЕКСТЫ , ТЕКСТЫ В КРАЙНЮЮ ОЧЕРЕДЬ ЧТОБ НЕ ПЕРЕКРЫВАЛСЯ ЛИНИЯМИ
void DrawArrowRootByDeikstraWayAndCoordinates(const std::vector<GraphDirection> &shortestroot,
                                              const PointPositionsMap &positions,
                                              std::vector<std::shared_ptr<Text>> &texts,
                                              std::ostream &os,
                                              const std::set<std::string> &uniq_ways)
{
    for (auto &&one_move : shortestroot)
    {
        // ИЩЕМ АДРЕС ТЕКСТА ОТКУДА ПУТЬ
        const std::string *from = &*uniq_ways.find(one_move.from);
        // ИЩЕМ АДРЕС ТЕКСТА КУДА ПУТЬ
        const std::string *to = &*uniq_ways.find(one_move.to);

        if (positions.count(from) == 0 || positions.count(to) == 0)
        {
            // ЕСЛИ КАКОЙ-ТО ИЗ ПУТЕЙ НЕ ННАЙДЕН
            throw std::runtime_error("error in only deikstraway printing");
        }
        // СОЗДАЕМ МЕНОВАННУЮ СТРЕЛКУ
        NamedArrow arw(positions.at(from), positions.at(to), one_move.how_much);
        ModifyNamedArrow(arw, GCP::deikstra_arrow_pr_); // ЗАДАЕМ ЕЙ СТИЛЬ
        arw.GetLine()->Draw(os);                        // ПЕЧАТЬ ЛИНИИ
        arw.GetTriangle()->Draw(os);                    // ПЕЧАТЬ ТРЕУГОЛЬНИКА
        texts.push_back(arw.GetText());                 // ТЕКСТЫ В ОТЛОЖЕННУЮ ОЧЕРЕДЬ НА ПЕЧАТЬ
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
PrinterSVGbase::PrinterSVGbase(Graph &source_graph)
    : source_graph_(source_graph)
{
    Init();
}

std::unordered_map<const std::string *, Point, Hasher> point_positions_;

auto &PrinterSVGbase::_Graph() const
{
    return source_graph_._Graph();
}

// ЕСЛИ РЕБРО - 1, ЕСЛИ ДУГА - 0
bool PrinterSVGbase::IsEdge(const std::string *from, const std::string *to) const
{
    if (_Graph().at(to).count(from) == 0)
    {
        return false;
    }
    double forward_dist = _Graph().at(from).at(to);
    double backward_dist = _Graph().at(to).at(from);
    return IsEqualDouble(forward_dist, backward_dist);
}

// НАРИСОВАТЬ ДУГИ И РЕБРА , ТЕКСТЫ В КРАЙНЮЮ ОЧЕРЕДЬ ЧТОБ НЕ ПЕРЕКРЫВАЛСЯ ЛИНИЯМИ
void PrinterSVGbase::DrawEA(std::ostream &os, BoolGraph &visited, std::vector<std::shared_ptr<Text>> &texts) const
{

    // ПО ВСЕМ ЭЛЕМЕНТАМ ГРАФА
    for (auto &&graph_segment : source_graph_._Graph())
    {
        const std::string *point_from = graph_segment.first; // ТОЧКА "ОТКУДА"
        for (auto &&graph_subsegment : graph_segment.second)
        {
            const std::string *point_to = graph_subsegment.first; // ТОЧКА "КУДА"
            if (visited.count(point_from))
            {
                if (visited.at(point_from).count(point_to))
                {
                    continue; // ЕСЛИ ВЕРШИНА УЖЕ ПОСЕЩЕНА
                };
            }

            if (IsEdge(point_from, point_to)) // ЕСЛИ ДУГА
            {
                // МОДИФИЦИРУЕМ СПИСОК ПОСЕЩЕНИЙ
                visited[point_from][point_to] = true;
                visited[point_to][point_from] = true;
                // ДЕЛАЕМ ИМЕНОВАННУЮ ЛИНИЮ
                NamedLine ln(point_positions_.at(point_from), point_positions_.at(point_to),
                             source_graph_.GetDistance(*point_from, *point_to));

                ModifyNamedLine(ln, GCP::graph_line_pr_); // ЗАДАЕМ ЕЙ СТИЛЬ
                ln.GetLine()->Draw(os);                   // ПЕЧАТЬ ЛИНИИ
                texts.push_back(ln.GetText());            // ТЕКСТЫ В ОТЛОЖЕННУЮ ОЧЕРЕДЬ НА ПЕЧАТЬ
            }
            else
            {
                // МОДИФИЦИРУЕМ СПИСОК ПОСЕЩЕНИЙ
                visited[point_from][point_to] = true;
                // СОЗДАЕМ МЕНОВАННУЮ СТРЕЛКУ
                NamedArrow arw(point_positions_.at(point_from), point_positions_.at(point_to),
                               source_graph_.GetDistance(*point_from, *point_to));

                ModifyNamedArrow(arw, GCP::graph_arrow_pr_); // ЗАДАЕМ ЕЙ СТИЛЬ
                arw.GetLine()->Draw(os);                     // ПЕЧАТЬ ЛИНИИ
                arw.GetTriangle()->Draw(os);                 // ПЕЧАТЬ ТРЕУГОЛЬНИКА
                texts.push_back(arw.GetText());              // ТЕКСТЫ В ОТЛОЖЕННУЮ ОЧЕРЕДЬ НА ПЕЧАТЬ
            }
        }
    };
};

// ПЕЧАТЬ ДУГ И РЕБЕР
void PrinterSVGbase::DrawEdgesAndArcs(std::ostream &os, std::vector<std::shared_ptr<Text>> &texts) const
{
    BoolGraph visited;
    DrawEA(os, visited, texts);
};

void PrinterSVGbase::Init()
{
    // ВЫЧИСЛЯЕМ НУЖНЫЙ РАДИУС ПЕЧАТИ ОКРУЖНОСТИ
    double rad = CalculateNeededRadius(source_graph_._Ways().size());
    // ВЫЧИСЛЯЕМ СТОРОНУ КВАДРАТА ПРИ РАСПЕЧАТКЕ ВМЕСТЕ С ГРАФОМ(ОКРУЖНОСТЬ ЗАКЛЮЧАЕМ В КВАДРАТ)
    square_width_ = rad * 2 + diff;
    // ВЫЧИСЛЯЕМ ЦЕНТРАЛЬНУЮ ТОЧКУ
    Point pnt = {square_width_ / 2., square_width_ / 2.};
    // ВЫЧИСЛЯЕМ КООРДИНАТЫ ТОЧЕК НА ПЕЧАТНОМ КВАДРАТЕ
    point_positions_ = CreateWaypoinsCoordinates(source_graph_._Ways(), pnt, rad);
}

//////////////////////////////////////////////////////////////////////////////////PrinterSVGGraph

void PrinterSVGGraph::Draw(std::ofstream &os)
{
    std::vector<std::shared_ptr<Text>> texts;                  // CОЗДАЕМ ОЧЕРЕДЬ НА ПЕЧАТЬ ТЕКСТОВ
    os << GetMainOpenTagLine(square_width_, square_width_);    // ПЕЧАТАЕМ ОТКРЫВАЮЩИЙ ТЕГ
    DrawNamedCirclesWithoutTexts(os, texts, point_positions_); // ПЕЧАТЬ КРУГОВ
    DrawEdgesAndArcs(os, texts);                               // ПЕЧАТЬ ДУГ И РЕБЕР
    PrintDrawable(texts, os);                                  // ПЕЧАТЬ ТЕКСТА
    os << SVGstrings::maintagclose;                            // ПЕЧАТАЕМ ЗАКРЫВАЮЩИЙ ТЕГ
}

//////////////////////////////////////////////////////////////////////////////////DeikstraRoutePrinter
// ВОЗВРАЩАЕТ ИМЕНА ТОЧЕК
std::set<std::string> GetUniqueWayPoints(const std::vector<GraphDirection> &shortestroot)
{
    std::set<std::string> waypoints;
    bool is_first = true;
    for (auto &&rote_segment : shortestroot)
    {
        if (is_first)
        {
            is_first = false;
            waypoints.insert(rote_segment.from);
        }
        waypoints.insert(rote_segment.to);
    }
    return waypoints;
}

void DeikstraRoutePrinter::DrawOnlyWay(std::ostream &os, const std::string &from,
                                       const std::string &to) const
{
    // СЧИТАЕМ КРАТЧАЙШИЙ МАРШРУТ
    auto shortestroot = router_->DeikstraWayGraphDirection(from, to);
    // ПОЛУЧАЕМ ТОЧКИ МАРШРУТА
    std::set<std::string> waypoints = GetUniqueWayPoints(shortestroot);
    if (waypoints.empty())
    {
        return;
    }
    // СЧИТАЕМ РАДИУС РАСПОЛОЖЕНИЯ ТОЧЕК
    double needed_rad = CalculateNeededRadius(waypoints.size());
    double square_side = 2. * needed_rad + diff;

    // ВЫЧИСЛЯЕМ ЦЕНТРАЛЬНУЮ ТОЧКУ
    Point pnt = {square_side / 2., square_side / 2.};
    // ВЫЧИСЛЯЕМ КООРДИНАТЫ ТОЧЕК НА ПЕЧАТНОМ КВАДРАТЕ
    PointPositionsMap positions = CreateWaypoinsCoordinates(waypoints, pnt, needed_rad);

    std::vector<std::shared_ptr<Text>> texts;           // СОЗДАЕМ ХРАНИЛИЩЕ ТЕКСТОВ
    os << GetMainOpenTagLine(square_side, square_side); // ПЕЧАТАЕМ ОТКРЫВАЮЩИЙ ТЕГ
    DrawNamedCirclesWithoutTexts(os, texts, positions); // ПЕЧАТЬ КРУГОВ
    DrawArrowRootByDeikstraWayAndCoordinates(
        shortestroot, positions, texts, os, waypoints); // ПЕЧАТЬ МАРШРУТА(БЕЗ ИМЕН)
    PrintDrawable(texts, os);                           // ПЕЧАТЬ ТЕКСТА
    os << SVGstrings::maintagclose;                     // ПЕЧАТАЕМ ЗАКРЫВАЮЩИЙ ТЕГ
};

std::vector<NamedArrow> DeikstraRoutePrinter::GetWayAndUpdateVisited(const std::string &from,
                                                                     const std::string &to, BoolGraph &visited) const
{
    auto shortestroot = router_->DeikstraWayGraphDirection(from, to); // НАЙТИ КРАТЧАЙНИЙ ПУТЬ
    std::vector<NamedArrow> way;                                      // СОЗДАТЬ ОБЬЕКТЫ "ИМЕНОВАННЫЕ СТРЕЛКИ" МАРШРУТА
    for (auto &&one_move : shortestroot)
    {
        const std::string *from_p = &(*source_graph_._Ways().find(one_move.from)); // ИЩЕМ АДРЕС ТЕКСТА ОТКУДА ПУТЬ
        const std::string *to_p = &(*source_graph_._Ways().find(one_move.to));     // ИЩЕМ АДРЕС ТЕКСТА КУДА ПУТЬ
        // СОЗДАТЬ ОБЬЕКТ ИМЕНОВАННУЮ СТРЕЛКУ МАРШРУТА
        NamedArrow arw(point_positions_.at(from_p), point_positions_.at(to_p), one_move.how_much);
        ModifyNamedArrow(arw, GCP::deikstra_arrow_pr_); // ЗАДАЕМ ЕЙ СТИЛЬ
        way.push_back(std::move(arw));                  // ТЕКСТЫ В ОТЛОЖЕННУЮ ОЧЕРЕДЬ НА ПЕЧАТЬ
        // МОДИФИЦИРУЕМ СПИСОК ПОСЕЩЕНИЙ
        visited[from_p][to_p] = true;
        visited[to_p][from_p] = true;
    }
    return way;
};

void DeikstraRoutePrinter::DrawEdgesAndArcs(std::ostream &os, const std::string &from,
                                            const std::string &to,
                                            std::vector<std::shared_ptr<Text>> &texts) const
{
    BoolGraph visited; // ПОСЕЩЕННЫЕ НАПРАВЛЕНИЯ
    // СОЗДАТЬ ОБЬЕКТЫ "ИМЕНОВАННЫЕ СТРЕЛКИ" МАРШРУТА
    std::vector<NamedArrow> way = GetWayAndUpdateVisited(from, to, visited);
    DrawEA(os, visited, texts); // ПЕЧАТЬ ДУИ И РЕБЕР
    for (auto &&waypoint : way)
    {
        waypoint.GetLine()->Draw(os);     // ПЕЧАТЬ ЛИНИИ
        waypoint.GetTriangle()->Draw(os); // ПЕЧАТЬ ТРЕУГОЛЬНИКА
        waypoint.GetText()->Draw(os);     // ПЕЧАТЬ ТЕКСТА
    }
};

void DeikstraRoutePrinter::DrawWithGraph(std::ostream &os, const std::string &from,
                                         const std::string &to) const
{
    std::vector<std::shared_ptr<Text>> texts;                  // CОЗДАЕМ ОЧЕРЕДЬ НА ПЕЧАТЬ ТЕКСТОВ
    os << GetMainOpenTagLine(square_width_, square_width_);    // ПЕЧАТАЕМ ОТКРЫВАЮЩИЙ ТЕГ
    DrawNamedCirclesWithoutTexts(os, texts, point_positions_); // ПЕЧАТЬ КРУГОВ
    DrawEdgesAndArcs(os, from, to, texts);                     // ПЕЧАТЬ ДУГ И РЕБЕР
    PrintDrawable(texts, os);                                  // ПЕЧАТЬ ТЕКСТА
    os << SVGstrings::maintagclose;                            // ПЕЧАТАЕМ ЗАКРЫВАЮЩИЙ ТЕГ
}

DeikstraRoutePrinter::DeikstraRoutePrinter(Graph &source_graph, bool economy_memory) : PrinterSVGbase(source_graph)
{
    router_ = std::make_shared<DeikstraRouter>(source_graph_, economy_memory);
};
