#ifndef CHK_EVENT_HPP
#define CHK_EVENT_HPP

namespace chk {
	class UI_Object;

	// the Event class allows for the calling of functions binded upon being invoked.
	template<class T> class Event {
	public:
		// when this function is called, it will call all the functions binded to this event
		void invoke(T* val) {
			int tmp = 0;
			for (auto& f : M_BindedFunctionsWithArgsAndConsumedIndex) {
				f(val, tmp);
			}
			for (auto& f : M_BindedFunctionsWithArgs) {
				f(val);
			}
			for (auto& f : M_BindedFunctionsNoArgs) {
				f();
			}
		}

		inline void bind(std::function<void(T*)> func) {
			//if (!isAlreadyBound(func,M_BindedFunctionsWithArgs)) {
				M_BindedFunctionsWithArgs.push_back(func);
			//}
		}
		inline void bind(std::function<void(T*,int&)> func) {
			M_BindedFunctionsWithArgsAndConsumedIndex.push_back(func);
		}

		inline void bind(std::function<void()> func) {
			//if (!isAlreadyBound(func, M_BindedFunctionsNoArgs)) {
				M_BindedFunctionsNoArgs.push_back(func);
			//}
		}

		// also broken, because lambdas cant be compared.
		/*inline void unbind(std::function<void(T*)> func) {
			auto& v = M_BindedFunctionsWithArgs;
			v.erase(std::remove(v.begin(), v.end(), func), v.end());
		}

		inline void unbind(std::function<void()> func) {
			auto& v = M_BindedFunctionsNoArgs;
			v.erase(std::remove(v.begin(), v.end(), func), v.end());
		}*/
		
		inline void clearAllBindings() {
			M_BindedFunctionsWithArgs.clear();
			M_BindedFunctionsNoArgs.clear();
			M_BindedFunctionsWithArgsAndConsumedIndex.clear();
		}

		// unfortunately lambdas are not yet comparable, so this will not work
		/*bool checkForBinding(std::function<void(T*)> func) {
			return isAlreadyBound(func, M_BindedFunctionsWithArgs);
		}

		bool checkForBinding(std::function<void()> func) {
			return isAlreadyBound(func, M_BindedFunctionsNoArgs);
		}*/

		// returns as reference
		inline std::function<void(T*)>& getBindingsWithArgs() {
			return M_BindedFunctionsWithArgs;
		}

		// returns as reference
		inline std::function<void()>& getBindingsNoArgs() {
			return M_BindedFunctionsNoArgs;
		}
		// returns as reference
		inline std::function<void(T*, int&)>& getBindingsNoArgsAndConsumedIndex() {
			return M_BindedFunctionsWithArgsAndConsumedIndex;
		}

	protected:
		std::vector<std::function<void(T*)>> M_BindedFunctionsWithArgs;
		std::vector<std::function<void(T*,int&)>> M_BindedFunctionsWithArgsAndConsumedIndex;
		std::vector<std::function<void()>> M_BindedFunctionsNoArgs;

		// BROKEN: DOES NOT WORK ON LAMBDAS BECAUSE THEY CANNOT BE COMPARED
		// Helper to check if a function is already bound
		/*template<typename FuncType>
		bool isAlreadyBound(const std::function<FuncType>& func, const std::vector<std::function<FuncType>>& functionList) {
			return std::any_of(functionList.begin(), functionList.end(),
				[&](const std::function<FuncType>& existingFunc) {
					return func.target_type() == existingFunc.target_type() &&
						func.target<FuncType>() == existingFunc.target<FuncType>();
				});
		}*/
	};
}

#endif