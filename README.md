#Usage

    //Create a class that derives from EventDispatcher
	class Player : public EventDispatcher
	{
	
	};
	
	//Create a class that has a function
	class Game
	{
	public:
		void event1Handler(Event& ev){}		
	};
	
	// free functions also work
	void event2Handler(Event& ev){}
	
	int main() {
	  Player player;
	  MyGame handler;	
	
	  //addHandler returns a shared_ptr to the std::function
	  EventHandlerPtr eventHandler1 = player.addHandler("event1", &MyGame::event1Handler, handler);
	  player.addHandler("event2", &event2Handler);
		
	  // dispatching events will call the member function and the free function
	  player.dispatchEvent(Event("event1"));
	  player.dispatchEvent(Event("event2"));
      
	  // you can remove a handler using the shared_ptr returned from addHandler
	  player.removeHandler("event1", eventHandler1);
      
	  // dispatching again will only call event2Handler since eventHandler1 is removed
	  player.dispatchEvent(Event("event1"));
	  player.dispatchEvent(Event("event2"));
	
	  return 0;
	}
	
	
	