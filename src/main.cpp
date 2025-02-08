#include "achiveabler/achiveabler.h"
#include "svg_printers/svg_printers.h"
#include "console_printers/graph_achive_border.h"
#include "AStar/astardeclare.h"
int main(){

 const std::filesystem::path config("F:/WITH_CONAN/NewGraph/build/Astconf.conf");
 const std::filesystem::path matrix("F:/WITH_CONAN/NewGraph/build/Astarm.txt");

 AStar ast(config,matrix);
 
 auto& map = ast.GetMap();
 PrintMatrix(map.GetMapMatrix());


 for(auto && i : map.GetPossibleSteps({0,0})){
         std::cout<<i<<std::endl;
 }
 


 
 
 
 //ast.Design().PrintParametrs();
 //PrintMatrix(ast.GetMap().GetMapMatrix());

 // DesignAstar ast(, );
 // ast.PrintParametrs();



}


/*
int size = static_cast<int>(map.GetMapMatrix().size());

for(int r = 0; r < size + 7; ++r){
   for(int c = 0; c < size + 7; ++c){
     int cnt = 0;
     MatrixPosition ps{r,c};

    if(map.IsCorrectMapPosition(ps)){ 
     for (auto&& mod : map.TurnModificators()){
      if(map.IsCorrectMapPosition(ps + mod)){++cnt;}
     }
    }
    
    std::cout<<cnt;
    }
     std::cout<< std::endl;
}

 int size = static_cast<int>(map.GetMapMatrix().size());

for(int r = 0; r < size ; ++r){
   
   int sizex = static_cast<int>(map.GetMapMatrix()[r].size());
   for(int c = 0; c < sizex  ; ++c){
   std::cout << map.IsPossibleToStandOn(r,c);   

   }
   std::cout<< std::endl;
   } 

*/