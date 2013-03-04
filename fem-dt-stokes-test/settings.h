#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <string>

class Settings {
public:
    Settings(int argc, char *argv[]);
	virtual ~Settings();
	std::string toString();

    int nx;
    double t;
    double dt;
	std::string output_dir;
	std::string solver_name;
	std::string precond_name;
	int log_level;
    std::string scheme;
private:
    std::string optString();
    void set(int option, std::string value);
};

#endif /* SETTINGS_H_ */
