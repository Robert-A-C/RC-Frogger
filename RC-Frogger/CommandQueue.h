/**
@file    CommandQueue.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the COmmandQueue class

*/
#pragma once
#include <queue>
#include "Command.h"

namespace GEX {
	class CommandQueue
	{
	public:
		void push(const Command& command);	// pushes a command onto the queue
		Command pop();						// pops the queue
		bool isEmpty() const;				// tests if queue is empty

	private:
		std::queue<Command>		_queue;
	};
}
