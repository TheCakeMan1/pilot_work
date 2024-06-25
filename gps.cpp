#include "gps.h"

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void parser(std::string line, GPS &gps_data) {
    std::vector<std::string> tokens = splitString(line, ',');
    if (tokens.size() == 0) {
        return;
    }
    else {
        if(tokens[0] == "$GNGGA"){
            gps_data.shir = tokens[2];
            gps_data.nap_shir = tokens[3];
            gps_data.dolg = tokens[4];
            gps_data.nap_dolg = tokens[5];
        } else if (tokens[0] == "$GNRMC"){
            gps_data.speed = std::stof(tokens[7]);
        }
    }
}
