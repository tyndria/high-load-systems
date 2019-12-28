//
//  client.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/28/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include <cstdlib>
#include <time.h>
#include <ctime>

#include "client.h"
#include "../utils/hmac.h"


std::string timestamp() {
    time_t raw_time = std::time(nullptr);
    struct tm *info;
    
    info = gmtime(&raw_time);
    
    char iso_time[25];
    /* YYYY-MM-DDThh:mm:ssZ */
    strftime(iso_time, sizeof(iso_time), "%Y-%m-%dT%H:%M:%SZ", info);
    
    return std::string(iso_time);
}


Client::Client(const std::string &access_key, const std::string &secret_key, const std::string endpoint)
    : access_key_(access_key), endpoint_(endpoint), secret_key_(secret_key) {
        base_params_ = {
            QueryParam("AWSAccessKeyId", access_key_),
            QueryParam("SignatureVersion", "2"),
            QueryParam("SignatureMethod", "HmacSHA256"),
            QueryParam("Version", "2009-04-15")
        };
}

std::string Client::Add(trashcan trashcan) {
    std::string coordinates = std::to_string(trashcan.coordinates[0]) + "," + std::to_string(trashcan.coordinates[1]);
    std::string trash_name = "trash_" + coordinates;
    
    QueryParams params = {
        QueryParam("AWSAccessKeyId", access_key_),
        QueryParam("Action", "PutAttributes"),
        QueryParam("Attribute.1.Name", "coordinates"),
        QueryParam("Attribute.1.Value", coordinates),
        QueryParam("Attribute.2.Name", "plastic"),
        QueryParam("Attribute.2.Value", trashcan.plastic ? "true": "false"),
        QueryParam("Attribute.3.Name", "paper"),
        QueryParam("Attribute.3.Value", trashcan.paper ? "true": "false"),
        QueryParam("Attribute.4.Name", "glass"),
        QueryParam("Attribute.4.Value", trashcan.glass ? "true": "false"),
        QueryParam("DomainName", "urucca"),
        QueryParam("ItemName", trash_name),
        QueryParam("SignatureMethod", "HmacSHA256"),
        QueryParam("SignatureVersion", "2"),
        QueryParam("Timestamp", timestamp()),
        QueryParam("Version", "2009-04-15")
    };
    
    return MakeRequest(params);
}

std::string Client::MakeRequest(QueryParams query_params) {
    Poco::URI uri(endpoint_);

    uri.setPath("/");
    
    for (const auto &param : query_params) {
        uri.addQueryParameter(param.first, param.second);
    }
    
    std::string raw_query = uri.getRawQuery();
    std::string signature = sign(secret_key_, "GET\nsdb.amazonaws.com\n/\n" + raw_query);
    
    uri.addQueryParameter("Signature", signature);

    Poco::Net::HTTPClientSession session(endpoint_);
    Poco::Net::HTTPRequest request("GET", uri.getPathAndQuery());
    
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    auto &response_body = session.receiveResponse(response);

    if (response.getStatus() != 200) {
        if (response.getStatus() / 100 == 5) {
            // handle error
        } else if (response.getStatus() / 100 == 4) {
            // handle error
        }
       // handle error
    }

    std::string result(std::istreambuf_iterator<char>(response_body), {});

    return result;
}
