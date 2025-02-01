/**
 * \file frefoo.h
 * \brief Свободные служебные функции
 * \details Содержит вспомогательные функции 
 */
#pragma once

#include "structs.h"
//! ЯВЛЯЕТСЯ ЛИ СИМВОЛ РАЗДЕЛИТЕЛЬНЫМ
bool IsTrimmerSymb(char ch);
//! СПЕРЕДИ И СЗАДИ СТРОКИ УБИРАЕТ ЛИШНИЕ ПРОБЕЛЫ
void Trim(std::string &line);
//! ДРОБИТ СТРОКУ ПО ЗАНАКУ "|"
std::vector<std::string> SplitBy(std::string line);
//! ВОЗВРАЩАЕТ МАТРИЦУ size x size СОСТОЯЩЕЙ из infinity()
double_matrix GetCrowlDoubleMaxMatrix(int size);
//!СОЗДАЕТ МАТРИЦУ size x size, bool , равных false
bool_matrix GetCrowlBoolMatrix(int size);
//! ПАРСИТ СТРОКУ И ДЕЛАЕТ СТРУКТУРУ ДЛЯ ЗАГРУЗКИ ДАННЫХ В ГРАФ
GraphDirection MakeOneDir(std::string line);
//! СОЗДАЕТ ПОТОК ДЛЯ ПЕЧАТИ КУДА_ЛИБО
std::ofstream CreateFileStream(const std::filesystem::path &pth, bool trunc);
//! ВОЗВРАЩАЕТ МАТРИЦУ size x size СОСТОЯЩЕЙ из nullptr
const_str_ptr_matrix GetStringPointersMatrix(int size);
//! ВЫВОДИТ СТУКТУРУ GraphDirection В НУЖНЫЙ ПОТОК
std::ostream &operator<<(std::ostream &ofs, const GraphDirection &gr);
//! ЯВЛЯЕТСЯ ЛИ ДАННОЕ ЧИСЛО МАКСИМАЛЬНЫМ DOUBLE
bool IsMaxDouble(double db);
//! ЯВЛЯЕТСЯ ЛИ ОДНО dOUBLE МЕНЬШЕ ДРУГОГО
bool IsLessDouble(double one, double two);
//! РАВНЫ ЛИ 2 ЧИСЛА ТИПА DOUBLE
bool IsEqualDouble(double one, double two);
//! ОТЛАДОЧНАЯ ФУНКЦИЯ
void ALLGOOD();
//! ПРЕДУПРЕЖДАЕТ ПОЛЬЗОВАТЕЛЯ ЧТО ЕСТЬ ЗНАЧЕНИЯ МЕНЬШЕ 0
void WarnValueLess0();


/**
 * \brief Порядковый номер элемента в контейнере
 * \param value Значене которое нужно искать
 * \param container Контейнер
 * \returns Указатель на элемент в контейнере, если order валиден, или nullptr
 */
template <typename Container, typename T>
int GetElementOrder(const T& value, const Container& container){
    auto it = container.find(value);
    if(it == container.end()) {return -1;}
    return std::distance(container.begin(), it);     
}

/**
 * \brief Указатель на элемент в контейнере
 * \param order Порядковый номер
 * \param container Контейнер 
 * \returns Указатель на элемент в контейнере, если order валиден, или nullptr
 */
template <typename Container>
auto GetPointerIfHasContainer(int order, const Container& container)
->const typename std::iterator_traits<decltype(container.begin())>::value_type*
{
    if( (order < 0) || (order + 1 > static_cast<int>(container.size()))){
        return nullptr;
    }
   
   auto it = container.begin();
   std::advance(it, order); 
   return &*it;
} 


