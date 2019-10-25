#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <event_hub.hpp>
#include <thread>
#include <chrono>
#include <any>
#include <list>
#include <algorithm>
//#include <iostream>

#include "testclass_elstnr.hpp"

#define thrwait(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

using namespace hapnmc::messy_events;

struct EventHubFixture
{
    EventHubFixture()
    {
    }
    ~EventHubFixture()
    {
    }

    EventHub event_hub;

    std::string evnt_key{"testing"};

    std::list<int> testlist {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
};

BOOST_FIXTURE_TEST_SUITE(EventHubTest, EventHubFixture)

BOOST_AUTO_TEST_CASE(event_hub_multithreading_events)
{
	BOOST_CHECK(event_hub.HasEvents(evnt_key) == 0);

	
	// generate events
	std::thread thr_1([this](){

		BOOST_CHECK(event_hub.HasEvents(evnt_key) == 0);

		thrwait(1);

		for(int i=1; i<20; i+=2) {
			std::any a = i;
			Event e;
			e.setContext(a);

			event_hub.NewEvent(evnt_key, e);

			//std::cout << "populated event " << i << std::endl;

			//thrwait(1);
		}
	});

	// generate more events
	std::thread thr_2([this](){

		thrwait(1);

		for(int i=0; i<20; i+=2) {
			std::any a = i;
			Event e;
			e.setContext(a);

			event_hub.NewEvent(evnt_key, e);

			//std::cout << "populated event " << i << std::endl;

			//thrwait(1);
		}
	});

	// consume events and check if they match
	std::thread thr_consumer([this](){

		tests::TestclassElstnr ec_el;
		event_hub.AddListener(evnt_key, ec_el);

		thrwait(40);

		// check if the expected number of events arrived
		BOOST_CHECK(ec_el.num_events_latest == (int)testlist.size());

		int while_loop_ctr{0};
		while(event_hub.HasEvents(evnt_key) && while_loop_ctr < 21) {

			// consume individual event
			event_hub.ProcessNextEvent(evnt_key, [this](const std::string& key, const Event& e){
				int value = std::any_cast<int>(e.getContext());

				//std::cout << "consumed event " << value << std::endl;

				std::list<int>::iterator findIter = std::find(testlist.begin(), testlist.end(), value);
				BOOST_REQUIRE(findIter != testlist.end());

				testlist.remove(value);
			});

			while_loop_ctr++;
		}

		// check that all events have been consumed
		BOOST_CHECK(testlist.empty());
	});


	thr_1.join();
	thr_2.join();
	thr_consumer.join();
	
} 

BOOST_AUTO_TEST_SUITE_END()