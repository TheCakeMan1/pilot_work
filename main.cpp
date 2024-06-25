/*
Зависимости:
nlohmann-json3-dev
wget https://github.com/yhirose/cpp-httplib/raw/master/httplib.h
libssl-dev
sqlite3 libsqlite3-dev
*/
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <sqlite3.h>
#include "uart_connect.h"


GPS gps_data;
using json = nlohmann::json;

struct Config {
    std::string ip;
    int port;
};

Config load_config() {
    std::ifstream file("settings");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file");
    }

    json config_json;
    file >> config_json;

    Config config;
    config.ip = config_json["ip"].get<std::string>();
    config.port = config_json["port"].get<int>();

    return config;
}

void response(httplib::Server &svr){
    svr.Get("/status", [](const httplib::Request& req, httplib::Response& res) {
        std::cout << req.path << std::endl;
        res.set_content("OK", "text/plain");
    });
    svr.Get("/video_list", [](const httplib::Request& req, httplib::Response& res){

    });
    svr.Get("/gps_data", [](const httplib::Request& req, httplib::Response& res){
        std::string temp = gps_data.shir + '"' + gps_data.nap_shir + '\n' + gps_data.dolg + '"' + gps_data.nap_dolg + '\n' + std::to_string(gps_data.speed);
        res.set_content(temp, "text/plain");
    });
}

int main() {
    std::cout << "Starting server" << std::endl;

    //создаем соединение с бд
    sqlite3* db;
    int rc = sqlite3_open("data.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    //считываем конфиг
    Config config;
    try {
        config = load_config();
    } catch (const std::exception& e) {
        std::cerr << "Error loading config: " << e.what() << std::endl;
        return -1;
    }

    //создание сервера
    httplib::Server svr;
    response(svr);
    //поток на uart
    std::thread t(gps, std::ref(gps_data));

    std::cout << "Run server in " << config.ip << ":" << config.port << std::endl;
    svr.listen(config.ip, config.port);
    t.join();
    return 0;
}
