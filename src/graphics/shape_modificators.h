#pragma once

#include "def_configurator.h"
#include "../graphics/drawable_shapes.h"

/**
 * \brief Модифицировать круг
 * \param cir сслылка на круг, который нужно модифицировать
 * \param conf_db структура откуда взять стили для оформления
 */
void ModifyCircle(Circle &cir, SVGCirlePrint &conf_db);

/**
 * \brief Модифицировать текст
 * \param cir сслылка на текст , который нужно модифицировать
 * \param conf_db структура откуда взять стили для оформления
 */
void ModifyText(Text &txt, SVGTextPrint &conf_db);

/**
 * \brief Модифицировать линию 
 * \param cir сслылка на линию , который нужно модифицировать
 * \param conf_db структура откуда взять стили для оформления
 */
void ModifyNamedLine(NamedLine &ln, SVGNamedLinePrint &conf_db);

/**
 * \brief Модифицировать стрелку 
 * \param cir сслылка на стрелку , который нужно модифицировать
 * \param conf_db структура откуда взять стили для оформления
 */
void ModifyNamedArrow(NamedArrow &arw, SVGArrowPrint &conf_db);

/**
 * \brief Модифицировать круг с именем 
 * \param cir сслылка на круг с именем , который нужно модифицировать
 * \param conf_db структура откуда взять стили для оформления
 */
void ModifyNamedCircle(NamedCircle& cir, SVGNamedCirclePrint&conf_db);