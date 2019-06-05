//
//  slingu2.c
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


//MERGE SORT FOR THE ARRAY

//****************************************************************************************

//Merge sort the array
void merge(BSTElementType *arr, int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 =  right - middle;
    
    //creating the temperarory array
    int L1[n1], R1[n2] , L2[n1] , R2[n2];
    
    //copyint the data into the temperory arrays
    for (i = 0; i < n1; i++){
        L1[i] = arr[left + i].number_of_reviews;
        L2[i] = arr[left + i].user_id;
    }
    
    for (j = 0; j < n2; j++){
        R1[j] = arr[middle + 1+ j].number_of_reviews;
        R2[j] = arr[middle + 1+ j].user_id;
    }
    
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L1[i] >= R1[j])
        {
            arr[k].number_of_reviews = L1[i];
            arr[k].user_id = L2[i];
            i++;
        }
        else
        {
            arr[k].number_of_reviews = R1[j];
            arr[k].user_id = R2[j];
            j++;
        }
        k++;
    }
    //copy the values from the temp arrays to the main array
    while (i < n1)
    {
        arr[k].number_of_reviews = L1[i];
        arr[k].user_id = L2[i];
        
        i++;
        k++;
    }
    
    //copy the values from the temp arrays to the main array
    while (j < n2)
    {
        arr[k].number_of_reviews = R1[j];
        arr[k].user_id = R2[j];
        
        j++;
        k++;
    }
}

//****************************************************************************************
//Helper function for the merge to initialise and call.
void mergeSort(BSTElementType *arr, int left, int right)
{
    if (left < right)
    {
        //initialise the middle
        int middle = left + (right-left) / 2;
        
        // Sort first and second half
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        //merge them
        merge(arr, left, middle, right);
    }
}

//****************************************************************************************


int main() {
    
    int totol_reviews = 0;
    BSTNode *root = NULL;
    int *total = &totol_reviews;
    root = Build("reviews.csv" , total);
    int height = Height(root);
    int size = count(root);
    
    
    BSTElementType *array = Inorder(root);
    
    mergeSort(array, 0, size);
    
    printf("** Netflix User Reviews **\n\n\n");
    printf(">> Processing reviews...\n");
    printf(">> # of reviews:\t\t%d\n", totol_reviews);
    printf(">> # of users in tree:\t\t%d\n", size);
    printf(">> Tree height:\t\t\t%d\n", height);
    
    printf("\n\n** Top 10 Most Active Users **\n");
    printf("Rank\t\tUserId\t\t# of Reviews\n");
    
    int i;
    
    for(i=0;i<10;i++){
        printf("%d\t\t%d\t\t%d\n", i+1 , array[i].user_id , array[i].number_of_reviews);
    }
    
    free(array);
    printf("\n**Done \n");
    return 0;
}
//****************************************************************************************




//THE END...












