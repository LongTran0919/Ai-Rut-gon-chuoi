#include <algorithm>
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>
#include <string>
#include <iostream>
#include <time.h>
#include<random>
#include "RutGonChuoi.h"

using namespace std;

enum class Actions { AB, AC, BB, EA, EB, EC, EE };
#define SIDE 256 // Length of the board


typedef struct Node_array
{

	char state[SIDE];
	struct Node_array* parent; // tree search
	int depth;
	Actions actions;
	struct Node_array* nextNode; // list


} Node;

struct NodeList {
	unsigned int nodeCount;    //the number of nodes in the list
	Node* head;            //pointer to the first node in the list
	Node* tail;            //pointer to the last node in the list
};

bool checkTrue(char a[])
{
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] != 'E' && a[i] != 'e' && a[i] != 'A' && a[i] != 'a' && a[i] != 'B' && a[i] != 'b' && a[i] != 'C' && a[i] != 'c')
			return false;
	}
	return true;
}
bool  checkFail(char a[])
{
	int dem = 0;
	if ((a[0] == 'B' && a[1] == 'C') || a[0] == 'B' || a[0] == 'C'||a[strlen(a)-1]=='A')
		return true;
	for (int i = 0; i < strlen(a); i++)
	{
		
		if (a[i] == 'B')
		{
			dem++;
		}
	}
	if (dem % 2 == 1)
		return true;
	return false;
}
void copy_string(char a[], char b[])//copy b to a
{
	int i;
	int len = strlen(b);
	a[len] = '\0';
	for (i = 0; i < len; i++)
		a[i] = b[i];
}

int is_equal(char a[])
{
	int flag = 0;
	if (strcmp(a, "E") == 0)
		flag = 1;
	return flag;
}
void Actionnn(Node* node)
{
	printf("      Action: ");
	if (node->actions == Actions::AB)
		printf("AB->BC");
	if (node->actions == Actions::AC)
		printf("AC->E");
	if (node->actions == Actions::BB)
		printf("BB->E");
	if (node->actions == Actions::EA)
		printf("EA->A");
	if (node->actions == Actions::EB)
		printf("EB->B");
	if (node->actions == Actions::EC)
		printf("EC->C");
	if (node->actions == Actions::EE)
		printf("EE->E");

}
void Solution(Node* node) {
	printf("======================================");
	printf("\nSolution\n");
	while (node->parent != NULL)
	{
		puts(node->state);
		printf("-------------------------\n");
		printf("            ^            \n");
		Actionnn(node);
		printf("\n");
		node = node->parent;
	}
	printf("-------------------------\n");
	puts(node->state);
	printf("-------------------------\n");

}

Node* Child_node(Node* node, int x)
{
	Node* child = (Node*)malloc(sizeof(Node));
	int len = strlen(node->state);
	copy_string(child->state, node->state);
	int i = x;
	int j = i + 1;
	child->parent = node;
	if (child->state[i] == 'A')
	{
		if (child->state[j] == 'B')
		{
			child->state[i] = 'B';
			child->state[j] = 'C';
			child->actions = Actions::AB;
		}
		else if (child->state[j] == 'C')
		{
			child->state[i] = 'E';
			for (int h = j; h < len - 1; h++)
			{
				child->state[h] = child->state[h + 1];
			}
			child->state[len - 1] = '\0';
			child->actions = Actions::AC;
		}
	}
	else if (child->state[i] == 'B')
	{
		if (child->state[j] == 'B')
		{
			child->state[i] = 'E';
			for (int h = j; h < len - 1; h++)
			{
				child->state[h] = child->state[h + 1];
			}
			child->state[len - 1] = '\0';
			child->actions = Actions::BB;
		}
	}
	else if (child->state[i] == 'E')
	{
		if (child->state[j] == 'A')
		{
			child->state[i] = 'A';
			child->actions = Actions::EA;
		}
		if (child->state[j] == 'B')
		{
			child->state[i] = 'B';
			child->actions = Actions::EB;
		}
		if (child->state[j] == 'C')
		{
			child->state[i] = 'C';
			child->actions = Actions::EC;
		}
		if (child->state[j] == 'E')
		{
			child->state[i] = 'E';
			child->actions = Actions::EE;
		}
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
	}

	return child;
}

