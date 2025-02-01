#include "achiveabler/achiveabler.h"
#include "svg_printers/svg_printers.h"
#include "console_printers/graph_achive_border.h"
int main(){
     Graph gr("grsuper.txt");
     Achiveabler ach(gr);
     DeikstraRouter dr(gr, false);
     
     std::ofstream ofs("svg.svg", std::ios::trunc);
     DeikstraRoutePrinter drp(gr, true);
    // drp.DrawWithGraph(ofs,"X1", "X9");
     GraphPrinterAndStrPerfomance sper(gr);
     sper.PrintBorderMatrix(std::cout);
     
     
     
     ofs.close();





}