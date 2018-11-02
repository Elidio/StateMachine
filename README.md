# StateMachine

Arduino made easy embedded projecting and prototyping. You don't even need to be a pro to try your hand at this plataform.
However, doing two things at same time is dificult if you don't know what you are doing. Most useful project ideas requires
sensor reading, motor controlling and conectivity. How can you read your temperature sensor every 5 seconds, check your position
on GPS while you activate a servo motor and transmit it over GPRS to a remote NodeRed server using MQTT?
You don't. But you can init the sensor, then move the servo a few degrees, check your NMEA readings and issue an AT command.
Doing so is bafflingly complicated, but you can make your life easier using state machines.

# What is a State Machine?  

The technical definition of State Machine is a device that can be in one of a set number of states depending on it's previous
conditions and on the present value of the inputs.
On your project, a state machine is a set of functions associated with a larger task. Each function does a small part of said
task, check some condition and then changes the state, so the next time the state machine runs, another function will run thus 
progressing to the completion of that task.

# Why should I use State Machines?

Thinking with state machines will make your life easier when you want to multitask. You can run one state of state machine A,
then one state of state machine B, and so on, giving to the user of your gadget the impression that you are doing a lot of things
at same time. It will allow you to focus on coding one module at a time and still be able to make lots of things at same time.
Using state machines in interleaving is the closest you will get to multithreading with Arduino.

# Usage

This library is not like your average library. It does not deliver a set of functions to acomplish some task like reading an RTC
or displaying data on a LCD. In fact, this library provides exactly zero functions.

# So, How I use it?

First of all, you must create an state machine. A state machine is a class that inherits the magic sauce of this library.
Doing so is easy.

#include <StateMachine.h>

``` c++
  class STATEMACHINE(MyStateMachine) {
  }
```
Then you must create the states. The STATE object is a wrapper. It allows the library to know that one function is a state
and what to do with it.

``` c++
  class STATEMACHINE(MyStateMachine) {
    CREATE_STATE(s1);
    CREATE_STATE(s2);
    CREATE_STATE(s3);
    ...
  }
```
Then you create the function associated with each state.

``` c++
  class STATEMACHINE(MyStateMachine) {
    CREATE_STATE(s1);
    CREATE_STATE(s2);
    CREATE_STATE(s3);
    ...
    
    void s1(){
    // do something here
    }
    
    void s2(){
    // do something here
    }
    
    void s3(){
    // do something here
    }
    
    ...
    
  }
```

Then you must create the class constructor. The constructor is an special function that is called when the class is instantiated
and it serves to initialize all variables to it's initial conditions.

``` c++
  class STATEMACHINE(MyStateMachine) {
    CREATE_STATE(s1);
    CREATE_STATE(s2);
    CREATE_STATE(s3);
    ...
    
    void s1(){
    // do something here
    }
    
    void s2(){
    // do something here
    }
    
    void s3(){
    // do something here
    }
    
    ...
    
    MyStateMachine(/*the initialization parameters*/) :
      INIT_STATE(s1),
      INIT_STATE(s2),
      INIT_STATE(s3),
      ...
    
  }
```

That is all.

# How do I use the State Machine?

To use your state machine you have to instantiate it. There are two ways of doing so:

MyStateMachine myStateMachine(/*init parameters*/);
MyStateMachine *myStateMachine = new MyStateMachine(/*init parameters*/);

You should do so on global space, so your state machines are accessible to the loop() function.

in the loop function you just call your machine state.

``` c++
 loop() {
  myStateMachine() // call it like this if you instantiated to a variable
  (*myStateMachine)() // call it like this if you instantiated to a pointer.
 }
```
# Changing States

The fun in dealing with state machines is that each time it is called it does a different thing. In order to control what it 
will do, you have to change states. To change states is easy


``` c++
  *this << &STATE(s1);
``` 

This can be done from anywhere whithin the machine state class. Any method public or private, not only states. 
The state machine starts on the idle state. It is a hidden state that does nothing. You can define the initial state of your 
state machine doing that command from the class constructor, or awake the state machine from a public method.

To send the state machine back to sleep is easy.

``` c++
  *this << &STATE(NULL);
``` 
This sends the state machine back to idle mode.

You may also want to make the state machine wait some time in idle mode before transitioning to the next state. That can be 
easyly acomplished doing this:

``` c++
  *this << &STATE(s2) << 5000;
``` 
This will make the state machine become idle for 5 seconds before switching to state s2.

For more information, please check the example section.

