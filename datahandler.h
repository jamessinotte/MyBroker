#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <nlohmann/json.hpp>
#include <map>

class datahandler
{
public:
    datahandler();
    std::map<std::string, std::string> parseObject(const std::string &dataString);
};

#endif // DATAHANDLER_H
