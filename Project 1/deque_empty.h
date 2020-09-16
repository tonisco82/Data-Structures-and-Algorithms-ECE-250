//============================================================================
// Name        : deque_empty.h
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#ifndef DEQUE_EMPTY_H_
#define DEQUE_EMPTY_H

class deque_empty{	//exception handling
public:
	const char* msg() const throw(){
		return "failure";
	}
};

#endif /* DEQUE_EMPTY_H_ */
