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

#include "bst.h"

//****************************************************************************************

//Fucntion to calculare the height of the tree
int Height(BSTNode *root) {
    if (root == NULL)  //if tree is null
        return -1;
    else {
        int left_height = Height(root->left);
        int right_height = Height(root->right);
        if (left_height > right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

//****************************************************************************************

//Function to count the total number of nodes
int count(BSTNode *n)
{
    int c = 1;
    
    if (n == NULL)
        return 0;
    else
    {
        c += count(n->left);
        c += count(n->right);
        return c;
    }
}

//****************************************************************************************

//Function to check if the value stored is present in the tree
BSTNode *Contains(BSTNode *root, BSTElementType array){
    
    BSTNode *prev = NULL;
    BSTNode *cur = root;
    
    //
    while (cur != NULL)
    {
        if (array.user_id == cur->value.user_id){
            return root;
            
        }
        else if (array.user_id < cur->value.user_id)  // go left:
        {
            prev = cur;
            cur = cur->left;
        }
        else  // go right:
        {
            prev = cur;
            cur = cur->right;
        }
        
    }//while
    
    
    return NULL;
    
}

//****************************************************************************************

//Function to input the new nodes from  the file
BSTNode *Insert(BSTNode *root, BSTElementType array) {
    
    BSTNode *prev = NULL;
    BSTNode *cur = root;
    
    //Search if the value is already in the tree
    while (cur != NULL)
    {
        if (array.user_id == cur->value.user_id){
            (cur->value.number_of_reviews)++;   //increment the number of reviews if the value if found
            return root;
        }
        else if (array.user_id < cur->value.user_id)  // go left:
        {
            prev = cur;
            cur = cur->left;
        }
        else  // go right:
        {
            prev = cur;
            cur = cur->right;
        }
        
    }//while
    
    //insert the new user id if not found
    cur =  ( BSTNode *)malloc(sizeof(struct BSTNode));
    cur->value.user_id = array.user_id;
    (cur->value.number_of_reviews) = 1;
    cur->left = NULL;
    cur->right = NULL;
    
    
    if (prev == NULL)  // insert at root:
        root = cur;
    else if (array.user_id < prev->value.user_id)  // insert to left of prev:
        prev->left = cur;
    else  // insert to the right:
        prev->right = cur;
    
    return root;
}

//****************************************************************************************

//Get the values from the file and store them call the insert function
BSTNode *Build(char *filename , int * total_reviews)
{
    //initialise the array and the root
    BSTElementType *array = malloc(sizeof(*array));;
    BSTNode *root = NULL;
    FILE *input;
    char str[300];  //for the input line
    
    input = fopen(filename, "r"); // open the file:
    if (input == NULL) //if unable to open
    {
        printf("**Error: unable to open '%s'\n", filename);
        exit(-1);
    }
    
    //get the first line for disregarding
    fgets(str, 350, input);
    
    //Variables to store the values from the files
    int movie_id;
    int rating;
    char review_date[100];
    
    //while loop to run till the file runs out
    while (fgets(str, 350, input))
    {
        //printf("%s\n", str);
        
        //get line by line and break it into pieces
        char *token;
        token = strtok(str, ",");
        movie_id = atoi(str);
        
        token = strtok(NULL, ",");
        array->user_id = atoi(token);
        
        token = strtok(NULL, ",");
        rating = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(review_date, token);
        
        //printf("%d , %ld , %d  \n", movie_id , user_id , rating);
        (*total_reviews)++;
        Contains(root, *array);
        root = Insert(root, *array );
        
    }
    fclose(input);
    return root;
    
}

//****************************************************************************************
//Helper function for the inorder function
int _inorder(BSTNode *n, BSTElementType *array, int index){
    
    //Base case
    if(n == NULL)
        return index;
    //Goes to the left node
    if(n->left != NULL)
        index =  _inorder(n->left, array , index);
    
    //Insert the userid into the array
    array[index].user_id = n->value.user_id;
    array[index].number_of_reviews = n->value.number_of_reviews;
    index++;
    
    //Goes to the right node
    if(n->right != NULL)
        index =  _inorder(n->right, array, index) ;
    
    return index;
}

//****************************************************************************************
//Inorder function to initialise the array and call the helper to store it
BSTElementType *Inorder(BSTNode* n) {
    
    
    int size = count(n);
    
    BSTElementType* array = malloc(size * sizeof(*array));
    
    _inorder(n, array, 0);
    
    
    return array;
}


//****************************************************************************************

//**DONE**//






