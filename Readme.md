

# use readline.supp in valgrind/create valgrind.log:

	- valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log


## move logs & .opencodeignore into minishell/


# openCode prompt:

### 1:

Read the `valgrind.log` file in the root directory alongside my C codebase.

Focus exclusively on fixing "definitely lost" and "indirectly lost" blocks.

For each leak:
1. Identify the file and line number where the allocation occurred.
2. Trace the execution flow to find exactly where the pointer goes out of scope, gets overwritten, or where a process exits without a `free()`.
3. Check error-handling early `return` paths, skipped AST/token cleanups, and `fork()` child processes exiting before freeing global structures.
4. Provide the exact code changes to fix the leak while strictly respecting 42's Norminette (25 lines max per function).


### 2(probably best):

Read `valgrind.log`. We are going to fix these memory leaks STRICTLY ONE AT A TIME.

Execute this exact step-by-step plan for the FIRST distinct "definitely lost" leak you find:

1. Locate Allocation: Find the exact file and line in the stack trace where the memory was allocated.
2. Read the Code: Use your file-reading tools to open that file and examine the allocation.
3. Trace the Struct/Pointer: Trace where that pointer goes. If it is added to a struct (like a token list, AST, or env array), YOU MUST find and read the header file where that struct is defined.
4. Find the Drop Point: Trace the execution path to find exactly where it gets abandoned (e.g., an unhandled `return` on a syntax error, a `fork()` child calling `exit()`, or a missing recursive free).

Output a clear diagnostic for this SINGLE leak explaining the exact missing cleanup logic. 
Do NOT analyze any other leaks yet. Do NOT write the code to fix it yet. Stop and wait for my confirmation.


### 3(if 'non-42' answers):

Read the `valgrind.log` file in the root directory alongside my C codebase.

Focus exclusively on fixing "definitely lost" and "indirectly lost" blocks.

For each leak:
1. Identify the file and line number of the allocation.
2. Trace the execution flow to find exactly where the pointer goes out of scope, or where a process exits without a `free()`.
3. Check error-handling early `return` paths, skipped AST/token cleanups, and `fork()` child processes.
4. Provide the exact code changes to fix the leak.

STRICT CODING CONSTRAINTS (CRITICAL):
- No `for` loops, no `do...while` loops, no `switch` statements.
- Maximum 25 lines of code per function. If your fix pushes a function over 25 lines, you MUST refactor it into a helper function.
- Maximum 4 variables declared per function.
- Do not use standard C string libraries. Rely on our existing `libft` (e.g., `ft_strdup`, `ft_split`).
