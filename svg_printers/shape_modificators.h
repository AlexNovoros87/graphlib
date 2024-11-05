#pragma once

#include "def_configurator.h"
#include "../graphics/drawable_shapes.h"

void ModifyCircle(Circle &cir, SVGCirlePrint &conf_db);
void ModifyText(Text &txt, SVGTextPrint &conf_db);
void ModifyNamedLine(NamedLine &ln, SVGNamedLinePrint &conf_db);
void ModifyNamedArrow(NamedArrow &arw, SVGArrowPrint &conf_db);
void ModifyNamedCircle(NamedCircle& cir, SVGNamedCirclePrint&conf_db);