#include "drawable_shapes.h"
///////////////////////////
/// TRIANGLE
//////////////////////////
Triangle::Triangle(Point v1, Point v2, Point v3)
    : v1_(v1), v2_(v2), v3_(v3)
{
    ChangeFillColour("gray").ChangeStrokeColour("gray");
};

std::string Triangle::ConstructStringRepresentation() const
{
    std::string tmp;
    tmp.append(SVGstrings::sttag).append("polygon").append(SVGstrings::gap);
    tmp.append(MakeParameter("points", PolygonPointsStr(v1_, v2_, v3_)));
    tmp.append(AdditionalModStr()).append(SVGstrings::entag).append(SVGstrings::nesc);
    return tmp;
};

//////////////////////
////NAMED_LINE
/////////////////////
std::string NamedLine::MakeLineRepresentation() const
{
    // <line x1="10" y1="10" x2="80" y2="80" stroke="yellow" />
    std::string tmp;
    tmp.append(StartTag("line"));
    tmp.append(MakeParameter("x1", DoubleToStr(from_.x))).append(SVGstrings::gap);
    tmp.append(MakeParameter("y1", DoubleToStr(from_.y))).append(SVGstrings::gap);
    tmp.append(MakeParameter("x2", DoubleToStr(to_.x))).append(SVGstrings::gap);
    tmp.append(MakeParameter("y2", DoubleToStr(to_.y)));
    tmp.append(AdditionalModStr()).append(SVGstrings::entag).append(SVGstrings::nesc);
    return tmp;
}

NamedLine::NamedLine(Point from, Point to, double weigth)
    : from_(from), to_(to)
{
    Point mid = MidPoint(from, to);
    mid.x += 3.;
    mid.y -= 3.;
    text_line_ = std::make_shared<Text>(DoubleToStr(weigth), std::move(mid));
};

std::string NamedLine::MakeTextRepresentation() const
{
    return (*text_line_).ConstructStringRepresentation();
}

std::string NamedLine::ConstructStringRepresentation() const
{
    std::string tmp;
    tmp.append(MakeLineRepresentation())
        .append(MakeTextRepresentation());
    return tmp;
}

std::shared_ptr<Text> NamedLine::GetLineText()
{
    return text_line_;
}
///////////////////
/// NAMED ARROW
//////////////////
NamedArrow::NamedArrow(Point from, Point to, double weigth)
{
    line_ = std::make_shared<NamedLine>(from, to, weigth);

    std::pair<Point, Point> perpendicularpoints = GetPerpendicularLine(from, to, 7);
    triangle_ = std::make_shared<Triangle>(
        std::move(to), std::move(perpendicularpoints.first),
        std::move(perpendicularpoints.second));
};

std::string NamedArrow::ConstructStringRepresentation() const
{
    std::string tmp;
    tmp.append((*line_).MakeLineRepresentation());
    tmp.append((*triangle_).ConstructStringRepresentation());
    tmp.append((*line_).MakeTextRepresentation());
    return tmp;
};

std::shared_ptr<NamedLine> NamedArrow::Getline()
{
    return line_;
};
std::shared_ptr<Triangle> NamedArrow::GetTriangle()
{
    return triangle_;
}

std::shared_ptr<Text> NamedArrow::GetLineText()
{
    return line_->GetLineText();
}