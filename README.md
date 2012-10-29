#Usage

    // define an event handler
	EventHandler playerHitHandler;
	
	// bind a function to it		
	playerHitHandler.bind<Game>(&Game::handleHit,this);
	
	// add the handler to a class that inherits EventDispatcher	
	player.addHandler("hit",playerHitHandler);
	
	// dispatch the event
	std::shared_ptr<PlayerEvent> event(new PlayerEvent(this));
	player.dispatchEvent("hit",event.get());
	
	// the handler Game::handleHit will be called and passed the PlayerEvent
	void handleHit(const Event* event) const
	{
		const PlayerEvent* e = dynamic_cast<const PlayerEvent*>(event);
		std::cout<<"Player Hit Handler Health ["<<e->player->health<<"]"<<std::endl;
	}
	
	//to remove and event call removeHandler and pass the EventHandler object
	player.removeHandler("hit",playerHitHandler);