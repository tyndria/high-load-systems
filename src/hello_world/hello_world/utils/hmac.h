//
//  hmac.h
//  hello_world
//
//  Created by avertsinskaya on 12/27/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef hmac_h
#define hmac_h

#include <string>
#include <sstream>
#include <vector>

#include "Poco/Crypto/DigestEngine.h"
#include "Poco/HMACEngine.h"
#include "Poco/Base64Encoder.h"

std::string sign(std::string key, std::string plain);

#endif /* hmac_h */
