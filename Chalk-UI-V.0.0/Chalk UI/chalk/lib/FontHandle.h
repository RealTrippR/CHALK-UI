#ifndef FONT_HANDLE_H
#define FONT_HANDLE_H

namespace chk {
	class FontHandle {
	public:
		int index = 0; // -1 represents a clear handle
		FontHandle() = default;
		FontHandle(int i) {
			index = i;
		}
	};
}

#endif // !FONT_HANDLE_H
