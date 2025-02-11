#include "astardeclare.h"

AStar::AStar(std::filesystem::path configs, std::filesystem::path mp) : cfg_(configs)
{
   map_ = new AStarMap(cfg_, mp);
};

std::vector<PathElement> AStar::CreateUpdateOpenListCandidates(
    const PathElement &now_looking,
    const MatrixPosition &endpoint,
    const std::unordered_set<MatrixPositionHistory, MatrixPositionHistoryHasher> &visited) const
{
   // Возможные шаги с клетки from
   std::vector<Coordinates_Direction> possible_steps = map_->GetPossibleSteps(now_looking.current_pos);
   std::vector<PathElement> potential_to_open_list;

   for (auto &&step : possible_steps)
   {

      MatrixPositionHistory hstr{step.current_coordinates.row, step.current_coordinates.col};
      if (visited.count(hstr))
      {
         continue;
      }
      // Сконструировать PathElement
      auto tmp = ConstructPathElement(step, now_looking.current_pos, endpoint);
      potential_to_open_list.push_back(std::move(tmp));
   }
   return potential_to_open_list;
}

PathElement AStar::ConstructPathElement(const Coordinates_Direction &step,
                                        const MatrixPosition &parent,
                                        const MatrixPosition &endpoint) const
{
   PathElement pth;
   pth.current_pos = step.current_coordinates;
   pth.o_d = AStarConsts::GetODByDirection(step.dir);
   pth.evristica = Evristica(step.current_coordinates, endpoint);
   pth.comed_from = parent;
   return pth;
}

void AStar::UpdateOpenList(std::vector<PathElement> &candidates,
                           std::unordered_set<PathElement, PathElementHasher> &open_list,
                           std::unordered_map<MatrixPosition, MatrixPosition, MatrixPositionHasher> &adressbook) const
{
   // Идем по всем новым путям
   for (PathElement &newway : candidates)
   {
      // Если потенциально новый путь не найден в open_list
      if (open_list.count(newway) == 0)
      {
         //Обновляем адресную кгигу
         adressbook[newway.current_pos] = newway.comed_from;
         //Вставляем элемент
         open_list.insert(std::move(newway));
      }
      else
      {
         // Иначе находим элемент в open_list
         PathElement *ptr = const_cast<PathElement *>(&*open_list.find(newway));
         //Новая сумма пока равна ОД- коэфкеециенту нового элемента
         int new_sum = newway.o_d;
         //Стврая сумма пока равна ОД- коэфкеециенту старого элемента
         int old_sum = ptr->o_d;
         //Предок newway.comed_from (дудушка newway)
         MatrixPosition* grandparentnew = nullptr;
         //Предок ptr->comed_from (Дедушка ptr)
         MatrixPosition* grandparentold = nullptr;
       
         //Если у нового есть "Дедушка"
         if(adressbook.count(newway.comed_from)){
            grandparentnew = &adressbook.at(newway.comed_from);
            new_sum += PosititionCoefficient(newway.comed_from, *grandparentnew);
         }
      
         //Если у старого есть "Дедушка
         if(adressbook.count(ptr->comed_from)){
            grandparentold = &adressbook.at(ptr->comed_from);
            old_sum += PosititionCoefficient(ptr->comed_from, *grandparentold);
         }
         
         if (old_sum > new_sum)
         {
            // Переписываем ему новый коэффециент
            ptr->o_d = newway.o_d;
            // Родителем элемента в списке становится родитель нового эемента
            ptr->comed_from = newway.comed_from;
            //Обновляем адресную кгигу
            adressbook[ptr->current_pos] = newway.comed_from;

         }
      }
   }
}

AStar::~AStar()
{
   delete map_;
}

const ConfigAStar &AStar::GetConfig() const
{
   return cfg_;
}

const AStarMap &AStar::GetMap() const
{
   return *map_;
}

std::vector<MatrixPosition> AStar::GetWay(MatrixPosition from, MatrixPosition to) const
{
   // Если точки from или to непроходимые или from и to равны
   if (!(map_->IsPossibleToStandOn(from) || !(map_->IsPossibleToStandOn(to)) || (from == to)))
   {
      return {};
   };

   ///! Клетки открытоко списка
   std::unordered_set<PathElement, PathElementHasher> open_list;
   ///! Посещенные клетки
   std::unordered_set<MatrixPositionHistory, MatrixPositionHistoryHasher> visited;
   ///! Адреса истории
   std::unordered_map<MatrixPosition, MatrixPosition, MatrixPositionHasher> adressbook;
   ///! Создаем текущий из точки "from"
   PathElement now_obj = {from, {-1, -1}, 0, 0};
   ///! Настраиваем указатель на рассмвтриваемый элемент
   const PathElement *now_looking = &now_obj;
   ///! В открытый лист кладем наш новый элемент
   open_list.insert(*now_looking);
   ///! Создаем флаг поиска
   bool found = false;

   while (!open_list.empty() && !found)
   {
      ///! Ишем элемент с минимальной функцией (manhatten)
      auto iter_list = FindMinStep(open_list);
      assert(iter_list != open_list.end());
      now_looking = &*(FindMinStep(open_list));

      ///! В Посещенные вставляем координаты посещенного узла и возвращаем на него итератор
      auto pair = visited.insert({now_looking->current_pos.row, now_looking->current_pos.col, now_looking->comed_from});
      ///! Если вставился

      if (now_looking->current_pos == to)
      {
         auto it = pair.first;
         adressbook[{it->row, it->col}] = *it->parent;
         found = true;
         break;
      }
      // Кандидаты на добавление или обновление open_list;
      std::vector<PathElement> potential_to_open_list = CreateUpdateOpenListCandidates(*now_looking, to, visited);
      // Обновление Open_list
      UpdateOpenList(potential_to_open_list, open_list, adressbook);
      // Из открытого списка удаляем текущий рассматриваемый узел
      open_list.erase(*now_looking);
   }

   // Не не найден путь - возврат пустого
   if (!found)
   {
      return {};
   }
   std::vector<MatrixPosition> moves;
   // Назначаем текущую
   MatrixPosition current_pos = now_looking->current_pos;
   while (!(current_pos == from))
   {
      // Присоединяем текущую позицию
      moves.push_back(current_pos);
      // В адресах по координатам получаем координаты "предка"
      current_pos = adressbook.at(current_pos);
   }
   // Добавляем точку откуда пришли
   moves.push_back(from);
   std::reverse(moves.begin(), moves.end());
   return moves;
}

AStar::OpenListIterator
AStar::FindMinStep(const std::unordered_set<PathElement, PathElementHasher> &open_list) const
{
   auto pth = open_list.begin();
   for (auto it = open_list.begin(); it != open_list.end(); ++it)
   {
      int foo_pth = pth->evristica + pth->o_d;
      int current_foo = it->o_d + it->evristica;
      if (current_foo < foo_pth)
      {
         pth = it;
      }
   }
   return pth;
}