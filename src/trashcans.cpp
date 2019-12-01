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

#include "trashcans.h"


using namespace mapbox::geometry;

trashcans::trashcans(cppcms::service &srv): cppcms::application(srv) {
  dispatcher().assign("/trashcans/lat/(\\d+)/lng/(\\d+)/r/(\\d+)", &trashcans::get, this, 1, 2, 3);
  mapper().assign("get", "/trashcans/lat/{1}/lng/{2}/r/{3}");


  dispatcher().assign("/trashcans", &trashcans::welcome, this);
  mapper().assign("trashcans");
}

void trashcans::get(std::string lat_str, std::string lng_str, std::string r_str) {
  int lat = atoi(lat_str.c_str());
  int lng = atoi(lng_str.c_str());
  
  point<double> pt(lat, lng);
  response().out() << "The ONE POINT IS " << pt.x << " " << pt.y << "<br/>\n";
};

void trashcans::welcome() {
  response().out() << "<h1> Welcome To Page with links </h1>\n"
   "<a href='" << url("/get", 1, 2, 3)  << "'>See trashcans filtering</a><br>\n";
};
