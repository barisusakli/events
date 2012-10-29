#include <functional>
#include <iostream>
 
#include "EventDispatcher.h"
#include "PlayerEvent.h"


class Player: public EventDispatcher
{
public:
	Player():health(100){}

	int health;

	void hit()
	{
		health -= 5;
		std::shared_ptr<PlayerEvent> event(new PlayerEvent(this));
		dispatchEvent("hit",event.get());
	}
};

class Game
{
public:
	EventHandler playerHitHandler;
	EventHandler playerHitHandler2;

	void init(Player& player)
	{
		
		playerHitHandler.bind<Game>(&Game::handleHit,this);
		playerHitHandler2.bind<Game>(&Game::handleHit2,this);
		
		player.addHandler("hit",playerHitHandler);
		player.addHandler("hit",playerHitHandler2);

	}

	void handleHit(const Event* event) const
	{
		const PlayerEvent* e = dynamic_cast<const PlayerEvent*>(event);
		std::cout<<"Player Hit Handler Health ["<<e->player->health<<"]"<<std::endl;
	}

	void handleHit2(const Event* event) const
	{
		const PlayerEvent* e = dynamic_cast<const PlayerEvent*>(event);
		std::cout<<"Player Hit Handler 2 Health ["<<e->player->health<<"]"<<std::endl;
	}
};

int main()
{

	Player p;
	Game g;

	g.init(p);
	
    p.hit();
	p.hit();
	p.removeHandler("hit",g.playerHitHandler);
	p.hit();

	int value;
	std::cin>>value;
	return 0;
}



