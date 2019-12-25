//
//  trashcan.h
//  hello_world
//
//  Created by avertsinskaya on 12/25/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef trashcan_h
#define trashcan_h


struct TrashcanProperties {
    bool plastic;
    bool paper;
    bool glass;
};

struct TrashcanGeometry {
    std::string type;
    std::vector<double> coordinates;
};

// TODO: add links to properties?
struct Trashcan {
    std::string type;
    TrashcanGeometry geometry;
    TrashcanProperties properties;
};

#endif /* trashcan_h*/
