#include "svg_printers.h"

std::unordered_map<const std::string *, Point, Hasher>
CreateWaypoinsCoordinates(const std::set<std::string> &waypoints, Point center, double radius)
{
    std::unordered_map<const std::string *, Point, Hasher> point_coords;
    std::vector<Point> coords_pack = DistributePointsOnCircle(center, radius, static_cast<int>(waypoints.size()));
    int coord_num = 0;
    for (auto &&waypoint : waypoints)
    {
        point_coords[&waypoint] = std::move(coords_pack[coord_num++]);
    }
    return point_coords;
}



GraphPrinterSVG::GraphPrinterSVG(Graph &source_graph)
    : source_graph_(source_graph)
{
    Init();
}

void GraphPrinterSVG::Draw(std::ofstream &os)
{
    os << GetMainOpenTagLine(square_width_, square_width_);
    DrawNamedCircles(os);
    DrawEdgesAndArcs(os);
    os << SVGstrings::maintagclose;
}

std::unordered_map<const std::string *, Point, Hasher> point_positions_;

auto &GraphPrinterSVG::_Graph() const
{
    return source_graph_._Graph();
}

bool GraphPrinterSVG::IsEdge(const std::string *from, const std::string *to) const
{
    if (_Graph().at(to).count(from) == 0)
        return false;
    double forward_dist = _Graph().at(from).at(to);
    double backward_dist = _Graph().at(to).at(from);
    return IsEqualDouble(forward_dist, backward_dist);
}

void GraphPrinterSVG::DrawNamedCircles(std::ostream &os) const
{
    for (auto &&[point_name, point] : point_positions_)
    {
        NamedCircle cr(point, 10, *point_name);
        ModifyNamedCircle(cr, GCP::graph_tops_pr_);
        cr.Draw(os);
    }
}

void GraphPrinterSVG::DrawEA(std::ostream &os, BoolGraph &visited) const
{
    for (auto &&graph_segment : source_graph_._Graph())
    {
        const std::string *point_from = graph_segment.first;
        for (auto &&graph_subsegment : graph_segment.second)
        {
            const std::string *point_to = graph_subsegment.first;
            if (visited.count(point_from))
            {
                if (visited.at(point_from).count(point_to))
                {
                    continue;
                };
            }

            if (IsEdge(point_from, point_to))
            {
                visited[point_from][point_to] = true;
                visited[point_to][point_from] = true;
                NamedLine ln(point_positions_.at(point_from), point_positions_.at(point_to),
                             source_graph_.GetDistance(*point_from, *point_to));
                ModifyNamedLine(ln, GCP::graph_line_pr_);
                ln.Draw(os);
            }
            else
            {
                visited[point_from][point_to] = true;
                NamedArrow arw(point_positions_.at(point_from), point_positions_.at(point_to),
                               source_graph_.GetDistance(*point_from, *point_to));

                ModifyNamedArrow(arw, GCP::graph_arrow_pr_);
                arw.Draw(os);
            }
        }
    };
};

void GraphPrinterSVG::DrawEdgesAndArcs(std::ostream &os) const
{
    BoolGraph visited;
    DrawEA(os, visited);
};

void GraphPrinterSVG::Init()
{
    int n_v = static_cast<int>(source_graph_._Ways().size());
    double number_vertices = static_cast<double>(n_v);
    double rad = number_vertices <= 10 ? 120. : number_vertices * 11;
    square_width_ = rad * 2 + diff;
    Point pnt = {square_width_ / 2., square_width_ / 2.};
    point_positions_ = CreateWaypoinsCoordinates(source_graph_._Ways(), pnt, rad);
}