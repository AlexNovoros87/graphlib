#include "freefoo.h"

constexpr std::string Constants::tr = "true";
constexpr std::string Constants::fls = "false";
constexpr std::string Constants::inf = "INFINITY";
constexpr char Constants::gap = ' ';
constexpr char Constants::delim = '|';
constexpr char Constants::ln = '-';
constexpr std::string Constants::no_ways = "NO WAYS";
constexpr std::string Constants::arrow = " --> ";

bool IsTrimmerSymb(char ch)
{
    if (ch == ' ')
    {
        return true;
    }
    if (isdigit(ch) or isalpha(ch))
    {
        return false;
    }
    if (ch == '\n' or ch == '\t' or ch == '\r')
    {
        return true;
    }
    return false;
}

void Trim(std::string &line)
{
    if (line.empty())return;

    int pos = 0;
    while (IsTrimmerSymb(line[pos]))
    {
        ++pos;
    }
    if (pos != 0)
    {
        line = line.substr(pos);
    }
    if (line.empty())return;
    pos = static_cast<int>(line.size()) - 1;
    while (IsTrimmerSymb(line[pos]))
    {
        --pos;
    }
    if (pos != line.size() - 1)
    {
        line = line.substr(0, pos + 1);
    }
}

std::vector<std::string> SplitBy(std::string line)
{
    std::vector<std::string> splitted;
    std::string tmp;

    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] != '|')
        {
            tmp += line[i];
        }
        else
        {
            Trim(tmp);
            splitted.push_back(tmp);
            tmp.clear();
        }
    }
    Trim(tmp);
    splitted.push_back(std::move(tmp));
    if (splitted.size() != 3)
    {
        throw std::invalid_argument("error splitting size");
    }
    return splitted;
}

std::vector<std::vector<double>> GetCrowlDoubleMaxMatrix(int size)
{
    std::vector<double> oneline(size, std::numeric_limits<double>::infinity());
    std::vector<std::vector<double>> border(size, oneline);
    for (int i = 0; i < static_cast<int>(border.size()); ++i)
    {
        border[i][i] = 0.;
    }
    return border;
}

std::vector<std::vector<bool>> GetCrowlBoolMatrix(int size)
{
    std::vector<bool> line(size, false);
    return std::vector(size, line);
}

bool IsMaxDouble(double db)
{
    return std::abs(std::numeric_limits<double>::max() - db) < std::numeric_limits<double>::epsilon();
}

bool IsLessDouble(double one, double two)
{
    return one - two > std::numeric_limits<double>::epsilon();
}

bool IsEqualDouble(double one, double two){
     return std::abs(one - two) < std::numeric_limits<double>::epsilon();  
};

GraphDirection MakeOneDir(std::string line)
{
    std::vector<std::string> ready_params = SplitBy(std::move(line));
    size_t stod;
    double len = std::stod(ready_params[2], &stod);
    if (stod != ready_params[2].size())
        throw std::invalid_argument("error in making double");
    return {std::move(ready_params[0]), std::move(ready_params[1]), len};
}

std::ofstream CreateFileStream(const std::filesystem::path &pth, bool trunc)
{
    auto mode = trunc ? std::ios::trunc : std::ios::app;
    std::ofstream ofs(pth, mode);
    return ofs;
};

std::ostream& operator <<(std::ostream& ofs, const GraphDirection& gr){
    ofs << "The way from: "<<gr.from << " to: "<< gr.to <<" "<< " is: "<< gr.how_much;  
  return ofs; 
}

void ALLGOOD(){
     std::cout<<"ALL GOOD "<< std::endl;
}

