//
//
// Netflix movie reviews using binary search trees. //
// <<Srinivas Lingutla>>
// << Mac OS X 10.11.5 , XCODE>> // U. of Illinois, Chicago
// CS251, Fall 2016
// HW #4
//
//  main.c
//  Homework 4 - 251
//
//  Created by Srinivas Lingutla on 9/2/16.
//  Copyright © 2016 Srinivas Lingutla. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************************************************************************

//Structures to contain the movie nodes
typedef struct BinaryTreeNodeMovies

{
    int movie_id;
    char movie_name[255];
    int pub_year;
    int ratings_1;
    int ratings_2;
    int ratings_3;
    int ratings_4;
    int ratings_5;
    struct BinaryTreeNodeMovies *left;
    struct BinaryTreeNodeMovies *right;
    
    
}BinaryTreeNodeMovies;

//****************************************************************************************

void PrintInorder(BinaryTreeNodeMovies *root) {   //print the nodes in order for debugging
    if (root == NULL) { // base case: empty tree
        return;
    }
    else // recursive case: non-empty tree
    {
        PrintInorder( root->left );
        printf("%d , %s , %d\n", root->movie_id , root->movie_name , root -> ratings_5);
        PrintInorder( root->right );
    }
}


//****************************************************************************************

//Function to input the new nodes from  the file
BinaryTreeNodeMovies *Insert(BinaryTreeNodeMovies *root, int id, char name[255], int year) {
    
    //check if the root is null
    if (root == NULL) {
        
        
        root =  ( BinaryTreeNodeMovies *)malloc(sizeof(struct BinaryTreeNodeMovies));
        root->movie_id = id;
        strcpy(root->movie_name, name);
        root->pub_year = year;
        root->left = NULL;
        root->right = NULL;
        return root;
        
    }
    //if the root is not null
    if (id < root->movie_id)
        
        root->left  = Insert(root->left, id, name , year);   //Move to the left node based on the value of id
    
    else if (id > root->movie_id)
        
        root->right  = Insert(root->right, id, name , year);   //Move to the right node based on the value of id
    
    return root;
}

//****************************************************************************************

//Function to build and get the lines from the movies filename
BinaryTreeNodeMovies *Build(char *filename)
{
    //initialise the root
    BinaryTreeNodeMovies *root = NULL;
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
    char movie_name[255];
    int pub_year;
    
    //while loop to run till the file runs out
    while (fgets(str, 350, input))
    {
        //get line by line and break it into pieces
        char *token;
        token = strtok(str, ",");
        movie_id = atoi(str);
        
        token = strtok(NULL, ",");
        strcpy(movie_name, token);
        
        
        token = strtok(NULL, ",");
        pub_year = atoi(token);
        
        //printf("%d , %s , %d  \n", movie_id , movie_name , pub_year);
        
        root = Insert(root, movie_id , movie_name , pub_year);
        
    }
    fclose(input);
    return root;
    
}

//****************************************************************************************

//Function to get and store the reviews
long int ParseReviews (BinaryTreeNodeMovies *root , FILE *file){
    
    //variables to store the values from the file
    long int total_reviews = 0;;
    int id;
    char str[100];
    int rating;
    int temp;
    //get the first line
    fgets(str, 350, file);
    
    //while loop to run till the file runs out
    while (fgets(str, 350, file)){
        
        //initialize another node, so that root is left in the same position
        BinaryTreeNodeMovies *node = NULL;
        node = root;
        
        //Getting the value
        char *token;
        token = strtok(str, ",");
        id = atoi(str);
        
        token = strtok(NULL, ",");
        temp = atoi(token);
        
        token = strtok(NULL, ",");
        rating = atoi(token);
        
        //A while loop to reposition the node to point to the movie id
        while (node != NULL){
            if (id == node->movie_id)
                break;
            else if (id < node->movie_id)
                node = node->left;
            else
                node = node->right;
        }//end of while loop
        
        total_reviews++; //increase the total reviews count
        
        //switch case to increase the correct ratings.
        switch (rating) {
            case 1:     node->ratings_1++;     break;
            case 2:     node->ratings_2++;     break;
            case 3:     node->ratings_3++;     break;
            case 4:     node->ratings_4++;     break;
            case 5:     node->ratings_5++;     break;
            default:       break;
        }
    }
    //return the number of reviews
    return total_reviews;
}

