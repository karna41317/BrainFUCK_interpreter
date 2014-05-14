
//Include guard (Stdlib)
#ifndef __stdlib_H_INCLUDED__ 
	#define __stdlib_H_INCLUDED__
	#include <stdlib.h>

#endif

#ifndef __stdio_H_INCLUDED__
	#define __stdio_H_INCLUDED__
	#include <stdio.h>
#endif

#ifndef __string_H_INCLUDED__
	#define __string_H_INCLUDED__
	//Needed for memset
	#include <string.h>

#endif

//Get the struct and prototypes to fill
#include "BFState.h"

BFState createNewBFState(int size){
	BFState thing;
	thing.currentSize = size;
	//Allocate the memory for the array
	thing.tape = (char*) malloc(thing.currentSize);
	//Zero out the array
	memset(thing.tape,0,sizeof(thing.tape));
	thing.dataPointer = 0;

	return thing;
}

//Free's the memory allocated to the BFState's tape and resets its variables
void freeBFState(BFState * interp){
	free(interp->tape);
	interp->dataPointer = 0;
	interp->currentSize = 0;
}

//Takes a BFState pointer and modifys dataPointer and the size of the tape and currentSize
void incrementDataPointer(BFState * interp){
	//To make sure that we don't index out of bounds we can
	//Elect to either double the size of the tape, or to wrap.
	interp->dataPointer++;
	if(interp->dataPointer >= interp->currentSize){
		//Copy the array into a new one that is larger.
		char  newTape[(interp->currentSize*2)];
		int i;
		for(i=0; i < interp->currentSize; i++){
			newTape[i] = interp->tape[i];
		}
		interp->currentSize = interp->currentSize*2;
		interp->tape = newTape;
	}

}

//Modifies State of the BFState to have dataPointer -1
void decrementDataPointer(BFState * interp ){
	interp->dataPointer--;
	//We won't let it become negative
	if(interp->dataPointer < 0){
		printf("%s\n","Trying to decrement past 0. Ambigious behavior may occur");
		interp->dataPointer = 0;
	}
}

void incrementCurrentByte(BFState * interp){
	interp->tape[interp->dataPointer]++;
}

void decrementCurrentByte(BFState * interp){
	//Need to read the specification for BF to know to stop this at 0 or not
	interp->tape[interp->dataPointer]--;
}

void outputByte(const BFState * interp){
	//printf("%c", (char) interp->tape[interp->dataPointer]);
	putchar(interp->tape[interp->dataPointer]);
}

void inputByte(BFState * interp){
	printf("BF requests input: " );
	char c;
	//Do deal with a newline as input we have to get tricky:
	int i = 0;
	while((c = getchar()) != '\n'){
		i++;
		interp->tape[interp->dataPointer] = c;
	}
	if(i==0){
		interp->tape[interp->dataPointer] = '\n';
	}
	//scanf("%c",&interp->tape[interp->dataPointer]);
}

//Brackets [] where [ = while(tape[datapointer]!=0){  and  ] = } 
//should be implemented during program execution of reading the file or
//interpretting results.
