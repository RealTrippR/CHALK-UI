#ifndef CHK_INSTANCE_HPP
#define CHK_INSTANCE_HPP

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>

namespace chk {

	class UI_Object;
	class UI_Drawable;

	class instance {
	public:
		template <typename T> T& New(T* copyFrom = nullptr, std::string name="") {
			T* obj = NULL;
			if (copyFrom == nullptr) {
				obj = new T;
			} else {
				obj = new T;
				new (obj) T(*copyFrom);
				obj->M_parent = NULL;
			}
			if (!name.empty()) {
				obj->setName(name);
			}
			if (obj) {
				M_objects.push_back(obj);
			}
			else {
				std::cerr << "FAILED TO CREATE OBJ - OBJ WAS NULL!";
				throw std::runtime_error("FAILED TO CREATE OBJ - OBJ WAS NULL!");
			}
			dirty_render_flag = true; //refresh

			return *obj;
		}

		template <typename T> T& New(std::string name) {
			return New<T>(nullptr, name);
		}

		template <typename T> T& New() {
			return New<T>(nullptr,"");
		}

		void Remove(UI_Object* obj) {
			M_objects.erase(std::find(M_objects.begin(), M_objects.end(), obj));
			delete obj;
			obj = NULL;

			chk::dirty_render_flag = true; //refresh
		}
	private:
		std::vector<UI_Object*> M_objects;
	};

	extern instance Instance;

}

#endif // !CHK_INSTANCE_HPP