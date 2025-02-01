#pragma once
#include "../graphics/drawable_shapes.h"
#include "../routers/deikstrarouter.h"
#include "../graphics/shape_modificators.h"

using PointPositionsMap = std::unordered_map<const std::string *, Point, Hasher>;

/**
 * \brief Печатает все элементы Drawable
 * \param container контейнер с обьектами, которые нужно отрисовать
 * \param os поток для отрисовки
 */
template <template <typename, typename> typename Container, typename Drawable>
void PrintDrawable(const Container<Drawable, std::allocator<Drawable>> &container, std::ostream &os)
{
    for (const auto &item : container)
    {
        item->Draw(os);
    }
}

/**
 * \brief Базовый класс для SVG отрисовки графа или маршрута на основе маршрутизатора
 */
class PrinterSVGbase
{
public:
    PrinterSVGbase(Graph &source_graph);
    virtual ~PrinterSVGbase() {};

protected:
    //! ГРАФ
    Graph &source_graph_;
    //! СТОРОНА КВАДРАТА ДЛЯ ПЕЧАТИ
    double square_width_;
    //! ПОГРЕШНОСТЬ ОТСТУПА ПЕЧАТИ
    const double diff = 60.;
    //! ИМЯ ВЕРШИНЫ - КООРДИНАТА НА КРУГЕ
    PointPositionsMap point_positions_;
    //! ГРАФ
    auto &_Graph() const;
    /*
    Является обьект дугой или ребром
    true - дуга (двунаправленное расстояние)
    false - ребро (однонаправленное расстояние)
    */
    bool IsEdge(const std::string *from, const std::string *to) const;
    //! НАРИСОВАТЬ ДУГИ И РЕБРА
    virtual void DrawEdgesAndArcs(std::ostream &os, std::vector<std::shared_ptr<Text>> &texts) const;
    //! НАРИСОВАТЬ ДУГИ И РЕБРА
    void DrawEA(std::ostream &os, BoolGraph &visited, std::vector<std::shared_ptr<Text>> &texts) const;
    //! ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА
    void Init();
};

/**
 * \brief Класс для отрисовки графа в SVG
 */
class PrinterSVGGraph : public PrinterSVGbase
{
public:
    void Draw(std::ofstream &os);
};

/**
 * \brief Класс для отрисовки графа в SVG + Маршрут по Алгоритму дейкстры
 */
class DeikstraRoutePrinter : public PrinterSVGbase
{
private:
    //! РОУТЕР
    std::shared_ptr<DeikstraRouter> router_;
    std::vector<NamedArrow> GetWayAndUpdateVisited(const std::string &from,
                                                   const std::string &to, BoolGraph &visited) const;
    //! НАРИСОВАТЬ ДУГИ И РЕБРА(С МАРШРУТАМИ)
    void DrawEdgesAndArcs(std::ostream &os, const std::string &from, const std::string &to,
                          std::vector<std::shared_ptr<Text>> &texts) const;

public:
    /**
     * \brief Отрисовать граф а на нем маршрут
     * \param from Начальная точка маршрута
     * \param to Конечная точка маршрута
     * \param os Поток для отрисовки
     */
    void DrawWithGraph(std::ostream &os, const std::string &from, const std::string &to) const;

    /**
     * \brief Отрисовать только маршрут
     * \param from Начальная точка маршрута
     * \param to Конечная точка маршрута
     * \param os Поток для отрисовки
     */
    void DrawOnlyWay(std::ostream &os, const std::string &from, const std::string &to) const;

    DeikstraRoutePrinter(Graph &source_graph, bool economy_memory = false);
};
