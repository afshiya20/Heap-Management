//Used Firstfit Method in this heap implementation

#include <stdio.h>
#include<stdlib.h>

int x = 0, y = 0;//global variables 

struct FreeBlock
{
    int ID;
    int size;
    struct FreeBlock* next;
};
struct FreeBlock* fhead = NULL;
struct FreeBlock* fprev = NULL;


struct AllocBlock 
{
    int block_no;
    int ID;
    int size;
    struct AllocBlock* next;
};
struct AllocBlock* ahead = NULL; 
struct AllocBlock* aprev = NULL;

// Below Function is to create free blocks of given size
void createFreeBlock(int fsize);
//Below Function is to display available freelist
void displayFree();
//Below Function is to display allocated memory
void displayAlloc();
//Below Function is to Allocate memory 
void allocate(int asize);
//Below Function is to deallocate and merge the adjacent free spaces
void deallocate(int id);


int main()
{
	int a,b,i,j,k,id,p;
	
	printf("Enter no.of blocks and then enter blocksize for each block\n");
	scanf("%d\n",&a);
	int block[a];

	for(k=0;k<a;k++)
	{
		scanf("%d",&block[k]);
	}
    
    printf("Enter no.of processblocks and then enter processblockSize for each processblock\n");
    scanf("%d\n",&b);
    int processBlock[b];
    for(j=0;j<b;j++)
    {
    	scanf("%d",&processBlock[j]);
	}
    
            
    for (i = 0; i < a; i++)
    {
    	createFreeBlock(block[i]);
	}

    for (i = 0; i < b; i++)
    {
    	allocate(processBlock[i]);
	}
        
    printf("allocated list\n");
    displayAlloc();
    
    printf("free list\n");
    displayFree();

    printf("\nEnter ID of block number you want to free\n");
    scanf("%d",&id);
    deallocate(id);
    
    printf("Enter size of the process you want to allocate\n");
    scanf("%d",&p);
    allocate(p);
    
    printf("After deleting block with ID number %d\n",id);
    
    printf("\nNewly allocated list is\n");
    displayAlloc();
    
    printf("\nChanged free list is\n");
    displayFree();
}

void createFreeBlock(int fsize)
{
    struct FreeBlock* ptr = (struct FreeBlock*)malloc(sizeof(struct FreeBlock));
    ptr->size = fsize;
    ptr->ID = x;
    ptr->next = NULL;
    if (fhead == NULL)
    {
    	fhead = ptr;
    }
    else
    {
    	fprev->next = ptr;
    }
    fprev = ptr;
    x++;
}


void displayFree()
{
    struct FreeBlock* ptr = fhead;
    printf("Block No \tFreeSize\n");
    while (ptr != NULL) 
	{
        printf(" %d   \t\t  %d\n" ,ptr->ID, ptr->size);
        ptr = ptr->next;
    }
}


void displayAlloc()
{
    struct AllocBlock* ptr = ahead;
    printf("ID\tBlock No\tAllocatedSize\n");
    while (ptr != NULL) 
	{
        printf("%d \t %d  \t\t    %d\n",ptr->ID,ptr->block_no,ptr->size);
        ptr = ptr->next;
    }
}


void allocate(int asize)
{
	int flag=0;
    // creating block for given processSize
    struct AllocBlock* ptr1 = (struct AllocBlock*)malloc(sizeof(struct AllocBlock));
    struct FreeBlock* ptr2 = fhead;
    ptr1->size = asize;
    ptr1->ID = y;
    ptr1->next = NULL;
    

    // finding block of appropriate size to allocate
    while (ptr2 != NULL && flag==0) 
	{
        if (ptr1->size <= ptr2->size)
        {
        	flag=1;
		}
		if(flag==0)
		{
			ptr2 = ptr2->next;
		}
        
    }

    // allocating block of given size
    if (ptr2 != NULL) 
	{
        ptr1->block_no = ptr2->ID;
        ptr2->size -= ptr1->size;
        if (ahead == NULL)
        {
        	ahead = ptr1;
		}
        else 
		{
            aprev = ahead;
            while (aprev->next != NULL)
            {
            	aprev = aprev->next;
			}
            aprev->next = ptr1;
        }
        y++;
    }
    else // if respective block is not found 
    {
    	printf("Block of size %d  can't be allocated\n",asize);
	}
        
}


void deallocate(int id)
{

    struct AllocBlock *aptr1 = ahead;
	struct AllocBlock *aptr2 = NULL;
	struct FreeBlock* fptr = fhead;
    int flag1=0;
    int flag2=0;
    // finding the block with respective id to deallocate
    while (aptr1 != NULL && flag1==0) {
        if (aptr1->ID == id)
        {
        	flag1=1;
		}
		if(flag1==0)
		{
		    aptr2 = aptr1;
            aptr1 = aptr1->next;	
		}
        
    }
    if (aptr1 == NULL)
    {
    	printf("ID doesn't exist\n");
	}
    else if (aptr1 == ahead)
    {
    	ahead = ahead->next;
	}
    else
    {
    	aptr2->next = aptr1->next;
	}
	//merging adjacent free blocks
    while (fptr != NULL && flag2==0) 
	{
        if (fptr->ID == aptr1->block_no) 
		{
            fptr->size += aptr1->size;
            flag2=1;
        }
        
        if(flag2==0)
        {
        	fptr = fptr->next;
		}
        
    }
}
