#ifndef CHK_UI_OBJECT_H
#define CHK_UI_OBJECT_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/Instance.h>
#include <chalk/lib/StandardEvents.h>
#include <chalk/lib/StandardFunctions.h>

namespace chk {
	class instance; // forward declaration
	class objectContainer; // forward declaration
	class UI_Object {
	public:

		virtual ~UI_Object() {} // Virtual destructor to make this class polymorphic

		inline virtual void updateTransform(bool callToParent = false) {

		}

		inline void refresh() {
			dirty_render_flag = true;
		}

	public:
		// SETTERS
		void setName(std::string name);

		void setParent(objectContainer* parent);


		// GETTERS
		std::string getName();

		objectContainer* getParent();
	protected:
		friend instance;
		friend objectContainer;

		objectContainer* M_parent = NULL;

		std::string M_Name;
	};
}

#endif // !CHK_UI_DRAWABLE_H