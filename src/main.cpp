#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/applications_pool.h>

#include <mapbox/geometry.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>


using namespace mapbox::geometry;


class trashcans: public cppcms::application {
public:
    trashcans(cppcms::service &srv): cppcms::application(srv) {
        dispatcher().assign("/trashcans/lat/(\\d+)/lng/(\\d+)/r/(\\d+)", &trashcans::get, this, 1, 2, 3);
        mapper().assign("get", "/trashcans/lat/{1}/lng/{2}/r/{3}");

  
        dispatcher().assign("/trashcans", &trashcans::welcome, this);
        mapper().assign("trashcans");
    }
    
    void get(std::string lat_str, std::string lng_str, std::string r_str) {
        int lat = atoi(lat_str.c_str());
        int lng = atoi(lng_str.c_str());
        int r = atoi(r_str.c_str());
        
        point<double> pt(lat, lng);
        
        response().out() << "The ONE POINT IS " << pt.x << " " << pt.y << "<br/>\n";
    };
    
    void welcome() {
        response().out() << "<h1> Welcome To Page with links </h1>\n"
         "<a href='" << url("/get", 1, 2, 3)  << "'>See trashcans filtering</a><br>\n";
    };
};


int main(int argc,char ** argv) {
    try {
        cppcms::service srv(argc, argv);
        
        srv.applications_pool().mount(
            cppcms::applications_factory<trashcans>()
        );
        srv.run();
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}



