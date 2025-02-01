#include "graph.h"

/**
 * \brief Констрнктор графа
 * \details Загружает все ребра и дуги графа, сторит матрицу смежности,
 * матрицу достижимости длиной в 1
 * \param way_to_file Путь где находится файл расстояний
 * \exception std::runtime_error("something error wit stream file")
 */
Graph::Graph(const std::string &way_to_file)
{
    /*ЗАГРУЗИТЬ ГРАФ С ФАЙЛА ПРИНИМЕТ В КАЧ-ВЕ АРГУМЕНТА ПУТЬ К ФАЙЛУ*/
    LoadDirections(std::filesystem::path(way_to_file).lexically_normal());
};

/**
 * \brief Загрузка расстояний
 * \details Загружает все ребра и дуги графа
 * \param path Путь где находится файл расстояний
 * \exception std::runtime_error("something error wit stream file")
 */
void Graph::LoadDirections(const std::filesystem::path &path)
{
    // ИНИЦИАЛИЗИРУЕМ ПОТОК ВВОДА
    std::ifstream ifs(path);
    // ЕСЛИ ПОТОК НЕ ИНИЦИАЛИЗИРОВАЛСЯ
    if (!ifs)
    {
        throw std::runtime_error("something error wit stream file");
    }
    // ВЕМЕННАЯ ПЕРЕМЕННАЯ ДЛЯ ЧТЕНИЯ
    std::string tmp;
    // ПОКА НЕ КОНЕЦ ФАЙЛА
    while (!ifs.eof())
    {
        // ЕСДИ ЧТО-ТО С ПОТОКОМ ВВОДА
        if (ifs.bad())
        {
            throw std::runtime_error("something error wit stream file");
        }
        // ЧИТАЕМ СТРОКУ С ПОТОКА В ТМР
        std::getline(ifs, tmp);
        // ОБРЕЗАЕМ ЛИШНИЕ СИМВОЛЫ ПО КРАЯМ
        Trim(tmp);
        // ЕСЛИ СТРОКА ПУСТА ИЛИ #КОМЕНТАРИЙ - ПРОПУСКАЕМ
        if ((tmp.empty()) || tmp[0] == '#')
            continue;

        /*ОТПРАВЛЯЕМ СТРОКУ НА ПАРСИНГ ЧТО БЫ ПОЛУЧИТЬ СТРУКТУРУ НАПРАВЛЕНИЯ
        ОТКУДА КУДА СКОЛЬКО*/
        auto direction = MakeOneDir(std::move(tmp));

        // ВО МНОЖЕСТВО НАЗВАНИЙ МАПРШРУТОВ ПОМЕЩАЕМ ОБЬЕКТЫ "ОТКУДА" И "КУДА"
        waypoints_.insert(direction.from);
        waypoints_.insert(direction.to);

        /*В ПРЕДСТАВЛЕНИИ ГРАФА ДЕЛАЕМ ПРОСТО ЧТОБ СУЩЕСТВОВАЛА ВЕРШИНА "КУДА"
          В ДАЛЬНЕЙШЕМ СКОКРАТИТ КОЛИЧЕСТВО ПРОВЕРОК НА СУЩЕСТВОВАНИЕ МАРШРУТА.*/
        graph_[&*waypoints_.find(direction.to)];

        // ЕСЛИ НЕТ ТЕКУЩЕГО НАПРАВЛЕНИЯ
        if (!AlreadyHasDirection(direction))
        {
            // СОЗДАЕМ ЕГО ОТКУДА-КУДА-СКОЛЬКО
            graph_[&*waypoints_.find(direction.from)]
                  [&*waypoints_.find(direction.to)] = direction.how_much;
        }
        else
        {
            /*ЕСЛИ ЕСТЬ ТЕКУЩЕЕ НАПРАВЛЕНИЕ ТО ДАЕМ ПОЛЗОВАТЕЛЮ ЗАПРОС НА
            ИЗМЕНЕНИЯ РАССТОЯНИЯ*/
            std::string disigion;
            std::cout << "The direction from: " << direction.from << " to: "
                      << direction.to << " already in graph, rewrite?" << std::endl;
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

double_matrix BuildBorderMatrix(const Graph &graph)
{
    /*КОНСТРУИРЕМ СЫРУЮ МАТРИЦУ N X N ГДЕ N КОЛИЧЕСТВО
     ВЕРШИН ГРАФА*/
    auto border = GetCrowlDoubleMaxMatrix(graph._Ways().size());

    for (const auto &pair : graph._Graph())
    {
        // ВЫЧИСЛЯЕМ ПОРЯДКОВЫЙ НОМЕР ПУНКТА "ОТКУДА" ВО МНОЖЕСТВЕ
        int line = GetElementOrder(*pair.first, graph._Ways());
        for (const auto &sec : pair.second)
        {
            // ВЫЧИСЛЯЕМ ПОРЯДКОВЫЙ НОМЕР ПУНКТА "КУДА" ВО МНОЖЕСТВЕ
            int col = GetElementOrder(*sec.first, graph._Ways());
            // МЕНЯЕТ В СЫРОЙ МАТРИЦЕ ЗНАЧЕНИЕ НА "СКОЛЬКО" ОТ "ОТКУДА" ДО "КУДА"
            border[line][col] = graph._Graph().at(pair.first).at(sec.first);
        }
    }
    return border;
}


std::vector<double> BuildMatrixLine(const std::string &from, const Graph& graph){
     std::vector<double> line(graph._Ways().size(), std::numeric_limits<double>::max());
     int cnt = 0;
     for(auto && to : graph._Ways()){
        line[cnt++] = graph.GetDistance(from,to);
     }
     return line;
};


double Graph::GetDistance(const std::string &from, const std::string &to) const
{
    if (!CheckInput(from)  or !CheckInput(to))
    {
        return std::numeric_limits<double>::max();
    }
    const std::string*  f_lnk = &*waypoints_.find(from);
    const std::string*  t_lnk = &*waypoints_.find(to);
    
    if(graph_.count(f_lnk)){
        if(graph_.at(f_lnk).count(t_lnk)){
            return graph_.at(f_lnk).at(t_lnk);
        }
    }
    
    return std::numeric_limits<double>::max();
}