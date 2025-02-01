#include "shape_modificators.h"
void ModifyCircle(Circle &cir, SVGCirlePrint &conf_db)
{
    cir.ChangeFillColour(conf_db.circle_fill_color)
        .ChangeStrokeColour(conf_db.circle_stroke_color)
        .ChangeStrokeWidth(conf_db.circle_stroke_size);
}

void ModifyText(Text &txt, SVGTextPrint &conf_db)
{
    txt.ChangeStrokeColour(conf_db.text_stroke_color)
        .ChangeFillColour(conf_db.text_fill)
        .ChangeStrokeWidth(conf_db.text_stroke_size);
    txt.SetFont(conf_db.text_font_family)
        .SetFontSize(conf_db.text_font_size);
};

void ModifyNamedLine(NamedLine &ln, SVGNamedLinePrint &conf_db)
{
    ModifyText(*ln.GetText(), conf_db);
    ln.GetLine()->ChangeStrokeColour(conf_db.line_stroke_color)
        .ChangeFillColour(conf_db.line_fill);
};

void ModifyNamedArrow(NamedArrow &arw, SVGArrowPrint &conf_db)
{
    ModifyNamedLine( arw , conf_db);
    arw.GetTriangle()->ChangeStrokeColour(conf_db.triangle_stroke_color);
    arw.GetTriangle()->ChangeFillColour(conf_db.triangle_fill);
}

void ModifyNamedCircle(NamedCircle &cir, SVGNamedCirclePrint &conf_db)
{
    ModifyCircle(*cir.GetCircle() , conf_db);
    ModifyText(*cir.GetText(), conf_db);
}