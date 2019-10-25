#ifndef MESSYEVENTS_EVENT_HPP
#define MESSYEVENTS_EVENT_HPP

#include <any>
#include <chrono>

namespace hapnmc { namespace messy_events {

	/** A basic universal event.
	 *
	 *  Set the context (any relevant data) and let it loose in the hub, not much else going on here.
	 */
	class Event
	{
    private:
	    
	    //bool _processed{false};
	    
	    std::any _context;

	    std::chrono::system_clock::time_point _context_creation_system_clock_time;
        
        
	public:
	    Event() noexcept {};
	    Event(const std::any& ctx) { setContext(ctx); }

	    virtual ~Event(){};

	    /* Processed flag indicating whether the event was successfully processed before.
	    bool getProcessed() const noexcept { return _processed; }
	    void setProcessed(bool processed) noexcept { _processed = processed; }  */
	    
	    /** Context is used to store any data relevant to the event handlers. Set manually. */
	    const std::any& getContext() const noexcept { return _context; }
	    void setContext(const std::any& ctx) 
	    { 
	    	_context = ctx;
	    	_context_creation_system_clock_time = std::chrono::system_clock::now();
	    }
	    const bool hasContext() const noexcept { return _context.has_value(); }

	    /** System clock time at the moment context was set, intended to be used for comparison between events in an asynchronous environment. Potential pitfall: system_clock is not monotonic. */
	    const std::chrono::system_clock::time_point& getContextCreationTime() const noexcept 
	    { return _context_creation_system_clock_time; }

	};

}} // hapnmc::messy_events

#endif // MESSYEVENTS_EVENT_HPP