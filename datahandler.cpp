#include "datahandler.h"

datahandler::datahandler() {

}


std::map<std::string, std::string> datahandler::parseObject(const std::string &dataString) {
    nlohmann::json jsonData = nlohmann::json::parse(dataString);


    nlohmann::json data = jsonData[0];


    std::map<std::string, std::string> Object;


    for (auto& [key, value] : data.items()) {
        Object[key] = value.dump();
    }


    return Object;

}