//****************************************************************************************

//function to count the total number of nodes / total movies
int Count(BinaryTreeNodeMovies *root)
{
    int count = 1;
    if (root == NULL) //if empty tree
        return 0;
    
    else
    {
        count += Count(root->left);
        count += Count(root->right);
        return count;
    }
}

//****************************************************************************************

//Fucntion to get the max height of the tree
int Height(BinaryTreeNodeMovies *root)
{
    if (root == NULL)//if the tree is empty
        return -1;
    
    int height_left = Height(root->left);
    int height_right = Height(root->right);
    
    if (height_left >= height_right){
        return(height_left+1) ;
    }
    else {
        return(height_right+1) ;
    }
    
    
}

//****************************************************************************************


//interactive search of stations for the user.
void search_movies (BinaryTreeNodeMovies *stat){
    
    while(1){
        int id;
        BinaryTreeNodeMovies *node = stat;
        printf("\n\n>> Please enter Movie ID (0 to quit): ");
        //getting the user input
        scanf("%d", &id);
        
        //checking if user entered nothing
        if(id == 0)
            exit(0);
        
        //Checking if the id user entered is present in the movies list, and if not, print error
        while (node != NULL){  //a while loop to traverse the list
            if (id == node->movie_id)
                break;
            else if (id < node->movie_id)
                node = node->left;
            else if(id > node->movie_id)
                node = node->right;
            if(node == NULL){
                printf("Movie ID not found, try again!\n");
                search_movies(stat);
            }
            
        }
        
        node = stat; //reposition the stat pointer
        
        //a while loop to print the path to the correct movie
        while (node != NULL){
            printf("[%d:  '%s']\n" , node->movie_id, node->movie_name);
            if (id == node->movie_id)
                break;
            else if (id < node->movie_id)
                node = node->left;
            else if(id > node->movie_id)
                node = node->right;
        }
        
        //Printing out the ratings
        printf("%d:  '%s'  (%d)\nRatings:\n" , node->movie_id, node->movie_name , node->pub_year);
        printf("  1: %d\n", node->ratings_1);
        printf("  2: %d\n", node->ratings_2);
        printf("  3: %d\n", node->ratings_3);
        printf("  4: %d\n", node->ratings_4);
        printf("  5: %d\n", node->ratings_5);
        
        //Calculating the average
        double average = (double)(1*node->ratings_1 + 2*node->ratings_2 + 3*node->ratings_3 + 4*node->ratings_4 + 5*node->ratings_5) / (node->ratings_1 + node->ratings_2 + node->ratings_3 + node->ratings_4 + node->ratings_5);
        
        printf("Average Rating: %lf\n", average);
        
    }
}


//****************************************************************************************

int main() {
    
    BinaryTreeNodeMovies *root = NULL;
    FILE* file = fopen("reviews.csv", "r");
    if (!file)
        return -1; //error if the file didnt open
    
    
    root = Build("movies.csv");
    
    long int total_reviews = ParseReviews(root , file);
    
    //PrintInorder(root);   //for debugging
    
    printf("** Netflix Movie Reviews **\n\n\n");
    printf(">> Processing movies...\n");
    
    //getting the movie count
    int movie_count = Count(root);
    printf(">> Movie count: %d\n", movie_count);
    
    //getting the height of the max tree
    int tree_height = Height(root);
    printf(">> Tree height: %d\n\n", tree_height);
    
    
    printf(">> Processing reviews...\n");
    printf(">> Num reviews: %ld\n", total_reviews);
    
    
    //interactive search function
    search_movies(root);
    
    printf("**\nDone \n");
    fclose(file);
    return 0;
}
//****************************************************************************************
//THE END...

