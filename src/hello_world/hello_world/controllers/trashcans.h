//
//  trashcans.h
//  hello_world
//
//  Created by avertsinskaya on 12/1/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef trashcans_h
#define trashcans_h

#include <cppcms/application.h>
#include "../utils/client.h"

class trashcans: public cppcms::application {
public:
    trashcans(cppcms::service &srv);
    void get(std::string lat_str, std::string lng_str, std::string r_str);
    void welcome();
    void add();
    void prepend_cors_headers();
private:
    Client * client;
};


#endif /* trashcans_h */
