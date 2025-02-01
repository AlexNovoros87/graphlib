#include "graph_achive_border.h"


std::string GraphPrinterAndStrPerfomance::HeaderStrPerfomance(int max) const
{
    std::string firstline;
    std::string gaps = std::string(max_len_word_, Constants::gap);
    firstline.append(std::move(gaps)).push_back(Constants::delim);
    gaps.clear();

    for (auto &&wp : graph_._Ways())
    {
        if (max - wp.size() > 0)
        {
            gaps = std::string(max - wp.size(), Constants::gap);
        }
        firstline.append(gaps).append(wp).push_back(Constants::delim);
    }
    return firstline;
};


std::vector<std::string> GraphPrinterAndStrPerfomance::ContentStrPerfomanceAchiveable(int moves)
{
    if(achiveabler_ == nullptr){
        achiveabler_ = std::make_shared<Achiveabler>(graph_);
    }
    
    std::vector<std::string> container;
    int cur_matrix_line = 0;
    //ДОСТАЕМ МАТРИЦУ ДОСТИЖИМОСТИ ДЛЯ НУЖНОГО КОЛИЧЕСТВА ШАГОВ
    const auto &ach_matrix = achiveabler_->GetAchiveableMatrix(moves);
    //ПРОБЕЛЫ
    std::string gaps;
    //ПО ВСЕМУ МНОЖЕСТВУ ПУТЕЙ.
    for (auto &&w_p : graph_._Ways())
    {
        /*ВЫЧИСЛЯЕМ КОЛИЧЕСТВО НУЖНЫХ ПРОБЕЛОВ ПУТЕМ ВЫЧИТАНИЯ
          ИЗ ЗНАЧЕНИЯ КОЛ-ВА СИМВОЛОВ В САМОМ ДЛИННОМ ИМЕНИ
          ВЕРШИНЫ КОЛИЧЕСТВА СИМВОЛОВ ТЕКУЩЕГО НАЗВАНИЯ.
        */
        if (max_len_word_ - w_p.size() > 0)
        {
            gaps = std::string(max_len_word_ - w_p.size(), ' ');
        }
        std::string tmp;
        //ДЕЛАЕМ  |        ПУНКТ А|
        tmp.append(std::move(gaps)).append(w_p).push_back(Constants::delim);
        /* В ЦИКЛЕ ДЕЛАЕМ|    ПУНКТ А|       TRUE|      FALSE|
        */
        for (bool bl : ach_matrix[cur_matrix_line])
        {
            gaps.clear();
            switch (bl)
            {
            case true:
                if (max_len_word_ - Constants::tr.size() > 0)
                {
                    gaps = std::string(max_len_word_ - Constants::tr.size(), ' ');
                }
                tmp.append(gaps).append(Constants::tr).push_back(Constants::delim);
                break;
            case false:
                if (max_len_word_ - Constants::fls.size() > 0)
                {
                    gaps = std::string(max_len_word_ - Constants::fls.size(), ' ');
                }
                tmp.append(gaps).append(Constants::fls).push_back(Constants::delim);
                break;
            }
        }
        //КЛАДЕМ СТРОКУ В ВЕКТОР
        container.push_back(std::move(tmp));
        //ПЕЕХОДИМ К СЛЕДУЮЩЕЙ ЛИНИИ.
        ++cur_matrix_line;
    }
    return container;
}


