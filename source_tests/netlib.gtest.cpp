#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "netlib/netlib.h"

using namespace netlib;

namespace {

	class mock_network : public network {
	public:
		MOCK_METHOD2(send_packet, bool(const char* const packet, const size_t size));
		MOCK_METHOD1(get_packet, const char* const(size_t* const size));
		MOCK_CONST_METHOD1(validate, void(const std::string& key));
	};

}


TEST(netlib, constructors) {
	EXPECT_NO_THROW(mock_network mn);
	mock_network mn;
	EXPECT_NO_THROW(net_protocol np(mn));
}

TEST(netlib, test_heartbeat) {
	mock_network mn;
	net_protocol np(mn);

	EXPECT_CALL(mn, send_packet(testing::_, 9))
		.Times(testing::Exactly(2))
		.WillOnce(testing::Return(true))
		.WillOnce(testing::Return(false));

	EXPECT_NO_THROW(np.heartbeat());
	EXPECT_THROW(np.heartbeat(), std::logic_error);
}

TEST(netlib, test_connect) {
	mock_network mn;
	net_protocol np(mn);
	EXPECT_CALL(mn, send_packet(testing::_, 12))
		.Times(2)
		.WillRepeatedly(testing::Return(true));

	EXPECT_CALL(mn, get_packet(testing::_))
		.Times(2)
		.WillOnce(testing::DoAll(
			testing::SetArgPointee<0>(5),
			testing::Return("world")
			))
		.WillOnce(testing::DoAll(
			testing::SetArgPointee<0>(6),
			testing::Return("no way")
			));
	EXPECT_NO_THROW(np.connect("the_password"));
	EXPECT_THROW(np.connect("the_password"), std::logic_error);
}

TEST(netlib, test_validate) {
	testing::NiceMock<mock_network> mn;
	net_protocol np(mn);

	EXPECT_NO_THROW(np.validate("key 1"));
	EXPECT_NO_THROW(np.validate("key 2"));
}


TEST(netlib, test_local_cache) {
	testing::StrictMock<mock_network> mn;
	net_protocol np(mn);

	EXPECT_NO_THROW(np.is_in_local_cache("key 1"));
	EXPECT_NO_THROW(np.is_in_local_cache("key 2"));
}
