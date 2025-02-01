#include <stdexcept>
#include "../free/freefoo.h"


/**
 * \brief Аттрибуты SVG для стилизации текста
 */
struct SVGTextPrint
{
   //! Цвет заливки
   std::string text_fill;
   //! Цвет обода
   std::string text_stroke_color;
   //! Толшина обода
   double text_stroke_size;
   //! Шрифт
   std::string text_font_family;
   //! Размер шрифта
   double text_font_size;
};

/**
 * \brief Аттрибуты SVG для стилизации круга
 */
struct SVGCirlePrint
{
   //! Цвет заливки
   std::string circle_fill_color;
   //! Цвет обода
   std::string circle_stroke_color;
   //! Толшина обода 
   double circle_stroke_size;
};

/**
 * \brief Аттрибуты SVG для стилизации линий
 */
struct SVGLinePrint
{
   //! Цвет заливки
   std::string line_fill;
   //! Цвет обода
   std::string line_stroke_color;
   //! Толшина обода 
   double line_stroke_size;
};

/**
 * \brief Аттрибуты SVG для стилизации треугольника
 */
struct SVGTrianglePrint
{
   //! Цвет заливки
   std::string triangle_fill;
   //! Цвет обода
   std::string triangle_stroke_color;
   //! Толшина обода 
   double triangle_stroke_size;
};

/**
 * \brief Аттрибуты SVG для стилизации именованной линии
 */
struct SVGNamedLinePrint : public SVGTextPrint, public SVGLinePrint
{
   /*
      std::string text_fill;
      std::string text_stroke_color;
      double text_stroke_size;
      std::string text_font_family;
      double text_font_size;
      std::string line_fill;
      std::string line_stroke_color;
      double line_stroke_size;
   */
};
/**
 * \brief Аттрибуты SVG для стилизации именованной стрелки
 */
struct SVGArrowPrint : public SVGNamedLinePrint, public SVGTrianglePrint
{
   /*
      std::string text_fill;
      std::string text_stroke_color;
      double text_stroke_size;
      std::string text_font_family;
      double text_font_size;
      std::string line_fill;
      std::string line_stroke_color;
      double line_stroke_size;
      std::string triangle_fill;
      std::string triangle_stroke_color;
      double triangle_stroke_size;
   */
};

/**
 * \brief Аттрибуты SVG для стилизации именованного круга
 */
struct SVGNamedCirclePrint : public SVGCirlePrint, public SVGTextPrint
{
   /*
    std::string circle_fill_color;
    std::string circle_stroke_color;
    double circle_stroke_size;
    std::string text_fill;
    std::string text_stroke_color;
    double text_stroke_size;
    std::string text_font_family;
    double text_font_size;
   */
};


/**
 * \brief Аттрибуты SVG для стилизации
 * \details GCP - Global Config Print. Главный объект, который 
 * содержит стили для отрисовки всех SVG элементов
 */
struct GCP
{
   //! КОНФИГ СТИЛЯ ПЕЧАТИ СТРЕЛОК В АЛГОРИТМЕ ДЕЙКСТРЫ
   static SVGArrowPrint deikstra_arrow_pr_;
   //! КОНФИГ СТИЛЯ ПЕЧАТИ СТРЕЛОК В ОТРИСОВКЕ ГРАФА
   static SVGArrowPrint graph_arrow_pr_;
   //! КОНФИГ СТИЛЯ ПЕЧАТИ ЛИНИИ С ТЕКСТОМ В ОТРИСОВКЕ ГРАФА
   static SVGNamedLinePrint graph_line_pr_;
   //! КОНФИГ СТИЛЯ ПЕЧАТИ ВЕРШИН ГРАФА
   static SVGNamedCirclePrint graph_tops_pr_;
};

/**
 * \brief Обновить аттрибуты SVG для стилизации
 * \details Обновляет стилизацию если есть конфигурационный файл стилей
 * \param pth путь к файлу
 */
void UpdateSVGPrintDefaults(std::filesystem::path pth);