NodeList* FIFO_initial()
{
	NodeList* list;
	list = (NodeList*)malloc(sizeof(NodeList));
	list->nodeCount = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}
void FIFO_add(NodeList* list, Node* node) {
	if (list->nodeCount <= 0) {
		list->head = node;
		list->tail = node;
		list->nodeCount += 1;
		return;
	}
	list->tail->nextNode = node;


	list->tail = node;
	list->nodeCount += 1;
}
Node* FIFO_pop(NodeList* list) {
	if (list->nodeCount <= 0) {
		return NULL;
	}
	Node* temp = list->head;
	list->nodeCount -= 1;
	if (list->nodeCount <= 0) {
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		list->head = temp->nextNode;
	}
	return temp;
}
void LIFO_add(NodeList* list, Node* node)
{
	if (list->nodeCount <= 0)
	{
		list->head = node;
		list->tail = node;
		list->nodeCount += 1;
		return;
	}
	node->nextNode = list->head;
	list->head = node;
	list->nodeCount += 1;
}
Node* LIFO_pop(NodeList* list)
{
	if (list->nodeCount <= 0)
	{
		return NULL;
	}
	Node* temp = list->head;
	if (list->nodeCount <= 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->head = temp->nextNode;
	}
	list->nodeCount -= 1;
	return temp;
}
Node* RemoveNode(NodeList* list, Node* node)
{
	Node* n1 = list->head;
	Node* n2 = n1->nextNode;
	if (list->nodeCount <= 0)
	{
		return NULL;
	}
	for (int i = 0; i < list->nodeCount; i++)
	{
		if (is_equal(n2->state))
		{
			n1->nextNode = n2->nextNode;
		}
		n1 = n1->nextNode;
	}
}
bool Goal_test(Node* node)
{
	return is_equal(node->state);
}
bool checkExist(NodeList* list, Node* node) {
	Node* _node;
	int i = 0;
	_node = list->head;
	while (i < list->nodeCount)
	{
		if (strcmp(node->state, _node->state) == 0)
		{
			return true;
		}
		_node = _node->nextNode;
		i++;
	}
	return false;
}

void breadthFirstSearch(Node* root) {
	Node* node = root;
	if (Goal_test(node))
	{
		Solution(node);
		return;
	}
	NodeList* frontier;// open
	NodeList* explorer;//cloese
	frontier = FIFO_initial();
	explorer = FIFO_initial();

	FIFO_add(frontier, node);
	do
	{
		node = (FIFO_pop(frontier));
		/*if (checkFail(node->state) == true)
		{
			printf("No Solution\n");
			return;
		}*/
		FIFO_add(explorer, node);
		for (int i = 0; i < strlen(node->state) - 1; i++)
		{
			Node* child = (Child_node(node, i));
			if (checkExist(explorer, child) == false || checkExist(frontier, child) == false)
			{
				child->depth = node->depth + 1;
				if (Goal_test(child))
				{
					Solution(child);
					return;
				}
				if (child->depth < 20)
					FIFO_add(frontier, child);
			}

		}
	} while (frontier->nodeCount > 0);
	printf("No Solution\n");
}

int heuristic(Node* root, Node* node)
{
	int sum = 0;
	for (int i = 0; i < strlen(node->state); i++)
	{
		if (node->state[i] == 'E')
		{
			sum++;
		}
		if ((node->state[i] == 'A' && node->state[i + 1] == 'C') || (node->state[i] == 'B' && node->state[i + 1] == 'B'))
		{
			sum++;
		}
	}
	sum += strlen(root->state) - strlen(node->state);
	return sum;
}

void heuristic_add(NodeList* list, Node* root, Node* node)
{
	if (list->nodeCount <= 0)
	{
		list->head = node;
		list->tail = node;
		list->nodeCount += 1;
		return;
	}
	else
	{
		Node* temp = list->head;
		Node* p;
		if (heuristic(root, temp) < heuristic(root, node))
		{
			node->nextNode = list->head;
			list->head = node;
			list->nodeCount += 1;
		}
		else
		{
			FIFO_add(list, node);
			/*node->nextNode = temp->nextNode;
			list->head->nextNode = node;
			list->nodeCount += 1;*/
		}


	}
}
Node* prenode(NodeList* list, Node* a)
{
	Node* temp = list->head;
	while (temp->nextNode != a)
	{
		temp = temp->nextNode;
	}
	return temp;
}



