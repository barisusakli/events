#ifndef INC_FUNCTIONOBJECT_H
#define INC_FUNCTIONOBJECT_H


class Event;

class EventDispatcher;

class EventHandler
{
public:
	typedef std::function<void(const EventDispatcher&,const Event*)> HandlerFunc;
	
	EventHandler(){}
	EventHandler(HandlerFunc h):handlerFunc(new HandlerFunc(h)){}

	template <class T>
	void bind(void (T::*funcName)(const Event*)const,T* object)
	{
		HandlerFunc h = std::bind(funcName,object,std::placeholders::_2); 
		handlerFunc.reset(new HandlerFunc(h));
	}

	bool isBound() const
	{
		return handlerFunc;
	}
	
	void operator()(const EventDispatcher& dispatcher,const Event* event) const
    {
		if(handlerFunc)
    		(*handlerFunc)(dispatcher,event);
    }

	bool operator==(EventHandler const& other)
    {
		return handlerFunc == other.handlerFunc;
    }
private:
	std::shared_ptr<HandlerFunc> handlerFunc;
};

#endif