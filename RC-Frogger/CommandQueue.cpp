/**
@file    CommandQueue.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the CommandQueue class

*/
#include "CommandQueue.h"

namespace GEX {

	void CommandQueue::push(const Command& command)		// pushes a command onto the queue
	{
		_queue.push(command);
	}

	Command CommandQueue::pop()						// pops the queue
	{
		auto result = _queue.front();
		_queue.pop();
		return result;
	}
	bool CommandQueue::isEmpty() const		// tests if queue is empty
	{
		return _queue.empty();
	}
}