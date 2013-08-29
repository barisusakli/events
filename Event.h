#ifndef INC_EVENT_H
#define INC_EVENT_H

class EventDispatcher;

class Event
{
public:
	Event(const std::string& type):type(type), target(nullptr){}
	
	virtual ~Event(){};

	std::string type;
	EventDispatcher* target;
};

#endif 