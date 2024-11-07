#include "def_configurator.h"

using ChangeFoo = std::function<void(std::string str)>;
using ChangeDir = std::unordered_map<std::string, const std::unordered_map<std::string, ChangeFoo> &>;

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

SVGNamedLinePrint GCP::graph_line_pr_ = {"white",
                                         "white", 1., "Arial", 10., "gray", "gray", 1.};

SVGArrowPrint GCP::deikstra_arrow_pr_ = {"cyan",
                                         "cyan", 1., "Arial", 10., "yellow", "yellow", 1., "yellow", "yellow", 1.};

SVGArrowPrint GCP::graph_arrow_pr_ = {"white", "white", 1., "Arial", 10., "gray", "gray", 1., "gray", "orange", 1.};

SVGNamedCirclePrint GCP::graph_tops_pr_ = {"black", "green", 1., "red",
                                           "red", 1., "Arial", 10.};

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

std::unordered_map<std::string, ChangeFoo> GraphTopsLampdas(SVGNamedCirclePrint &ncp)
{
    std::unordered_map<std::string, ChangeFoo> tmp;
    ProvideChTextLampdas(tmp, GCP::graph_tops_pr_);
    ProvideChCirceLampdas(tmp, ncp);
    return tmp;
}

std::unordered_map<std::string, ChangeFoo> LineLampdas(SVGNamedLinePrint &lpr)
{
    std::unordered_map<std::string, ChangeFoo> tmp;
    ProvideChTextLampdas(tmp, lpr);
    ProvideChLineLampdas(tmp, lpr);
    return tmp;
}

std::unordered_map<std::string, ChangeFoo> ArrowLampdas(SVGArrowPrint &arrow)
{
    std::unordered_map<std::string, ChangeFoo> tmp = LineLampdas(arrow);
    ProvideChTriangleLampdas(tmp, arrow);
    return tmp;
}

std::unordered_map<std::string, ChangeFoo> deikstra_arrow_conf_;
std::unordered_map<std::string, ChangeFoo> graph_arrow_conf_;
std::unordered_map<std::string, ChangeFoo> graph_line_conf_;
std::unordered_map<std::string, ChangeFoo> graph_tops_conf_;

ChangeDir def_configurator_ = {

    {"graph_line", graph_line_conf_},
    {"graph_arrow", graph_arrow_conf_},
    {"deikstra_arrow", deikstra_arrow_conf_},
    {"graph_tops", graph_tops_conf_}};

void ProvideDefConfigurarorLampdas()
{
    deikstra_arrow_conf_ = ArrowLampdas(GCP::deikstra_arrow_pr_);
    graph_arrow_conf_ = ArrowLampdas(GCP::graph_arrow_pr_);
    graph_line_conf_ = LineLampdas(GCP::graph_line_pr_);
    graph_tops_conf_ = GraphTopsLampdas(GCP::graph_tops_pr_);
}

void ReportErrorLine(const std::string &param, int where)
{
    std::cerr << " mistake on  " << param << " on line " << where << std::endl;
}
void TryExecuteCommand(std::vector<std::string> &&params, int line)
{
    static bool provide_conf = false;
    std::cerr<<provide_conf;
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
    pth.lexically_normal();
    std::ifstream ifs(std::move(pth));
    if (!ifs)
    {
        return;
    }
    std::string tmp;
    int line_counter = 0;
    while (!ifs.eof())
    {
        std::getline(ifs, tmp);
        Trim(tmp);
        ++line_counter;
        if(tmp.empty() || tmp[0] == '#') {continue;}
        TryExecuteCommand(SplitBy(tmp), line_counter);
        tmp.clear();
    }
};
