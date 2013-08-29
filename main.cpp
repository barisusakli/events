#include <functional>
#include <iostream>
#include <vector>
#include <sstream>

#include "EventDispatcher.h"

class MyGame
{
public:
	MyGame():game(1){}

	void event1Handler(Event& event)
	{
		std::cout<<"Event received "<<event.type <<", target "<<event.target<<"\n";
	}
	
	int game;
};


class Player : public EventDispatcher
{
public:
	Player():a(5),b(3) {}
	
private:
	int a;
	int b;
};

void event2Handler(Event& event)
{	
	std::cout<<"Event received "<<event.type <<", target "<<event.target<<"\n";
}


int main()
{
	Player player;
	MyGame handler;	
		
	EventHandlerPtr eventHandler1 = player.addHandler("event1", &MyGame::event1Handler, handler);
	EventHandlerPtr eventHandler2 = player.addHandler("event2", &event2Handler);
		

	player.dispatchEvent(Event("event1"));
	player.dispatchEvent(Event("event2"));

	player.removeHandler("event1", eventHandler1);

	player.dispatchEvent(Event("event1"));
	player.dispatchEvent(Event("event2"));

	std::string word;
	std::cin>>word;
	return 0;
}



