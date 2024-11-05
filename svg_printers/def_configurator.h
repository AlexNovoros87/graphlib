#include <stdexcept>
#include "../free/freefoo.h"


struct SVGTextPrint
{
   std::string text_fill;
   std::string text_stroke_color;
   double text_stroke_size;
   std::string text_font_family;
   double text_font_size;
};

struct SVGCirlePrint
{
   std::string circle_fill_color;
   std::string circle_stroke_color;
   double circle_stroke_size;
};

struct SVGLinePrint
{
   std::string line_fill;
   std::string line_stroke_color;
   double line_stroke_size;
};

struct SVGTrianglePrint
{
   std::string triangle_fill;
   std::string triangle_stroke_color;
   double triangle_stroke_size;
};

struct SVGNamedLinePrint : public SVGTextPrint, public SVGLinePrint
{
};
struct SVGArrowPrint : public SVGNamedLinePrint, public SVGTrianglePrint
{
};
struct SVGNamedCirclePrint : public SVGCirlePrint, public SVGTextPrint
{
};

struct GCP
{
   static SVGArrowPrint deikstra_arrow_pr_;
   static SVGArrowPrint graph_arrow_pr_;
   static SVGNamedLinePrint graph_line_pr_;
   static SVGNamedCirclePrint graph_tops_pr_;
};

void UpdateSVGPrintDefaults(std::filesystem::path pth);


