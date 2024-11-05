#pragma once
#include "../graphics/drawable_shapes.h"
#include "../routers/routers.h"
#include "shape_modificators.h"

std::unordered_map<const std::string *, Point, Hasher>
CreateWaypoinsCoordinates(const std::set<std::string> &waypoints, Point center, double radius);



class GraphPrinterSVG
{
public:
    GraphPrinterSVG(Graph &source_graph);
    virtual void Draw(std::ofstream &os);
    virtual ~GraphPrinterSVG() {};

protected:
    Graph &source_graph_;
    double square_width_;
    const double diff = 60.;
    std::unordered_map<const std::string *, Point, Hasher> point_positions_;
    auto &_Graph() const;
    bool IsEdge(const std::string *from, const std::string *to) const;
    void DrawNamedCircles(std::ostream &os) const;
    virtual void DrawEdgesAndArcs(std::ostream &os) const;
    void DrawEA(std::ostream &os, BoolGraph &visited) const;
    void Init();
};

class DeikstraRoutePrinter : GraphPrinterSVG
{
private:
    std::shared_ptr<DeikstraRouter> router_;

    std::vector<NamedArrow> GetWayAndUpdateVisited(const std::string &from,
                                                   const std::string &to, BoolGraph &visited) const {
       auto shortestroot = router_->DeikstraWayGraphDirection(from, to);
        std::vector<NamedArrow> way;
        for (auto &&one_move : shortestroot)
        {
            const std::string *from_p = &(*source_graph_._Ways().find(one_move.from));
            const std::string *to_p = &(*source_graph_._Ways().find(one_move.to));
            NamedArrow arw(point_positions_.at(from_p), point_positions_.at(to_p), one_move.how_much);
            ModifyNamedArrow(arw, GCP::deikstra_arrow_pr_);
            way.push_back(std::move(arw));
            visited[from_p][to_p] = true;
            visited[to_p][from_p] = true;
        }
      return way;
    };

    void DrawEdgesAndArcs(std::ostream &os, const std::string &from, const std::string &to) const
    {
        BoolGraph visited;
        std::vector<NamedArrow> way = GetWayAndUpdateVisited(from, to , visited);
        DrawEA(os, visited);
        for (auto &&waypoint : way)
        {
            waypoint.Draw(os);
        }
    };

public:
    void Draw(std::ostream &os, const std::string &from, const std::string &to) const
    {
        os << GetMainOpenTagLine(square_width_, square_width_);
        DrawNamedCircles(os);
        DrawEdgesAndArcs(os, from, to);
        os << SVGstrings::maintagclose;
    }

    DeikstraRoutePrinter(Graph &source_graph) : GraphPrinterSVG(source_graph)
    {
        router_ = std::make_shared<DeikstraRouter>(source_graph_);
    };
};
