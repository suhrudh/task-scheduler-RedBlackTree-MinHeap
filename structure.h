//
// Created by Suhrudh Reddy on 11/15/19.
//

#ifndef ADS_STRUCTURE_H
#define ADS_STRUCTURE_H

#include "Nodes.h"
#include <fstream>
#include <vector>
#include <string>

class MinHeapElement;
class RedBlackElement;
using namespace std;

// Maintains the root and the Minheap Array which stores the pointers to min heap elements
class Structure
{
public:

    int heapSize ; // Heap Size
    MinHeapElement *content[2000]; //Array of length 2000
    RedBlackElement* root = NULL ; // root of the Red Black Tree

    Structure();

    //----------- START OF HEAP FUNCTIONS ---------

    // returns parent position
    int Parent(int position);
    // returns left child position
    int Left(int position);
    //returns right child position
    int Right(int position);

    //Removes the min Element
    void removeMin();

    // corrects the heap from the input position downward
    void heapDown(int position);

    //Insert Element into the heap
    void heapInsert(MinHeapElement *key);

    //heapifying upward by decreasing a particular value
    void heapDecreaseKey(int position,int valueDecreasedTo);

    //swaps the minheap pointers in the minheap array
    void swapElements(int position1,int position2);

    // returns first element of the array
    MinHeapElement* minElement();

    // ------------ END OF HEAP FUNCTIONS ------------


    //************* START OF RED BLACK FUNCTIONS ****************

    //Functions used for Insert
    RedBlackElement* ParentSibling(RedBlackElement* node);
    void BSTinsert(RedBlackElement* root1,RedBlackElement* node);
     void RBTinsert(RedBlackElement* node);
     void RecursiveCorrect(RedBlackElement* node);

    //Rotation
     void LeftRotationWithColorChange(RedBlackElement* node);
     void RightRotationWithColorChange(RedBlackElement* node);
     void LeftRotation(RedBlackElement* node);
     void RightRotation(RedBlackElement* node);

    //Deletion
     void RBTdelete(RedBlackElement* node);
     RedBlackElement* InorderSuccesor(RedBlackElement* node);
     void SwapNodes(RedBlackElement* node1,RedBlackElement* node2);
     void DoubleBlackCases(RedBlackElement* node);
     RedBlackElement* Sibling(RedBlackElement*node);
     void DeleteDoubleBlackNullNode(RedBlackElement* DoubleBlackNull);

     //Searching - returns null if not found
    static RedBlackElement* SearchTreeByValue(int building_num,RedBlackElement* root);

    //************* END OF RED BLACK FUNCTIONS ****************

    //%%%%%%%%%%%%%%%%%% RISING CITY FUNCTIONS %%%%%%%%%%%%%%%%%%
     void InsertBuilding(int building_num, int total_time);
     void PrintBuilding(int building_num, ofstream& output);
     void ExecuteCommand(vector <string> command, ofstream& output);
     string PrintBuildingForRange(int building_num1,int building_num2,RedBlackElement* node, string result);

};



#endif //ADS_MINHEAP_H
