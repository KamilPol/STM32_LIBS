#ifndef STATES_H
#define STATES_H
#include "board.h"

enum class StateNames; 

class States
{
private:
    
    
public:
    static void setState (StateNames _state);
    static void updateState();
    static void setInitState(StateNames _defState);
    static StateNames checkState (); 
    static volatile uint8_t picker; 
    static volatile uint8_t currentStateInt; 
    static volatile uint8_t maxStateInt;
    
};



#endif // STATES_H


