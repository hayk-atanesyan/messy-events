#ifndef MESSYEVENTS_IEVENT_LISTENER_HPP
#define MESSYEVENTS_IEVENT_LISTENER_HPP

#include <string>

namespace hapnmc { namespace messy_events {
    
    /**
     * Optional interface for notifying when an event with a specific key got added.
     * 
     * A listener is NOT supposed to process events in a callback, this is 
     * strictly an optional component for altering the state of the event processor
     * and notifying it to check for new events in case it normally does not.
     */
    class IEventListener 
    {
    public:
        virtual void EventAdded(std::string key, int curr_num_events) = 0;
    };
    
}} // hapnmc::messy_events

#endif // MESSYEVENTS_IEVENT_LISTENER_HPP