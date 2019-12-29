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
#include "../db/client.h"

class trashcans: public cppcms::application {
public:
    trashcans(cppcms::service &srv);
    void welcome();
    void list(std::string lat_str, std::string lng_str, std::string r_str);
    void one();
    void prepend_cors_headers();
private:
    Client * client;
};


#endif /* trashcans_h */
