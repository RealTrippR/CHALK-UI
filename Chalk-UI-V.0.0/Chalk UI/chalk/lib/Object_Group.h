#include "Universal_Includes.h";


#ifndef CHK_OBJECT_GROUP
#define CHK_OBJECT_GROUP

namespace chk {

	class object_group {
	public:

		// returns true if the object exists, returns false if otherwise.
		bool checkForObjectByName(const std::string& name) {
			auto it = M_NameMap.find(name);
			return it != M_NameMap.end();
		}
		// returns a reference to the object. If it's found, it will return null.

		template <typename T>
		T& getObjectByName(const std::string& name) {
			auto it = M_NameMap.find(name);
			if (it == M_NameMap.end()) {
				throw std::runtime_error("Error: Object not found!");
			}
			std::shared_ptr<UI_Object> base_ptr = M_Objects[it->second];
			std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(base_ptr);
			if (ptr) {
				return *ptr;
			}
			else {
				throw std::runtime_error("Error: Object could not be dynamically cast!");
			}
		}
		
		//
		template <typename T>
		std::shared_ptr<UI_Object> addObject(T &obj) {
			if (M_NameMap.find(obj.getName()) == M_NameMap.end()) {
				M_Objects.push_back(std::make_shared<T>(obj));
				M_NameMap[obj.getName()] = M_Objects.size() - 1;
				return M_Objects.back();
			}
			else {
				throw std::runtime_error("Error: An object with this name already exists");
			}
		}

		void removeObjectByName(const std::string& name) {
			auto it = M_NameMap.find(name);
			if (it == M_NameMap.end()) {
				throw std::runtime_error("Error: Object not found!");
			}
			int index = it->second;
			M_Objects.erase(M_Objects.begin() + index);
			M_NameMap.erase(it);

			// Update indices in M_NameMap
			for (auto& pair : M_NameMap) {
				if (pair.second > index) {
					--pair.second;
				}
			}
		}

		// returns a reference to a vector of all objects
		std::vector<std::shared_ptr<UI_Object>>& getObjects() {
			return M_Objects;
		}

		size_t getSizeOfChildren() {
			return M_Objects.size();
		}
	private:
		std::unordered_map<std::string, int> M_NameMap;

		std::vector<std::shared_ptr<UI_Object>> M_Objects;
	};
}
#endif // !CHK_OBJECT_GROUP