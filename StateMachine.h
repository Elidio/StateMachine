#ifndef __STATEMACHINE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __STATEMACHINE_H_INCLUDED__   //   #define this so the compiler knows it has been included

//#include "Function.h"
#include <elapsedMillis.h>

template <typename...Ts>
class Self;

template <typename X, typename...Ts>
class Self<X, Ts...> : public Ts...
{
protected:
    typedef X self;
};

#define WITH_SELF(X) X : public Self<X>
#define WITH_SELF_DERIVED(X,...) X : public Self<X,__VA_ARGS__>


#define STATEMACHINE(X) WITH_SELF_DERIVED(X, StateMachine)
#define CREATE_STATE(state) State<self> state_##state
#define INIT_STATE(state) state_##state(this, &self::state)
#define STATE(state) state_##state

class StateMachine;

class IState
{ 
      friend class StateMachine;
      int delay = 0;    
    public:
      virtual void operator()();
      virtual ~IState(){};
};

template <class T> class State : public IState
{
    T *sm;
    void (T::*state)();
  public:
    void operator()() {(sm->*state)();};
    State(T *sm, void (T::*state)()) :
      sm(sm),
    state(state)
    { 
    };

    ~State()
    {
    }
};

class WITH_SELF(StateMachine)
{

  private:
    elapsedMillis timer;
    int delay = 0;
    void doNothing();
    void wait();
    IState *state;
    IState *nextState;

    CREATE_STATE(doNothing);
    CREATE_STATE(wait);
 
  public:
    StateMachine(): 
      INIT_STATE(doNothing),
      INIT_STATE(wait),
      state(&STATE(doNothing)),
      timer(0)
    {
    }

    StateMachine(IState *state): 
      INIT_STATE(doNothing),
      INIT_STATE(wait),
      state(state),
      timer(0)
    { 
    }

    ~StateMachine()
    {
    }

    void operator()();


    StateMachine& operator<<(IState* state);
    StateMachine& operator<<(void * ptr);
    StateMachine& operator<<(int delay);
    operator IState (){return IState(*state);};
    
};

#endif 

