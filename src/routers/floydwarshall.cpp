#include "floydwarshall.h"
#include <cmath>

FloydWarshallRouter::FloydWarshallRouter(const Graph &gr) : graph_(gr)
    {
        SetupShortestDistanses(graph_);
    };

    const const_str_ptr_matrix& FloydWarshallRouter::GetHistoryMathrix() const
    {
        return history_mtrx_;
    }

    const double_matrix & FloydWarshallRouter::GetShortestWayTable() const
    {
        return shortest_matrix_;
    }

    double FloydWarshallRouter::GetShortestWayLength(const std::string& from, const std::string& to) const {
        if(!graph_.CheckInput(from) || !graph_.CheckInput(to)) {return std::numeric_limits<double>::infinity();}
        
        int f = GetElementOrder(from, graph_._Ways());
        int t = GetElementOrder(to, graph_._Ways());
        return shortest_matrix_[f][t];
    }


    std::vector<const std::string *> FloydWarshallRouter::ShortestWay (const std::string& from, const std::string& to) const {       
         if(!graph_.CheckInput(from) || !graph_.CheckInput(to)) {return{};}
         
         
        const std::string* f = &*graph_._Ways().find(from);
        const std::string* t = &*graph_._Ways().find(to);
         
         
         int order_f =  GetElementOrder(*f, graph_._Ways()); 
         int order_t = GetElementOrder(*t, graph_._Ways()); 
            
         if(history_mtrx_[order_f][order_t] == nullptr) {return{};}
         std::vector<const std::string *> way;
         way.push_back(f);
         
         int cur_from = order_f;
         auto cur_ptr = history_mtrx_[cur_from][order_t];
         while (*cur_ptr != *t)
         {
           cur_ptr = history_mtrx_[cur_from][order_t];
           way.push_back(cur_ptr);
           cur_from = GetElementOrder(*cur_ptr, graph_._Ways()); 
              
         }
         if(way.size() == 1){way.push_back(t);}
         
        return way;
    
    }


const_str_ptr_matrix FloydWarshallRouter::GetHistoryMatrixByWeightMatrix
(const double_matrix &wm) const {
   //ПОЛУЧАЕМ СЫРУЮ МАТРИУ ИСТОРИИ
   auto hm = GetStringPointersMatrix(wm.size());
   //РАЗМЕР МАТРИЦЫ 
   int sz = static_cast<int>(wm.size());
   for (int i = 0; i < sz; ++i)
    {
        for (int j = 0; j < sz; ++j)
        {
           
            GetPointerIfHasContainer(j, graph_._Ways()) ;
            if(i == j){
               hm[i][j] = GetPointerIfHasContainer(j, graph_._Ways());
               continue;
            }
            if (!std::isinf(wm[i][j]))
            {
                hm[i][j] = GetPointerIfHasContainer(j, graph_._Ways());
            }
        }
    }
    return hm;
};


void FloydWarshallRouter::SetupShortestDistanses(const Graph &gr)
{
    auto wm = BuildBorderMatrix(gr);
    auto hm = GetHistoryMatrixByWeightMatrix(wm);
    int sz = static_cast<int>(wm.size());
    
    
    for (int A = 0; A < sz; ++A)
    {
        for (int B = 0; B < sz; ++B)
        {
            if ((wm[A][B] < 0) && !warned_){
                warned_ = true;
                WarnValueLess0();
            }
            
            if(std::isinf(wm[A][B])) {continue;}
            for (int C = 0; C < sz; ++C)
            {
                double current = wm[A][C];
                double candidate = wm[A][B] + wm[B][C];
                if (candidate < current) {
                    wm[A][C] = candidate;
                    hm[A][C] = hm[A][B];
                }
            }
        }
    }
  shortest_matrix_ = std::move(wm);
  history_mtrx_ = std::move(hm);
};