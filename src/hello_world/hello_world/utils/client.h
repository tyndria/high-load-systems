//
//  client.h
//  hello_world
//
//  Created by avertsinskaya on 12/28/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef client_h
#define client_h

#include <string>

#include "Poco/URI.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"

#include "../models/trashcan.h"

using QueryParam = std::pair<std::string, std::string>;
using QueryParams = std::vector<QueryParam>;

class Client {
public:
    Client() = delete;
 
    Client(const std::string &access_key, const std::string &secret_key, const std::string endpoint);
    
    std::string Add(trashcan trashcan);
    std::string GetNearest(double lat, double lang);
 private:
    std::string MakeRequest(QueryParams query_params);
    
    std::string access_key_;
    std::string secret_key_;
    std::string endpoint_;
    QueryParams base_params_;
};

#endif /* client_h */
