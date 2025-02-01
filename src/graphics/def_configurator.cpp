#include "def_configurator.h"

using ChangeFoo = std::function<void(std::string str)>;
using ChangeDir = std::unordered_map<std::string, const std::unordered_map<std::string, ChangeFoo> &>;

//! СДЕЛАТЬ DOUBLE ИЗ STRING 
double TryMakeDouble(const std::string &str)
{
    std::string ex = str + " can not be as string";
    if (str.empty())
    {
        throw std::logic_error(ex);
    }
    size_t buf;
    double dbl = std::stod(str, &buf);
    if (buf != str.size())
    {
        throw std::logic_error(ex);
    }
    return dbl;
}

//! ОБЪЕКТ ДЕФОЛТНЫХ КОНФИГУРАЦИЙ ПЕЧАТИ ЛИНИЙ ГРАФА
SVGNamedLinePrint GCP::graph_line_pr_ = {"white",
                                         "white", 1., "Arial", 10., "gray", "gray", 1.};

//! ОБЪЕКТ ДЕФОЛТНЫХ КОНФИГУРАЦИЙ ПЕЧАТИ СТРЕЛОК АЛГОРИТМАА ДЕЙКСТРЫ
SVGArrowPrint GCP::deikstra_arrow_pr_ = {"cyan",
                                         "cyan", 1., "Arial", 10., "yellow", "yellow", 1., "yellow", "yellow", 1.};

//! ОБЪЕКТ ДЕФОЛТНЫХ КОНФИГУРАЦИЙ ПЕЧАТИ СТРЕЛОК ГРАФА
SVGArrowPrint GCP::graph_arrow_pr_ = {"white", "white", 1., "Arial", 10., "gray", "gray", 1., "gray", "orange", 1.};

//! ОБЪЕКТ ДЕФОЛТНЫХ КОНФИГУРАЦИЙ ПЕЧАТИ ВЕРШИН ГРАФА
SVGNamedCirclePrint GCP::graph_tops_pr_ = {"black", "green", 1., "red",
                                           "red", 1., "Arial", 10.};

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ ТЕКСТА.*/ 
void ProvideChTextLampdas(std::unordered_map<std::string, ChangeFoo> &client, SVGTextPrint &tpr)
{
    client.insert(
        {"text_fill", [&](std::string str)
         { tpr.text_fill = std::move(str); }});

    client.insert(
        {"text_stroke_color", [&](std::string str)
         { tpr.text_stroke_color = std::move(str); }});

    client.insert(
        {"text_stroke_size",
         [&](std::string str)
         {
             tpr.text_stroke_size = TryMakeDouble(str);
         }});

    client.insert(
        {"text_font_family", [&](std::string str)
         { tpr.text_font_family = std::move(str); }}

    );

    client.insert(
        {"text_font_size",
         [&](std::string str)
         {
             tpr.text_font_size = TryMakeDouble(str);
         }});
}

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ КРУГА.*/ 
void ProvideChCirceLampdas(std::unordered_map<std::string, ChangeFoo> &client, SVGCirlePrint &cpr)
{
    client.insert(
        {"circle_fill_color", [&cpr](std::string str)
         { cpr.circle_fill_color = std::move(str); }});

    client.insert(
        {"circle_stroke_color", [&cpr](std::string str)
         { cpr.circle_stroke_color = std::move(str); }});

    client.insert(
        {
            "circle_stroke_size",
            [&cpr](std::string str)
            { cpr.circle_stroke_size = TryMakeDouble(str); },
        });
}

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ ЛИНИИ.*/ 
void ProvideChLineLampdas(std::unordered_map<std::string, ChangeFoo> &client, SVGLinePrint &lpr)
{
    client.insert(
        {"line_fill", [&lpr](std::string str)
         { lpr.line_fill = std::move(str); }});

    client.insert(
        {"line_stroke_color", [&lpr](std::string str)
         { lpr.line_stroke_color = std::move(str); }});

    client.insert(
        {
            "line_stroke_size",
            [&lpr](std::string str)
            { lpr.line_stroke_size = TryMakeDouble(str); },
        });
}

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ ТРЕУГОЛЬНИКА.*/ 
void ProvideChTriangleLampdas(std::unordered_map<std::string, ChangeFoo> &client, SVGTrianglePrint &tpr)
{
    client.insert(
        {"triangle_fill", [&tpr](std::string str)
         { tpr.triangle_fill = std::move(str); }});

    client.insert(
        {"triangle_stroke_color", [&tpr](std::string str)
         { tpr.triangle_stroke_color = std::move(str); }});

    client.insert(
        {"triangle_stroke_size",
         [&tpr](std::string str)
         { tpr.triangle_stroke_size = TryMakeDouble(str); }});
}

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ ВЕРШИН ГРАФА.*/ 
std::unordered_map<std::string, ChangeFoo> GraphTopsLampdas(SVGNamedCirclePrint &ncp)
{
    std::unordered_map<std::string, ChangeFoo> tmp;
    ProvideChTextLampdas(tmp, GCP::graph_tops_pr_);
    ProvideChCirceLampdas(tmp, ncp);
    return tmp;
}

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ ИМЕНОВАНЫХ ЛИНИЙ ГРАФА.*/ 
std::unordered_map<std::string, ChangeFoo> LineLampdas(SVGNamedLinePrint &lpr)
{
    std::unordered_map<std::string, ChangeFoo> tmp;
    ProvideChTextLampdas(tmp, lpr);
    ProvideChLineLampdas(tmp, lpr);
    return tmp;
}

