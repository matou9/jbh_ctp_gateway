#include "../0_CTP_gateway.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

void CTP_gateway::init(const char* config_file_name)
{
    std::ifstream config_file(config_file_name);
    if (!config_file.is_open())
    {
        std::cout << "CTP_gateway::init() : config file open failed!" << std::endl;
        return;
    }
    nlohmann::json config = nlohmann::json::parse(config_file);
    config_file.close();

    front_addr = config["front"];
    broker = config["broker"];
    user = config["user"];
    password = config["password"];
    app = config["app"];
    auth_code = config["authcode"];
    flow_dir = config["flowdir"];

    
}