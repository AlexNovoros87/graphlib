#include "deikstra_printer.h"
DeikstraPrinter::DeikstraPrinter(const DeikstraRouter &router) : router_(router) {};

std::string DeikstraPrinter::GetWaysString(const std::string &from, const std::string &to) const
{
    auto container = router_.DeikstraWayString(from, to);
    std::string tmp;
    for (int i = 0; i < static_cast<int>(container.size()); ++i)
    {
        tmp.append(*container[i]);
        if (i + 1 == container.size())
        {
            break;
        }
        tmp.append(Constants::arrow);
    }
    return tmp;
}

void DeikstraPrinter::PrintStringToConsole(const std::string &from, const std::string &to) const
{
    PrintString(from, to);
}

void DeikstraPrinter::PrintStringToFile(const std::string &from, const std::string &to, const std::string &file, bool trunc) const
{
    auto stream = CreateFileStream(file, trunc);
    PrintString(from, to, stream);
}

void DeikstraPrinter::PrintStringToYourStream(const std::string &from, const std::string &to, std::ostream &stream) const
{
    PrintGraphDir(from, to, stream);
}

void DeikstraPrinter::PrintGraphDirToConsole(const std::string &from, const std::string &to) const
{
    PrintGraphDir(from, to);
}

void DeikstraPrinter::PrintGraphDirToFile(const std::string &from, const std::string &to, const std::string &file, bool trunc) const
{
    auto stream = CreateFileStream(file, trunc);
    PrintGraphDir(from, to, stream);
}

void DeikstraPrinter::PrintGraphDirToYourStream(const std::string &from, const std::string &to, std::ostream &stream) const
{
    PrintGraphDir(from, to, stream);
}

void DeikstraPrinter::PrintString(const std::string &from, const std::string &to, std::ostream &os) const
{
    os << GetWaysString(from, to);
}

void DeikstraPrinter::PrintGraphDir(const std::string &from, const std::string &to, std::ostream &os) const
{
    auto container = router_.DeikstraWayGraphDirection(from, to);
    for (auto &&i : container)
    {
        os << i << std::endl;
    }
}