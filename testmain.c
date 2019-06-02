#include "skiplist.h"
#include "list.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXLEVEL 15
#define PROB 2
#define MAXDATA 150000

void swap(int *data, int a,int b);

int main(){
	//set random
	srand(time(0));
	int i;
	int * data = (int *)malloc(sizeof(int) * MAXDATA);
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
	SkipList *skip = create_skip_list(PROB, MAXLEVEL);
	for(i=0;i<initSize;i++) {
		insert_skip_list(skip, data[i]);
	}
	// init the normal list
	Naive_List *naive = create_naive_list();
	for(i=0;i<initSize;i++){
		insert_naive_list(naive, data[i]);
	}
	//test begins!
	clock_t begin_s, end_s, begin_n, end_n;
	double times,duration_s,duration_n;
	//test insert (N = initSize)
	//test skip list
	begin_s = clock();
	for(i=0;i<testSize;i++){
		insert_skip_list(skip, data[i + initSize]);
	}
	end_s = clock();
	//test normal list
	begin_n = clock();
	for(i=0;i<testSize;i++){
		insert_naive_list(naive, data[i+initSize]);
	}
	end_n = clock();
	duration_s = (double)(end_s - begin_s);
	duration_n = (double)(end_n - begin_n);
	//times is the quotient of skipList divided by normalList
	times = duration_s / duration_n;
	printf("Insert_skip_list %d elements costs %lf\n", initSize, duration_s);
	printf("Insert_naive_list %d elements costs %lf\n", initSize, duration_n);
	printf("ratio : %lf\n",times);
	//delete (to keep random, we delete_skip_list part of initial array)
	//test skip list
	begin_s = clock();
	for(i=0;i<testSize;i++){
		delete_skip_list(skip, data[i]);
	}
	end_s = clock();
	//test normal list
	begin_n = clock();
	for(i=0;i<testSize;i++){
		delete_naive_list(naive, data[i]);
	}
	end_n = clock();
	duration_s = (double)(end_s - begin_s);
	duration_n = (double)(end_n - begin_n);
	times = duration_s / duration_n;
	printf("Delete_skip_list %d elements costs %lf\n", initSize, duration_s);
	printf("Delete_naive_list %d elements costs %lf\n", initSize, duration_n);
	printf("ratio : %lf\n",times);
	//search
	//test skip list
	begin_s = clock();
	for(i=testSize;i<testSize * 2;i++){
		search_skip_list(skip, data[i]);
	}
	end_s = clock();
	//test normal list
	begin_n = clock();
	for(i=testSize;i<testSize*2;i++){
		search_naive_list(naive, data[i]);
	}
	end_n = clock();
	duration_s = (double)(end_s - begin_s);
	duration_n = (double)(end_n - begin_n);
	times = duration_s / duration_n;
	printf("Search_skip_list %d elements costs %lf\n", initSize, duration_s);
	printf("Search_naive_list %d elements costs %lf\n", initSize, duration_n);
	printf("ratio : %lf\n",times);
	//free space
	free_skip_list(skip);
	free_naive_list(naive);
}

// swap the two elements in array
void swap(int *data, int a,int b){
	int temp;
	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}
