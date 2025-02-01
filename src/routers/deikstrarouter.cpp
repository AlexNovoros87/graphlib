#include "deikstrarouter.h"
DeikstraRouter::DeikstraRouter(const Graph &graph, bool economy_memory = false) : source_grph_(graph) {
  economy_memory_ = economy_memory;
  if(!economy_memory){
    border_matrix_ = BuildBorderMatrix(graph); 
  }
};

 DeikstraTable DeikstraRouter::MakeCrowTableToDeikstra(const std::string &start) const
    {
        DeikstraTable res;
        auto iter = source_grph_._Ways().find(start);
        const std::string *strt = &*iter;
        for (const auto &way : source_grph_._Ways())
        {
            double tmp = std::numeric_limits<double>::infinity();
            res[&way].now_distance = tmp;
        }
        res[strt].now_distance = 0;
        return res;
    }

    const std::string* DeikstraRouter::CheckValidWayPointsAndLookingNowPointer(const std::string &from, const std::string &to) const
    {
        if (!source_grph_.CheckInput(from) || !source_grph_.CheckInput(to))
        {
            std::cout << "Check Deikstra way inputs" << std::endl;
            return nullptr;
        }
        // УКАЗАТЕЛЬ КОТОРЫЙ РАССМАТРИВАЕМ ПОКА РАВЕН ПУНКТУ "ОТКУДА"
        const std::string *now_looking_ptr = &*source_grph_._Ways().find(from);
        return now_looking_ptr;
    };

    const std::string* DeikstraRouter::NewNowLooking(const std::unordered_set<const std::string *, Hasher> &visited,
                                     const DeikstraTable &table) const
    {
        double min = std::numeric_limits<double>::max();
        std::string *to_return = nullptr;
        std::string *anyway = nullptr;

        for (auto &&point : table)
        {
            if (visited.count(point.first) > 0)
            {
                continue;
            }
            anyway = const_cast<std::string*>(point.first);
            if (point.second.now_distance < min)
            {
                to_return = anyway;
                anyway = nullptr;
                min = point.second.now_distance;
            };
        }
        return to_return ? to_return : anyway;
    }

    DeikstraTable DeikstraRouter::ConstructShortestRoutesTable(const std::string &from, const std::string &to) const
    {
        //ПРОВЕРИТЬ ВАЛИДНОСТЬ ПУНКТОВ И УСТАНОВИТЬ СЕЙЧАС РАССМАТРИВАЕМЫ УКАЗАТЕЛЬ НА НАЧАЛЬНЫЙ ПУНКТ
        std::string *now_looking_ptr = const_cast<std::string *>(CheckValidWayPointsAndLookingNowPointer(from, to));
        if (!now_looking_ptr) { return {};}
        //СДЕЛАТЬ ТАБЛИЦУ МАРШУТОВ ОТ НАЧАЛА И ДО ТОЧЕК ОТКУДА ИДУТ ОТ НЕЕ НАПРАВЛЕНИЯ 
        auto table = MakeCrowTableToDeikstra(from); 
        if (table.empty())
        {
            return {};
        }
         
         const auto &waypoints_link = source_grph_._Ways(); //ССЫЛКА НА ИМЕНА ТОЧЕК ГРАФА
         std::unordered_set<const std::string *, Hasher> visited; //ПОСЕЩЕННЫЕ ТОЧКИ

        while (visited.size() != waypoints_link.size()) //ПОКА НЕ ПОСЕЩЕНЫ ВСЕ ТОЧКИ
        {
             /*6*/ const int from_ind = GetElementOrder(*now_looking_ptr, source_grph_._Ways());
                   
                  
                   
            // ПОЛУЧАЕМ ВСЕ РАССТОЯНИЯ ОТ ПУНКА "ОТКУДА" ДО ВСЕХ ПУНКТОВ
            
            const auto &now_looking_line = !economy_memory_ ? 
            (*border_matrix_)[from_ind] : BuildMatrixLine(*now_looking_ptr, source_grph_);
            
            const double in_place_distance = now_looking_line[from_ind];
            double summator_looking_ptr = table.at(now_looking_ptr).now_distance;
            visited.insert(now_looking_ptr);
            if (source_grph_._Graph().count(now_looking_ptr) > 0)
            {

                for (const auto &directions : source_grph_._Graph().at(&*now_looking_ptr))
                {
                    // УКАЗАТЕЛЬ НА НАЗВАНИЕ "КУДА"
                    const std::string *direction_to = directions.first;
                    // ПОЛУЧАЕМ ПОРЯДКОВЫЙ НОМЕР НАЗВАНИЯ ПУНКТА "КУДА"
                    // ДЛЯ РАБОТЫ С МАТРИЦЕЙ СМЕЖНОСТИ
                    const int to_ind = GetElementOrder(*direction_to,source_grph_._Ways());
                    // РАССТОЯНИЕ ОТКУДА -----> КУДА
                    const double dist = now_looking_line[to_ind] + summator_looking_ptr;
                    // ТЕКУЩЕЕ МИНИМАЛЬНОЕ РАССТОЯНИЕ В ТАБЛИЦЕ
                    double &now_table_value = table.at(direction_to).now_distance;
                    if (now_table_value > dist)
                    {
                        now_table_value = dist;
                        auto &needed_points = table.at(direction_to).way_points_;

                        if (needed_points.empty())
                        {
                            needed_points.push_back(now_looking_ptr);
                        }
                        else
                        {
                            needed_points[0] = now_looking_ptr;
                        }
                    }
                }
            }

            now_looking_ptr = const_cast<std::string *>(NewNowLooking(visited, table));

            if (!now_looking_ptr)
            {
                break;
            }
        }

        return table;
    }

    std::vector<const std::string *> DeikstraRouter::DeikstraWayString(const std::string &from, const std::string &to) const
    {
        DeikstraTable table = ConstructShortestRoutesTable(from, to);        
        if (table.empty())
        {
            return {};
        }
        std::string *way_to = const_cast<std::string *>(&*source_grph_._Ways().find(to));
        std::vector<const std::string *> &now_point_vctr = table.at(way_to).way_points_;
        std::vector<const std::string *> route;
        route.push_back(way_to);

        while (!now_point_vctr.empty())
        {
            for (int i = static_cast<int>(now_point_vctr.size()) - 1; i >= 0; --i)
            {
                route.push_back(now_point_vctr[i]);
            }
            way_to = const_cast<std::string *>(now_point_vctr[0]);
            now_point_vctr = table.at(way_to).way_points_;
        }
        std::reverse(route.begin(), route.end());
        return route;
    }

    std::vector<GraphDirection> DeikstraRouter::DeikstraWayGraphDirection(const std::string &from, const std::string &to) const
    {
        std::vector<const std::string *> string_route = DeikstraWayString(from, to);
        std::vector<GraphDirection> way;

        if (string_route.empty())
        {
            return {};
        }
        else if (string_route.size() == 1)
        {
            if (*string_route[0] != from)
               { return {}; }
            double distance = source_grph_.GetDistance(*string_route[0], *string_route[0]);
            way.push_back({*string_route[0], *string_route[0], distance});
        }
        else
        {
            for (int i = 0, j = 1; j < static_cast<int>(string_route.size()); ++i, ++j)
            {
                double distance = source_grph_.GetDistance(*string_route[i], *string_route[j]);
                way.push_back({*string_route[i], *string_route[j], distance});
            }
        }
        return way;
    }

DeikstraRouter::DeikstraRouter(const Graph &graph) : source_grph_(graph){};