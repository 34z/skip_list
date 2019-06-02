#include "skiplist.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	srand(time(0));
	SkipList * list = create_skip_list(2, 4);
	int data[] = {1, 2, 3, 123, 235, 231, 657, 54, 65, 4, 5, 9, 6, 7};
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
//		printf("inserting %d\n", data[i]);
		insert_skip_list(list, data[i]);
//		printf("-------\n");
	}
	print_skip_list(list);

	printf("%p\n", search_skip_list(list, 7));
	printf("%p\n", search_skip_list(list, 1));
	printf("%p\n", search_skip_list(list, 657));
	printf("%p\n", search_skip_list(list, 757));
	printf("%p\n", search_skip_list(list, 1024));

	delete_skip_list(list, 7);
	print_skip_list(list);

	free_skip_list(list);
	return 0;
}