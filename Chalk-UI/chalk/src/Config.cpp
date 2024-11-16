// Engine config
#include <chalk/lib/Config.h>

using namespace chk;

std::string engine_configuration::getProjectDirectory() {
	return projectDirectory;
}
void engine_configuration::setProjectDirectory(std::string project_directory) {
	projectDirectory = project_directory;
}

void engine_configuration::setMaxCores(const unsigned short cores) {
	maxCores = std::clamp(cores, unsigned short(1), unsigned short(USHRT_MAX));
}

unsigned int engine_configuration::getMaxCores() {
	return maxCores;
}