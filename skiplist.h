#ifndef SKIP_LIST_SKIPLIST_H
#define SKIP_LIST_SKIPLIST_H

typedef int ElementType;

typedef struct _Node Node;

typedef struct _Pointer
{
	Node * next;
//	Node * prev;
} Pointer;

struct _Node
{
	ElementType value;
	int level;
	Pointer ** pointer_list;
};

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

SkipList * insert(SkipList * list, ElementType value);
Node * search(SkipList * list, ElementType value);
SkipList * delete(SkipList * list, ElementType value);

int calculate_maxlevel(int prob, int number);
int random_level(int prob, int MaxLevel);

void print(SkipList * list);

void free_node(Node * node);
void free_skip_list(SkipList * list);

#endif //SKIP_LIST_SKIPLIST_H
