//
//  trashcan.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/25/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include "trashcan.h"

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <string>
#include <fstream>

#include "models/trashcan_model.h"


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


trashcan::trashcan(cppcms::service &srv): cppcms::application(srv) {
    dispatcher().assign("/trashcan", &trashcan::add, this);
    mapper().assign("trashcan");

    mapper().root("/hello_world");
}

void trashcan::add() {
    response().set_header("Access-Control-Allow-Origin", "*");
    response().set_header("Access-Control-Allow-Headers", "accept,Content-Type");
    response().set_header("Access-Control-Allow-Methods",
                          "GET,POST,PATCH,DELETE");
    response().set_content_header("application/json");
    
    
    if (request().request_method() == "OPTIONS") {
        response().out();
    } else if (request().request_method() == "POST") {
        cppcms::json::value trashcan = parse_body(request().raw_post_data());
        
        /* Here we are working with database */
    
        
        response().out() << trashcan;
    }
};
