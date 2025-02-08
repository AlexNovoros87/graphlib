#pragma once
#include"astarsupport.h"

class AStar
{
public:
   AStar(std::filesystem::path configs, std::filesystem::path mp) : cfg_(configs)
   {
      map_ = new AStarMap(mp, cfg_.GetTranparentSym(), cfg_.GetNoTranparent());
   };

   ~AStar()
   {
      delete map_;
   }

   const ConfigAStar &GetConfig() const
   {
      return cfg_;
   }

   const AStarMap &GetMap() const
   {
      return *map_;
   }

private:
   AStarMap *map_ = nullptr;
   ConfigAStar cfg_;
};
