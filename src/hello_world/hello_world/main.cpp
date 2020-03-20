#include <cppcms/service.h>
#include <cppcms/applications_pool.h>

#include <iostream>
#include <fstream>

#include "controllers/trashcans.h"



int main(int argc,char ** argv) {
    if (getenv("SECRET_KEY")) {
      std::ifstream arq(getenv("SECRET_KEY"));
      std::cin.rdbuf(arq.rdbuf());
    }
    
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



