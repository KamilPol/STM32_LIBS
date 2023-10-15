#include "states.h"

volatile uint8_t States::picker = 0; 
volatile uint8_t States::currentStateInt = 0; 
volatile uint8_t States::maxStateInt =0;

void States::setState (StateNames _state)
{
    picker = static_cast <uint8_t>(_state);
}

void States::updateState()
{
    uint8_t maxStateInt = static_cast <uint8_t>(StateNames::count);
	(picker < maxStateInt -1) ? picker++ : picker=0;	

}
void States::setInitState(StateNames _defState)
{
	picker = static_cast<uint8_t>(_defState);
}

StateNames States::checkState ()
{
	return static_cast <StateNames>(picker);

}



