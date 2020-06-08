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
	int random3; //0~100000�� random number
	int r1, r2, r3;
	int* array;
	int* array2;
	int* array3;
	int* array4;
	int t;
	int a, b; //swap�� ���� ��
	time_t start, end;
	double result;
	printf("100000 ������ ���ڸ� �Է��Ͻÿ�: ");
	scanf("%d", &n);

	array = (int*)malloc(sizeof(int) * n);   //sorting ��->��
	array2 = (int*)malloc(sizeof(int) * n);   //sorting ��


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
	insertion(n, &Q, array); //array�� ����� ������ n���� ���ڹ迭�� ���� ���ʷ� �ִ´�.

	/////////////////////////////////////////////////////////////
	start = time(NULL); //�ð� ���� ����

	//bubble_sort(array, n);

	end = time(NULL);//�ð� ���� ��
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


	// random�� �迭�� 1~n���� ���


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
	newnode->data = data; //�Ű������� �Է¹��� data�� ���θ��� data�� ����ֱ�

	newnode->next = NULL; //�ڿ� �߰����ִ� next�� �ƹ��͵� �ش���� �ʴ´�.

	if (isEmpty(Q))//������ ��
	{
		Q->head = newnode;
		Q->tail = newnode;
	}
	else
	{
		Q->tail->next = newnode; // �տ� �����ϴ� ����� ������ �̾��ֱ�
		Q->tail = newnode; // Queue�� ������ �� ���� ����
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
	eliminate = Q->head; //����ȭ
	data = eliminate->data; // ���� �� Node�� ����� data�� return�� �̿��Ͽ� ��ȯ�Ѵ�.

	Q->head = eliminate->next; // eliminate�� �Ǿ��� node�� ����ȭ ������, Q->front�� �ι�° node(eliminate->next)�� �̾��ش�
	Q->count = Q->count - 1;
	free(eliminate); //����
	return data;
}

int isEmpty(PriorityQ* Q)
{
	if (Q->head == NULL || Q->tail == NULL)
		return 1;
	else
		return 0;
}