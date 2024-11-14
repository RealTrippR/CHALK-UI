#ifndef CHK_ENUMS_HPP
#define CHK_ENUMS_HPP
namespace chk {
	enum grid_alignment {
		horizontal,
		vertical
	};

	enum inputHandlingType {
		consume,
		passThrough,
		consumeAndPassThrough
	};
}

#endif // !CHK_ENUMS_HPP