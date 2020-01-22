//
// Created by Suhrudh Reddy on 11/16/19.
//

#include <iostream>
#include "Nodes.h"
#include "structure.h"

using namespace std;

//please find comments for heap in header file

Structure ::Structure() {
    heapSize = 0;
    for(int i=0;i<2000;i++)
    {
        content[i] = nullptr;
    }
}

int Structure::Parent(int position)
{
    return (position-1)/2;
}
int Structure:: Left(int position)
{
    return 2*position+1;
}
int Structure:: Right(int position)
{
    return 2*position+2;
}

void Structure:: removeMin()
{
    content[0] = content[heapSize-1];
    content[heapSize-1] = nullptr;
    heapSize--;
    heapDown(0);
}

void Structure:: heapDown(int position) {
    int left = Left(position);
    int right = Right(position);

    while (position < heapSize &&
           ((left < heapSize && (content[position]->exec_time > content[left]->exec_time || (content[position]->exec_time == content[left]->exec_time && content[position]->building_num > content[left]->building_num)  ) ) ||
            (right < heapSize && (content[position]->exec_time > content[right]->exec_time || (content[position]->exec_time == content[right]->exec_time && content[position]->building_num > content[right]->building_num)) )
           )
            ) {
        int next = -1;
        if (left < heapSize && right < heapSize) {
            if (content[left]->exec_time < content[right]->exec_time) {
                next = left;
            } else if(content[left]->exec_time > content[right]->exec_time) {
                next = right;
            }else {
                next = content[left]->building_num > content[right]->building_num ? right : left;
            }
        }else {
            if (left > heapSize) {
                next = right;
            } else {
                next = left;
            }
        }
        swapElements(position, next);
        position = next;
        left = Left(position);
        right = Right(position);
    }
}

void Structure:: heapInsert(MinHeapElement *key)
{
    heapSize += 1;
    content[heapSize-1] = key; // adding a node with highest value
    heapDecreaseKey(heapSize-1,key->exec_time);
}

void Structure:: heapDecreaseKey(int position,int valueDecreasedTo)
{
    content[position]->exec_time = valueDecreasedTo;
    int parentPosition = Parent(position);
    while(
            position > 0 && (content[parentPosition]->exec_time > content[position]->exec_time ||
                             (content[parentPosition]->exec_time == content[position]->exec_time && content[parentPosition]->building_num > content[position]->building_num))
            )
    {
        swapElements(parentPosition,position);
        position = parentPosition;
        parentPosition = Parent(position);
    }
}

void Structure:: swapElements(int position1,int position2)
{
    MinHeapElement *temp = content[position1];
    content[position1] = content[position2];
    content[position2] = temp;
}

MinHeapElement* Structure:: minElement()
{
    return content[0];
}

RedBlackElement* Structure::ParentSibling(RedBlackElement *node) {
    if(node->parent != nullptr)
    {
        if(node->parent->parent != nullptr){
            if(node->parent->parent->rightChild == node->parent)
            {
                return node->parent->parent->leftChild;
            }else{
                return node->parent->parent->rightChild;
            }
        }else{
            throw("grand parent is null");
        }
    }else {
        throw ("parent null");
    }
}

//null check for the root & node is mandatory
void Structure ::BSTinsert(RedBlackElement* root1,RedBlackElement* node){

    if(root1->building_num > node->building_num)
    {
        if(root1->leftChild != nullptr){
            BSTinsert(root1->leftChild,node);
        }else{
            root1->leftChild = node;
            node->parent = root1;
        }
    }else{
        if(root1->rightChild != nullptr){
            BSTinsert(root1->rightChild,node);
        }else{
            root1->rightChild = node;
            node->parent = root1;
        }
    }
}


//BST insert followed by recursive correction according to Red Black tree rules
void Structure::RBTinsert( RedBlackElement *node) {
    node->color = Red;
    if(root == NULL){
        node->color = Black;
        root = node;
        return;
    }
    else{
        BSTinsert(root,node);
        RecursiveCorrect(node);
    }
}

