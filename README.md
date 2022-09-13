# Heap-Management

Creating a simulator for the heap management schema using linked list

First Fit Algorithm for Memory Management: The first memory partition which is sufficient to accommodate the process is allocated.

Approach:

The idea is to use the memory block with a unique tag id. Each process of different sizes are given block id, which signifies to which memory block they belong to, and unique tag id to delete particular process to free up space. Create a free list of given memory block sizes and allocated list of processes.

Create allocated list:

Create an allocated list of given process sizes by finding the first memory block with sufficient size to allocate memory from. If the memory block is not found, then simply print it. Otherwise, create a node and add it to the allocated linked list.

Delete process:

Each process is given a unique tag id. Delete the process node from the allocated linked list to free up some space for other processes. After deleting, use the block id of the deleted node to increase the memory block size in the free list.
