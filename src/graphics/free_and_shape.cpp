#include "functions_interfaces.h"

constexpr double PI = 3.14159265358979323846;
const std::string SVGstrings::nesc = "\n";
const std::string SVGstrings::sttag = "<";
const std::string SVGstrings::entag = "/>";
const std::string SVGstrings::gap = " ";
const std::string SVGstrings::circle_svg = "circle";
const std::string SVGstrings::text_svg = "text";
const std::string SVGstrings::maintagclose = "\n\n\n</svg>";

Point MidPoint(const Point &p1, const Point &p2)
{
    // Находим середину отрезка
    double midX = (p1.x + p2.x) / 2;
    double midY = (p1.y + p2.y) / 2;
    return {midX, midY};
};

std::string StartTag(std::string tag)
{
    std::string tmp = SVGstrings::sttag + tag + SVGstrings::gap;
    return tmp;
};

std::vector<Point> DistributePointsOnCircle(Point center, double radius, int numPoints)
{
    if(numPoints == 0) {std::runtime_error("numPoints is 0");}
    std::vector<Point> points;
    for (int i = 0; i < numPoints; ++i)
    {
        double angle = 2 * PI * i / numPoints;
        double x = center.x + radius * cos(angle);
        double y = center.y + radius * sin(angle);
        points.push_back({x, y});
    }
    return points;
}

std::pair<Point, Point> GetPerpendicularLine(const Point &p1, const Point &p2, double length)
{
    // Находим середину отрезка
    double midX = (p1.x + p2.x) / 2;
    double midY = (p1.y + p2.y) / 2;

    // Вычисляем вектор исходной линии
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    // Нормализуем вектор перпендикуляра
    double perpDx = -dy;
    double perpDy = dx;
    double norm = std::sqrt(perpDx * perpDx + perpDy * perpDy);
    perpDx /= norm;
    perpDy /= norm;

    // Вычисляем точки перпендикулярной линии
    Point perpPoint1 = {midX + perpDx * length / 2, midY + perpDy * length / 2};
    Point perpPoint2 = {midX - perpDx * length / 2, midY - perpDy * length / 2};
    return {perpPoint1, perpPoint2};
}

std::string ToQuote(const std::string &str)
{
    return "\"" + str + "\"";
}
std::string MakeParameter(const std::string &name, const std::string &value)
{
    return name + '=' + ToQuote(value);
};
std::string DoubleToStr(double db)
{
    std::string tmp = std::to_string(db);
    tmp = tmp.substr(0, tmp.size() - 4);
    return tmp;
}

std::string PolygonPoint(const Point &p)
{
    std::string tmp = DoubleToStr(p.x);
    tmp.push_back(',');
    tmp.append(DoubleToStr(p.y));
    return tmp;
};

void Drawable::Draw(std::ostream &os) const
{
    os << ConstructStringRepresentation();
};

std::string GetMainOpenTagLine(double w, double h){
  std::string tmp = "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
  tmp.append(MakeParameter("width", DoubleToStr(w))).append(SVGstrings::gap);
  tmp.append(MakeParameter("height", DoubleToStr(h))).push_back('>');
  tmp.append("\n\n\n");
  return tmp;
}

///////////////////////////////////////////////////

Shape &Shape::ChangeFillColour(std::string color)
{
    fill_ = std::move(color);
    return *this;
}

Shape &Shape::ChangeStrokeColour(std::string color)
{
    stroke_ = std::move(color);
    return *this;
}

Shape &Shape::ChangeStrokeWidth(double width)
{
    stroke_wigth_ = width;
    return *this;
}

double Shape::StrokeWidth() const { return stroke_wigth_; }
const std::string &Shape::GetStrokeColor() const { return stroke_; }
const std::string &Shape::GetFillColor() const { return fill_; }

std::string Shape::AdditionalModStr() const
{
    std::string tmp;
    tmp.append(SVGstrings::nesc).append(MakeParameter("fill", fill_));
    tmp.append(SVGstrings::gap).append(MakeParameter("stroke", stroke_));
    tmp.append(SVGstrings::gap);
    tmp.append(MakeParameter("stroke-width", DoubleToStr(stroke_wigth_)));
    return tmp;
}