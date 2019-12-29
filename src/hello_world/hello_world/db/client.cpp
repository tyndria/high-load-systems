//
//  client.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/28/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include <cstdlib>

#include "client.h"
#include "utils.h"
#include "../utils/hmac.h"




Client::Client(const std::string &access_key, const std::string &secret_key, const std::string endpoint)
    : access_key_(access_key), endpoint_(endpoint), secret_key_(secret_key) {}


std::string Client::PatchOne(cppcms::json::value const &v) {
    QueryParams params = {
        QueryParam("AWSAccessKeyId", access_key_),
        QueryParam("Action", "PutAttributes"),
    };
    
    std::string paramName = "";
    bool paramValue;

    if (v.type("properties.plastic")) {
        paramName = "plastic";
        paramValue = v.get<bool>("properties.plastic");
    }
    
    if (v.type("properties.paper")) {
       paramName = "paper";
       paramValue = v.get<bool>("properties.paper");
    }
    
    if (v.type("properties.glass")) {
       paramName = "glass";
       paramValue = v.get<bool>("properties.glass");
    }
    
    if (paramName != "") {
        params.insert(params.end(), {
            QueryParam("Attribute.1.Name", paramName),
            QueryParam("Attribute.1.Replace", bool_to_string(true)),
            QueryParam("Attribute.1.Value", bool_to_string(paramValue)),
        });
    }
    
    params.insert(params.end(), {
        QueryParam("DomainName", "urucca"),
        QueryParam("ItemName", v.get<std::string>("properties.id")),
        QueryParam("SignatureMethod", "HmacSHA256"),
        QueryParam("SignatureVersion", "2"),
        QueryParam("Timestamp", timestamp()),
        QueryParam("Version", "2009-04-15")
    });
    return MakeRequest(params);
}

std::string Client::AddOne(Trashcan trashcan) {
    std::string latitude = format_number(trashcan.coordinates[0], LATITUDE_PADDING, LATITUDE_MAX_DIGITS);
    std::string longtitude = format_number(trashcan.coordinates[1], LONGTITUDE_PADDING, LONGTITUDE_MAX_DIGITS);
    
    std::string trash_name = "trash_" + latitude + longtitude;

    QueryParams params = {
        QueryParam("AWSAccessKeyId", access_key_),
        QueryParam("Action", "PutAttributes"),
        QueryParam("Attribute.1.Name", "lat"),
        QueryParam("Attribute.1.Value", latitude),
        QueryParam("Attribute.2.Name", "long"),
        QueryParam("Attribute.2.Value", longtitude),
        QueryParam("Attribute.3.Name", "plastic"),
        QueryParam("Attribute.3.Value", bool_to_string(trashcan.plastic)),
        QueryParam("Attribute.4.Name", "paper"),
        QueryParam("Attribute.4.Value", bool_to_string(trashcan.paper)),
        QueryParam("Attribute.5.Name", "glass"),
        QueryParam("Attribute.5.Value", bool_to_string(trashcan.glass)),
        QueryParam("DomainName", "urucca"),
        QueryParam("ItemName", trash_name),
        QueryParam("SignatureMethod", "HmacSHA256"),
        QueryParam("SignatureVersion", "2"),
        QueryParam("Timestamp", timestamp()),
        QueryParam("Version", "2009-04-15")
    };
    
    return MakeRequest(params);
}

std::string Client::GetNearest(double lat, double lng, double r) {
    std::string latitude = format_number(lat, LATITUDE_PADDING, LATITUDE_MAX_DIGITS);
    std::string longtitude = format_number(lng, LONGTITUDE_PADDING, LONGTITUDE_MAX_DIGITS);
    
    // TODO: just random formula, ure real calculations
    std::string exp ="select * from urucca where lat > '" + latitude + "' and long < '" + longtitude +"'";
    
    QueryParams params = {
        QueryParam("AWSAccessKeyId", access_key_),
        QueryParam("Action", "Select"),
        QueryParam("SelectExpression", exp),
        QueryParam("SignatureMethod", "HmacSHA256"),
        QueryParam("SignatureVersion", "2"),
        QueryParam("Timestamp", timestamp()),
        QueryParam("Version", "2009-04-15")
    };
    
    std::string result_xml = MakeRequest(params);
    return result_xml;
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
