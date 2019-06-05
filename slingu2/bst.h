//
//  bst.c
//  Homework 6
//
//  Created by Srinivas Lingutla on 9/15/16.
//  Copyright © 2016 Srinivas Lingutla. All rights reserved.
//
//
//
// Netflix movie reviews using binary search trees. //
// <<Srinivas Lingutla>>
// << Mac OS X 10.11.5 , XCODE>> // U. of Illinois, Chicago
// CS251, Fall 2016
// HW #6
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************************************************************************

#define max2ints(a,b) ((a)>(b)?(a):(b))


//dynamic array
typedef struct BSTElementType
{
    int user_id;
    int number_of_reviews;
}BSTElementType;



//Structures to contain the user nodes
typedef struct BSTNode

{
    BSTElementType value;
    struct BSTNode *left;
    struct BSTNode *right;
    
    
}BSTNode;



//****************************************************************************************

//functions to count the total number of nodes and calculate the array height
int count(BSTNode *n);
int Height(BSTNode *root);

//BSTNODE fucntion to insert and build the binary tree
BSTNode *Contains(BSTNode *root, BSTElementType array);
BSTNode *Insert(BSTNode *root, BSTElementType array);
BSTNode *Build(char *filename , int * total_reviews);

//Store the binary tree into an array and sort the array.
int _inorder(BSTNode *n, BSTElementType *array, int index);
BSTElementType *Inorder(BSTNode* n);





