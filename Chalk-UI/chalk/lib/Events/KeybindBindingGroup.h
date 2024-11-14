#ifndef CHK_KEYBIND_BINDING_GROUP_HPP
#define CHK_KEYBIND_BINDING_GROUP_HPP

namespace chk {
	class keybind; // FORWARD DECLARATION

	class keybindBindingGroup {
	public:
		keybindBindingGroup() = default;
		keybindBindingGroup(keybind* kb) {
			M_ParentRef = kb;
		}
	public:
		void invoke() {
			for (auto& f : M_BindedFunctionsNoArgs) {
				f();
			}
			for (auto& f : M_BindedFunctionsWithArgs) {
				f(M_ParentRef);
			}
		}
	public:
		inline void bind(void(*func)()) {
			if (M_BindedFunctionsNoArgs_ExistenceRecord.find(func) != M_BindedFunctionsNoArgs_ExistenceRecord.end()) {
				M_BindedFunctionsNoArgs.push_back(func);
			}
		}

		inline void bind(void(*func)(keybind*)) {
			if (M_BindedFunctionsWithArgs_ExistenceRecord.find(func) != M_BindedFunctionsWithArgs_ExistenceRecord.end()) {
				M_BindedFunctionsWithArgs.push_back(func);
			}
		}

		inline void unbind(void(*func)()) {
			M_BindedFunctionsNoArgs_ExistenceRecord.erase(M_BindedFunctionsNoArgs_ExistenceRecord.find(func));
			M_BindedFunctionsNoArgs.erase(
				std::remove(M_BindedFunctionsNoArgs.begin(), M_BindedFunctionsNoArgs.end(), func),
				M_BindedFunctionsNoArgs.end()
			);
		}

		inline void unbind(void(*func)(keybind*)) {
			M_BindedFunctionsWithArgs_ExistenceRecord.erase(M_BindedFunctionsWithArgs_ExistenceRecord.find(func));
			M_BindedFunctionsWithArgs.erase(
				std::remove(M_BindedFunctionsWithArgs.begin(), M_BindedFunctionsWithArgs.end(), func),
				M_BindedFunctionsWithArgs.end()
			);
		}

		inline void clearAllBindings() {
			M_BindedFunctionsNoArgs.clear();
			M_BindedFunctionsWithArgs.clear();
		}

		inline std::vector<void(*)()>& getBindingsNoArgs() {
			return M_BindedFunctionsNoArgs;
		}

		inline std::vector<void(*)(keybind*)>& getBindingsWithArgs() {
			return M_BindedFunctionsWithArgs;
		}

		inline bool checkForBinding(void(*func)(keybind*)) {
			return (M_BindedFunctionsWithArgs_ExistenceRecord.find(func) != M_BindedFunctionsWithArgs_ExistenceRecord.end());
		}

		inline bool checkForBinding(void(*func)()) {
			return (M_BindedFunctionsNoArgs_ExistenceRecord.find(func) != M_BindedFunctionsNoArgs_ExistenceRecord.end());
		}

	private:
		friend keybind;
		std::vector<void(*)()> M_BindedFunctionsNoArgs;
		std::set<void(*)()> M_BindedFunctionsNoArgs_ExistenceRecord;
		std::set<void(*)(keybind*)> M_BindedFunctionsWithArgs_ExistenceRecord;
		std::vector<void(*)(keybind*)> M_BindedFunctionsWithArgs;

		keybind* M_ParentRef = NULL;
	};
}
#endif // !CHK_KEYBIND_BINDING_GROUP_HPP