/* ФУНКЦИЯ ПРИВЯЗЫВАЮЩАЯ ЛЯМБДЫ В MAP<STRING, CHANGEFOO> КОТОРЫЕ 
ОТВЕЧАЮТ ЗА СТИЛЬ ОТРИСОВКИ ОДНОНАПРАВЛЕНЫХ НАПРАВЛЕНИЙ(СТРЕЛОК) ГРАФА.*/ 
std::unordered_map<std::string, ChangeFoo> ArrowLampdas(SVGArrowPrint &arrow)
{
    std::unordered_map<std::string, ChangeFoo> tmp = LineLampdas(arrow);
    ProvideChTriangleLampdas(tmp, arrow);
    return tmp;
}

/*
ЗАГОТОВКИ ДЛЯ ChangeDir def_configurator_
*/
std::unordered_map<std::string, ChangeFoo> deikstra_arrow_conf_;
std::unordered_map<std::string, ChangeFoo> graph_arrow_conf_;
std::unordered_map<std::string, ChangeFoo> graph_line_conf_;
std::unordered_map<std::string, ChangeFoo> graph_tops_conf_;


/*ГЛАВНЫЙ ОБЬЕКТ ОТВЕЧАЮЩИЙ ЗА ЗАДАЧУ СТИЛЕЙ ОТРИСОВКИ
 ПРИМЕР: 
 ЗАДАТЬ ЧЕРНЫЙ ЦВЕТ ТЕКСТА В ОТРИСОВКЕ ВЕРШИН - 
 def_configurator_.at("graph_tops").at("text_fill")("black");
*/
ChangeDir def_configurator_ = {

    /*ЛИНИЯ В ОТРИСОВКЕ ГРАФА*/
    {"graph_line", graph_line_conf_},
    /*СТРЕЛА В ОТРИСОВКЕ ГРАФА*/
    {"graph_arrow", graph_arrow_conf_},
    /*СТРЕЛКА В ОТРИСОВКЕ МАРШРУТА ДЕЙКСТРЫ*/
    {"deikstra_arrow", deikstra_arrow_conf_},
    /*ВЕРШИНЫ В ОТРИСОВКЕ ГРАФА*/
    {"graph_tops", graph_tops_conf_}};

