#include "graph.h"

const std::string *Graph::Number_matrix_assotiation(int num) const
{
    if (num < 0)
    {
        return nullptr;
    }
    if (num >= waypoints_.size())
    {
        return nullptr;
    }
    auto it = waypoints_.begin();
    std::advance(it, num);
    return &*it;
}

const std::vector<std::vector<bool>> &Graph::GetAchiveableMatrix(int lenght)
{
    if (lenght < 1)
    {
        throw std::invalid_argument("GetAchiveableMatrix error");
    }
    if (achievability_list_.count(lenght) == 0)
    {
        MakeAchievebility(lenght);
    }
    return achievability_list_.at(lenght);
}

    double Graph::GetDistance(const std::string &from, const std::string &to) const
    {
        if (!CheckInputs(from, to))
        {
            return std::numeric_limits<double>::max();
        }
        int ind_f = GetOrderNumWaypoint(&from);
        int ind_t = GetOrderNumWaypoint(&to);
        return border_matrix_[ind_f][ind_t];
    }



