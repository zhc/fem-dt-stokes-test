#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <string>

class Settings {
public:
    Settings(int argc, char *argv[]);
	virtual ~Settings();
	std::string toString();

    int mesh_size;
    double delta_time;
    std::string scheme;
    std::string solver;
    std::string preconditioner;

    std::string output_dir;
    double max_time;
    int log_level;

    std::string mode; //not user option

    void prepareTest();
    void prepareEx();
private:
    int test_mesh_size;
    double test_delta_time;
    std::string test_scheme;
    std::string test_solver;
    std::string test_preconditioner;

    int ex_mesh_size;
    double ex_delta_time;
    std::string ex_solver;
    std::string ex_preconditioner;
    std::string ex_scheme;

};

#endif /* SETTINGS_H_ */
