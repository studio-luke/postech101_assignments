#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);

typedef struct Node {
	int data;
	struct Node* next;
}Node;

typedef struct PriorityQ {
	int count;
	struct Node* head;
	struct Node* tail;
}PriorityQ;

void startQ(PriorityQ* Q);
void enQ(PriorityQ* Q, int data);
int deQ(PriorityQ* Q);
void insertion(int n, PriorityQ* Q, int* array);

int main()
{
	int n;
	int random1; //srand%10000
	int random2; //srand%11
	int random3; //0~100000의 random number
	int r1, r2, r3;
	int* array;
	int* array2;
	int* array3;
	int* array4;
	int t;
	int a, b; //swap에 쓰일 수
	time_t start, end;
	double result;
	printf("100000 이하의 숫자를 입력하시오: ");
	scanf("%d", &n);

	array = (int*)malloc(sizeof(int) * n);   //sorting 전->후
	array2 = (int*)malloc(sizeof(int) * n);   //sorting 전


	for (t = 0; t < n; t++)
	{
		array[t] = t + 1;
	}
	printf("\n");

	srand(time(NULL));


	for (t = 0; t < n; t++)
	{
		random1 = rand() % 10000;
		random2 = rand() % 11;
		random3 = random1 * 10 + random2;
		a = random3 % n;

		r1 = rand() % 10000;
		r2 = rand() % 11;
		r3 = r1 * 10 + r2;
		b = r3 % n;

		swap(&array[a], &array[b]);
	}

	for (t = 0; t < n; t++)
	{
		array2[t] = array[t];
	}

	for (t = 0; t < n; t++)
	{
		printf("%d ", array2[t]);
	}

	PriorityQ Q;
	startQ(&Q);
	insertion(n, &Q, array); //array에 저장된 랜덤한 n개의 숫자배열을 값을 차례로 넣는다.

	/////////////////////////////////////////////////////////////
	start = time(NULL); //시간 측정 시작

	//bubble_sort(array, n);

	end = time(NULL);//시간 측정 끝
	result = (double)(end - start);
	printf("\n");
	printf("time spent: %f sec", result);
	printf("\n");
	/////////////////////////////////////////////////////////////
	if (n < 11)
	{
		printf("before sorting:\n");
		for (t = 0; t < n; t++)
		{
			printf("%d ", array2[t]);
		}
		printf("\n");

		printf("after sorting:\n");
		for (t = 0; t < n; t++)
		{
			printf("%d ", deQ(&Q));
		}
	}


	// random한 배열로 1~n까지 출력


}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertion(int n, PriorityQ* Q, int* array)
{
	int i;
	for (i = 0; i < n; i++)
	{
		enQ(Q, array[i]);
	}
}

void enQ(PriorityQ* Q, int data)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data; //매개변수로 입력받은 data를 새로만든 data에 집어넣기

	newnode->next = NULL; //뒤에 추가해주니 next엔 아무것도 해당되지 않는다.

	if (isEmpty(Q))//시작할 때
	{
		Q->head = newnode;
		Q->tail = newnode;
	}
	else
	{
		Q->tail->next = newnode; // 앞에 선행하는 노드의 꼬리를 이어주기
		Q->tail = newnode; // Queue의 꼬리를 새 노드와 연결
	}
	Q->count = Q->count + 1;
}

void startQ(PriorityQ* Q)
{
	Q->head = NULL;
	Q->tail = NULL;
	Q->count = 0;
}

int deQ(PriorityQ* Q)
{
	int data;
	Node* eliminate;
	//eliminate = (Node*)malloc(sizeof(Node));
	eliminate = Q->head; //동기화
	data = eliminate->data; // 삭제 전 Node의 저장된 data를 return을 이용하여 반환한다.

	Q->head = eliminate->next; // eliminate를 맨앞의 node와 동기화 했으니, Q->front를 두번째 node(eliminate->next)와 이어준다
	Q->count = Q->count - 1;
	free(eliminate); //삭제
	return data;
}

int isEmpty(PriorityQ* Q)
{
	if (Q->head == NULL || Q->tail == NULL)
		return 1;
	else
		return 0;
}