/*КОНФИГУРИРУЕТ ОБЪЕКТ , УПРАВЛЯЮЩИЙ ФУНКЦИЯМИ
ЗАДАНИЕЯ СТИЛЕЙ */   
void ProvideDefConfigurarorLampdas()
{
    //ПРИВЯЗЫВАЕМ ЛЯБДЫ ДЛЯ УПРАВЛЕНИЯ СТИЛЯМИ СТРЕЛОК АЛГОРИТМА ДЕЙКСТРЫ
    deikstra_arrow_conf_ = ArrowLampdas(GCP::deikstra_arrow_pr_);
     //ПРИВЯЗЫВАЕМ ЛЯБДЫ ДЛЯ УПРАВЛЕНИЯ СТИЛЯМИ СТРЕЛОК ГРАФА
    graph_arrow_conf_ = ArrowLampdas(GCP::graph_arrow_pr_);
    //ПРИВЯЗЫВАЕМ ЛЯБДЫ ДЛЯ УПРАВЛЕНИЯ СТИЛЯМИ ЛИНИЙ ГРАФА
    graph_line_conf_ = LineLampdas(GCP::graph_line_pr_);
    //ПРИВЯЗЫВАЕМ ЛЯБДЫ ДЛЯ УПРАВЛЕНИЯ СТИЛЯМИ ВЕРШИН ГРАФА
    graph_tops_conf_ = GraphTopsLampdas(GCP::graph_tops_pr_);
}

//ДОЛОЖИТЬ ОБ ОШИБКЕ
void ReportErrorLine(const std::string &param, int where)
{
    std::cerr << " mistake on  " << param << " on line " << where << std::endl;
}
//ВЫПОЛНИТЬ КОМАНДУ ПО ИЗМЕНЕНИЮ СТИЛЯ
void TryExecuteCommand(std::vector<std::string> &&params, int line)
{
    /*provide_conf = false ОЗНАЧАЕТ ЧТО ProvideDefConfigurarorLampdas();
     НЕ ЗАПУСКАЛАСЬ И static СОХРАНЯЕТ СОСТОЯНИЕ TRUE ПОСЛЕ ПЕРВОГО ЗАПУСКА*/
    static bool provide_conf = false;
    //std::cerr<<provide_conf;
    
    if(!provide_conf){
          ProvideDefConfigurarorLampdas();
          provide_conf = true;
    }
    
    if (def_configurator_.count(params[0]) > 0)
    {
        if (def_configurator_.at(params[0]).count(params[1]) > 0)
        {
            try
            {
                //ЗАДАЕМ ТОТ ИЛИ ИНОЙ СТИЛЬ
                def_configurator_.at(params[0]).at(params[1])(params[2]);
            }
            catch (const std::exception &ex)
            {
                ReportErrorLine(std::string(ex.what()), line);
            }
        }
        else
        {
            ReportErrorLine(params[1], line);
        }
    }
    else
    {
        ReportErrorLine(params[0], line);
    }
}

void UpdateSVGPrintDefaults(std::filesystem::path pth)
{
    //ЛЕКСИЧЕСКИ НОРМАЛИЗУЕМ ПУТЬ
    pth.lexically_normal();
    //ОТКРЫВАЕМ ПОТОК ДЛЯ ЧТЕНИЯ ИЗ ФАЙЛА
    std::ifstream ifs(std::move(pth));
    //ЕСЛИ ЧТО С ПОТОКОМ - ВЫХОДИМ
    if (!ifs)
    {
        return;
    }
    //ВРЕМЕННАЯ ПЕРЕМЕННАЯ
    std::string tmp;
    //СЧЕТЧИК ЛИНИЙ
    int line_counter = 0;
    //ПОКА НЕ КОНЕЦ ФАЙЛА
    while (!ifs.eof())
    {
        //ЧИТАЕМ ЛИНИЮ
        std::getline(ifs, tmp);
        //ОБРЕЗАЕМ ЛИШНЕЕ ПО КРАЯМ
        Trim(tmp);
        //ИНКРЕМЕНИРУЕМ СЧЕТЧИК ЛИНИЙ
        ++line_counter;
        //ЕСЛИ ПУСТАЯ СТРОКА ИЛИ #КОММЕНТАРИЙ ПРОДОЛЖАЕМ
        if(tmp.empty() || tmp[0] == '#') {continue;}
        //ПЫТАЕМСЯ ВЫПОЛНИТЬ КОМАНДУ, ПРИ ЭТОМ РАСПАРСИВ СТРОКУ 
        //МЕТОДОМ SplitBy 
        TryExecuteCommand(SplitBy(tmp), line_counter);
        tmp.clear();
    }
};
