#include <event_hub.hpp>

namespace hapnmc { namespace messy_events {
    
    void EventHub::AddKey(const std::string& key)
    {
        if(_events.find(key) == _events.end()) {
            _events.emplace(key, EventQueue());
        }
        if(_listeners.find(key) == _listeners.end()) {
            _listeners.emplace(key, ListenerList());
        }
    }
    
    void EventHub::NewEvent(const std::string& key, Event e)
    { 
        std::unique_lock<std::mutex> lock(_mtx_lists);
        
        AddKey(key);
        _events[key].push(e);
        
        int size = _events[key].size();
        
        lock.unlock();
        
        if(_listeners.find(key) != _listeners.end()) {
            for (auto lstnr : _listeners[key]) {
                lstnr->EventAdded(key, size);
            }
        }
        
    }
    
    void EventHub::NewEvent(const std::string& key, const std::any& ctx)
    {
        Event e;
        e.setContext(ctx);
        
        NewEvent(key, e);
    }
    
    void EventHub::AddListener(const std::string& key, IEventListener& listener)
    {
        std::lock_guard<std::mutex> lock(_mtx_lists);
        
        AddKey(key);
        
        _listeners[key].push_back(&listener);
    }
    void EventHub::RemoveListener(const std::string& key, IEventListener& listener)
    {
        std::lock_guard<std::mutex> lock(_mtx_lists);
        
        if(_listeners.find(key) == _listeners.end()) {
            return;
        }

        _listeners[key].remove(&listener);
    }
    void EventHub::RemoveListener(IEventListener& listener)
    {
        std::lock_guard<std::mutex> lock(_mtx_lists);

        for (auto pair : _listeners)
        {
            pair.second.remove(&listener);
        }
    }

    bool EventHub::HasEvents(const std::string& key) noexcept
    {
        return NumEvents(key) > 0;
    }
    
    int EventHub::NumEvents(const std::string& key) noexcept
    {
        std::lock_guard<std::mutex> lock(_mtx_lists);
        
        if(_events.find(key) == _events.end()) {
            return 0;
        }
        return _events[key].size();
    }
    
    void EventHub::ProcessNextEvent(const std::string& key, std::function<void(const std::string& key, const Event& e)> f)
    {
        std::unique_lock<std::mutex> lock(_mtx_lists);
        
        Event e = _events[key].front();
        _events[key].pop();
        
        lock.unlock();

        f(key, e);
    }
    
}} // hapnmc::messy_events