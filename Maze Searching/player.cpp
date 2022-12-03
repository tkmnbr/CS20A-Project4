#include"player.h"
#include"entity.h"
#include"stack.h"
#include"list.h"
#include"room.h"
#include"maze.h"
#include<iostream>

//  Player( ... )
//		Constructs and initializes the Player/Entity and its member variables
//		Remembers and discovers the starting room.
Player::Player(Maze* maze, Room p, std::string name, char sprite, const bool tbacktrack)
	:Entity(maze, p, name, sprite),
	m_lookingPaper(),
	m_discoveredRooms(),
	m_btQueue(),
	m_btStack(),
	BACKTRACKENABLED(tbacktrack) {

	// Discover the starting room
	m_discoveredRooms.push_front(p);
	m_lookingPaper.enqueue(p);
}

//  stuck() 
//		See if the player is stuck in the maze (no solution)
bool Player::stuck() const {
	return Entity::state() == State::NOEXIT;
}

//  foundExit()
//		See if the player has found the exit
bool Player::foundExit() const {
	return Entity::state() == State::EXIT;
}

//  getTargetRoom()
//		Get the room the player wants to look around next.
//      If m_lookingPaper is empty then return an invalid room.
Room Player::getTargetRoom() const {
	if (m_lookingPaper.empty()) return Room(-1, -1);
	return m_lookingPaper.front();
}

// discovered
//		returns true if the item is in the list
bool Player::discovered(const Room &p) const {
	return (m_discoveredRooms.find(p) != -3);
}



// say()
//		What does the player say?
//		Already Implemented, nothing to do here
void Player::say() {

	// Freedom supercedes being eaten
	if (state() == State::EXIT) {
		std::cout << name() << ": WEEEEEEEEE!";
		return;
	} 
 
	// Being eaten supercedes being lost
	switch (interact()) {
	case Interact::ATTACK:
		std::cout << name() << ": OUCH!";
		break;
	case Interact::GREET:
		break;
	case Interact::ALONE:
	default:
		switch (state()) {
		case State::LOOK:
			std::cout << name() << ": Where is the exit?";
			break;
		case State::NOEXIT:
			std::cout << name() << ": Oh no! I am Trapped!";
			break;
		case State::BACKTRACK:
			std::cout << name() << ": Got to backtrack...";
			break;
		default:
			break;
		}

		break;
	}
}


//  update() 
//		This function implements an algorithm to look through the maze
//      for places to move (STATE::LOOK). update also handles moving the 
//		player as well, if there is an open undiscovered cell to move to the  
//		player just moves there.  However, there will be cases in the next 
//		desired room to look around is not adjacent (more than one cell away), 
//		at this room the player must backtrack (State::BACKTRACK) to a room 
//		that is adjacent to the next room the player was planning to visit
//
//		The player can only do one thing each call, they can either LOOK or 
//		BACKTRACK not both.  Nor should the player move more than one cell per
//		call to update.  If you examine the function calls for the entire game
//		you should observe that this is already be called within a loop. Your
//		Implementation should NOT have any loops that pertain to actual movement 
//		of the player.  
//
//		Backtracking is challenging, save it for the very very very last thing.
//		Make sure the STATE::LOOK aspect compiles and works first.
void Player::update() {

	if (BACKTRACKENABLED) {
		
	}
	else {
		//get the current pos
		//mark it as discovered
		//record curr pos 
		//m_lookingPaper.dequeu()
		//if next room is exit, then state EXIT

		//Room west(x-1, y)
		//Room east(x+1, y)
		//Room north(x, y-1)
		//Room south(x, y+1)

		//if west is open and not discovered, m_lookingPaper.enqueue(west) and m_discoveredRoom.pushfront(west)
		//...
		if (m_lookingPaper.empty()) {
			state(State::NOEXIT);
			return;
		}
		Room pos = m_lookingPaper.front();
		if (maze()->foundExit(pos)) {
			state(State::EXIT);
			return;
		}
		m_lookingPaper.dequeue();
		move(pos);

		Room west = Room(pos.x()-1, pos.y());
		Room east = Room(pos.x()+1, pos.y());
		Room north = Room(pos.x(), pos.y()-1);
		Room south = Room(pos.x(), pos.y()+1);

		if (maze()->open(west) and !discovered(west)) {
			m_lookingPaper.enqueue(west);
			m_discoveredRooms.push_front(west);
		}

		if (maze()->open(east) and !discovered(east)) {
			m_lookingPaper.enqueue(east);
			m_discoveredRooms.push_front(east);
		}

		if (maze()->open(north) and !discovered(north)) {
			m_lookingPaper.enqueue(north);
			m_discoveredRooms.push_front(north);
		}

		if (maze()->open(south) and !discovered(south)) {
			m_lookingPaper.enqueue(south);
			m_discoveredRooms.push_front(south);
		}

	}


	
}