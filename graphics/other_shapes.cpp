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
////LINE
/////////////////////
std::string Line::ConstructStringRepresentation() const
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

//////////////////////
////NAMED_LINE
/////////////////////

NamedLine::NamedLine(Point from, Point to, double weigth)
{
    Point mid = MidPoint(from, to);
    std::string str = DoubleToStr(weigth);
    if(!IsLessDouble(to.y , from.y)){
        mid.y +=5.;
        str+= 'U';
    }
    else if(IsLessDouble(to.y , from.y)) {
        mid.y -=5.;
        str += 'D';
    }
    text_ = std::make_shared<Text>( str, std::move(mid));
    line_ = std::make_shared<Line>(std::move(from),std::move(to));
};

std::shared_ptr<Text> NamedLine::GetText()
{
    return text_;
}

std::shared_ptr<Line> NamedLine::GetLine() {
    return line_ ;
};
///////////////////
/// NAMED ARROW
//////////////////
NamedArrow::NamedArrow(Point from, Point to, double weigth) : NamedLine(from, to, weigth)
{
    std::pair<Point, Point> perpendicularpoints = GetPerpendicularLine(from, to, 7);
    triangle_ = std::make_shared<Triangle>(
        std::move(to), std::move(perpendicularpoints.first),
        std::move(perpendicularpoints.second));
};

std::shared_ptr<Triangle> NamedArrow::GetTriangle()
{
    return triangle_;
}

