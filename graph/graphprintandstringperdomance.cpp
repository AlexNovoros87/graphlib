#include "graph.h"

std::string GraphPrinterAndStrPerfomance::HeaderStrPerfomance(int max) const
{
    std::string firstline;
    std::string gaps = std::string(graph_lnk_.max_len_word, Constants::gap);
    firstline.append(std::move(gaps)).push_back(Constants::delim);
    gaps.clear();

    for (auto &&wp : graph_lnk_.waypoints_)
    {
        if (max - wp.size() > 0)
        {
            gaps = std::string(max - wp.size(), Constants::gap);
        }
        firstline.append(gaps).append(wp).push_back(Constants::delim);
    }
    return firstline;
};

std::vector<std::string> GraphPrinterAndStrPerfomance::ContentStrPerfomanceAchiveable(int lenght)
{
    std::vector<std::string> container;
    int cur_matrix_line = 0;
    const auto &ach_matrix = graph_lnk_.GetAchiveableMatrix(lenght);
    std::string gaps;
    for (auto &&w_p : graph_lnk_.waypoints_)
    {
        if (graph_lnk_.max_len_word - w_p.size() > 0)
        {
            gaps = std::string(graph_lnk_.max_len_word - w_p.size(), ' ');
        }
        std::string tmp;
        tmp.append(std::move(gaps)).append(w_p).push_back(Constants::delim);

        for (bool bl : ach_matrix[cur_matrix_line])
        {
            gaps.clear();
            switch (bl)
            {
            case true:
                if (graph_lnk_.max_len_word - Constants::tr.size() > 0)
                {
                    gaps = std::string(graph_lnk_.max_len_word - Constants::tr.size(), ' ');
                }
                tmp.append(gaps).append(Constants::tr).push_back(Constants::delim);
                break;
            case false:
                if (graph_lnk_.max_len_word - Constants::fls.size() > 0)
                {
                    gaps = std::string(graph_lnk_.max_len_word - Constants::fls.size(), ' ');
                }
                tmp.append(gaps).append(Constants::fls).push_back(Constants::delim);
                break;
            }
        }
        container.push_back(std::move(tmp));
        ++cur_matrix_line;
    }
    return container;
}

std::vector<std::string> GraphPrinterAndStrPerfomance::ContentStrPerfomanceBorder()
{
    std::vector<std::string> container;
    int cur_matrix_line = 0;
    std::string gaps;
    for (auto &&w_p : graph_lnk_.waypoints_)
    {
        if (graph_lnk_.max_len_double - w_p.size() > 0)
        {
            gaps = std::string(graph_lnk_.max_len_word - w_p.size(), ' ');
        }
        std::string tmp;
        tmp.append(std::move(gaps)).append(w_p).push_back(Constants::delim);

        for (double bl : graph_lnk_.border_matrix_[cur_matrix_line])
        {
            gaps.clear();
            if (bl == std::numeric_limits<double>::infinity())
            {
                gaps = std::string(graph_lnk_.max_len_double - Constants::inf.size(), ' ');
                tmp.append(gaps).append(Constants::inf).push_back(Constants::delim);
            }
            else
            {
                std::string num_to_str = std::to_string(bl);
                gaps = std::string(graph_lnk_.max_len_double - num_to_str.size(), ' ');
                tmp.append(gaps).append(num_to_str).push_back(Constants::delim);
            }
        }
        container.push_back(std::move(tmp));
        ++cur_matrix_line;
    }
    return container;
}

std::vector<std::string> GraphPrinterAndStrPerfomance::StringPerfomanceAchiveableMatrix(int lenght)
{
    std::vector<std::string> container;
    container.push_back(HeaderStrPerfomance(graph_lnk_.max_len_word));
    auto content = ContentStrPerfomanceAchiveable(lenght);
    for (auto &el : content)
    {
        container.push_back(std::move(el));
    }
    return container;
}

const std::vector<std::string>&GraphPrinterAndStrPerfomance::StringPerfomanceBorderMatrix()
{
    if (!string_border_matrix_.empty())
    {
        return string_border_matrix_;
    }
    std::vector<std::string> container;
    container.push_back(HeaderStrPerfomance(graph_lnk_.max_len_double));
    auto content = ContentStrPerfomanceBorder();
    for (auto &el : content)
    {
        container.push_back(std::move(el));
    }
    string_border_matrix_ = std::move(container);
    return string_border_matrix_;
};

void GraphPrinterAndStrPerfomance::PrintBorderMatrix(std::ostream &ofs)
{
    const auto &bord_mtrx = StringPerfomanceBorderMatrix();
    std::string delline(bord_mtrx[0].size(), '-');
    for (const auto &line : bord_mtrx)
    {
        ofs << line << std::endl << delline << std::endl;
    };
};

void GraphPrinterAndStrPerfomance::PrintAchiveableMatrixToFile(int lenght, std::filesystem::path pth, bool trunc)
{
    std::ofstream ofs = CreateFileStream(pth,trunc);
    PrintAchiveableMatrix(lenght, ofs);
    ofs.close();
};

void GraphPrinterAndStrPerfomance::PrintBorderMatrixToFile(std::filesystem::path pth, bool trunc)
{
    std::ofstream ofs = CreateFileStream(pth,trunc);
    PrintBorderMatrix(ofs);
    ofs.close();
};

void GraphPrinterAndStrPerfomance::PrintDirections(std::ostream& ost = std::cout) const
{
    for (auto &&graph_node : graph_lnk_.graph_)
    {
        for (auto &&graph_node_second : graph_node.second)
        {
            ost << "The way from: " << *graph_node.first << " to: "
                      << *graph_node_second.first << " is: " << graph_node_second.second << std::endl;
        }
    }
}

void GraphPrinterAndStrPerfomance::PrintDirectionsToFile(std::filesystem::path pth, bool trunc) const{
      std::ofstream ofs = CreateFileStream(pth,trunc);
      PrintDirections(ofs);
      ofs.close();
};

void GraphPrinterAndStrPerfomance::PrintAchiveableMatrix(int lenght = 1, std::ostream &ofs = std::cout)
{
    if (lenght < 1)
    {
        std::cerr << "Length is incorrect" << std::endl;
        return;
    }
    const auto matrix = StringPerfomanceAchiveableMatrix(lenght);
    std::string delim_line = std::string(matrix[0].size(), '-');
    ofs << "The achivementable matrix on " << lenght << " turns" << std::endl;
    for (auto &&i : matrix)
    {
        ofs << i << std::endl
            << delim_line << std::endl;
    }
}

