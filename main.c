#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct stack stack;
typedef struct elephant elephant;


struct node
{
    int r, c;
    node *next;
};

struct stack
{
    node *head;
};

struct elephant
{
    stack memory;
};


// make node
node *createNode(int row, int col)
{
    // allocate
    node *res = (node *)malloc(sizeof(node));

    // give values
    res->r = row;
    res->c = col;
    res->next = NULL;

    return res;
}

// add node
node *insertHead(node *head, int row, int col)
{
    node *newHead = createNode(row, col);

    if (head == NULL)//check if empty
    {
        return newHead;
    }

    newHead->next = head;
    return newHead;
}

// delete node
node *removeHead(node *head)
{
    if (head == NULL)//check if emtpy
    {
        return NULL;
    }

    node *newHead = head->next;
    return newHead;
}

// create stack
stack *createStack()
{
    stack *stk = (stack *)malloc(sizeof(stack));
    stk->head = NULL;
    return stk;
}

// add to stack
void push(stack *stk, int row, int col)
{
    stk->head = insertHead(stk->head, row, col);
}

// remove from stack
void pop(stack *stk)
{
    if (stk->head)
    {
        stk->head = removeHead(stk->head);
    }
}

// peek at stack
void top(stack *stk, int *row_ptr, int *col_ptr)
{
    if (stk && stk->head)
    {
        (*row_ptr) = stk->head->r;
        (*col_ptr) = stk->head->c;
    }
}

//add watermelons to grid
void addBait(int **grid, int row, int col, int amt)
{
    grid[row][col] += amt;
}

//return/update amt of watermelons
int eatBait(int **grid, int row, int col)
{
    int amt = grid[row][col];
    grid[row][col] = 0;
    return amt;
}

// move to adjecent spot with most watermelons
void move(elephant *ele_ptr, int **grid)
{
    // find where elephant
    int r;
    int c;
    top(&ele_ptr->memory, &r, &c);

    // find amt in adjecent spots
    int curSpot = grid[r][c];
    int nAmt;
    int sAmt;
    int wAmt;
    int eAmt;

    //check if in bounds
    if (r == 500)
    {
        nAmt = 0;
    }
    else
    {
        nAmt = grid[r + 1][c];
    }

    if (r == 1)
    {
        sAmt = 0;
    }
    else
    {
        sAmt = grid[r - 1][c];
    }

    if (c == 500)
    {
        eAmt = 0;
    }
    else
    {
        eAmt = grid[r][c + 1];
    }

    if (c == 1)
    {
        wAmt = 0;
    }
    else
    {
        wAmt = grid[r][c - 1];
    }

    // find largest amt
    if (nAmt == 0 && sAmt == 0 && wAmt == 0 && eAmt == 0 && curSpot == 0)//no nearby watermelon
    {
        if (ele_ptr->memory.head->next != NULL)
        {
            pop(&(ele_ptr->memory));
        }
    }
    else if(curSpot > 0)//watermelon at current spot
    {
        return;
    }
    else if (nAmt > sAmt && nAmt > wAmt && nAmt > eAmt)//most north
    {
        push(&ele_ptr->memory, r + 1, c);
    }
    else if (sAmt > nAmt && sAmt > wAmt && sAmt > eAmt)//most south
    {
        push(&ele_ptr->memory, r - 1, c);
    }
    else if (wAmt > nAmt && wAmt > sAmt && wAmt > eAmt)//most west
    {
        push(&ele_ptr->memory, r, c - 1);
    }
    else if (eAmt > nAmt && eAmt > sAmt && eAmt > wAmt)//most east
    {
        push(&ele_ptr->memory, r, c + 1);
    }
}

// updates grid
int progress_hour(elephant *ele_arr, int num_ele, int **grid)
{
    int count = 0;
    int r;
    int c;

    //move all elephants
    for (int i = 0; i < num_ele; i++)
    {
        move(&ele_arr[i], grid);
    }

    //update grid
    for (int i = 0; i < num_ele; i++)
    {
        top(&ele_arr[i].memory, &r, &c);
        count += eatBait(grid, r, c);
    }

    return count;
}

int main()
{
    // vars
    int numEle;
    int r, c, amt;
    char input[5];
    int **grid = (int **)calloc(501, sizeof(int));

    // allocate grid
    for (int i = 0; i < 501; i++)
    {
        grid[i] = (int *)calloc(501, sizeof(int));
    }

    // get num of elep
    scanf("%d", &numEle);

    // arr of elephants
    elephant elep[numEle];

    // place elephants
    for (int i = 0; i < numEle; i++)
    {
        scanf("%d %d", &r, &c);

        elep[i].memory = *createStack();


        push(&elep[i].memory, r, c);
    }

    while (1)
    {
        scanf("%s", input);

        if (strcmp(input, "BAIT") == 0) // place baits
        {
            scanf("%d %d %d", &r, &c, &amt);
            addBait(grid, r, c, amt);
        }
        else if (strcmp(input, "HOUR") == 0) // move elephants
        {
            printf("%d\n", progress_hour(elep, numEle, grid));
        }
        else // QUIT
        {
            for (int i = 0; i < numEle; i++)
            {
                // print results
                printf("%d %d\n", elep[i].memory.head->r, elep[i].memory.head->c);
            }

            break;
        }
    }

    return 0;
}