void HeuristicSearch(Node* root)
{
	Node* node = root;
	int action;
	if (Goal_test(node))
	{
		Solution(node);
		return;
	}

	NodeList* frontier;
	NodeList* explorer;
	frontier = FIFO_initial();
	explorer = FIFO_initial();
	LIFO_add(frontier, node);
	while (frontier->nodeCount > 0)
	{
		node = LIFO_pop(frontier);

		LIFO_add(explorer, node);
		//action
		for (int i = 0; i < strlen(node->state) - 1; i++)
		{
			Node* child = (Child_node(node, i));
			if (checkExist(explorer, child) == false)
				if (checkExist(frontier, child) == false)
				{
					child->depth = node->depth + 1;
					if (Goal_test(child))
					{
						Solution(child);
						return;
					}


					heuristic_add(frontier, root, child);
				}

		}
	}
	printf("No solution\n");
}

void TestCode(char* chuoi, int dodaichuoi)
{
	srand(time(NULL));
	char khuon[9] = "ABCEabce";
	int dodaikhuon = strlen(khuon);

	for (int i = 0; i < dodaichuoi; i++)
	{

		chuoi[i] = khuon[rand() % 9];
	}
	chuoi[dodaichuoi] = '\0';
}

int random(int a, int b)
{
	int x = a + rand() % (b - a + 1);
	return x;

}

int main()
{
	
	clock_t start_t, end_t, total_t;
	double time_use1, time_use2;
	Node* Start;
	Start = (Node*)malloc(sizeof(Node));
	Start->parent = NULL;
	Start->depth = 0;
	int turn;
	do
	{
		printf("Enter your Start state:");
		gets_s(Start->state);
		_strupr_s(Start->state);
		printf("Chon 1 de thuc thi thuat toan BFS\nChon 2 de thuc thi thuat toan A*\n");
		
		do
		{
			scanf_s("%d", &turn);
		} while (turn != 1 && turn != 2);
	} while (checkTrue(Start->state) == false);
	start_t = clock();
	if(turn==1)
	{
		breadthFirstSearch(Start);
	}
	if(turn==2)
	{
		HeuristicSearch(Start);
	}
	end_t = clock();
	time_use1 = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("ton %f giay\n", time_use1);
	//printf("Chon 1 de thuc thi thuat toan BFS\nChon 2 de thuc thi thuat toan A*\n");
	//int turn;
	//do
	//{
	//scanf_s("%d", &turn);
	//} while (turn != 1 && turn != 2);
	//clock_t start_t, end_t, total_t;
	//double time_use1, time_use2;
	//Node* chuoi;
	//chuoi = (Node*)malloc(sizeof(Node));
	//chuoi->parent = NULL;
	//chuoi->depth = 0;
	//int i = 0;
	//int longg;
	//printf("Mời nhập độ dài bộ thử:");
	//scanf_s("%d", &longg);
	//int sum = 0;
	//int timeTB = 0;
	//srand(5);
	//start_t = clock();
	//while (i < 1)
	//{
	//	int dodai = longg;
	//	int x;
	//	for (int j = 0; j < dodai; j++)
	//	{
	//		x = random(0, 3);
	//		if (x == 0)
	//		{
	//			chuoi->state[j] = 'A';
	//		}
	//		if (x == 1)
	//		{
	//			chuoi->state[j] = 'B';
	//		}
	//		if (x == 2)
	//		{
	//			chuoi->state[j] = 'C';
	//		}
	//		if (x == 3)
	//		{
	//			chuoi->state[j] = 'E';
	//		}
	//	}
	//	chuoi->state[dodai] = '\0';
	//	puts(chuoi->state);
	//	_strupr_s(chuoi->state);
	//	//start_t = clock();
	//	if(turn==1)
	//	{
	//	breadthFirstSearch(chuoi, sum);
	//	}
	//	if(turn==2)
	//	{
	//	HeuristicSearch(chuoi,sum);
	//	}
	//	/*end_t = clock();
	//	time_use1 = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	//	timeTB += time_use1;*/
	//	i++;
	//}
	//printf("Sum : %d \n", sum);
	//end_t = clock();
	//time_use1 = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	//printf("ton %f giay\n", time_use1);
	return 0;
}
//aecababbbbb





