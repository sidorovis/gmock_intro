#include "mathlib.h"

#include <math.h>
#include <limits>

using namespace mathlib;

number::number() {
}

number::~number() {
}

namespace pimpl {
	class number_impl : public number {
	public:
		explicit number_impl(const int value) 
		: _value(value) 
		{
		}

		int value() const {
			return _value;
		}
		operator int() const {
			return value();
		}
		bool positive() const {
			return value() > 0;
		}
		bool add(const number& other) {
			const bool valid = _value + other.value() >= _value;
			if (valid)
				_value += other.value();
			return valid;
		}
		bool subtract(const number& other) {
			const bool valid = _value - other.value() <= _value;
			if (valid)
				_value -= other.value();
			return valid;
		}
		std::vector<int> prime_decomposition() const {
			std::vector<int> result;
			return result;
		}
	private:
		int _value;
	};
}

algebra::algebra(const int start_value)
	: _start_value(start_value) {
}

number* const algebra::create_number(int value) const {
	return new pimpl::number_impl(value);
}