//checks for the uncle, if Black rotatations and if Red Re-coloring
void Structure::RecursiveCorrect( RedBlackElement *node) {

    if(root == nullptr){
        node->color = Black;
        root = node;
    }else {
        if(node->parent!= nullptr && node->parent->parent!= nullptr&& node->parent->color == Red){
            //parent exits or not check
            //parent sibling is red check
            RedBlackElement *uncle = ParentSibling(node);
            RedBlackElement* grandParent = node->parent->parent;
            RedBlackElement* parent = node->parent;
            if (uncle == nullptr || uncle->color == Black) {
                //parent is right child to grand parent
                if(grandParent->rightChild == parent){
                    //RR rotation - node is right child to parent
                    if(parent->rightChild == node){
                        LeftRotationWithColorChange(parent);
                    }
                        //RL rotation
                    else{
                        RightRotation(node);
                        LeftRotationWithColorChange(node);
                    }
                }else{
                    //LR rotation - node is right child to parent
                    if(parent->rightChild == node){
                        LeftRotation(node);
                        RightRotationWithColorChange(node);
                    }
                        //LL rotation
                    else{
                        RightRotationWithColorChange(parent);
                    }
                }
            } else {
                //recoloring
                uncle->color = Black;
                parent->color = Black;
                if(grandParent->parent == nullptr){
                    grandParent->color = Black;
                }else{
                    grandParent->color = Red;
                    RecursiveCorrect(grandParent); // recur upwards to check correctness of Red Black tree
                }
            }
        }

    }
}

//Rotation

//Left Rotation color changes
void Structure::LeftRotationWithColorChange(RedBlackElement *node) {
    if(node->rightChild != nullptr){
        node->rightChild->color = Red;
    }
    node->color = Black;
    node->parent->color = Red;

    LeftRotation(node); //Rotation part
}

// only Left rotate, used in Red Black deltion as well
void Structure ::LeftRotation( RedBlackElement *node) {
    //grandParent's parent changed
    RedBlackElement* temp1 = node->parent->parent;
    RedBlackElement* temp2 = node->parent;
    temp2->parent = node;
    node->parent = temp1;
    if(node->parent == nullptr){
        root = node;
    }

    //left child of node to right child of parent
    temp2->rightChild = node->leftChild;
    if(node->leftChild != nullptr){
        node->leftChild->parent = temp2;
    }

    if(temp1 != nullptr){
        if(temp1->leftChild == temp2){
            temp1->leftChild = node;
        }else{
            temp1->rightChild = node;
        }
    }
    node->leftChild = temp2;
}

//Right Rotation Color Chnages
void Structure::RightRotationWithColorChange(RedBlackElement *node) {
    if(node->leftChild != nullptr){
        node->leftChild->color = Red;
    }
    node->color = Black;
    node->parent->color = Red;

    RightRotation(node);// Right Rotation
}

// only Right rotate, used in Red Black deltion as well
void Structure::RightRotation( RedBlackElement *node) {
    //grandParent's parent changed
    RedBlackElement* temp1 = node->parent->parent;
    RedBlackElement* temp2 = node->parent;
    temp2->parent = node;
    node->parent = temp1;
    if(node->parent == nullptr){
        root = node;
    }

    //left child of node to right child of parent
    temp2->leftChild = node->rightChild;
    if(node->rightChild != nullptr){
        node->rightChild->parent = temp2;
    }

    if(temp1!= nullptr){
        if(temp1->leftChild == temp2){
            temp1->leftChild = node;
        }else{
            temp1->rightChild = node;
        }
    }
    node->rightChild = temp2;
}


