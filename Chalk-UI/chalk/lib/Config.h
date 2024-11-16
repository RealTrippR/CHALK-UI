#ifndef CHK_CONFIG_H
#define CHK_CONFIG_H
namespace chk {



	struct engine_configuration {
	public:
		std::string getProjectDirectory() {
			return projectDirectory;
		}
		void setProjectDirectory(std::string project_directory) {
			projectDirectory = project_directory;
		}
		void setMaxCores(const unsigned short cores) {
			maxCores = std::clamp(cores, unsigned short(1), unsigned short (USHRT_MAX));
		}

		unsigned int getMaxCores() {
			return maxCores;
		}
	private:
		std::string projectDirectory;

		unsigned short maxCores = 1;
	} config;

}
#endif // !CHK_CONFIG_H