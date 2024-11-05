#include "graph.h"
bool Graph::CalculateDisjunction(const std::vector<std::vector<bool>> &temp, int row, int col)
{
    size_t size = achievability_list_.at(1).size();
    const auto &needed_row = temp[row];

    for (size_t i = 0; i < size; ++i)
    {
        if (needed_row[i] == true && achievability_list_.at(1)[i][col] == true)
        {
            return true;
        }
    }
    return false;
}

void Graph::MakeAchievebility(int length)
{
    if (length < 2)
    {
        return;
    }
    auto temp_matrix = achievability_list_.at(max_achivement);
    auto target_matrix = achievability_list_.at(1);

    size_t size = achievability_list_.at(1).size();
    int loop_repeats = length - max_achivement;

    for (int lp = 0; lp < loop_repeats; ++lp)
    {
        for (int line = 0; line < size; ++line)
        {
            for (int col = 0; col < size; ++col)
            {
                bool res = CalculateDisjunction(temp_matrix, line, col);
                target_matrix[line][col] = res;
            }
        }
        achievability_list_[++max_achivement] = target_matrix;
        temp_matrix = target_matrix;
    }
}


