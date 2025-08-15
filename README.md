An interface-based state machine utility

Quick start
1. Add a UEFiniteStateMachineComponent to an Actor specialization (can be done in Blueprint or C++)
2. Create states by deriving from UEFiniteStateComponent (can be done in Blueprint or C++)
3. In each state override the desired Enter, Execute, and Exit functionality
4. Add those states to the same Actor
5. Assign the `InitialClass` property of the UEFiniteStateMachineComponent to the desired starting state
6. Add the Actor to the Map


Information


The provided component classes not required to use the tool. 
If building from scratch, first ensure the IUEFiniteStateMachine interface is implemented by the desired UObject.
Then, implement the IUEFiniteStateInterface for each UObject that will function as a state.
States can be added to the FSM using the interface functionality.
Runtime logic must call the appropriate state logic (e.g. Enter(), [First]Execute(), Exit().)
