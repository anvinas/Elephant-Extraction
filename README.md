# Elephant Extraction
This project is a school assignment designed to simulate elephants navigating a grid in search of watermelons. Each elephant uses a stack data structure to remember the locations it has visited, with the objective of maximizing the amount of watermelons consumed. The simulation allows for the dynamic placement of bait and tracks the movement and feeding behavior of the elephants over time.

## Files in the Repository

- `main.c`: The main source file containing the implementation of the simulation.
- `README.md`: This file, providing an overview and instructions for the project.

## Input and Execution

The program expects input in the following format:

1. An integer `numEle`, representing the number of elephants.
2. For each elephant, an integer pair `(r, c)` representing the initial row and column position of the elephant.
3. Commands to place bait or progress the simulation by an hour.

Example:

```
3
1 1
2 2
3 3
BAIT 2 3 5
HOUR
QUIT
```

### Example

#### Input

```
3
1 1
2 2
3 3
BAIT 2 3 5
HOUR
QUIT
```

#### Output

```
5
1 1
2 3
3 3
```

This means in the first hour, the elephants ate 5 watermelons. The final positions of the elephants are `(1, 1)`, `(2, 3)`, and `(3, 3)`.

## Code Explanation

### Data Structures

- **Node**

  ```c
  typedef struct node {
      int r, c;
      struct node *next;
  } node;
  ```

  Represents a position in the grid.

- **Stack**

  ```c
  typedef struct stack {
      node *head;
  } stack;
  ```

  A stack to manage the positions that an elephant has visited.

- **Elephant**

  ```c
  typedef struct elephant {
      stack memory;
  } elephant;
  ```

  Represents an elephant with a memory stack.

### Functions

- **Node Creation and Manipulation**

  - `node* createNode(int row, int col)`: Creates a new node with the given position.
  - `node* insertHead(node* head, int row, int col)`: Inserts a node at the head of the list.
  - `node* removeHead(node* head)`: Removes the head node from the list.

- **Stack Operations**

  - `stack* createStack()`: Initializes an empty stack.
  - `void push(stack* stk, int row, int col)`: Pushes a position onto the stack.
  - `void pop(stack* stk)`: Pops the top position from the stack.
  - `void top(stack* stk, int *row_ptr, int *col_ptr)`: Returns the top position from the stack.

- **Utility Functions**

  - `void addBait(int **grid, int row, int col, int amt)`: Adds watermelons to a specific position in the grid.
  - `int eatBait(int **grid, int row, int col)`: Returns and resets the amount of watermelons at a specific position.
  - `void move(elephant *ele_ptr, int **grid)`: Moves the elephant to the adjacent position with the most watermelons.
  - `int progress_hour(elephant *ele_arr, int num_ele, int **grid)`: Simulates one hour of the elephants moving and eating watermelons.

### Main Function

The `main` function orchestrates the simulation by:

1. Reading the number of elephants and their initial positions.
2. Handling commands to place bait or progress the simulation by an hour.
3. Printing the final positions of the elephants when the simulation ends.
