#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "mathlib/mathlib.h"

using namespace mathlib;

namespace {

	class mock_number : public number {
	public:
		explicit mock_number(number* const initial)
			: _initial( initial ) {
		}
		explicit mock_number() 
			: _initial(algebra().create_number(45))
		{
			delegate_to_fake();
		}
		operator int() const {
			return value();
		}
		MOCK_CONST_METHOD0(value, int());
		MOCK_CONST_METHOD0(positive, bool());
		MOCK_METHOD1(add, bool(const number& other));
		MOCK_METHOD1(subtract, bool(const number& other));
		MOCK_CONST_METHOD0(prime_decomposition, std::vector<int>());

		void delegate_to_fake() {
			ON_CALL(*this, value()).
				WillByDefault(testing::Invoke(_initial.get(), &number::value));
		}
	private:
		const std::unique_ptr<number> _initial;
	};

}

//namespace {
//    class number_mock : public tl::number {
//    public:
//        MOCK_METHOD1(copy, void(const number& copy));
//        MOCK_CONST_METHOD0(valid, bool());
//        MOCK_CONST_METHOD0(int_value, int());
//
//        MOCK_CONST_METHOD0(prime_decomposition, std::vector<int>());
//
//        MOCK_METHOD1(add, void(const int i));
//        MOCK_METHOD1(subtract, void(const int i));
//    };
//
//
//    std::vector<int> to_int(const std::vector<std::unique_ptr<tl::number>>& v) {
//        std::vector<int> res;
//        for(const auto& i : v) {
//            res.push_back(i->int_value());
//        }
//        return res;
//    }
//}
//
TEST(mathlib, constructors) {
	ASSERT_NO_THROW(algebra);
	algebra myalgebra;
	number* n45 = myalgebra.create_number(45);
	EXPECT_EQ(45, *n45);
	delete n45;
	testing::NiceMock<mock_number> mn45;
	EXPECT_EQ(45, mn45);
}

TEST(mathlib, number_value) {
	algebra myalgebra(33);
	testing::NiceMock<mock_number> n0(myalgebra.create_number(-33));
	EXPECT_EQ(0, n0);
	EXPECT_EQ(0, n0.value());
}
//
//TEST(tl_test, add_subtract) {
//    std::unique_ptr<tl::number> number(tl::number::create_unique_number(3));
//    EXPECT_EQ(3, number->int_value());
//    ASSERT_NO_THROW(number->add(6));
//    EXPECT_EQ(9, number->int_value());
//    ASSERT_NO_THROW(number->subtract(4));
//    EXPECT_EQ(5, number->int_value());
//}
//
//TEST(tl_test, algebra_sum) {
//    std::unique_ptr<number_mock> five(new number_mock);
//    std::unique_ptr<number_mock> seven(new number_mock);
//    tl::algebra algebra;
//
//    EXPECT_CALL(*five, int_value())
//            .Times(1)
//            .WillOnce(testing::Return(5));
//
//    EXPECT_CALL(*seven, int_value())
//            .Times(1)
//            .WillOnce(testing::Return(7));
//
//    std::unique_ptr<tl::number> sum_result(algebra.sum(*five, *seven));
//
//    EXPECT_EQ(12, sum_result->int_value());
//}
//
//TEST(tl_test, algebra_subtract) {
//    std::unique_ptr<number_mock> five(new number_mock);
//    std::unique_ptr<number_mock> seven(new number_mock);
//    tl::algebra algebra;
//
//    EXPECT_CALL(*five, int_value())
//            .Times(1)
//            .WillOnce(testing::Return(5));
//
//    EXPECT_CALL(*seven, int_value())
//            .Times(1)
//            .WillOnce(testing::Return(7));
//
//    std::unique_ptr<tl::number> subtract_result(algebra.subtract(*five, *seven));
//
//    EXPECT_EQ(-2, subtract_result->int_value());
//}
//
//TEST(tl_test, algebra_prime_decomposition) {
//    tl::algebra algebra;
//
//    std::unique_ptr<number_mock> number(new number_mock);
//    EXPECT_CALL(*number, int_value())
//            .Times(testing::Exactly(10))
//            .WillOnce(testing::Return(2))
//            .WillOnce(testing::Return(3))
//            .WillOnce(testing::Return(4))
//            .WillOnce(testing::Return(5))
//            .WillOnce(testing::Return(6))
//            .WillOnce(testing::Return(7))
//            .WillOnce(testing::Return(17))
//            .WillOnce(testing::Return(22))
//            .WillOnce(testing::Return(32))
//            .WillOnce(testing::Return(100));
//
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(2));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(3));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(2, 2));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(5));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(2, 3));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(7));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(17));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(2, 11));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(2, 2, 2, 2, 2));
//    ASSERT_THAT(to_int(algebra.prime_decomposition(*number)), testing::ElementsAre(2, 2, 5, 5));
//}
//
//TEST(tl_test, algebra_max) {
//    tl::algebra algebra;
//    std::vector<std::unique_ptr<tl::number> vec;
//    vec.emplace_back(new number_mock);
//    vec.emplace_back(new number_mock);
//    vec.emplace_back(new number_mock);
//    vec.emplace_back(new number_mock);
//    vec.emplace_back(new number_mock);
//    vec.emplace_back(new number_mock);
//
//    EXPECT_CALL(*vec[0], int_value())
//            .Times(testing::AtMost(1))
//            .WillOnce(testing::Return(15));
//}
//
////TEST(A,B) {
////    numberMock number1(7);
////    numberMock number2(9);
//
////    EXPECT_CALL(number1, m3(testing::Ge(4)))
////          .Times(2)
////          .WillOnce(testing::Return(5))
////          .WillOnce(testing::Return(2));
//
////    EXPECT_CALL(number2, m3(testing::An<int>()))
////            .Times(testing::AtMost(2))
////            .WillOnce(testing::Return(2))
////            .WillOnce(testing::Return(6));
//
////    tl::operation o;
////    const std::unique_ptr<tl::number> number3 = o.sum(number1, number2);
////    ASSERT_EQ(7, number3->m3(1000));
//
////    const std::unique_ptr<tl::number> number4 = o.sum(number1, number2);
////    ASSERT_EQ(8, number4->m3(1000));
//
//
////    EXPECT_CALL(number1, m7(testing::_))
////          .Times(1)
////          .WillOnce(testing::Return(std::vector<int>{4, 5}));
//
////    ASSERT_EQ((std::vector<int>{4, 5}), number1.m7(std::vector<int>{7, 8}));
//
////    EXPECT_CALL(number1, m7(testing::WhenSorted(testing::UnorderedElementsAre(7,8))))
////          .Times(testing::AtMost(1))
////          .WillOnce(testing::Return(std::vector<int>{4, 5}));
//
////    ASSERT_EQ((std::vector<int>{4, 5}), number1.m7(std::vector<int>{8, 7}));
//
////    int a, b;
//
////    EXPECT_CALL(number1, m3(testing::_))
////          .Times(testing::AtLeast(2))
////          .WillOnce(testing::DoAll(testing::SaveArg<0>(&a), testing::Return(8)))
////          .WillOnce(testing::DoAll(testing::SaveArg<0>(&b), testing::Return(4)));
//
////    EXPECT_EQ(4, o.diff(number1, number1)->m3(1000));
////    EXPECT_EQ(4, a);
////    EXPECT_EQ(6, b);
//
////}
