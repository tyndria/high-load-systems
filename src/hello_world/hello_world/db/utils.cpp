//
//  utils.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/29/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include "utils.h"


std::string timestamp() {
    time_t raw_time = std::time(nullptr);
    struct tm *info;
    
    info = gmtime(&raw_time);
    
    char iso_time[25];
    /* YYYY-MM-DDThh:mm:ssZ */
    strftime(iso_time, sizeof(iso_time), "%Y-%m-%dT%H:%M:%SZ", info);
    
    return std::string(iso_time);
}

std::string add_padding(std::string s, int max_digits_number) {
    std::string::size_type pos = s.find(".");
    int digits_num = static_cast<int>(pos);
    
    int padding_size = std::max(0, max_digits_number - digits_num);
    std::string padding = std::string(padding_size, '0');
    
    return padding + s;
}

std::string format_number(double n, int padding, int max_digits_number) {
    return add_padding(std::to_string(n + padding), max_digits_number);
}

std::string bool_to_string(bool b) {
  return b ? "true" : "false";
}
