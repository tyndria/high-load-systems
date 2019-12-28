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


#define LATITUDE_MAX_DIGITS 2
#define LONGTITUDE_MAX_DIGITS 3
#define LATITUDE_PADDING 90
#define LONGTITUDE_PADDING 180


std::string timestamp() {
    time_t raw_time = std::time(nullptr);
    struct tm *info;
    
    info = gmtime(&raw_time);
    
    char iso_time[25];
    /* YYYY-MM-DDThh:mm:ssZ */
    strftime(iso_time, sizeof(iso_time), "%Y-%m-%dT%H:%M:%SZ", info);
    
    return std::string(iso_time);
}

std::string add_padding(std::string s, int max_digits_number) {
    std::string::size_type pos = s.find(".");
    int digits_num = static_cast<int>(pos);
    
    int padding_size = std::max(0, max_digits_number - digits_num);
    std::string padding = std::string(padding_size, '0');
    
    return padding + s;
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
    double latitute = trashcan.coordinates[0] + LATITUDE_PADDING;
    double longtitude = trashcan.coordinates[1] + LONGTITUDE_PADDING;
    
    std::string coordinates = std::to_string(latitute) + "," + std::to_string(longtitude);
    std::string trash_name = "trash_" + coordinates;

    
    QueryParams params = {
        QueryParam("AWSAccessKeyId", access_key_),
        QueryParam("Action", "PutAttributes"),
        QueryParam("Attribute.1.Name", "lat"),
        QueryParam("Attribute.1.Value", add_padding(std::to_string(latitute), LATITUDE_MAX_DIGITS)),
        QueryParam("Attribute.2.Name", "long"),
        QueryParam("Attribute.2.Value", add_padding(std::to_string(longtitude), LONGTITUDE_MAX_DIGITS)),
        QueryParam("Attribute.3.Name", "plastic"),
        QueryParam("Attribute.3.Value", trashcan.plastic ? "true": "false"),
        QueryParam("Attribute.4.Name", "paper"),
        QueryParam("Attribute.4.Value", trashcan.paper ? "true": "false"),
        QueryParam("Attribute.5.Name", "glass"),
        QueryParam("Attribute.5.Value", trashcan.glass ? "true": "false"),
        QueryParam("DomainName", "urucca"),
        QueryParam("ItemName", trash_name),
        QueryParam("SignatureMethod", "HmacSHA256"),
        QueryParam("SignatureVersion", "2"),
        QueryParam("Timestamp", timestamp()),
        QueryParam("Version", "2009-04-15")
    };
    
    return MakeRequest(params);
}

std::string Client::GetNearest(double lat, double lang) {
    std::string exp ="select * from urucca where lat > '40' and long < '240'";
    
    QueryParams params = {
        QueryParam("AWSAccessKeyId", access_key_),
        QueryParam("Action", "Select"),
        QueryParam("SelectExpression", exp),
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
