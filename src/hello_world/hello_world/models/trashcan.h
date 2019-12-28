//
//  trashcan.h
//  hello_world
//
//  Created by avertsinskaya on 12/25/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#ifndef trashcan_h
#define trashcan_h

#include <cppcms/json.h>

// TODO: add links to properties?
struct trashcan {
    std::vector<double> coordinates;
    std::string type;
    bool plastic;
    bool paper;
    bool glass;
};

namespace cppcms {
    namespace json {
        template<> struct traits<trashcan> {
           static trashcan get(value const &v) {
               trashcan t;
               if(v.type() != is_object) {
                   throw bad_value_cast();
               }
               
               t.plastic = v.get<bool>("properties.plastic");
               t.glass = v.get<bool>("properties.glass");
               t.paper = v.get<bool>("properties.paper");
               t.coordinates = v.get<std::vector<double>>("geometry.coordinates");
               return t;
           }
            
            static void set(value &v, trashcan const &in) {
                v.set("type", "Feature");
                v.set("geometry.type", "Point");
                v.set("geometry.type", in.coordinates);
                v.set("properties.plastic", in.plastic);
                v.set("properties.paper", in.paper);
                v.set("properties.glass", in.glass);
            }
        };
    } // json
} // cppcms  

#endif /* trashcan_h*/