//Deletion
void Structure::RBTdelete( RedBlackElement *node) {
    //checking for 0 or 1 child condition
    if(node == root){
        if(root->leftChild == nullptr && root->rightChild == nullptr)
        {
            root = NULL;
            delete node;
            return;
        }else if(root->leftChild == nullptr){
            root = root->rightChild;
            root->parent = nullptr;
            return;
        }else if(root->rightChild == nullptr){
            root = root->leftChild;
            root->parent = nullptr;
            return;
        }
    }

    if(node->rightChild == nullptr ){
        //Red Case
        if(node->color == Red){
            if(node->parent->rightChild == node){
                node->parent->rightChild = node->leftChild;
            }else{
                node->parent->leftChild = node->leftChild;
            }

            if(node->leftChild != nullptr){
                node->leftChild->parent = node->parent;
            }
            //deleting the node
            delete(node);
            return;
        }
    }else if(node->leftChild == nullptr){
        //Red Case
        if(node->color == Red){
            if(node->parent->rightChild == node){
                node->parent->rightChild = node->rightChild;
            }else{
                node->parent->leftChild = node->rightChild;
            }

            if(node->rightChild != nullptr){
                node->rightChild->parent = node->parent;
            }
            //deleting the node
            delete(node);
            return;
        }
    }else{
        //Inorder succesor swap step
        RedBlackElement* succesorNode = InorderSuccesor(node->rightChild);
        SwapNodes(node,succesorNode);
        RBTdelete(succesorNode);
        return;
    }

    //if execution reaches here, node color is black
    if( node->rightChild != nullptr && node->rightChild->color == Red ){
        if(node->parent->rightChild == node){
            node->parent->rightChild = node->rightChild;
        }else{
            node->parent->leftChild = node->rightChild;
        }
        node->rightChild->parent = node->parent;
        node->rightChild->color = Black;
        //deleting the node
        delete(node);
        return;
    }else if(node->leftChild != nullptr && node->leftChild->color == Red){
        if(node->parent->rightChild == node){
            node->parent->rightChild = node->leftChild;
        }else{
            node->parent->leftChild = node->leftChild;
        }
        node->leftChild->parent = node->parent;
        node->leftChild->color = Black;
        //deleting the node
        delete(node);
        return;
    }
    else{
        // The node has both black children
        //double black case
        if(node->rightChild == nullptr && node->leftChild == nullptr){
            //if a leaf node becomes double black node , we need a dummy node as a double black,since the branches are null
            // dummy double black node's building number is marked -1
            node->building_num = -1;
            DoubleBlackCases(node);
        }
        // deleting the redblack node, and re arranging it's branches and marking double Black node
        else{
            if(node->rightChild == nullptr){
                if(node->parent->rightChild == node){
                    node->parent->rightChild = node->leftChild;
                }else{
                    node->parent->leftChild = node->leftChild;
                }
                node->leftChild->parent = node->parent;
                DoubleBlackCases(node->leftChild);
            }else{
                if(node->parent->rightChild == node){
                    node->parent->rightChild = node->rightChild;
                }else{
                    node->parent->leftChild = node->rightChild;
                }
                node->rightChild->parent = node->parent;

                DoubleBlackCases(node->rightChild);
            }
            //the node is deleted in the end
            delete(node);
            return;
        }
    }
}

void Structure ::DoubleBlackCases( RedBlackElement *node) {

    //case 1 : root is double black
    if (node == root) {
        node->color = Black;
        return;
    }

    RedBlackElement* sibling = Sibling(node);
    //case 2 : sibling color is red
    if(sibling->color == Red){
        //color exchange
        node->parent->color = Red;
        sibling->color = Black;

        if(sibling == node->parent->rightChild){
            LeftRotation(sibling);
        }else{
            RightRotation(sibling);
        }

        DoubleBlackCases(node);
        return;
    }

    Color parentColor = node->parent->color;
    //case 3 : sibling color is black and both the siblings of child are black
    if(parentColor == Black && sibling->color == Black
       && ( sibling->rightChild == nullptr ||sibling->rightChild->color == Black)
       && ( sibling->leftChild == nullptr || sibling->leftChild->color == Black) ){

        sibling->color = Red;
        if(node->building_num == -1){
            DeleteDoubleBlackNullNode(node);
        }
        DoubleBlackCases(sibling->parent);
        return;
    }

    //case 4: parent is red and sibling is black, both the children of the sibling are black
    if(parentColor == Red && sibling->color == Black
       && ( sibling->rightChild == nullptr ||sibling->rightChild->color == Black)
       && ( sibling->leftChild == nullptr || sibling->leftChild->color == Black)) {

        node->parent->color = Black;
        sibling->color = Red;
        if(node->building_num == -1){
            DeleteDoubleBlackNullNode(node);
        }
        return;
    }

    //case 5 & 6: relationship between node and siblings child being on the far end or the nearer end respectively
    if(sibling->color == Black){
        if(node->parent->leftChild == node){
            if(sibling->leftChild != nullptr &&  sibling->leftChild->color == Red &&
            (sibling->rightChild == nullptr || sibling->rightChild->color == Black)
            ){
                //case 5-1
                sibling->color = Red;
                sibling->leftChild->color = Black;
                RightRotation(sibling->leftChild);
                DoubleBlackCases(node);
            }else{
                //case 6-1
                sibling->color = node->parent->color;
                node->parent->color = Black;
                sibling->rightChild->color = Black;
                LeftRotation(sibling);
                if(node->building_num == -1){
                    DeleteDoubleBlackNullNode(node);
                }
            }

            return;
        }else{
            if(sibling->rightChild != nullptr &&  sibling->rightChild->color == Red &&
            (sibling->leftChild == nullptr || sibling->leftChild->color == Black)
            ){
                //case 5-1
                sibling->color = Red;
                sibling->rightChild->color = Black;
                LeftRotation(sibling->rightChild);
                DoubleBlackCases(node);
            }else{
                //case 6
                sibling->color = node->parent->color;
                node->parent->color = Black;
                sibling->leftChild->color = Black;
                RightRotation(sibling);
                if(node->building_num == -1){
                    DeleteDoubleBlackNullNode(node);
                }
            }
            return;
        }
    }
    cout<<"reached impossible Double Node Case"<<endl;
}

