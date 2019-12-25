//
//  trashcans.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/1/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <mapbox/geometry.hpp>

#include <string>
#include <fstream>

#include "models/trashcan_model.h"
#include "trashcans.h"


using namespace mapbox::geometry;

trashcans::trashcans(cppcms::service &srv): cppcms::application(srv) {
    dispatcher().assign("/trashcans/lat/(\\d+)/lng/(\\d+)/r/(\\d+)", &trashcans::get, this, 1, 2, 3);
    mapper().assign("get", "/trashcans/lat/{1}/lng/{2}/r/{3}");

    dispatcher().assign("/trashcans", &trashcans::welcome, this);
    mapper().assign("trashcans");
    
    mapper().root("/hello_world");
}

void trashcans::get(std::string lat_str, std::string lng_str, std::string r_str) {
    std::string trash_str = "{ \
        \"type\": \"Feature\",\
        \"geometry\": { \
            \"type\": \"Point\", \
            \"coordinates\": \"[-104.99404, 39.75621]\" \
        }, \
        \"properties\": { \
            \"plastic\": \"true\", \
            \"paper\": \"false\", \
            \"glass\": \"false\" \
        } \
    }";
    
    cppcms::json::value trash_obj;
    std::stringstream ss;
    ss << trash_str;
    
    trash_obj.load(ss, true);
    
    response().out() << trash_obj;
};

void trashcans::welcome() {
    response().out() << "<h1> Welcome To Page with links </h1>\n"
    "<a href='" << url("/get", 1, 2, 3)  << "'>See trashcans filtering</a><br>\n";
};
