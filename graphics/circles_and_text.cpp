#include "drawable_shapes.h"

//////////////////////
// CIRCLE
/////////////////////

std::string Circle::SvgCircleRepresentation() const
{
    std::string tmp;
    tmp.append(SVGstrings::sttag).append(SVGstrings::circle_svg).append(SVGstrings::gap);
    tmp.append(MakeParameter("cx", DoubleToStr(center_.x))).append(SVGstrings::gap);
    tmp.append(MakeParameter("cy", DoubleToStr(center_.y))).append(SVGstrings::gap);
    tmp.append(MakeParameter("r", DoubleToStr(radius_))).append(SVGstrings::gap);
    tmp.append(AdditionalModStr()).append(SVGstrings::gap);
    tmp.append(SVGstrings::entag).append(SVGstrings::nesc);
    return tmp;
}

std::string Circle::ConstructStringRepresentation() const
{
    return SvgCircleRepresentation();
}

Circle::Circle(Point center, double radius)
    : center_(center), radius_(radius) {};

const Point &Circle::GetCenterPoint() const { return center_; }
double Circle::GetRadius() const { return radius_; }
//////////////////////
// NAMED CIRCLE
/////////////////////
std::string NamedCircle::ConstructStringRepresentation() const
{
    std::string tmp;
    tmp.append(SvgCircleRepresentation());
    tmp.append((*text_).ConstructStringRepresentation());
    return tmp;
}

NamedCircle::NamedCircle(Point center, double radius, std::string name)
    : Circle(center, radius)
{
    Point p = center;
    p.y -= radius_ + 2;
    text_ = std::make_shared<Text>(name, p);
}

std::shared_ptr<Text> NamedCircle::GetTextLink() const
{
    return text_;
}

/////////////////////////
// TEXT
////////////////////////
std::string Text::ConstructStringRepresentation() const
{
    std::string tmp;
    tmp.append(SVGstrings::sttag).append("text").append(SVGstrings::gap);
    tmp.append(MakeParameter("x", DoubleToStr(coordinates_.x))).append(SVGstrings::gap);
    tmp.append(MakeParameter("y", DoubleToStr(coordinates_.y)));
    tmp.append(AdditionalModStr()).append(SVGstrings::nesc);
    tmp.append(MakeParameter("font-family", font_)).append(SVGstrings::gap);
    tmp.append(MakeParameter("font-size", std::to_string(font_size_))).append(SVGstrings::gap).push_back('>');
    tmp.append(SVGstrings::nesc).append(text_).append(SVGstrings::nesc).append("</text>").append(SVGstrings::nesc);
    return tmp;
};

Text::Text(std::string text, Point coordinates,
           std::string font, int font_size)
    : text_(std::move(text)), font_(std::move(font)),
      font_size_(font_size), coordinates_(coordinates) {};

const std::string &Text::GetText() const { return text_; }
const std::string &Text::GetFont() const { return font_; }
const Point &Text::GetCoordinates() const { return coordinates_; }
int Text::GetFontSize() const { return font_size_; }

Text &Text::SetFontSize(int fz)
{
    font_size_ = fz;
    return *this;
}

Text &Text::SetFont(std::string fnt)
{
    font_ = std::move(fnt);
    return *this;
}
