#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node *next;
} Node;
/*
 *
 */
typedef struct
{
    /* TODO: ADD YOUR CODE HERE */
    Node *head;
    Node *tail;
} Queue;
/*
 *
 */
Queue *initialize()
{
    /* TODO: ADD YOUR CODE HERE */
    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}
/*
 *
 */
Node *newNode(Process p)
{
    Node *n = malloc(sizeof(Node));
    n->data = p;
    n->next = NULL;
    return n;
}
/*
*
*/
int isEmpty(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    if (q->head == NULL && q->tail == NULL)
        return 1;
    return 0;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
    }
    else
    {
        Node *temp = q->head;
        Process data = temp->data;
        q->head = temp->next;
        free(temp);
        if (q->head == NULL)
            q->tail = NULL;
        return data;
    }
}
/*
 *
 */
void enqueue(Queue *q, Process x)
{
    /* TODO: ADD YOUR CODE HERE */
    Node *n = newNode(x);
    if (isEmpty(q))
    {
        q->head = q->tail = n;
    }
    else
    {
        q->tail->next = n;
        q->tail = n;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    free(q);
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char *filename)
{
    /* TODO: ADD YOUR CODE HERE */
    printf("\n");
    Process p[15];
    Process temp;
    Queue *q = initialize();
    int i, watchingTime, count = 0;
    FILE *f = fopen(filename, "r");
    fscanf(f, "Watching time slots = %d", &watchingTime);
    while (!feof(f))
    {
        p[count].name = malloc(sizeof(char) * 15);
        fscanf(f, "%s %d %d", p[count].name, &p[count].starting_time, &p[count].remaining_time);
        count++;
    }
    fclose(f);

    for (i = 0; i < watchingTime; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (p[j].starting_time == i)
            {
                enqueue(q, p[j]);
            }
        }

        if (isEmpty(q))
        {
            printf("idle \t(%d-->%d)\n", i, i + 1);
        }
        else
        {
            temp = dequeue(q);
            printf("%s   \t(%d-->%d)", temp.name, i, i + 1);
            if (temp.remaining_time != 0)
            {
                temp.remaining_time--;
            }

            if (temp.remaining_time > 0)
            {
                enqueue(q, temp);
                printf("\n");
            }
            else
            {
                printf(" %s aborts\n", temp.name);
            }
        }
    }
    if (isEmpty(q))
    {
        printf("stop\n\n");
        destroy(q);
    }
    else
    {
        printf("stop, (watching time is over but some processes are not finished)\n\n");
        destroy(q);
    }
}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while (fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename) - 1] = '\0';
        if (fopen(filename, "r"))
        {
            RoundRobin(filename);
        }
        else
        {
            puts("\nFile Not Found!");
            puts("----------------------------------");
        }
        puts("\nEnter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }
    return 0;
}
