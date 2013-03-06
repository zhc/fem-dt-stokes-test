#include "settings.h"
#include <dolfin.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>

Settings::Settings(int argc, char *argv[]) {
    test_mesh_size = 20;
    test_delta_time = 0.01;
    test_scheme = "im";
    test_solver = "default";
    test_preconditioner = "default";

    ex_mesh_size = 25;
    ex_delta_time = 0.01;
    ex_scheme = "im";
    ex_solver = "default";
    ex_preconditioner = "default";
//    ex_mesh_size = 160;
//    ex_delta_time = 0.00125;
//    ex_scheme = "im";
//    ex_solver = "default";
//    ex_preconditioner = "default";

    max_time = 0.2;
	output_dir = "results";
	log_level = dolfin::INFO;


    int option_index;
    struct option long_options[] = {
        {"ex-mesh-size",     required_argument, 0,  0 },
        {"ex-delta-time",  required_argument, 0,  0 },
        {"ex-solver",  required_argument, 0,  0},
        {"ex-preconditioner",    required_argument, 0,  0 },
        {"ex-scheme",    required_argument, 0,  0 },

        {"test-mesh-size",     required_argument, 0,  0 },
        {"test-delta-time",  required_argument, 0,  0 },
        {"test-solver",  required_argument, 0,  0},
        {"test-preconditioner",    required_argument, 0,  0 },
        {"test-scheme",    required_argument, 0,  0 },

        {"output-dir", required_argument, 0,  0 },
        {"max-time",  required_argument,       0,  0 },
        {"log-level",    required_argument, 0,  0 },
        {0,         0,                 0,  0 }
    };

    int c;
    while((c = getopt_long(argc, argv, "", long_options, &option_index)) != -1){
        if (0 == c){
            printf("%s = %s\n", long_options[option_index].name, optarg);
            switch(option_index){
            case 0:
                ex_mesh_size = atoi(optarg);
                break;
            case 1:
                ex_delta_time = atof(optarg);
                break;
            case 2:
                ex_solver = optarg;
                break;
            case 3:
                ex_preconditioner = optarg;
                break;
            case 4:
                ex_scheme = optarg;
                break;
            case 5:
                test_mesh_size = atoi(optarg);
                break;
            case 6:
                test_delta_time = atof(optarg);
                break;
            case 7:
                test_solver = optarg;
                break;
            case 8:
                test_preconditioner = optarg;
                break;
            case 9:
                test_scheme = optarg;
                break;
            case 10:
                output_dir = optarg;
                break;
            case 11:
                max_time = atof(optarg);
                break;
            case 12:
                log_level = atoi(optarg);
                break;
            }
        } else {
            printf("Valid options\n");
            struct option* p = long_options;
            while(p->name){
                printf("%s ", p->name);
                p++;
            }
            printf("\n");
            exit(-1);
        }
    }

    prepareTest();
}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

std::string Settings::toString() {
    char buf[512];
    sprintf(buf,
        "test-mesh-size=%d "
        "test-delta-time=%f "
        "test-scheme=%s "
        "test-solver=%s "
        "test-preconditioner=%s "

        "ex-mesh-size=%d "
        "ex-delta-time=%f "
        "ex-scheme=%s "
        "ex-solver=%s "
        "ex-preconditioner=%s "

        "max-time=%f "
        "output-dir=%s "
        "log-level=%d ",
        test_mesh_size,
        test_delta_time,
        test_scheme.c_str(),
        test_solver.c_str(),
        test_preconditioner.c_str(),

        ex_mesh_size,
        ex_delta_time,
        ex_scheme.c_str(),
        ex_solver.c_str(),
        ex_preconditioner.c_str(),

        max_time,
        output_dir.c_str(),
        log_level
    );

    std::string r = buf;
    return r;
}

void Settings::prepareTest()
{
    mesh_size = test_mesh_size;
    delta_time = test_delta_time;
    scheme = test_scheme;
    solver = test_solver;
    preconditioner = test_preconditioner;
    mode = "test";
}

void Settings::prepareEx()
{
    mesh_size = ex_mesh_size;
    delta_time = ex_delta_time;
    scheme = ex_scheme;
    solver = ex_solver;
    preconditioner = ex_preconditioner;
    mode = "ex";
}
