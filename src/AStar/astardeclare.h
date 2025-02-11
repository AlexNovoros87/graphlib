#pragma once
#include "astarsupport.h"


class AStar
{
private:
   using OpenListIterator = std::unordered_set<PathElement, PathElementHasher>::const_iterator;
   
   OpenListIterator 
   FindMinStep(const std::unordered_set<PathElement, PathElementHasher> &open_list) const;

   /// @brief Создает список клетое, доступных для посещения 
   /// @param now_looking объект, относительно корого будет строится список клеток
   /// @param endpoint Конечная точка, Нужна для вычисления Манхеттеновского значения.
   /// @param visited Посещенные узлы
   /// @return 
   std::vector<PathElement> CreateUpdateOpenListCandidates(
       const PathElement &now_looking,
       const MatrixPosition &endpoint,
       const std::unordered_set<MatrixPositionHistory, MatrixPositionHistoryHasher> &visited) const;

   /// @brief Конструирует PathElement
   /// @param step //Структура , хранящая текущие координаты и откуда был 
   /// сделан шаг, чтобы вычислить ортогональное или диагональное 
   /// расположение относительно parent откуда шаг был сделан
   /// @param parent Откуда был сделан шаг
   /// @param endpoint Конечная точка, Нужна для вычисления Манхеттеновского значения.
   PathElement ConstructPathElement(const Coordinates_Direction &step,
                                    const MatrixPosition &parent,
                                    const MatrixPosition &endpoint) const;

   /// @brief Обновить открытый лист
   /// @param candidates Кандидаты для обновления
   /// @param open_list Открытый лист
   void UpdateOpenList(std::vector<PathElement> &candidates,
                       std::unordered_set<PathElement, PathElementHasher> &open_list,
                       std::unordered_map<MatrixPosition, MatrixPosition, MatrixPositionHasher>& adressbook) const;

public:
   /// @brief Конструктор
   /// @param configs Файл с конфигурациями
   /// @param mp Файл с Картой
   AStar(std::filesystem::path configs, std::filesystem::path mp);

   ~AStar();
   /// @brief Конфигуратор настроек объекта 
   const ConfigAStar &GetConfig() const;

   /// @brief карта объекта 
   const AStarMap &GetMap() const;

   /// @brief Получить путь
   /// @param from Начальная точка
   /// @param to Конечная точка
   std::vector<MatrixPosition> GetWay(MatrixPosition from, MatrixPosition to) const;

private:
   ConfigAStar cfg_;
   AStarMap *map_ = nullptr;
   
};
