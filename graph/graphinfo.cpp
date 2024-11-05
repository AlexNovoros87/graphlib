#include "graph.h"

bool Graph::AlreadyHasDirection(const GraphDirection &gr) const
    {
        if (graph_.count(&*waypoints_.find(gr.from)))
        {
            if (graph_.at(&*waypoints_.find(gr.from))
                    .count(&*waypoints_.find(gr.to)))
            {
                return true;
            }
        }
        return false;
    }

    bool Graph::AlreadyHasDirection(const std::string &from, const std::string &to) const
    {
        if (graph_.count(&*waypoints_.find(from)))
        {
            if (graph_.at(&*waypoints_.find(from))
                    .count(&*waypoints_.find(to)))
            {
                return true;
            }
        }
        return false;
    }

    int Graph::GetOrderNumWaypoint(const std::string *wp) const
    {
        auto it = waypoints_.find(*wp);
        if (it == waypoints_.end())
        {
            return -1;
        }
        return std::distance(waypoints_.begin(), it);
    }

    bool Graph::CheckInputs(const std::string &from, const std::string &to) const
    {
        if (waypoints_.find(from) == waypoints_.end() || waypoints_.find(to) == waypoints_.end())
        {
            std::cout << "Check input data" << std::endl;
            return false;
        }
        return true;
    }