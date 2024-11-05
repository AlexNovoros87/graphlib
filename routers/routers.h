#pragma once
#include "../graph/graph.h"

class DeikstraRouter
{
private:
    DeikstraTable MakeCrowTableToDeikstra(const std::string &start) const;
    const std::string *CheckValidWayPointsAndLookingNowPointer(const std::string &from, const std::string &to) const;
    const std::string *NewNowLooking(const std::unordered_set<const std::string *, Hasher> &visited,
                                     const DeikstraTable &table) const;
    
    const Graph &source_grph_;
public:
    DeikstraRouter(const Graph &graph);
    std::vector<const std::string *> DeikstraWayString(const std::string &from, const std::string &to) const;
    std::vector<GraphDirection> DeikstraWayGraphDirection(const std::string &from, const std::string &to) const;
    DeikstraTable ConstructShortestRoutesTable(const std::string &from, const std::string &to) const;
    const auto& _Graph(){return source_grph_;}
};

class DeikstraPrinter
{
public:
    DeikstraPrinter(const DeikstraRouter &router);
    std::string GetWaysString(const std::string &from, const std::string &to) const;
    void PrintStringToConsole(const std::string &from, const std::string &to)const;
    void PrintStringToFile(const std::string &from, const std::string &to, const std::string &file, bool trunc = true)const;
    void PrintStringToYourStream(const std::string &from, const std::string &to, std::ostream &stream)const;
    void PrintGraphDirToConsole(const std::string &from, const std::string &to)const;
    void PrintGraphDirToFile(const std::string &from, const std::string &to, 
                             const std::string &file, bool trunc = true) const;
    void PrintGraphDirToYourStream(const std::string &from, const std::string &to, std::ostream &stream) const;
private:
    void PrintString(const std::string &from, const std::string &to, std::ostream &os = std::cout) const;
    void PrintGraphDir(const std::string &from, const std::string &to, std::ostream &os = std::cout) const;
    const DeikstraRouter &router_;
};