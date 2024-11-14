#ifndef UI_PADDING_DATA_H
#define UI_PADDING_DATA_H

namespace chk {
	class UI_PaddingData {
	public:
		UI_PaddingData() = default;
		UI_PaddingData(int left, int right, int top, int bottom) {
			this->top = top;
			this->bottom = bottom;
			this->left = left;
			this->right = right;
		}

		int top = 0;
		int bottom = 0;
		int left = 0;
		int right = 0;
	};
}

#endif // !UI_PADDING_DATA_H
