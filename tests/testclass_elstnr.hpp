#ifndef MESSYEVENTS_TESTCLASS_ELSTNR_HPP
#define MESSYEVENTS_TESTCLASS_ELSTNR_HPP

#include <ievent_listener.hpp>
#include <list>

namespace hapnmc { namespace messy_events { namespace tests {

	class TestclassElstnr : public IEventListener
	{
	public:
		int num_events_latest{0};

		void EventAdded(std::string key, int curr_num_events) override
		{
			num_events_latest = curr_num_events;
		}
	};

}}} // hapnmc::messy_events::tests

#endif // MESSYEVENTS_TESTCLASS_ELSTNR_HPP