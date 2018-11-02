/*
 * StateMachine.cpp
 *
 *  Created on: 5 de out de 2017
 *      Author: Elidio
 */


#include "StateMachine.h"

StateMachine& StateMachine::operator<<(void * ptr)
{
  if(!ptr)
  {
    this->state = &STATE(doNothing);
  }
  return *this;
}

StateMachine& StateMachine::operator<<(int delay) {
  this->delay += delay;
  timer = 0;
  nextState = state;
  this->state = &STATE(wait);
  return *this;
}

StateMachine& StateMachine::operator<<(IState *state)
{
  if(!this->delay) {
      this->state = state;
      return *this;
  }
  else {
      nextState = state;
      this->state = &STATE(wait);
      timer = 0;
      return *this;
  }
}

void StateMachine::operator()()
{
  (*state)();
}

void StateMachine::wait()
{
     if (timer > delay) {
        state = nextState;
        delay = 0;
     }
}

void StateMachine::doNothing()
{
}



