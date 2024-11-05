#pragma once
#include "../structs.h"

// ЯВЛЯЕТСЯ ЛИ СИМВОЛ РАЗДЕЛИТЕЛЬНЫМ
bool IsTrimmerSymb(char ch);
// СПЕРЕДИ И СЗАДИ СТРОКИ УБИРАЕТ ЛИШНИЕ ПРОБЕЛЫ
void Trim(std::string &line);
// ДРОБИТ СТРОКУ ПО ЗАНАКУ "|"
std::vector<std::string> SplitBy(std::string line);
// ВОЗВРАЩАЕТ ЗАГОТОВКУ МАТРИЦЫ СМЕЖНОСТИ
std::vector<std::vector<double>> GetCrowlDoubleMaxMatrix(int size);
// BОЗВРАЩАЕТ ЗАГОТОВКУ МАТРИЦЫ ДОСТИЖИМОСТИ
std::vector<std::vector<bool>> GetCrowlBoolMatrix(int size);
// ПАРСИТ СТРОКУ И ДЕЛАЕТ СТРУКТУРУ ДЛЯ ЗАГРУЗКИ ДАННЫХ В ГРАФ
GraphDirection MakeOneDir(std::string line);

std::ofstream CreateFileStream(const std::filesystem::path &pth, bool trunc);

std::ostream &operator<<(std::ostream &ofs, const GraphDirection &gr);

bool IsMaxDouble(double db);
bool IsLessDouble(double one, double two);
bool IsEqualDouble(double one, double two);
void ALLGOOD();