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
	private:
		std::string projectDirectory;
	} config;

}
#endif // !CHK_CONFIG_H