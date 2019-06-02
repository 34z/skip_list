#ifndef SKIP_LIST_SKIPLIST_H
#define SKIP_LIST_SKIPLIST_H

typedef int ElementType;

typedef struct _Node Node;

/**
 * struct _Pointer
 * @member next				[the pointer to next node]
 */
typedef struct _Pointer
{
	Node * next;
} Pointer;

/**
 * struct _Node
 * @member value
 * @member level			[the level of current node]
 * @member pointer_list		[list of pointers, whose size is equal to level]
 */
struct _Node
{
	ElementType value;
	int level;
	Pointer ** pointer_list;
};

/**
 * @member head
 * @member prob				[the probability is equal to 1 / prob]
 * @member MAXLEVEL
 * @member number			[current node number in list]
 *
 */
typedef struct _SkipList
{
	Node * head;
	int prob;
	int MAXLEVEL;
	int level;
	int number;
} SkipList;

SkipList * create_skip_list(int prob, int MAX);
Pointer ** create_pointer_list(int level);
Pointer * create_pointer();
Node * create_node(ElementType value, int level);

SkipList * insert_skip_list(SkipList *list, ElementType value);
Node * search_skip_list(SkipList *list, ElementType value);
SkipList * delete_skip_list(SkipList *list, ElementType value);

int calculate_maxlevel(int prob, int number);
int random_level(int prob, int MaxLevel);

void print_skip_list(SkipList *list);

void free_node(Node * node);
void free_skip_list(SkipList * list);

#endif //SKIP_LIST_SKIPLIST_H
