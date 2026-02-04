# ToyForth

**ToyForth** is a minimalist, stack-based programming language implemented in C, heavily inspired by the **Forth** philosophy. It features a virtual machine with dual-stack architecture, a dynamic dictionary for user-defined words, and robust memory management via reference counting.

---

## Features

* **Dual-Stack Architecture**: Separate **Data Stack** for parameter passing/arithmetic and **Return Stack** for loop indices and temporary storage.
* **Dynamic Dictionary**: Define new words at runtime using the `: name ... ;` syntax.
* **Control Flow**: Supports standard Forth branching and looping:
* `IF ... ELSE ... THEN`
* `BEGIN ... WHILE ... REPEAT`
* `DO ... LOOP` with index access via `I`.


* **Memory Management**: Automatic memory handling using **Reference Counting** to prevent leaks in complex structures.
* **Interactive REPL**: A built-in interpreter for live coding and testing.

---

## Building and Running

### Prerequisites

* A C compiler (e.g., `gcc`)
* `make` utility

### Build

To compile the project, simply run:

```bash
make

```

### Usage

Run the interactive interpreter:

```bash
./toyforth

```

Execute a specific Forth file:

```bash
./toyforth program.tf

```

---

## Language Reference

### Stack Manipulation

| Word | Effect | Description |
| --- | --- | --- |
| `DUP` | `( n -- n n )` | Duplicate the top element. |
| `DROP` | `( n -- )` | Discard the top element. |
| `SWAP` | `( n1 n2 -- n2 n1 )` | Swap the top two elements. |
| `OVER` | `( n1 n2 -- n1 n2 n1 )` | Copy the second element to the top. |

### Arithmetic & Comparison

* **Operators**: `+`, `-`, `*`, `/`, `MOD`
* **Logic**: `<`, `>`, `==`, `<=`, `>=`, `!=`
* **Output**: `.` (dot) pops and prints the top of the stack.

### Control Structures

```forth
\ Conditional
10 20 < IF S" True" . ELSE S" False" . THEN

\ Definite Loop (prints 0 to 4)
5 0 DO I . LOOP

\ Indefinite Loop
5 BEGIN DUP 0 > WHILE DUP . 1 - REPEAT

```

### Defining New Words

```forth
: SQUARE DUP * ;
5 SQUARE .  \ Outputs 25

```

---

## Architecture

The system is built around the `tf_vm` structure, which maintains the execution context:

* **Data Stack**: A dynamic array of `tfobj` pointers.
* **Return Stack**: Used for internal control flow and the `>R`, `R>`, `R@` primitives.
* **Dictionary**: A linked list of `tf_dict_node` entries mapping strings to executable instruction lists.

### Memory Management

ToyForth uses a **Reference Counting** system. Every `tfobj` tracks how many references to it exist (on stacks, in lists, or in the dictionary).

* `tfobj_retain()`: Increments the reference count.
* `tfobj_release()`: Decrements the count and automatically frees memory when it reaches zero.

