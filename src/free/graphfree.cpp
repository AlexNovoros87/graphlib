#include "freefoo.h"
using namespace std::literals;
const std::string Constants::tr = "true"s;
const std::string Constants::fls = "false"s;
const std::string Constants::inf = "INFINITY"s;
constexpr char Constants::gap = ' ';
constexpr char Constants::delim = '|';
constexpr char Constants::ln = '-';
const std::string Constants::no_ways = "NO WAYS"s;
const std::string Constants::arrow = " --> "s;


//! ЯВЛЯЕТСЯ ЛИ ДАННЫЙ СИМВОЛ КОТОРЫЙ НУЖНО ОБРЕЗАТЬ
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

//! ДВУСТОРОННЯЯ ОЧИСТКА СТОРКИ ОТ ПРОБЕЛОВ И ESC-СИМВОЛОВ
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

//! РАЗДЕЛИТЕЛЬ ПО "|"
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

//! СОЗДАТЬ ЗАГОТОВКУ МАТРИЦЫ РАССТОЯНИЙ
double_matrix GetCrowlDoubleMaxMatrix(int size)
{
    std::vector<double> oneline(size, std::numeric_limits<double>::infinity());
    double_matrix border(size, oneline);
    return border;
}

//!СОЗДАЕТ МАТРИЦУ size x size, из указателей string*, равных nullptr
const_str_ptr_matrix GetStringPointersMatrix(int size){
       std::vector<const std::string*> oneline(size,nullptr);
       const_str_ptr_matrix mtrx(size, oneline);
       return mtrx;
}

//!СОЗДАЕТ МАТРИЦУ size x size, bool , равных false
bool_matrix GetCrowlBoolMatrix(int size)
{
    std::vector<bool> line(size, false);
    return std::vector(size, line);
}

//! ЯВЛЯЕТСЯ ЛИ ДАННОЕ ЧИСЛО МАКСИМАЛЬНЫМ DOUBLE
bool IsMaxDouble(double db)
{
    return std::abs(std::numeric_limits<double>::max() - db) < std::numeric_limits<double>::epsilon();
}

//! ЯВЛЯЕТСЯ ЛИ ОДНО dOUBLE МЕНЬШЕ ДРУГОГО
bool IsLessDouble(double one, double two)
{
    return std::abs(one - two) > std::numeric_limits<double>::epsilon();
}

//! РАВНЫ ЛИ 2 ЧИСЛА ТИПА DOUBLE
bool IsEqualDouble(double one, double two){
     return std::abs(one - two) < std::numeric_limits<double>::epsilon();  
};

//! ПАРСИТ СТРОКУ И ДЕЛАЕТ СТРУКТУРУ ДЛЯ ЗАГРУЗКИ ДАННЫХ В ГРАФ
GraphDirection MakeOneDir(std::string line)
{
    std::vector<std::string> ready_params = SplitBy(std::move(line));
    size_t stod;
    double len = std::stod(ready_params[2], &stod);
    if (stod != ready_params[2].size())
        throw std::invalid_argument("error in making double");
    return {std::move(ready_params[0]), std::move(ready_params[1]), len};
}

//! СОЗДАЕТ ПОТОК ДЛЯ ПЕЧАТИ КУДА_ЛИБО
std::ofstream CreateFileStream(const std::filesystem::path &pth, bool trunc)
{
    auto mode = trunc ? std::ios::trunc : std::ios::app;
    std::ofstream ofs(pth, mode);
    return ofs;
};

//! ВЫВОДИТ СТУКТУРУ GraphDirection В НУЖНЫЙ ПОТОК
std::ostream& operator <<(std::ostream& ofs, const GraphDirection& gr){
    ofs << "The way from: "<<gr.from << " to: "<< gr.to <<" "<< " is: "<< gr.how_much;  
  return ofs; 
}

//! ОТЛАДОЧНАЯ ФУНКЦИЯ
void ALLGOOD(){
     std::cout<<"ALL GOOD "<< std::endl;
}

//! ПРЕДУПРЕЖДАЕТ ПОЛЬЗОВАТЕЛЯ ЧТО ЕСТЬ ЗНАЧЕНИЯ МЕНЬШЕ 0
void WarnValueLess0(){
    std::cerr<<"DETECTED VALUE LESS THAN 0, ALGORITHM CAN WORK INCORRECTLY"<<std::endl;
};







