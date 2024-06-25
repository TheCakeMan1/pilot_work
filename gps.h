#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#ifndef GPS_H
#define GPS_H

struct GPS{
    std::string shir;
    std::string nap_shir;
    std::string dolg;
    std::string nap_dolg;
    int speed;
};

std::vector<std::string> splitString(const std::string& str, char delimiter);
void parser(std::string line, GPS &gps_data);

#endif
