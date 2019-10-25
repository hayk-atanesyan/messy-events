#ifndef MESSYEVENTS_EVENTHUB_HPP
#define MESSYEVENTS_EVENTHUB_HPP

#include <event.hpp>
#include <ievent_listener.hpp>

#include <queue>
#include <list>
#include <unordered_map>
#include <string>
#include <functional>
#include <mutex>

namespace hapnmc { namespace messy_events {

    typedef std::queue<hapnmc::messy_events::Event> EventQueue;
    typedef std::unordered_map<std::string, EventQueue> EventQueueMap;
    typedef std::list<IEventListener* > ListenerList;
    typedef std::unordered_map<std::string, ListenerList> ListenerListMap;
    
	/** Central event manager.
	 *
	 *	Handles thread safe registering and consuming of events.
     *  Each event has a category, or a 'key' and listeners are registered to
     *  individual keys.
	 */
	class EventHub
	{    
	private:
        EventQueueMap _events;
        ListenerListMap _listeners;
        
        std::mutex _mtx_lists;
        
        void AddKey(const std::string& key);
        
	public:
		EventHub(){};
        
        /** An event is put into the internal queue and appropriate listeners are notified */
        void NewEvent(const std::string& key, Event e);
        void NewEvent(const std::string& key, const std::any& ctx);
        
        /** Listeners will be notified if an event is added with this key */
        void AddListener(const std::string& key, IEventListener& listener);
        /** Only unregister listener from a specific key, leave the rest if any. */
        void RemoveListener(const std::string& key, IEventListener& listener);
        /** Unregister the listener from every existing key */
        void RemoveListener(IEventListener& listener);
        
        bool HasEvents(const std::string& key) noexcept;
        
        int NumEvents(const std::string& key) noexcept;
        
        /*const Event& GetNextEvent(const std::string& key);
        void ConsumeEvent(const std::string& key, const Event& e);
        void ConsumeNextEvent(const std::string& key);*/
        
        /** The intended way of processing events. Provided function gets the next event in queue,
         *  which is removed from the hub immediately before the function is called.
         */
        void ProcessNextEvent(const std::string& key, std::function<void(const std::string& key, const Event& e)> f);
	};

}} // hapnmc::messy_events

#endif // MESSYEVENTS_EVENTHUB_HPP