#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <event.hpp>
#include <any>

using namespace hapnmc::messy_events;

struct EventFixture
{
    EventFixture()
    {
    }
    ~EventFixture()
    {
    }

    Event event;
};

BOOST_FIXTURE_TEST_SUITE(EventTest, EventFixture)

BOOST_AUTO_TEST_CASE(event_generic)
{
	BOOST_CHECK(!event.hasContext());

	std::string some_str = "some text";
	std::any myany;
	myany = some_str;
	event.setContext(myany);
	BOOST_CHECK(event.hasContext());

	BOOST_CHECK(std::any_cast<std::string>(event.getContext()).compare(some_str) == 0);
} 

BOOST_AUTO_TEST_SUITE_END()