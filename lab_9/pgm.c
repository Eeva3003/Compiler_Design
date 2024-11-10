//there has to be a struct
//dot function is not used
//all function void
//referring NFA *nfa (always in star)


#include<stdio.h>
#define MAX_STATES 100
#define MAX_SYMBOLS 100

 typedef struct {// dont forget typedef
int transition[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
int epsilon[MAX_STATES][MAX_STATES];
int numStates;
int numSymbols;
} NFA; //This is capital nfa , later u declare small nfa with this in main 

/*void addTransition(NFA *nfa, int from, int to, int symbol)
void addEpsilonTransition(NFA *nfa, int from, int to)
void epsilonClosure(NFA *nfa, int state, int *closure, int *closureSize)
*/

//This function adds a regular transition for the NFA:
void addTransition(NFA *nfa, int from, int to, int symbol) {//include dat structure with eaxch 
nfa->transition[from][symbol][to] = 1;
}

//This function adds an epsilon tran
void addEpsilonTransition(NFA *nfa, int from, int to) {
nfa->epsilon[from][to] = 1;
}

/*The function adds the current state to the closure.
It recursively checks for any epsilon transitions from the current state to other states and includes them in the closure if not already included.
The closure is built by exploring all epsilon transitions reachable from the state.*/



void epsilonClosure(NFA *nfa, int state, int *closure, int *closureSize) {// clsoure is the array storing the elemenys , closuresize is the poinetr to number of closure in the array(initially at 0)
closure[*closureSize] = state;//adding itself into the closure array first
(*closureSize)++;
// Check for epsilon transitions
for (int i = 0; i < nfa->numStates; i++) {
if (nfa->epsilon[state][i]) {
// Check if state is already in closure
int alreadyInClosure = 0;
for (int j = 0; j < *closureSize; j++) {
//This inner loop iterates over the states currently in the closure array, which contains all the states that are already included in the epsilon closure.
if (closure[j] == i) {
alreadyInClosure = 1;
break;
}
}
if (!alreadyInClosure) {
epsilonClosure(nfa, i, closure, closureSize);// no * at all in calling, iteratively calling for more epsilon clousre
}
}
}
}


int main() {
NFA nfa;
int epsilonClosureResult[MAX_STATES];
printf("Enter the number of states: ");
scanf("%d", &nfa.numStates);// here dot opetator is used 
printf("Enter the number of input symbols: ");
scanf("%d", &nfa.numSymbols);

for (int i = 0; i < nfa.numStates; i++) {
for (int j = 0; j < nfa.numSymbols; j++) {
for (int k = 0; k < nfa.numStates; k++) {
//It initializes the transition and epsilon matrices with zeros, indicating no transitions initially.
nfa.transition[i][j][k] = 0; // No transitions
}
}

for (int k = 0; k < nfa.numStates; k++) {
nfa.epsilon[i][k] = 0; // No epsilon transitions
}
}

 //then prompts the user to input the transitions for each state. For each state and symbol,
 //the user is asked to input a state to transition to. If the user enters -1, it indicates the end of input for that symbol (or an epsilon transition).

for (int i = 0; i < nfa.numStates; i++) {
printf("\nEnter the transitions for state %d\n",i);
for (int j = 0; j < nfa.numSymbols; j++) {
printf("\t for symbol %c: ", j==nfa.numSymbols-1? 35 : j+97);

int toState;

while (1) {// a wihle loop here
scanf("%d", &toState);

if(toState == -1) break;

if(j==nfa.numSymbols-1) //checking whether epsilon transition or normal input transition
addEpsilonTransition(&nfa, i, toState); // &nfa is given

else
addTransition(&nfa, i, toState, j);
}
}
}

for (int i = 0; i < nfa.numStates; i++) {
int closure[MAX_STATES];// initialise closure and closuresizr
int closureSize = 0;
epsilonClosure(&nfa, i, closure, &closureSize);// & not used for array
printf("Epsilon closure of state %d: { ", i);
for (int j = 0; j < closureSize; j++) {
printf("%d ", closure[j]);
}
printf("}\n");
}
return 0;
}
