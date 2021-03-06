/*
Arduino Buffered Serial
A library that helps establish buffered serial communication with a 
host application.
Copyright (C) 2010 Sigurður Örn Aðalgeirsson (siggi@media.mit.edu)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
 
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "IntBuffer.h"


IntBuffer::IntBuffer(){

}

void IntBuffer::init(unsigned int buf_length){
	data = (int*)malloc(sizeof(int)*buf_length);
	capacity = buf_length;
	position = 0;
	length = 0;
}

void IntBuffer::deAllocate(){
	free(data);
}

void IntBuffer::clear(){
	position = 0;
	length = 0;
}

int IntBuffer::getSize(){
	return length;
}

int IntBuffer::getCapacity(){
	return capacity;
}

int IntBuffer::peek(unsigned int index){
	return data[(position+index)%capacity];
}

int IntBuffer::put(int in){
	if(length < capacity){
		// save data at end of buffer
		data[(position+length) % capacity] = in;
		// increment the length
		length++;
		return 1;
	}
	// return failure
	return 0;
}



int IntBuffer::autoput(int in){
  if(length >= capacity){
    length--;
    // return failure
    //return 0;
  }
  
  // save data  at end of buffer
  if( position == 0 )
    position = capacity-1;
  else
    position = (position-1)%capacity;
  data[position] = in;
  // increment the length
  length++;
  return 1;

}


int IntBuffer::putInFront(int in){
	if(length < capacity){
		// save data byte at end of buffer
		if( position == 0 )
			position = capacity-1;
		else
			position = (position-1)%capacity;
		data[position] = in;
		// increment the length
		length++;
		return 1;
	}
	// return failure
	return 0;
}

int IntBuffer::get(){
	int b = 0;


	if(length > 0){
		b = data[position];
		// move index down and decrement length
		position = (position+1)%capacity;
		length--;
	}

	return b;
}

int IntBuffer::getFromBack(){
	int b = 0;
	if(length > 0){
		b = data[(position+length-1)%capacity];
		length--;
	}

	return b;
}

