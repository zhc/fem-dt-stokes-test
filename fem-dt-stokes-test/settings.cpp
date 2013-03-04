#include "settings.h"
#include <dolfin.h>
#include <unistd.h>

Settings::Settings(int argc, char *argv[]) {
    nx = 20;
    t = 0.2;
    dt = 0.001;
	output_dir = "results";
	solver_name = "default";
	precond_name = "default";
	log_level = dolfin::INFO;
    scheme = "im";

    int opt = -1;
    while ((opt = getopt(argc, argv, optString().c_str())) != -1) {
        if (opt == '?') {
            std::cerr << "Error option: " << opterr << std::endl;
            std::exit(-1);
        } else {
            set(opt, optarg);
        }
    }
}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

std::string Settings::toString() {
	std::stringstream ss;
    ss << "num=" << nx << " T=" << t << " dt=" << dt << " outputPath=" << output_dir << " slaeSolver=" << solver_name << " precond=" << precond_name << " log=" << log_level << " scheme=" <<scheme;
	return ss.str();
}

std::string Settings::optString() {
    return "n:t:d:o:l:p:v:s:";
}

void Settings::set(int option, std::string value){
	switch(option){
	case 'n':
        nx = atoi(value.c_str());
		break;
    case 't':
        t = atof(value.c_str());
		break;
    case 'd':
        dt = atof(value.c_str());
		break;
	case 'o':
		output_dir = value;
		break;
    case 'l':
		solver_name = value;
		break;
	case 'p':
		precond_name = value;
		break;
    case 'v':
		log_level = atoi(value.c_str());
		break;
    case 's':
        scheme = value;
		break;
	default:
        std::cerr << "Unknown option: " << (char)option << std::endl;
		std::exit(-1);
		break;
	}
}