std::vector<std::string> GraphPrinterAndStrPerfomance::ContentStrPerfomanceBorder()
{
    if(weigth_matrix_ == nullptr){
            weigth_matrix_ = std::make_shared<double_matrix>(BuildBorderMatrix(graph_));
    }
    
    std::cout<<"DB " <<max_len_double_ << "WD" << max_len_word_<< std::endl;
    
    std::vector<std::string> container;
    int cur_matrix_line = 0;
    std::string gaps;
    for (auto &&w_p : graph_._Ways())
    {
        
       
        /*ВЫЧИСЛЯЕМ КОЛИЧЕСТВО НУЖНЫХ ПРОБЕЛОВ ПУТЕМ ВЫЧИТАНИЯ
          ИЗ ЗНАЧЕНИЯ КОЛ-ВА СИМВОЛОВ В САМОМ ДЛИННОМ ИМЕНИ
          ВЕРШИНЫ КОЛИЧЕСТВА СИМВОЛОВ ТЕКУЩЕГО НАЗВАНИЯ.
        */
        if (max_len_double_ - w_p.size() > 0)
        {
            gaps = std::string(max_len_word_ - w_p.size(), ' ');
        }

        std::string tmp;
        tmp.append(std::move(gaps)).append(w_p).push_back(Constants::delim);

        /* В ЦИКЛЕ ДЕЛАЕМ|    ПУНКТ А|       1.77777|      INFINITE|  ..... 
        */
        for (double bl : (*weigth_matrix_)[cur_matrix_line])
        {
            gaps.clear();
            if (bl == std::numeric_limits<double>::infinity())
            {
                gaps = std::string(max_len_double_ - Constants::inf.size(), ' ');
                tmp.append(gaps).append(Constants::inf).push_back(Constants::delim);
            }
            else
            {
                std::string num_to_str = std::to_string(bl);
                gaps = std::string(max_len_double_ - num_to_str.size(), ' ');
                tmp.append(gaps).append(num_to_str).push_back(Constants::delim);
            }
        }
        //КЛАДЕМ СТРОКУ В ВЕКТОР
        container.push_back(std::move(tmp));
        //ПЕЕХОДИМ К СЛЕДУЮЩЕЙ ЛИНИИ
        ++cur_matrix_line;
    }
    return container;
}

std::vector<std::string> GraphPrinterAndStrPerfomance::StringPerfomanceAchiveableMatrix(int moves)
{
    std::vector<std::string> container;
    container.push_back(HeaderStrPerfomance(max_len_word_));
    auto content = ContentStrPerfomanceAchiveable(moves);
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
    container.push_back(HeaderStrPerfomance(max_len_double_));  
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


void GraphPrinterAndStrPerfomance::PrintAchiveableMatrixToFile(int moves, std::filesystem::path pth, bool trunc)
{
    std::ofstream ofs = CreateFileStream(pth,trunc);
    PrintAchiveableMatrix(moves, ofs);
    ofs.close();
};


void GraphPrinterAndStrPerfomance::PrintBorderMatrixToFile(std::filesystem::path pth, bool trunc)
{
    std::ofstream ofs = CreateFileStream(pth,trunc);
    PrintBorderMatrix(ofs);
    ofs.close();
};

/**
 * \brief Напечатать все пути графа в поток
 * \param ost поток куда печатать
 */
void GraphPrinterAndStrPerfomance::PrintDirections(std::ostream& ost = std::cout) const
{
    for (auto &&graph_node : graph_._Graph())
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


void GraphPrinterAndStrPerfomance::PrintAchiveableMatrix(int moves = 1, std::ostream &ofs = std::cout)
{
    if (moves < 1)
    {
        std::cerr << "Length is incorrect" << std::endl;
        return;
    }
    const auto matrix = StringPerfomanceAchiveableMatrix(moves);
    std::string delim_line = std::string(matrix[0].size(), '-');
    ofs << "The achivementable matrix on " << moves << " turns" << std::endl;
    for (auto &&i : matrix)
    {
        ofs << i << std::endl
            << delim_line << std::endl;
    }
}


void GraphPrinterAndStrPerfomance::UpdateStrLengths()
    {
        for (auto &&from_pair : graph_._Graph())
        {
            const std::string *from_ptr = from_pair.first;
            // Если название вершины длиннее max_len_word_ то
            // max_len_word_ = ДЛИНЕ НАЗВАНИЯ ВЕРШИНЫ
            max_len_word_ = std::max(static_cast<int>(from_ptr->size()), max_len_word_);
            for (auto &&to_pair : graph_._Graph().at(from_ptr))
            {
                const std::string *to_ptr = to_pair.first;
                // Если название вершины длиннее max_len_word_ то
                // max_len_word_ = ДЛИНЕ НАЗВАНИЯ ВЕРШИНЫ
                max_len_word_ = std::max(static_cast<int>(from_ptr->size()), max_len_word_);
                double distanse = graph_._Graph().at(from_ptr).at(to_ptr);
                // Если длина distanse > 8 (0.000000) напрмер (-100.000000) то max_len_double будет 11
                max_len_double_ = std::max(DoubleStrSummator(distanse), max_len_double_);
            }
        }
    }

    int GraphPrinterAndStrPerfomance::DoubleStrSummator(double val)
    {
        int summator = 8;
        if (val < 0)
        {
            summator += 1;
            val *= -1;
        }
        while (val >= 10)
        {
            val /= 10;
            summator += 1;
        }
        return summator;
    };

