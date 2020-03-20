//
//  hmac.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/27/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include "hmac.h"

class SHA256Engine : public Poco::Crypto::DigestEngine {
public:
    enum {
        BLOCK_SIZE = 64,
        DIGEST_SIZE = 32
    };

    SHA256Engine(): Poco::Crypto::DigestEngine("SHA256"){}
};

std::string base64encode(std::string str) {
    std::stringstream ss;
    ss.str("");
    
    Poco::Base64Encoder encoder(ss);
    encoder << str;
    encoder.close();

    return ss.str();
}


std::string sign(std::string key, std::string plain) {
    Poco::HMACEngine<SHA256Engine> hmac(key);
    hmac.update(plain);
    
    std::vector<unsigned char> digests = hmac.digest();
    return base64encode(std::string(digests.begin(), digests.end()));
}
