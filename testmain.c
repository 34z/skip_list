#include "skiplist.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXLEVEL 12
#define PROB 2
#define MAXDATA 200000

void swap(int *data, int a,int b);

int main(){
	//set random
	srand(time(0));
	int i;
	int data[MAXDATA];
	// build up an array with nonredundant elements
	for(i=0;i<MAXDATA;i++) data[i] = i;
	int a,b; 
	// swap two elements randomly to make array random
	for(i=0;i<MAXDATA;i++){
		a = rand() % MAXDATA;
		b = rand() % MAXDATA;
		swap(data, a, b);
	}
	// cut a part as the init
	int initSize = 100000, testSize = 100;
	if(initSize + testSize > MAXDATA){
		printf("Please adjust the MAXDATA or size");
		return 0;
	}
	//init the skip list
	SkipList *list = create_skip_list(PROB, MAXLEVEL);
	for(i=0;i<initSize;i++) {
		insert(list, data[i]);
		//print(list);
	}
	//test begins!
	clock_t begin, end;
	double duration;
	//insert
	begin = clock();
	for(i=0;i<testSize;i++){
		insert(list, data[i+initSize]);
		//print(list);
	}
	end = clock();
	duration = (double)(end - begin);
	//duration = (double)(end - begin) / CLK_TCK / testSize;
	printf("Insert data into a skip list with %d elements\n", initSize);
	printf("costs %lf sec each step\n",duration);
	//delete (to keep random, we delete part of initial array)
	begin = clock();
	for(i=0;i<testSize;i++){
		delete(list, data[i]);
		//print(list);
	}
	end = clock();
	duration = (double)(end - begin);
	//duration = (double)(end - begin) / CLOCKS_PER_SEC / testSize;
	printf("Delete data from a skip list with %d elements\n", initSize);
	printf("costs %lf sec each step\n",duration);
	free_skip_list(list);
}

void swap(int *data, int a,int b){
	int temp;
	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}
