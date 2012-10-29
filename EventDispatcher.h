


#ifndef INC_EVENTDISPATCHER_H
#define INC_EVENTDISPATCHER_H

#include <map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

#include "EventHandler.h"

class EventDispatcher
{
public:

	void addHandler(const std::string& type,EventHandler& handler)
	{
		if(!handler.isBound())
			return;
		_handlers[type].push_back(handler);
	}

	void removeHandler(const std::string& type,EventHandler& handler)
	{
		auto &v = _handlers[type];
		auto it = std::find(v.begin(),v.end(),handler);
		
		if(it != v.end()) {
			v.erase(it);
			if(!v.size())
				_handlers.erase(type);
		}		
	}
	
	void dispatchEvent(const std::string& type,const Event* event) const
	{
		auto it = _handlers.find(type);
		if(it != _handlers.end())
		{
			auto &v = it->second;
			for (auto eventHandler : v)
			{
				eventHandler(*this,event);
			}
		}
	}

private:
	std::map<std::string,std::vector<EventHandler>> _handlers;
};

#endif