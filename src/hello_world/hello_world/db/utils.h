//
//  utils.h
//  hello_world
//
//  Created by avertsinskaya on 12/29/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string>
#include <time.h>
#include <ctime>

std::string timestamp();
std::string add_padding(std::string s, int max_digits_number);
std::string format_number(double n, int padding, int max_digits_number);
std::string bool_to_string(bool b);

#endif /* utils_h */
