#include <cppcms/service.h>
#include <cppcms/applications_pool.h>

#include <iostream>

#include "trashcans.h"


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



