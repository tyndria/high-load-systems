//
//  trashcans.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/1/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//
#include <cppcms/json.h>
#include <cppcms/application.h>
#include <cppcms/http_request.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <mapbox/geometry.hpp>

#include <string>
#include <fstream>

#include "trashcans.h"

#include "../models/trashcan.h"

using namespace mapbox::geometry;

cppcms::json::value parse_body(const std::pair<void *, size_t> &post_data) {
  cppcms::json::value body;
    
  if (post_data.second > 0) {
    std::istringstream ss(std::string(
        reinterpret_cast<char const *>(post_data.first), post_data.second));
      
      if (!body.load(ss, true)) {
          // TODO: handle error
      }
  }

  return body;
}

trashcans::trashcans(cppcms::service &srv): cppcms::application(srv) {
    client = new Client("AKIA4A5DKQCYPBQP4SWY", "", "sdb.amazonaws.com");
    
    dispatcher().assign("/trashcans/lat/(\\d+)/lng/(\\d+)/r/(\\d+)", &trashcans::get, this, 1, 2, 3);
    mapper().assign("get", "/trashcans/lat/{1}/lng/{2}/r/{3}");

    dispatcher().assign("/trashcans", &trashcans::welcome, this);
    mapper().assign("trashcans");
    
    dispatcher().assign("/trashcan", &trashcans::add, this);
    mapper().assign("trashcan");
    
    mapper().root("/hello_world");
}

void trashcans::get(std::string lat_str, std::string lng_str, std::string r_str) {
    prepend_cors_headers();
    
    if (request().request_method() == "GET") {
        std::string result = client->GetNearest(1, 2);
            
        response().out() << result;
    }
};

void trashcans::add() {
    prepend_cors_headers();
    
    if (request().request_method() == "POST") {
        cppcms::json::value t = parse_body(request().raw_post_data());
        
        std::string result = client->Add(t.get_value<trashcan>());
            
        response().out() << result;
    }
};

void trashcans::welcome() {
    response().out() << "<h1> Welcome </h1>\n";
};

void trashcans::prepend_cors_headers() {
    response().set_header("Access-Control-Allow-Origin", "*");
    response().set_header("Access-Control-Allow-Headers", "accept,Content-Type");
    response().set_header("Access-Control-Allow-Methods",
                        "GET,POST,PATCH,DELETE");
    response().set_content_header("application/json");
}
