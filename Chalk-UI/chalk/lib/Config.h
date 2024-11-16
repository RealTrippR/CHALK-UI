// Engine config
#ifndef CHK_CONFIG_H
#define CHK_CONFIG_H

#include <chalk/lib/Universal_Includes.h>;

namespace chk {

	struct engine_configuration {
	public:
		std::string getProjectDirectory();

		void setProjectDirectory(std::string project_directory);

		void setMaxCores(const unsigned short cores);

		unsigned int getMaxCores();
	private:
		std::string projectDirectory;

		unsigned short maxCores = 1;
	};
	extern engine_configuration config;
}
#endif // !CHK_CONFIG_H