#include <iostream>
#include <sstream>
#include "structure.h"

using namespace std;

//Processes a string command to vector of strings diving the command into parts
//input Format : X:Command(P,Q) or X:Command(P,Q,R)
vector<string> CommandProcessing(string command){
    vector<string> result;
    replace(command.begin(),command.end(),':',' ');
    replace(command.begin(),command.end(),')',' ');
    replace(command.begin(),command.end(),'(',' ');
    replace(command.begin(),command.end(),',',' ');
    stringstream stream(command);
    string parts;
    while(getline(stream,parts,' ')){
        if(parts.length() > 0){
            result.push_back(parts);
        }
    }
    return result;
}



int main(int count, char* args[])
{
    int dayCounter = 0;
    Structure city;

    //File Input
    ifstream input;
    input.open("/Users/suhrudh_reddy/CLionProjects/ADS/input.txt");

    ofstream output;
    output.open("/Users/suhrudh_reddy/CLionProjects/ADS/output.txt");

    //variable maintaining the current command
    vector<string> currentCommand ;
    int fiveDayCount = 5;


    MinHeapElement* curMinHeapNode = NULL; //current project being worked on

    //work while : there is input left or root still has value
    while(input || city.root != NULL) {

        string command;//stores command as a string
        //takes the first command as input, only time when command is empty when the input file still has commands left
        if(currentCommand.size() == 0 && input){
            getline(input, command);
            currentCommand = CommandProcessing(command);
        }

        //Current command day matches with the present day
        if (currentCommand.size() > 0 && stoi(currentCommand[0]) == dayCounter) {
            city.ExecuteCommand(currentCommand, output);
            getline(input, command);
            currentCommand = CommandProcessing(command);
        }

        //Building is complete case(removal of the building from the data structure)
        if (curMinHeapNode!=NULL && curMinHeapNode->exec_time == curMinHeapNode->total_time) {
            output<<"("<<curMinHeapNode->building_num<<","<<dayCounter<<")"<<endl; //output to file
            city.RBTdelete(curMinHeapNode->Node); //Deleting in RedBlack Tree.
            delete curMinHeapNode;//Deleting the Min heap element, Removed from MinHeap already
            curMinHeapNode = NULL;
        }

        //5 Day count check
        //when the project is being worked on, it's already removed from the MinHeap
        if (fiveDayCount == 0 && curMinHeapNode != NULL) {
            city.heapInsert(curMinHeapNode);
            curMinHeapNode = NULL;
        }

        //If the previous project has been completed or dropped, picking a new one
        if(curMinHeapNode == NULL && city.heapSize != 0){
            curMinHeapNode = city.minElement();
            city.removeMin(); //removed from Minheap when being worked on
            fiveDayCount = 5;
        }

        // execution time increase and five day count decrease
        if(curMinHeapNode != NULL){
            curMinHeapNode->exec_time++;
            fiveDayCount--;
        }
        dayCounter++;
    }

    //closing the output file
    output.close();

    return 0;
}
