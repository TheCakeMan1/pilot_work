#include "gps.h"

void parser(std::string line, GPS &gps_data) {
    std::vector<std::string> tokens = splitString(line, ',');
    if (tokens.size() == 0) {
        continue;
    }
    else {
        if(tokens[0] == "$GNGGA"){
            gps_data.shir = tokens[2];
            gps_data.nap_shir = tokens[3];
            gps_data.dolg = tokens[4];
            gps_data.nap_dolg = tokens[5];
        } else if (tokens[0] == "$GNRMC"){
            gps_data.speed = tokens[7];
        }
    }
}
