//
//  trashcan.cpp
//  hello_world
//
//  Created by avertsinskaya on 12/25/19.
//  Copyright © 2019 avertsinskaya. All rights reserved.
//

#include <cppcms/json.h>

#include "trashcan_model.h"


namespace cppcms {
namespace json {
    template<>
    struct traits<TrashcanProperties> {
       static TrashcanProperties get(value const &v) {
           TrashcanProperties t;
           if(v.type() != is_object) {
               throw bad_value_cast();
           }
         
           t.plastic = v.get<bool>("plastic");
           t.glass = v.get<bool>("glass");
           t.paper = v.get<bool>("paper");
           return t;
       }
        
        static void set(value &v, TrashcanProperties const &in) {
            v.set("plastic", in.plastic);
            v.set("glass", in.glass);
            v.set("paper", in.paper);
        }
    };

    template<>
    struct traits<TrashcanGeometry> {
       static TrashcanGeometry get(value const &v) {
           TrashcanGeometry t;
           if(v.type() != is_object) {
               throw bad_value_cast();
           }
         
           t.type = v.get<std::string>("type");
           t.coordinates = v.get<std::vector<double>>("coordinates");
           return t;
       }
        
        static void set(value &v, TrashcanGeometry const &in) {
            v.set("type", in.type);
            v.set("coordinates", in.coordinates);
        }
    };
 
    template<>
    struct traits<Trashcan> {
       static Trashcan get(value const &v) {
           Trashcan t;
           if(v.type() != is_object) {
               throw bad_value_cast();
           }
         
           t.type = v.get<std::string>("type");
           t.geometry = v.get<TrashcanGeometry>("geometry");
           t.properties = v.get<TrashcanProperties>("properties");
           return t;
       }
        
        static void set(value &v, Trashcan const &in) {
            v.set("type", in.type);
            v.set("geometry", in.geometry);
            v.set("properties", in.properties);
        }
    };
} // json
} // cppcms  
