/*
Trung Le
4/12/2024
Lab Assignment 9
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int id;
	char name;
	int order;
};

// Node for linked list
struct Node
{
	// Data stored in the node
	struct RecordType data;
	// Pointer to the next node in the linked list
	struct Node* next;
};

// Hash Table Structure
struct HashType
{
	// Pointer to the head of the linked list for separate chaining
	struct Node* head; 
};

// Compute the hash function
// Parameters:
//   x: Key to be hashed
//   size: Size of the hash table
// Returns:
//   Hash value computed based on the key and hash table size
int hash(int x, int size)
{
	// Simple modulus hashing for even distribution
	return x % size;
}

// Function to insert a record into hash table
void insertRecord(struct HashType* hashTable, int hashSize, struct RecordType data)
{
	int index = hash(data.id, hashSize);
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL)
	{
		printf("Memory allocation failed.\n");
		exit(1);
	}
	newNode->data = data;
	newNode->next = NULL;

	// If this is the first node in the list
	if (hashTable[index].head == NULL)
	{
		hashTable[index].head = newNode;
	}
	else
	{
		// Traverse to the end of the list
		struct Node* current = hashTable[index].head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		// Append the new node to the end of the list
		current->next = newNode;
	}
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType* hashTable, int hashSize)
{
	for (int i = 0; i < hashSize; ++i)
	{
		struct Node* current = hashTable[i].head;
		if (current != NULL)
		{
			printf("Index %d -> ", i);
			while (current != NULL)
			{
				printf("%d, %c, %d", current->data.id, current->data.name, current->data.order);
				if (current->next != NULL)
					printf(" -> ");
				current = current->next;
			}
			printf("\n");
		}
	}
}

int main(void)
{
	// Pointer to store records read from the file
	struct RecordType* pRecords;
	// Number of records read from the file
	int recordSz = 0;

	// Open the input file for reading
	FILE* inFile = fopen("input_lab_9.txt", "r");
	if (inFile == NULL)
	{
		printf("Error opening file. Make sure the file exists in the current directory.\n");
		return 1;
	}

	// Read number of records from the input file
	fscanf(inFile, "%d\n", &recordSz);

	// Allocate memory to store records
	pRecords = (struct RecordType*)malloc(recordSz * sizeof(struct RecordType));
	if (pRecords == NULL)
	{
		printf("Memory allocation failed.\n");
		fclose(inFile);
		return 1;
	}

	// Read records from the input file
	for (int i = 0; i < recordSz; ++i)
	{
		fscanf(inFile, "%d %c %d\n", &pRecords[i].id, &pRecords[i].name, &pRecords[i].order);
	}

	fclose(inFile);

	// Hash table size
	int hashSize = 11; // Example size, you can choose another prime number

	// Create hash table
	struct HashType* hashTable = (struct HashType*)malloc(hashSize * sizeof(struct HashType));
	if (hashTable == NULL)
	{
		printf("Memory allocation failed.\n");
		free(pRecords);
		return 1;
	}

	// Initialize hash table
	for (int i = 0; i < hashSize; ++i)
	{
		hashTable[i].head = NULL;
	}

	// Insert records into hash table
	for (int i = 0; i < recordSz; ++i)
	{
		insertRecord(hashTable, hashSize, pRecords[i]);
	}

	// Display records in the hash structure
	displayRecordsInHash(hashTable, hashSize);

	// Free allocated memory
	for (int i = 0; i < hashSize; ++i)
	{
		struct Node* current = hashTable[i].head;
		while (current != NULL)
		{
			struct Node* temp = current;
			current = current->next;
			// Free memory for node in the linked list
			free(temp);
		}
	}
	// Free memory for hash table and records array.
	free(hashTable);
	free(pRecords);

	return 0;
}
