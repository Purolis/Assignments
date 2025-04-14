#include <stdio.h>
#include <stdlib.h>

#define G "S->pA:A->oS|pB:B->pC|o:C->o\0" //:D
#define STATE_SIZE 10

struct Grammar {
	struct State ** start;
};

struct State {
	char id;
	struct Transition ** transitions;
};

struct Transition {
	char transition;
	struct State * next;
};

struct Grammar * parseGrammar(char *);
struct State * makeState();
struct State * fillState(char *);
int findState(char car, struct State ** stList);
void printGram(struct Grammar *);

int main() {
	struct Grammar * g1 = parseGrammar(G);
}

struct Grammar * parseGrammar(char * grahm) {
	struct Grammar * g = malloc(sizeof(struct Grammar));
	struct State ** stList = malloc(STATE_SIZE * sizeof(struct State *));
	int stListCrount = 0;
	int crount = 0;
	while (grahm[crount] != '\0') {
		// //stuff goes here
		// printf("%c\n", grahm[crount]);
		// printf("Count: %d\n", crount);
		if (grahm[crount] == 45) { //B)
			stList[stListCrount] = makeState();
			stList[stListCrount]->id = grahm[crount-1];
			stListCrount++;
		}
		crount++;
	}
	crount = 0;
	stListCrount = -1;
	int trainNum = 0;
	while (grahm[crount] != '\0') {
		//transitions now
		printf("%c\n", grahm[crount]);
		if (grahm[crount] == 62 || grahm[crount] == 124) { // > or |
		// 	// Foundded a new trans
			if (grahm[crount+1] >= 97 && grahm[crount+1] <= 122) { //low :) == terminal
				printf("Term: %c\n", grahm[crount+1]);

			stList[stListCrount]->transitions[trainNum]->transition = grahm[crount+1];
			}
			if (grahm[crount+2] >= 65 && grahm[crount+2] <= 90) { //upper, we also have more room  we foundded the next state
				printf("State: %c\n", grahm[crount+2]);

		 		int state = findState(grahm[crount+2], stList);
				//stList[stListCrount]->transitions[trainNum]->next = stList[state];
			}
		trainNum++;
		}
		if (grahm[crount + 1] == '-') {
			stListCrount++;
			trainNum = 0;
		}
		crount++;
	}
	g->start = stList;
	return g;
}

void printGram(struct Grammar * g) {
	int count = 0;
	while (g->start[count] != NULL) {
		printf("stateName: %c\n", g->start[count]->id);
		int count2 = 0;
		do {
			printf("\tterminal: %c\n", g->start[count]->transitions[count2]->transition);
			if (g->start[count]->transitions[count2]->next != NULL) {
				printf("\tnextState: %c\n", g->start[count]->transitions[count2]->next->id);
			}
			count2++;
		} while (g->start[count]->transitions[count2]->transition != '\0');
		count++;
	}
}

int findState(char car, struct State ** stList) {
	int count = 0;
	int fart = -1;

	printf("Car: %c\n", car);

	while (stList[count] != NULL) {
		printf("--?%c\n",stList[count]->id);
		if (stList[count]->id == car) {
			fart = count;
			printf("%d\n", fart);
		}
		count++;
		printf("%d\n", count);
		printf("------%d\n", fart);
	}
	if (fart == -1) {
		printf("state list does not contain that Procedure??\n");
	}

	return fart;
}

struct State* fillState(char * transitions) {
	struct State * state = makeState();
	state->id = '\0';
	int count = 0;
	while (transitions[count] != '\0') {
		state->transitions[count]->transition = transitions[count];
		state->transitions[count]->next = NULL;
		count++;
	}
	return state;
}


struct State * makeState() {
	struct State * s1 = malloc(sizeof(struct State));
	s1->transitions = malloc(STATE_SIZE * sizeof(struct Transition *));
	s1->transitions[STATE_SIZE] = NULL;
	for (int i = 0; i < STATE_SIZE; i++) {
		s1->transitions[i] = malloc(sizeof(struct Transition));
	}

	return s1;
}
