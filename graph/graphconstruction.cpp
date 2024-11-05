#include "graph.h"
Graph::Graph(const std::string& way_to_file)
{
    LoadDirections(std::filesystem::path(way_to_file).lexically_normal());
    BuildAchievebilityOne();
    BuildBorderMatrix();
};

void Graph::LoadDirections(const std::filesystem::path &path)
{
    std::ifstream ifs(path);
    if (!ifs)
    {
        throw std::runtime_error("something error wit stream file");
    }
    std::string tmp;

    while (!ifs.eof())
    {
        if (ifs.bad())
        {
            throw std::runtime_error("something error wit stream file");
        }
        std::getline(ifs, tmp);
        Trim(tmp);
        if( (tmp.empty()) || tmp[0] == '#') continue;
        
        auto direction = MakeOneDir(std::move(tmp));

        if (direction.from.size() > max_len_word)
        {
            max_len_word = direction.from.size();
        }
        if (direction.to.size() > max_len_word)
        {
            max_len_word = direction.to.size();
        }
        int d_lenght = static_cast<int>(std::to_string(direction.how_much).size());
        if(d_lenght > max_len_double) 
        {
            max_len_double  = d_lenght;
        }

        waypoints_.insert(direction.from);
        waypoints_.insert(direction.to);
        graph_ [&*waypoints_.find(direction.to)];

        if (!AlreadyHasDirection(direction))
        {
            graph_[&*waypoints_.find(direction.from)]
                  [&*waypoints_.find(direction.to)] = direction.how_much;
        }
        else
        {
            std::string disigion;
            std::cout << "The direction from: " << direction.from << " to: " << direction.to << " already in graph, rewrite?" << std::endl;
            std::cout << "Type 'Y' to rewrite or other to continue." << std::endl;
            std::getline(std::cin, disigion);

            if (disigion == "Y")
            {
                graph_[&*waypoints_.find(direction.from)]
                      [&*waypoints_.find(direction.to)] = direction.how_much;
            }
        }
    }
}

void Graph::BuildBorderMatrix()
{
    auto border = GetCrowlDoubleMaxMatrix(waypoints_.size());
    for (const auto &pair : graph_)
    {
        int line = GetOrderNumWaypoint(pair.first);
        for (const auto &sec : pair.second)
        {
            int col = GetOrderNumWaypoint(sec.first);
            border[line][col] = graph_.at(pair.first).at(sec.first);
        }
    }
    border_matrix_ = std::move(border);
}

void Graph::BuildAchievebilityOne()
{
    std::vector<std::vector<bool>> achievability_ = GetCrowlBoolMatrix(waypoints_.size());
    for (const auto &pair : graph_)
    {
        int line = GetOrderNumWaypoint(pair.first);
        for (const auto &sec : pair.second)
        {
            int col = GetOrderNumWaypoint(sec.first);
            achievability_[line][col] = true;
        }
    }
    achievability_list_[1] = std::move(achievability_);
}