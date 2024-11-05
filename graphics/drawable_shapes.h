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

class NamedCircle : public Circle
{
private:
    std::shared_ptr<Text> text_;
public:
    NamedCircle(Point center, double radius, std::string name);
    std::string ConstructStringRepresentation() const override;
    std::shared_ptr<Text> GetTextLink() const;
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

class NamedLine : public Shape, public Drawable
{
protected:
    Point from_;
    Point to_;
    std::shared_ptr<Text> text_line_;

public:
    std::string MakeLineRepresentation() const;
    NamedLine(Point from, Point to, double weigth);
    std::string MakeTextRepresentation() const;
    std::string ConstructStringRepresentation() const override;
    std::shared_ptr<Text> GetLineText();
};

class NamedArrow : public Drawable
{
public:
    NamedArrow(Point from, Point to, double weigth);
    virtual std::string ConstructStringRepresentation() const override;
    std::shared_ptr<NamedLine> Getline();
    std::shared_ptr<Triangle> GetTriangle();
    std::shared_ptr<Text> GetLineText();

private:
    std::shared_ptr<NamedLine> line_;
    std::shared_ptr<Triangle> triangle_;
};