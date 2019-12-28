//
//  trashcan.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/25/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include <ctime>

#include "trashcan.h"

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <string>
#include <fstream>

#include "../models/trashcan.h"

#include "../utils/hmac.h"
#include "../utils/query.h"
#include "../utils/httplib.h"


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

