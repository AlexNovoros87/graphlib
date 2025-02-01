#pragma once
#include "functions_interfaces.h"
/**
 * \file Описывает структуры Для Отрисовки в SVG
 */

/**
 * \brief Описываает Текст
 */
class Text : public Shape, public Drawable
{
private:
    //! Текст
    std::string text_;
    //! Координаты
    Point coordinates_;
    //! Шрифт
    std::string font_;
    //! Размер шрифта
    int font_size_;

public:
    std::string ConstructStringRepresentation() const override;

    /**
     * \brief Конструктор
     * \param text Текст
     * \param coordinates Координаты
     * \param font Шрифт
     * \param font_size Размер шрифта
     */
    Text(std::string text, Point coordinates,
         std::string font = "Arial", int font_size = 10);
    /**
     * \brief Текст
     */
    const std::string &GetText() const;
    /**
     * \brief Шрифт
     */
    const std::string &GetFont() const;
    /**
     * \brief Координаты
     */
    const Point &GetCoordinates() const;
    /**
     * \brief Размер шрифта
     */
    int GetFontSize() const;
    /**
     * \brief Установить размер шрифта
     * \param fz Новый размер шрифта
     */
    Text &SetFontSize(int fz);
    /**
     * \brief Установить шрифт
     * \param fnt новый шрифт
     */
    Text &SetFont(std::string fnt);
};

/**
 * \brief Описывает Круг
 */
class Circle : public Shape, public Drawable
{
protected:
    Point center_;
    double radius_ = 30.;

public:
    /**
     * \brief SVG- описание круга
     */
    std::string SvgCircleRepresentation() const;
    std::string ConstructStringRepresentation() const override;
    /**
     * \brief Конструктор
     * \param center Центр
     * \param radius Радиус
     */
    Circle(Point center, double radius = 10);
    /**
     * \brief ентр круга
     */
    const Point &GetCenterPoint() const;
    /**
     * \brief Радиус круга
     */
    double GetRadius() const;
};

/**
 * \brief Описывает Круг и его название
 */
class NamedCircle
{
private:
    //! Круг
    std::shared_ptr<Circle> circle_;
    //! Текст
    std::shared_ptr<Text> text_;

public:
    /**
     * \brief Конструктор
     * \param center Центр
     * \param radius Радиус
     * \param name Имя круга
     */
    NamedCircle(Point center, double radius, std::string name);
    /**
     * \brief Составнной обхект Текст
     */
    std::shared_ptr<Text> GetText() const;
    /**
     * \brief Составнной обхект Круг
     */
    std::shared_ptr<Circle> GetCircle() const;
};

/**
 * \brief Описывает треугольник
 */
class Triangle : public Shape, public Drawable
{
private:
    Point v1_;
    Point v2_;
    Point v3_;

public:
    /**
     * \brief Конструктор
     * \param v1 Вершина 1
     * \param v2 Вершина 2
     * \param v3 Вершина 3
     */
    Triangle(Point v1, Point v2, Point v3);
    std::string ConstructStringRepresentation() const override;
};

/**
 * \brief Описывает линию
 */
class Line : public Shape, public Drawable
{
protected:
    //! Начальная Точка
    Point from_;
    //! Конечная точка
    Point to_;

public:
     /**
     * \brief Конструктор
     * \param from Первая точка прямой
     * \param to Вторая точка прямой
     */
    Line(Point from, Point to) : from_(from), to_(to) {};
    std::string ConstructStringRepresentation() const override;
};

/**
 * \brief Описывает линию с названием
 */
class NamedLine
{
protected:
    //! Линия
    std::shared_ptr<Line> line_;
    //! Текст
    std::shared_ptr<Text> text_;

public:
    /**
     * \brief Конструктор
     * \param from Первая точка прямой
     * \param to Вторая точка прямой
     * \param weight расстояние от from до to (значение из графа)
     */
    NamedLine(Point from, Point to, double weigth);
   /**
     * \brief Составнной обхект Текст
     */
    std::shared_ptr<Text> GetText();
     /**
     * \brief Составнной обхект Линия
     */
    std::shared_ptr<Line> GetLine();
};

/**
 * \brief Описывает "стрелку" с названием
 */
class NamedArrow : public NamedLine
{
public:
    /**
     * \brief Конструктор
     * \param from Первая точка прямой
     * \param to Вторая точка прямой
     * \param weight расстояние от from до to (значение из графа)
     */
    NamedArrow(Point from, Point to, double weigth);
    /**
     * \brief составной обьект треугольник
     */
    std::shared_ptr<Triangle> GetTriangle();

private:
    //! Треугольник
    std::shared_ptr<Triangle> triangle_;
};