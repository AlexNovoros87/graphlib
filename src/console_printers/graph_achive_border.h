#pragma once
#include "../achiveabler/achiveabler.h"

/**
 * \brief Печтать графа в таблицу, представление в виде строки и.т.п
 */
class GraphPrinterAndStrPerfomance
{
    //! Ссылка на граф
    Graph &graph_;
    //! Матрица расстояний в виде вектораа строк
    std::vector<std::string> string_border_matrix_;
    //! Минимальная длина слова (FALSE)
    int max_len_word_ = 5;
    //! Минимальная длина строкового представленмя double (0.000000)
    int max_len_double_ = 8;

    //! Матрица всесов
    std::shared_ptr<double_matrix> weigth_matrix_ = nullptr;
    //! Хранитель достижимости
    std::shared_ptr<Achiveabler> achiveabler_ = nullptr;

    //! Обновить max_len_word_ и max_len_double_
    void UpdateStrLengths();
    //! Используется для изменения max_len_double_
    int DoubleStrSummator(double val);

public:
    //! Конструктор
    GraphPrinterAndStrPerfomance(Graph &gr) : graph_(gr)
    {
        UpdateStrLengths();
    }
    /**
     * \brief Напечатать все пути графа в поток
     * \param ost поток куда печатать
     */
    void PrintDirections(std::ostream &ost) const;
    /**
     * \brief Напечатать все пути графа в файл
     * \param pth путь где создать файл
     * \param trunk уничтожать ли содержимое в файле перед запистью.
     */
    void PrintDirectionsToFile(std::filesystem::path pth, bool trunc) const;
    /**
     * \brief Напечатать матриу достижимости нужного кол-ва шагов в поток
     * \param moves кол-во шагов
     * \param ofs поток для печати.
     */
    void PrintAchiveableMatrix(int moves, std::ostream &ofs);
    /**
     * \brief Напечатать матрицу смежности в поток
     * \param ofs поток
     */
    void PrintBorderMatrix(std::ostream &ofs = std::cout);
    /**
     * \brief Напечатать матриу достижимости нужного кол-ва шагов в файл
     * \param moves кол-во шагов
     * \param pth путь где создать файл
     * \param trunk уничтожать ли содержимое в файле перед запистью.
     */
    void PrintAchiveableMatrixToFile(int moves, std::filesystem::path pth, bool trunc = true);
    /**
     * \brief Напечатать матриу смежности в файл
     * \param pth путь где создать файл
     * \param trunk уничтожать ли содержимое в файле перед запистью.
     */
    void PrintBorderMatrixToFile(std::filesystem::path pth, bool trunc = true);
    /**
     * \brief матрица достижимости в виде строки
     * \param moves на какое количество шагов построить матрицу
     * \returns матрицу достижимости в виде вектора строк
     */
    std::vector<std::string> StringPerfomanceAchiveableMatrix(int moves);
    /**
     * \brief матрица расстояний в виде вектора строк
     * \returns матрицу расстояний в виде вектора строк
     */
    const std::vector<std::string> &StringPerfomanceBorderMatrix();
    /**
     * \brief Матррица смежности (расстояний)
     * \details ПРЕДСТАВЛЕНИЕ ВЕКТОРА ИЗ СТРОК МАТРИЦЫ СМЕЖНОСТИ
     * ПУНКТ А|     1.222|     1.222|
     * ПУНКТ В|     1.222|     1.222|
     * ПУНКТ С|     1.222|     1.222|
     * \returns матрицу достижимости в иде вектора строк
     */
    std::vector<std::string> ContentStrPerfomanceBorder();

    /**
     * \brief Веррнуть матрицу достижимости за lеnght ходов
     * ПРЕДСТАВЛЕНИЕ ВЕКТОРА ИЗ СТРОК МАТРИЦЫ ДОСТИЖИМОСТИ
     *  ПУНКТ А|     true|     false|
     *  ПУНКТ В|     true|     false|
     *  ПУНКТ С|     true|     false|
     * \param moves Максимальная длина слова парименяемого в таблице min 5(FALSE)
     * \returns матрицу достижимости в виде вектора строк
     */
    std::vector<std::string> ContentStrPerfomanceAchiveable(int moves);

private:
    /**
     * \brief Первая линия таблицы
     * \details ВЕРНУТЬ ПЕРВУЮ ЛИНИЮ ДЛЯ ПЕЧАТИ В ФОРМАТЕ
     * |         |    ПУНКТ А|    ПУНКТ B|   ПУНКТ C|
     * \param max Максимальная длина слова парименяемого в таблице min 5(FALSE)
     * \returns |         |    ПУНКТ А|    ПУНКТ B|   ПУНКТ C| - одной стройкой
     */
    std::string HeaderStrPerfomance(int max) const;
};