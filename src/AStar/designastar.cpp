#include "astarsupport.h"

void ReportNonAvaliablechAndThrowException()
{
    std::ostringstream oss;
    oss << "Transparent: " << NON_AVAL_CH << " would not be as same as non-avaliable " << NON_AVAL_CH;
    throw std::logic_error(oss.str());
}

char ConfigAStar::GetTranparentSym() const
{
    return is_transparent_;
}

char ConfigAStar::GetNoTranparent() const
{
    return no_transparent_;
}

void ConfigAStar::PrintParametrs() const
{
    std::cout << "Transparent: " << is_transparent_ << '\n'
              << "NoneTransparent: " << no_transparent_ << '\n';
};

ConfigAStar::ConfigAStar(std::filesystem::path configs_way)
{
    LoadParamsSetter();
    configs_way.lexically_normal();
    LoadConfigs(configs_way);
}

void ConfigAStar::LoadConfigs(const std::filesystem::path &pth)
{
    // Загружаем файл с конфигурациями
    std::ifstream ifs(pth);
    if (!ifs)
    {
        std::cout << "No stream Load Conigs" << std::endl;
        return;
    }
    std::string tmp;

    while (!ifs.eof())
    {
        // Читаем линию команды
        std::getline(ifs, tmp);
        Trim(tmp);
        if (tmp.empty())
        {
            continue;
        }
        if (tmp[0] == '#')
        {
            continue;
        }
        // Пытаемся выполнить команду, предварительно распарсив строку.
        TryToExecuteCommand(SplitBy(tmp, '='));
    }
}

void ConfigAStar::TryToExecuteCommand(std::vector<std::string> &&commands)
{
    // Если формат пришедших данных не "Команда - значение" - выходим.
    if (commands.size() != 2)
    {
        return;
    }
    // Пытаемся выполнить команду , передав ей значение.
    if (params_setter_.count(commands[0]))
    {
        params_setter_.at(commands[0])(commands[1]);
    }
};

void ConfigAStar::LoadParamsSetter()
{
    // Transparent - функция меняет значение символа проходимой ячейки
    std::pair<std::string, std::function<void(const std::string &str)>> P1 =
        {"Transparent", [&](const std::string &str)
         {
             if (str.empty() || str.size() > 1)
             {
                 std::ostringstream oss;
                 oss << "Transparent: str.sise() is " << str.size() << " but must be 1";
                 throw std::logic_error(oss.str());
             }

             if (str[0] == no_transparent_)
             {
                 std::ostringstream oss;
                 oss << "Transparent: " << str[0] << " would not be as same as none-transparent " << no_transparent_;
                 throw std::logic_error(oss.str());
             };

             if (str[0] == NON_AVAL_CH)
             {
                 ReportNonAvaliablechAndThrowException();
             };

             is_transparent_ = str[0];
         }};
    params_setter_.insert(std::move(P1));

    // NoneTransparent - функция меняет значение символа непроходимой ячейки
    std::pair<std::string, std::function<void(const std::string &str)>> P2 = // NoneTranparent
        {"NoneTransparent", [&](const std::string &str)
         {
             if (str.empty() || str.size() > 1)
             {
                 std::ostringstream oss;
                 oss << "NoneTransparent: str.sise() is " << str.size() << " but must be 1";
                 throw std::logic_error(oss.str());
             }

             if (str[0] == is_transparent_)
             {
                 std::ostringstream oss;
                 oss << "NoneTrasnparent: " << str[0] << " would not be as same as transparent " << is_transparent_;
                 throw std::logic_error(oss.str());
             };

             if (str[0] == NON_AVAL_CH)
             {
                 ReportNonAvaliablechAndThrowException();
             };
             no_transparent_ = str[0];
         }};
    params_setter_.insert(std::move(P2));

    // NotAllowNearBlock - Устанавливает значение на запрес скоса возле непроходимых клеток
    std::pair<std::string, std::function<void(const std::string &str)>> P3 = // Not allow near block
        {"AllowNearBlock", [&](const std::string &str)
         {
             if (str != "true" && str != "false")
             {
                 std::ostringstream oss;
                 oss << "NotAllowNearBlock " << str << " is incorrect parametr (correct are true | false)";
                 throw std::logic_error(oss.str());
             }
             AllowNearBlock_ = (str == "true");
         }};
    params_setter_.insert(std::move(P3));
}

/*
#Запрет среза рядом
NotAllowNearBlock = true
*/