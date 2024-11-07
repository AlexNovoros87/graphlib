#pragma once
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <memory>
#include "../free/freefoo.h"
struct Point
{
    double x, y;
};

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

std::vector<Point> DistributePointsOnCircle(Point center, double radius, int numPoints);
std::string ToQuote(const std::string &str);
std::string MakeParameter(const std::string &name, const std::string &value);
std::string DoubleToStr(double db);
std::pair<Point, Point> GetPerpendicularLine(const Point &p1, const Point &p2, double length = 1.0);
std::string PolygonPoint(const Point &p);
Point MidPoint(const Point &p1, const Point &p2);
std::string StartTag(std::string tag);
std::string GetMainOpenTagLine(double w, double h);

template <typename... Points>
std::string PolygonPointsStr(Points... points)
{
    std::string tmp;
    (..., (tmp.append(PolygonPoint(points)).append(" ")));
    tmp.pop_back();
    return tmp;
};

class Drawable
{
public:
    virtual std::string ConstructStringRepresentation() const = 0;
    void Draw(std::ostream &os) const;
    virtual ~Drawable(){};
};

class Shape
{
protected:
    std::string fill_ = "black";
    std::string stroke_ = "green";
    double stroke_wigth_ = 1.;
    std::string empty_ = {};
    std::string AdditionalModStr() const;

public:
    virtual ~Shape() {};
    Shape &ChangeFillColour(std::string color);
    Shape &ChangeStrokeColour(std::string color);
    Shape &ChangeStrokeWidth(double width);
    double StrokeWidth() const;
    const std::string &GetStrokeColor() const;
    const std::string &GetFillColor() const;
};


