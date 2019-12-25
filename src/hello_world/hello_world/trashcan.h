//
//  trashcan.h
//  hello_world
//
//  Created by avertsinskaya on 12/25/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef trashcan_h
#define trashcan_h

#include <cppcms/application.h>
#include <cppcms/service.h>

#include <stdio.h>

class trashcan: public cppcms::application {
public:
    trashcan(cppcms::service &srv);
    void add();
};

#endif /* trashcan_h */
