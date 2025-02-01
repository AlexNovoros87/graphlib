#pragma once
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <memory>
#include "../free/freefoo.h"

/**
 * \brief Точка в двухмерном пространстве
 * \param x Координата Х
 * \param y Координата Y
 */
struct Point
{
    double x, y;
};

/**
 * \brief Структура для хранения строк для работы с SVG
 * \param nesc  "\n";
 * \param sttag  "<";
 * \param entag  "/>";
 * \param gap  " ";
 * \param circle_svg  "circle";
 * \param text_svg  "text";
 * \param maintagclose "\n\n\n</svg>";
 */
struct SVGstrings
{
    static const std::string nesc;
    static const std::string sttag;
    static const std::string entag;
    static const std::string gap;
    static const std::string circle_svg;
    static const std::string text_svg;
    static const std::string maintagclose;

private:
    SVGstrings() {};
};

/**
 * \brief Расположить точки равномерно по кругу
 * \param center центр относительно которого распологать точки
 * \param radius радиус
 * \param numPoints количество точек
 * \returns Вектор точек, расположенных равномерно по кругу
 */
std::vector<Point> DistributePointsOnCircle(Point center, double radius, int numPoints);

/**
 * \brief заключает строку в кавычки
 * \param str строка, которую нужно заключить в кавычки
 * \returns "str"
 */
std::string ToQuote(const std::string &str);

/**
 * \brief сделать строку вида " имя параметра = "значение" "
 * \param name имя параметра
 * \param value значение параметра
 * \returns строку вида " имя параметра = "значение" "
 */
std::string MakeParameter(const std::string &name, const std::string &value);

/**
 * \brief Превращает число с плавающей точкой в строку
 * \details и возвращает целую часть и 2 знака дробной части
 * \param db число которе нужно преобразовать
 * \returns строку вида "0.00"
 */
std::string DoubleToStr(double db);

/**
 * \brief Строит перпендекулярную линию
 * \param p1 точка исходной линии 1
 * \param p2 точка исходной линии 2
 * \param lehgth длина линии
 * \returns Точки препендекуляной линии
 */
std::pair<Point, Point> GetPerpendicularLine(const Point &p1, const Point &p2, double length = 1.0);

/**
 * \brief Сделать строку для преставления точки в svg - многоугольнике
 * \param p толчка
 * \returns  Пример: "123.45,678.90"
 */
std::string PolygonPoint(const Point &p);

/**
 * \brief Вычисляет центр прямой
 * \param p1 точка исходной линии 1
 * \param p2 точка исходной линии 2
 * \returns Центральную точку
 */
Point MidPoint(const Point &p1, const Point &p2);

/**
 * \brief Возвраащает открытие тега в виде строки
 * \param tag имя тега
 * \returns "< tagname "
 */
std::string StartTag(std::string tag);

/**
 * \brief Открывает начало SVG-файла
 * \param w ширина изображения
 * \param h высота изображения
 * \returns начало SVG-файла
 */
std::string GetMainOpenTagLine(double w, double h);

/**
 * \brief Возващаает в виде строки набор точек
 * \param points Набор точек
 * \returns Пример: "123.45,678.90 123.45,678.90 123.45,678.90 ...."
 */
template <typename... Points>
std::string PolygonPointsStr(Points... points)
{
    std::string tmp;
    (..., (tmp.append(PolygonPoint(points)).append(" ")));
    tmp.pop_back();
    return tmp;
};

/**
 * \brief Интерфейс объекта который может себя "Нарисовать"
 */
class Drawable
{
public:
    /**
     * \brief Обьект создает свое строковое представление
     */
    virtual std::string ConstructStringRepresentation() const = 0;
    /**
     * \brief Объект отрисовывает себя в заданный поток
     * \param os поток куда отрисовывать объект
     */
    void Draw(std::ostream &os) const;
    virtual ~Drawable() {};
};

/**
 * \brief Интерфейс объекта который является фигурой
 */
class Shape
{
protected:
    //! Заливкаа
    std::string fill_ = "black";
    //! Обод
    std::string stroke_ = "green";
    //! Толщина обода
    double stroke_wigth_ = 1.;
    //! Сконструировать свои параметры отображения SVG stroke, fill, stroke_wigth_
    std::string AdditionalModStr() const;

public:
    virtual ~Shape() {};
    /**
     * \brief Сменить цвет заливки
     * \param color цвет
     */
    Shape &ChangeFillColour(std::string color);

    /**
     * \brief Сменить цвет обода
     * \param color цвет
     */
    Shape &ChangeStrokeColour(std::string color);

    /**
     * \brief Сменть толщину обода
     * \param толшина
     */
    Shape &ChangeStrokeWidth(double width);

    /**
     * \brief Толщина обода
     */
    double StrokeWidth() const;

    /**
     * \brief Цвет обода
     */
    const std::string &GetStrokeColor() const;

    /**
     * \brief Цвет заливки
     */
    const std::string &GetFillColor() const;
};
