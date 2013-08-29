

#ifndef INC_EVENTDISPATCHER_H
#define INC_EVENTDISPATCHER_H

#include <map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

#include "Event.h"

typedef std::function<void(Event&)> EventHandler;
typedef std::shared_ptr<EventHandler> EventHandlerPtr;

class EventDispatcher
{
public:

	template<class T, class G>
	EventHandlerPtr addHandler(const std::string& type, T&& handlerFunc, G& handlerObject)
	{
		EventHandlerPtr ptr = std::make_shared<EventHandler>(std::bind(handlerFunc, handlerObject, std::placeholders::_1));		
		
		_handlers[type].push_back(ptr);
		return ptr;
	}

	template<class T>
	EventHandlerPtr addHandler(const std::string& type, T&& handlerFunc)
	{
		EventHandlerPtr ptr = std::make_shared<EventHandler>(std::bind(handlerFunc, std::placeholders::_1));		
		
		_handlers[type].push_back(ptr);
		return ptr;
	}

	void removeHandler(const std::string& type, EventHandlerPtr handler)
	{
		auto &v = _handlers[type];
		
		auto it = std::find(v.begin(), v.end(), handler);
		
		if(it != v.end()) {
			v.erase(it);
			if(!v.size())
				_handlers.erase(type);
		}		
	}
	
	void dispatchEvent(Event& event) 
	{
		auto it = _handlers.find(event.type);
		if(it != _handlers.end())
		{
			auto &v = it->second;
			event.target = this;
			for (auto eventHandler : v)
			{
				(*eventHandler)(event);
			}
		}
	}
	
private:

	std::map<std::string,std::vector<EventHandlerPtr>> _handlers;
};

#endif
