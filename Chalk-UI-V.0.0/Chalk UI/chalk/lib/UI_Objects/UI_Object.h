#ifndef CHK_UI_DRAWABLE_H
#define CHK_UI_DRAWABLE_H

#include <chalk/lib/Universal_Includes.h>
#include <chalk/lib/StandardEvents.h>
#include <chalk/lib/StandardFunctions.h>

namespace chk {
	class Instance; // forward declaration
	class objectContainer; // forward declaration
	class UI_Object {
	public:

		// SETTERS
		void setName(std::string name);

		void setParent(objectContainer* parent);


		// GETTERS
		std::string getName();

		objectContainer* getParent();
	protected:
		objectContainer* M_parent = NULL;

		std::string M_Name;
	};
}

#endif // !CHK_UI_DRAWABLE_H