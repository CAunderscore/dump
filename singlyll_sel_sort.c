#include <stdio.h>
#include <stdlib.h>

void display();

unsigned int count = 0;

struct node {						// struct for item details
	int itemID;
	struct node* next;				// pointer to next node
};

struct node* list = NULL;

struct node* seekPrev(struct node* n)
{
	struct node* temp = list;
	while (temp->next != NULL)
	{
		if (temp->next == n)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

struct node* nodeAt(int index)
{
	struct node* temp = list;

	if (index > count - 1)
		return NULL;

	for (int i = 0; i < index; i++)
		temp = temp->next;
	
	return temp;
}

void swap(struct node* left, struct node* right)
{
	struct node* leftPrev, * rNextTemp, * rightPrev;
	// When left elem. is the head and the right elem. is right next to it
	if (left == list && right == left->next)
	{
		left->next = right->next;
		right->next = left;
		list = right;
	}
	// if there's some elements between left and right and left is the head
	else if (left == list)
	{
		rightPrev = seekPrev(right);
		rNextTemp = right->next;
		right->next = left->next;
		left->next = rNextTemp;
		rightPrev->next = left;
		list = right;
	}
	// if left is NOT the head, and two nodes are next to each other
	else if (right == left->next)
	{
		leftPrev = seekPrev(left); rightPrev = seekPrev(right);
		rNextTemp = right->next;

		right->next = left;
		left->next = rNextTemp;
		leftPrev->next = right;
	}
	else
	{
		leftPrev = seekPrev(left); rightPrev = seekPrev(right);
		rNextTemp = right->next;

		right->next = left->next;
		left->next = rNextTemp;
		leftPrev->next = right;
		rightPrev->next = left;
	}
	display();
}

void add(int id)
{
	struct node* n = malloc(sizeof(struct node));
	n->itemID = id; n->next = NULL;
	struct node* last_elem = list;	// initialize a struct ptr var for traversal
	
	// if list is empty, the head is the item
	if (list == NULL)
		list = n;
	else
	{
		while (last_elem->next != NULL)
			last_elem = last_elem->next;
		last_elem->next = n;
	}
	count++;
}

void sort()
{
	// selection sort
	
	struct node* curr = NULL, * temp = NULL, * min = NULL;
	for (int i = 0; i < count - 1; i++) // last element is always sorted
	{
		curr = nodeAt(i);
		min = curr;
		temp = curr->next;
		while (temp != NULL)
		{
			// if the compare element is smaller than the current minimum, set current minimum to compare element
			if (temp->itemID < min->itemID)
				min = temp;
			
			temp = temp->next;
		}
		// then swap.
		// if the current Element is the head (the struct* variable "list"), make the minElem the head.
		if (min != curr)	// if the minimum element and current element are equal, don't swap
			swap(curr, min);
	}
	
}

void display()
{
	struct node* temp = list;
	while (temp != NULL)
	{
		printf("%d  ", temp->itemID);
		temp = temp->next;
	}
	printf("\n");
}
int main()
{
	add(3);
	add(5);
	add(2);
	add(4);
	add(1);
	display();
	sort();
	display();
	return 0;
}