//deleting double black node
void Structure :: DeleteDoubleBlackNullNode(RedBlackElement* DoubleBlackNull){
    if(DoubleBlackNull->parent->rightChild == DoubleBlackNull){
        DoubleBlackNull->parent->rightChild = nullptr;
    }else{
        DoubleBlackNull->parent->leftChild = nullptr;
    }
    delete DoubleBlackNull;

}

//returns sibling of the given node
RedBlackElement* Structure::Sibling(RedBlackElement *node) {
    if(node->parent->rightChild == node){
        return node->parent->leftChild;
    }else{
        return node->parent->rightChild;
    }
}

//returns Inorder Succesor of the given node
RedBlackElement* Structure::InorderSuccesor(RedBlackElement *rightNode) {
    while(rightNode->leftChild != nullptr){
        rightNode = rightNode->leftChild;
    }
    return rightNode;
}

//swap contents of the two nodes and change the address of the node in it's corresponding heap
void Structure::SwapNodes(RedBlackElement *node1, RedBlackElement *node2) {
    int temp = node1->building_num;
    node1->building_num = node2->building_num;
    node1->detail = node2->detail;

    node2->building_num = temp;

    //changing address at heap node
    node1->detail->Node = node1;
}

//returns the node pointer if found, returns null if not found
RedBlackElement* Structure::SearchTreeByValue(int building_num, RedBlackElement* root1) {
    if(root1 == nullptr){
        //cout<<"building not found"<<endl;
        return nullptr;
    }

    if(root1->building_num == building_num){
        return root1;
    }

    if(root1->building_num > building_num){
        return SearchTreeByValue(building_num,root1->leftChild);
    }

    if(root1->building_num < building_num){
        return SearchTreeByValue(building_num,root1->rightChild);
    }
}

//Inserts a building into the structure
void Structure:: InsertBuilding(int building_num, int total_time){
    RedBlackElement* treeNode = new RedBlackElement(building_num, nullptr, nullptr, nullptr,Red, nullptr);
    //creation of Min heap Node
    MinHeapElement* heapElement =  new MinHeapElement(building_num,0,total_time,treeNode);
    treeNode->detail = heapElement;

    if(root==NULL ){
        treeNode->color = Black;
        root = treeNode;
    }else{
        RBTinsert(treeNode);
    }
    heapInsert(heapElement);
}

//
void Structure::PrintBuilding(int building_num, ofstream& output) {
    //searching
    RedBlackElement *node = Structure::SearchTreeByValue(building_num, root);
    if (node != NULL) {
        MinHeapElement *heapNode = node->detail;
        output << "(" << heapNode->building_num << "," << heapNode->exec_time << "," << heapNode->total_time << ")"<< endl;
    }
    //if not found print (0,0,0)
    else{
        output <<"(0,0,0)"<<endl;
    }
    return;
}

//returns all the nodes between the range of Numbers
string Structure::PrintBuildingForRange(int building_num1,int building_num2,RedBlackElement* node, string result) {
    if (node == nullptr) {
        return result;
    }

    if(building_num1 < node->building_num){
        result = PrintBuildingForRange(building_num1,building_num2,node->leftChild, result);
    }

    if(building_num1 <= node->building_num && building_num2 >= node->building_num){
        if(result.length() == 0){
            result = "(" + to_string( node->detail->building_num )+ "," + to_string( node->detail->exec_time )+ "," + to_string( node->detail->total_time )+ ")";
        }else{
            result += ",(" + to_string( node->detail->building_num )+ "," + to_string( node->detail->exec_time )+ "," + to_string( node->detail->total_time )+ ")";
        }
    }

    if(building_num2 > node->building_num){
        result = PrintBuildingForRange(building_num1,building_num2,node->rightChild,result);
    }
    return result;
}

//command execution, reads first letter and number of fields
//I - Insert
//P - size 3: Print Building, size 4: Print Range
void Structure::ExecuteCommand(vector <string> command, ofstream& output){
    if(command[1][0] == 'I'){
        this->InsertBuilding(stoi(command[2]),stoi(command[3]));
    }
    else if(command[1][0] == 'P'){
        if(command.size() == 3){
            this->PrintBuilding(stoi(command[2]), output);
        }else{
            string temp = this->PrintBuildingForRange(stoi(command[2]),stoi(command[3]),this->root, "");
            if(temp.length() == 0){
                output<<"(0,0,0)"<<endl;
            }else{
                output<<temp<<endl;
            }
        }
    }
}


