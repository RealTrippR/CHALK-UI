#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/DirtyRenderFlag.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/UI_Objects/UI_Object.h>

namespace chk {
	template <class T>
	class value : public UI_Object {
	public:
		T val;

		// returns the typename of T
		// for example: value<int> v; v.getTypeName() would return int
		const char* getTypeName() {
			return typeid(T).name();
		}
	};
}