#pragma once
#include"../routers/deikstrarouter.h"
/**
 * Класс для получения маршрута в виде строки, для печати маршрута в различных вариантах на основе алгоритма Дейкстры.
 */
class DeikstraPrinter
{
public:
    /**
     * \brief Конструктор
     * \param router Маршрутизатор
     */
    DeikstraPrinter(const DeikstraRouter &router);

    /**
     * \brief Путь в виде строки
     * \param from Откуда
     * \param to Куда
     * \return Путь в виде "A --> D --> C --> E"
     */
    std::string GetWaysString(const std::string &from, const std::string &to) const;

    /**
     * \brief Печатает путь в консоль
     * \param from Откуда
     * \param to Куда
     * \details Печатает путь в виде "A --> D --> C --> E"
     */
    void PrintStringToConsole(const std::string &from, const std::string &to) const;

    /**
     * \brief Печатает путь в файл
     * \param from Откуда
     * \param to Куда
     * \param file Путь к файлу
     * \param trunk Уничтожать ли содержимое
     * \details Печатает путь в виде "A --> D --> C --> E"
     */
    void PrintStringToFile(const std::string &from, const std::string &to, const std::string &file, bool trunc = true) const;

    /**
     * \brief Печатает путь в консоль
     * \param from Откуда
     * \param to Куда
     * \param stream
     * \details Печатает путь в виде "A --> D --> C --> E"
     */
    void PrintStringToYourStream(const std::string &from, const std::string &to, std::ostream &stream) const;

     /**
     * \brief Печатает путь в консоль
     * \param from Откуда
     * \param to Куда
     * \details Печатает путь в виде :
     * The way from: A to: D  is: 1
     * The way from: D to: C  is: 4
     * The way from: C to: E  is: 4
     */
    void PrintGraphDirToConsole(const std::string &from, const std::string &to) const;
    
    /**
     * \brief Печатает путь в консоль
     * \param from Откуда
     * \param to Куда
     * \param file Путь к Файлу 
     * \param trunk Уничтожить содержимое файла?
     * \details Печатает путь в виде :
     * The way from: A to: D  is: 1
     * The way from: D to: C  is: 4
     * The way from: C to: E  is: 4
     */
    void PrintGraphDirToFile(const std::string &from, const std::string &to,
                             const std::string &file, bool trunc = true) const;
    
    /**
     * \brief Печатает путь в консоль
     * \param from Откуда
     * \param to Куда
     * \param stream Поток печати 
     * \details Печатает путь в виде :
     * The way from: A to: D  is: 1
     * The way from: D to: C  is: 4
     * The way from: C to: E  is: 4
     */
    void PrintGraphDirToYourStream(const std::string &from, const std::string &to, std::ostream &stream) const;

private:
    //! Печать пути в виде строки
    void PrintString(const std::string &from, const std::string &to, std::ostream &os = std::cout) const;
    //! Печать пути в "The way from: C to: E  is: 4"
    void PrintGraphDir(const std::string &from, const std::string &to, std::ostream &os = std::cout) const;
    //! Маршрутизатор
    const DeikstraRouter &router_;

};