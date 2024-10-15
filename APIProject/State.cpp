#include "pch.h"
#include "State.h"

#include "Player.h"
#include "StateMachine.h"

State::State(Player* player, StateMachine* stateMachine, PlayerState stateType)
: mPlayer(player), mStateMachine(stateMachine), mType(stateType)
{
}
