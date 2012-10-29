#ifndef INC_PLAYEREVENT_H
#define INC_PLAYEREVENT_H

#include <string>

#include "Event.h"

class Player;

class PlayerEvent: public Event
{
public:
	PlayerEvent(Player* player):player(player){}
	
	Player* player;
};

#endif 