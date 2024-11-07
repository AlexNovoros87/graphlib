#pragma once
#include "functions_interfaces.h"

class Text : public Shape, public Drawable
{
private:
    std::string text_;
    Point coordinates_;
    std::string font_;
    int font_size_;

public:
    std::string ConstructStringRepresentation() const override;

    Text(std::string text, Point coordinates,
         std::string font = "Arial", int font_size = 10);

    const std::string &GetText() const;
    const std::string &GetFont() const;
    const Point &GetCoordinates() const;
    int GetFontSize() const;
    Text& SetFontSize(int fz);
    Text& SetFont(std::string fnt);

};

class Circle : public Shape, public Drawable
{
protected:
    Point center_;
    double radius_ = 30.;
public:
    std::string SvgCircleRepresentation() const;
    std::string ConstructStringRepresentation() const override;
    Circle(Point center, double radius = 10);
    const Point &GetCenterPoint() const;
    double GetRadius() const;

};

class NamedCircle 
{
private:
     std::shared_ptr<Circle> circle_;
    std::shared_ptr<Text> text_;
public:
    NamedCircle(Point center, double radius, std::string name);
    std::shared_ptr<Text> GetText() const;
    std::shared_ptr<Circle> GetCircle() const;
};

class Triangle : public Shape, public Drawable
{
private:
    Point v1_;
    Point v2_;
    Point v3_;

public:
    Triangle(Point v1, Point v2, Point v3);
    std::string ConstructStringRepresentation() const override;
};


class Line : public Shape, public Drawable
{
protected:
    Point from_;
    Point to_;
public:
   
    Line(Point from, Point to) : from_(from),to_(to){};
    std::string ConstructStringRepresentation() const override;
};


class NamedLine 
{
protected:
    std::shared_ptr<Line> line_;
    std::shared_ptr<Text> text_;

public:
    NamedLine(Point from, Point to, double weigth);
    std::shared_ptr<Text> GetText();
    std::shared_ptr<Line> GetLine();

};

class NamedArrow : public NamedLine
{
public:
    NamedArrow(Point from, Point to, double weigth);
    std::shared_ptr<Triangle> GetTriangle();
private:
    std::shared_ptr<Triangle> triangle_;
};