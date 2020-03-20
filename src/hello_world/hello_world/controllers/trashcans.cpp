//
//  trashcans.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/1/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//
#include <cppcms/json.h>

#include <cppcms/http_request.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <string>
#include <fstream>

#include "trashcans.h"

#include "../models/trashcan.h"


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
    client = new Client("AKIA4A5DKQCYPBQP4SWY", getenv("SECRET_KEY"), "sdb.amazonaws.com");
    
    dispatcher().assign("/trashcans/lat/(\\d+)/lng/(\\d+)", &trashcans::list, this, 1, 2);
    mapper().assign("get", "/trashcans/lat/{1}/lng/{2}");

    dispatcher().assign("/trashcans", &trashcans::welcome, this);
    mapper().assign("trashcans");
    
    dispatcher().assign("/trashcan/(.*)", &trashcans::put, this, 1);
    mapper().assign("put", "/trashcan/{1}");
    
    dispatcher().assign("/trashcan", &trashcans::post, this);
    mapper().assign("trashcan");
    
    mapper().root("/hello_world");
}

void trashcans::list(std::string lat_str, std::string lng_str) {
    prepend_cors_headers();
    
    if (request().request_method() == "GET") {
        std::string result = client->GetNearest(std::stod(lat_str), std::stod(lng_str));
       
        response().out() << result;
    }
};

void trashcans::put(std::string id) {
    prepend_cors_headers();
    
    if (request().request_method() == "PATCH") {
        cppcms::json::value t = parse_body(request().raw_post_data());
        std::string result = client->PatchOne(t, id);
        response().out() << result;
    }
}

void trashcans::post() {
    prepend_cors_headers();
    
    if (request().request_method() == "POST") {
        cppcms::json::value t = parse_body(request().raw_post_data());
        std::string result = client->AddOne(t.get_value<Trashcan>());
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
