#include <vector>

namespace mathlib {

	class number {
		number(const number&) = delete;
		number& operator=(const number&) = delete;
	protected:
		number();
	public:
		virtual ~number();
		virtual int value() const = 0;
		virtual operator int() const = 0;
		virtual bool positive() const = 0;
		virtual bool add(const number& other) = 0;
		virtual bool subtract(const number& other) = 0;
		virtual std::vector<int> prime_decomposition() const = 0;
	};

	class algebra {
		algebra(const algebra&) = delete;
		algebra& operator=(const algebra&) = delete;
	public:
		explicit algebra(const int start_value = 0);
		number* const create_number(int value) const;

	private:
		const int _start_value;
	};

}
