// Kevin Alvarez, SID: 862131623, CS170 Spring 2021
// April 27, 2021

// To Compile this program: g++ -std=c++11 kevinsProject1.cpp

#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <iomanip>
#include <vector>
#include <list>
using namespace std;
bool goalCheck = false;
int expandedNodes = 0;
int secondChoice;
int maxQueue = 0;

//swap indexes
bool swap0and3 = false;
bool swap0and1 = false;
bool swap1and2 = false;
bool swap1and0 = false;
bool swap1and4 = false;
bool swap2and5 = false;
bool swap2and1 = false;
bool swap3and0 = false;
bool swap3and4 = false;
bool swap3and6 = false;
bool swap4and5 = false;
bool swap4and1 = false;
bool swap4and3 = false;
bool swap4and7 = false;
bool swap5and8 = false;
bool swap5and2 = false;
bool swap5and4 = false;
bool swap6and7 = false;
bool swap6and3 = false;
bool swap7and8 = false;
bool swap7and6 = false;
bool swap7and4 = false;
bool swap8and5 = false;
bool swap8and7 = false;




class Problem
{
public:
    int value;
    
    vector<int> init_state = {0,0,0,0,0,0,0,0,0}; // initial to all zero
    vector<int> goal_state = {1,2,3,4,5,6,7,8,0}; // desired goal state
    int depth = 0;
    //Problem* parent = NULL;

    
};

// This function will make sure that the element inside the frontier priority queue, that the one with the lowest value
// will be the one of top of queue
struct ComparePriority {
    bool operator()(Problem const &v1, Problem const &v2)
    {
        if(secondChoice == 1)
        {
            return v1.depth > v2.depth;
        }
        else{
        return v1.value > v2.value;
        }
    }
};


priority_queue<Problem, vector<Problem>,ComparePriority> frontier;   // priority queue for the vector of states
set<vector<int> > explored;                                         // explored set



// GOAL TEST
// This test will compare the passed in object's initial state without another object's goal state
// Every created object is initialized with a goal state of (1,2,3,4,5,6,7,8,0)
void goalTest(Problem obj)
{
    Problem checker;
    
    if(obj.init_state == checker.goal_state)
    {
        goalCheck = true;
    }
    else{
        goalCheck = false;
    }
}


// This function will go through indexes (0-8) to find where zero is located
// Once it's found it, depending on the located of it, it will decide what
// moves are possible from that location. Example: if 0 in index 0, it can
// only go down and up. So it assigns swap0and3 and swap0and1 as true
void locateZero(Problem obj)
{
    
    swap0and3 = false;
    swap0and1 = false;
    swap1and2 = false;
    swap1and0 = false;
    swap1and4 = false;
    swap2and5 = false;
    swap2and1 = false;
    swap3and0 = false;
    swap3and4 = false;
    swap3and6 = false;
    swap4and5 = false;
    swap4and1 = false;
    swap4and3 = false;
    swap4and7 = false;
    swap5and8 = false;
    swap5and2 = false;
    swap5and4 = false;
    swap6and7 = false;
    swap6and3 = false;
    swap7and8 = false;
    swap7and6 = false;
    swap7and4 = false;
    swap8and5 = false;
    swap8and7 = false;
    
    
    if(obj.init_state[0] == 0)
    {
        swap0and1 = true;
        swap0and3 = true;
    }
    else if(obj.init_state[1] == 0)
    {
        swap1and2 = true;
        swap1and4 = true;
        swap1and0 = true;
    }
    else if(obj.init_state[2] == 0)
    {
        swap2and5 = true;
        swap2and1 = true;
    }
    else if(obj.init_state[3] == 0)
    {
        swap3and4 = true;
        swap3and6 = true;
        swap3and0 = true;
    }
    else if(obj.init_state[4] == 0)
    {
        swap4and5 = true;
        swap4and7 = true;
        swap4and1 = true;
        swap4and3 = true;
        
    }
    else if(obj.init_state[5] == 0)
    {
        swap5and8 = true;
        swap5and2 = true;
        swap5and4 = true;
    }
    else if(obj.init_state[6] == 0)
    {
        swap6and7 = true;
        swap6and3 = true;
    }
    else if(obj.init_state[7] == 0)
    {
        swap7and8 = true;
        swap7and6 = true;
        swap7and4 = true;
    }
    else if(obj.init_state[8] == 0)
    {
        swap8and7 = true;
        swap8and5 = true;
    }
    
}


// This function will check how many numbers are in the incorrect spot.
// It checks each index(0-8) and each time the incorrect number is in that
// spot it will add 1 to the count. At the end it will return the total
// of this count.
float misplacedHeuristic(Problem obj)
{
    float heuristic = 0;
    if(obj.init_state[0] != 1)
    {
        heuristic++;
    }
    if(obj.init_state[1] != 2)
    {
        heuristic++;
    }
    if(obj.init_state[2] != 3)
    {
        heuristic++;
    }
    if(obj.init_state[3] != 4)
    {
        heuristic++;
    }
    if(obj.init_state[4] != 5)
    {
        heuristic++;
    }
    if(obj.init_state[5] != 6)
    {
        heuristic++;
    }
    if(obj.init_state[6] != 7)
    {
        heuristic++;
    }
    if(obj.init_state[7] != 8)
    {
        heuristic++;
    }
    
    //obj.value = heuristic;
    return heuristic;
    
    
}


// This function will check each index of the passed in object. and it will check all the numbers (one by one)
// and how far they are from their correct place. Each time it finds a number that is
// not in the correct spot it will add the eucledian distance from that incorrect spot.
float eucledianHeuristic(Problem obj)
{
    float temp = 0;
    
    if(obj.init_state[1] == 1)
    {
        temp += 1;
    }
    else if(obj.init_state[2] == 1)
    {
        temp += 2;
    }
    else if(obj.init_state[3] == 1)
    {
        temp += 1;
    }
    else if(obj.init_state[4] == 1)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[5] == 1)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[6] == 1)
    {
        temp += 2;
    }
    else if(obj.init_state[7] == 1)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[8] == 1)
    {
        temp += 2*sqrt(2);
    }
    
    
    // -------
    
    if(obj.init_state[0] == 2)
    {
        temp += 1;
    }
    else if(obj.init_state[2] == 2)
    {
        temp += 1;
    }
    else if(obj.init_state[3] == 2)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[4] == 2)
    {
        temp += 1;
    }
    else if(obj.init_state[5] == 2)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[6] == 2)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[7] == 2)
    {
        temp += 2;
    }
    else if(obj.init_state[8] == 2)
    {
        temp += sqrt(5);
    }
    
    // -----------
    
    if(obj.init_state[0] == 3)
    {
        temp += 2;
    }
    else if(obj.init_state[1] == 3)
    {
        temp += 1;
    }
    else if(obj.init_state[3] == 3)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[4] == 3)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[5] == 3)
    {
        temp += 1;
    }
    else if(obj.init_state[6] == 3)
    {
        temp += 2*sqrt(2);
    }
    else if(obj.init_state[7] == 3)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[8] == 3)
    {
        temp += 2;
    }
    
    // ---------------
    
    if(obj.init_state[0] == 4)
    {
        temp += 1;
    }
    else if(obj.init_state[1] == 4)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[2] == 4)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[4] == 4)
    {
        temp += 1;
    }
    else if(obj.init_state[5] == 4)
    {
        temp += 2;
    }
    else if(obj.init_state[6] == 4)
    {
        temp += 1;
    }
    else if(obj.init_state[7] == 4)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[8] == 4)
    {
        temp += sqrt(5);
    }
    
    // ---------------
    
    if(obj.init_state[0] == 5)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[1] == 5)
    {
        temp += 1;
    }
    else if(obj.init_state[2] == 5)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[3] == 5)
    {
        temp += 1;
    }
    else if(obj.init_state[5] == 5)
    {
        temp += 1;
    }
    else if(obj.init_state[6] == 5)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[7] == 5)
    {
        temp += 1;
    }
    else if(obj.init_state[8] == 5)
    {
        temp += sqrt(2);
    }
    
    // -----------------
    
    if(obj.init_state[0] == 6)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[1] == 6)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[2] == 6)
    {
        temp += 1;
    }
    else if(obj.init_state[3] == 6)
    {
        temp += 2;
    }
    else if(obj.init_state[4] == 6)
    {
        temp += 1;
    }
    else if(obj.init_state[6] == 6)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[7] == 6)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[8] == 6)
    {
        temp += 1;
    }
    
    // ---------------
    
    if(obj.init_state[0] == 7)
    {
        temp += 2;
    }
    else if(obj.init_state[1] == 7)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[2] == 7)
    {
        temp += 2*sqrt(2);
    }
    else if(obj.init_state[3] == 7)
    {
        temp += 1;
    }
    else if(obj.init_state[4] == 7)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[5] == 7)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[7] == 7)
    {
        temp += 1;
    }
    else if(obj.init_state[8] == 7)
    {
        temp += 2;
    }
    
    // ---------------

    
    if(obj.init_state[0] == 8)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[1] == 8)
    {
        temp += 2;
    }
    else if(obj.init_state[2] == 8)
    {
        temp += sqrt(5);
    }
    else if(obj.init_state[3] == 8)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[4] == 8)
    {
        temp += 1;
    }
    else if(obj.init_state[5] == 8)
    {
        temp += sqrt(2);
    }
    else if(obj.init_state[6] == 8)
    {
        temp += 1;
    }
    else if(obj.init_state[8] == 8)
    {
        temp += 1;
    }
    
    // ---------------
    
    
    
    return temp;
}


// Up function
// The up function will move the zero up in the puzzle. This function works with the locateZero function
// it first sends the object to that function and determine where the zero is at, so we know what moves are possible
// then after it finishes that function a new object is create and it copys that obj that was passed into this function
// we copy it to another object because if we use the same obj then the object will be different when it gets
// passed into the down, right, left functions, We want the same object and it's content to be used for all those
// functions.
// So depending on what variables got changed to true, it will move up. The only time the zero can move up is when
// its in index 3, 4, 5, 6, 7, 8. Thats why those if statements have those conditions.
// So if any of them are true(according to the locateZero function) they will swap with the
// correct index. If none of them are true then we don't move up and the Moved variable stays false.
void up(Problem obj)
{
    locateZero(obj);
    Problem obj2 = obj;
    bool moved = false;

    
    if(swap3and0 == true)
    {
        swap(obj2.init_state[3],obj2.init_state[0]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap4and1 == true)
    {
        swap(obj2.init_state[4],obj2.init_state[1]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap5and2 == true)
    {
        swap(obj2.init_state[5],obj2.init_state[2]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap6and3 == true)
    {
        swap(obj2.init_state[6],obj2.init_state[3]);
        //obj2.value++;
        moved = true;
    }
    else if(swap7and4 == true)
    {
        swap(obj2.init_state[7],obj2.init_state[4]);
        //obj2.value++;
        moved = true;
    }
    else if(swap8and5 == true)
    {
        swap(obj2.init_state[8],obj2.init_state[5]);
        //obj2.value++;
        moved = true;
    }
    
    if(moved == true)
        
    {
        if(secondChoice == 1)
        {
            obj2.depth++;
            obj2.value = obj2.depth;
        }
        if(secondChoice == 2)
        {
            float temp = misplacedHeuristic(obj2);
           
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        if(secondChoice == 3)
        {
            float temp = eucledianHeuristic(obj2);
            
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        frontier.push(obj2);
        
        
        // Depending on the choicr of algorithm
        // it will add/not add the heuristic and value

    }
    
    /*
    swap8and5 = false;
    swap7and4 = false;
    swap6and3 = false;
    swap5and2 = false;
    swap4and1 = false;
    swap3and0 = false;
    */
    
}


// Similar logic as Up function
void down(Problem obj)
{
    
    locateZero(obj);
    Problem obj2 = obj;
    bool moved = false;
    
    
    if(swap0and3 == true)
    {
        swap(obj2.init_state[0],obj2.init_state[3]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap1and4 == true)
    {
        swap(obj2.init_state[1],obj2.init_state[4]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap2and5 == true)
    {
        swap(obj2.init_state[2],obj2.init_state[5]);
        //obj2.value++;
        moved = true;
    }
    else if(swap3and6 == true)
    {
        swap(obj2.init_state[3],obj2.init_state[6]);
        //obj2.value++;
        moved = true;
    }
    else if(swap4and7 == true)
    {
        swap(obj2.init_state[4],obj2.init_state[7]);
        //obj2.value++;
        moved = true;
    }
    else if(swap5and8 == true)
    {
        swap(obj2.init_state[5],obj2.init_state[8]);
        //obj2.value++;
        moved = true;
    }
    
    if(moved == true)
    {
        if(secondChoice == 1)
        {
            obj2.depth++;
            obj2.value = obj2.depth;
        }
        if(secondChoice == 2)
        {
            float temp = misplacedHeuristic(obj2);
            //obj2.value += temp;
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        if(secondChoice == 3)
        {
            float temp = eucledianHeuristic(obj2);
            //obj2.value += temp;
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        
        frontier.push(obj2);
        //expandedNodes++;

    }
    
    /*
    swap5and8 = false;
    swap4and7 = false;
    swap3and6 = false;
    swap1and4 = false;
    swap2and5 = false;
    swap0and3 = false;
    */
}


// Similar logic as Up function
void right(Problem obj)
{
    locateZero(obj);
    Problem obj2 = obj;
    bool moved = false;
    
    
    if(swap0and1 == true)
    {
        swap(obj2.init_state[0],obj2.init_state[1]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap1and2 == true)
    {
        swap(obj2.init_state[1],obj2.init_state[2]);
        //obj2.value++;
        moved = true;
        
    }
    else if(swap3and4 == true)
    {
        swap(obj2.init_state[3],obj2.init_state[4]);
        //obj2.value++;
        moved = true;
    }
    else if(swap4and5 == true)
    {
        swap(obj2.init_state[4],obj2.init_state[5]);
        //obj2.value++;
        moved = true;
    }
    else if(swap6and7 == true)
    {
        swap(obj2.init_state[6],obj2.init_state[7]);
        //obj2.value++;
        moved = true;
    }
    else if(swap7and8 == true)
    {
        swap(obj2.init_state[7],obj2.init_state[8]);
        //obj2.value++;
        moved = true;
    }
    
    
    if(moved == true)
    {
        if(secondChoice == 1)
        {
            obj2.depth++;
            obj2.value = obj2.depth;
        }
        if(secondChoice == 2)
        {
            float temp = misplacedHeuristic(obj2);
            //obj2.value += temp;
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        if(secondChoice == 3)
        {
            float temp = eucledianHeuristic(obj2);
            //obj2.value += temp;
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        frontier.push(obj2);
        //expandedNodes++;

    }
    
    
/*
    swap7and8 = false;
    swap6and7 = false;
    swap4and5 = false;
    swap3and4 = false;
    swap1and2 = false;
    swap0and1 = false;
    */
    
}


// Similar logic as Up function
void left(Problem obj)
{
    locateZero(obj);
    Problem obj2 = obj;
    bool moved = false;
    
 
    
    if(swap1and0 == true)
    {
        swap(obj2.init_state[1],obj2.init_state[0]);
        //obj2.value++;
        moved = true;
    }
    else if(swap2and1 == true)
    {
        swap(obj2.init_state[2],obj2.init_state[1]);
        //obj2.value++;
        moved = true;
    }
    else if(swap4and3 == true)
    {
        swap(obj2.init_state[4],obj2.init_state[3]);
        //obj2.value++;
        moved = true;
    }
    else if(swap5and4 == true)
    {
        swap(obj2.init_state[5],obj2.init_state[4]);
        //obj2.value++;
        moved = true;
    }
    else if(swap7and6 == true)
    {
        swap(obj2.init_state[7],obj2.init_state[6]);
        //obj2.value++;
        moved = true;
    }
    else if(swap8and7 == true)
    {
        swap(obj2.init_state[8],obj2.init_state[7]);
        //obj2.value++;
        moved = true;
    }
    
    if(moved == true)
    {
        if(secondChoice == 1)
        {
            obj2.depth++;
            obj2.value = obj2.depth;
            
        }
        if(secondChoice == 2)
        {
            float temp = misplacedHeuristic(obj2);
            //obj2.value += temp;
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        if(secondChoice == 3)
        {
            float temp = eucledianHeuristic(obj2);
            //obj2.value += temp;
            obj2.depth++;
            obj2.value = obj2.depth + temp;
        }
        
        frontier.push(obj2);
        //
        //expandedNodes++;
    }
    
    /*
    swap8and7 = false;
    swap7and6 = false;
    swap5and4 = false;
    swap4and3 = false;
    swap1and0 = false;
    swap2and1 = false;
    */
    
}


// print function will print out the passed in objects init_state which is basically
// it's current state at that moment when it's passed in.
void printState(Problem obj)
{

    cout << endl;
    cout << obj.init_state[0] << '\t' << obj.init_state[1] << '\t' << obj.init_state[2] << endl;
    cout << obj.init_state[3] << '\t' << obj.init_state[4] << '\t' << obj.init_state[5] << endl;
    cout << obj.init_state[6] << '\t' << obj.init_state[7] << '\t' << obj.init_state[8] << endl;
    
    
}



void uniformCostSearch(Problem obj)
{
    //frontier.push(obj);
    
    if(frontier.size() == 0) // Check if frontier is zero
    {
        cout << "\nERROR!\n\n";
        exit(1);
    }
    else
    {
        bool startOver = false; // this variable will work with the next IF statement below
        do{
    
            
            do{
                
                startOver = false;
                
                if(!explored.empty() && !frontier.empty() && goalCheck == false) // Will only go in here if these conditions are met
                {
                    set <vector<int> > :: iterator it;  // iterator to got through the explored set

                    for(it = explored.begin(); it != explored.end(); it++) // start from beginning of set to the end
                    {

                
                        if(*it == frontier.top().init_state) // compares each vector in the explored set with the top in the frontier
                            {                                // if a vector in the frontier matches a vector in the explored set it deletes it
                                                            // If it finds at least one that is the same, the for loop will start over
                                frontier.pop();             // and do the same thing with the new top of the frontier
                                startOver = true;           // this turn to true so we can run the for loop again
                                
                                break; // breaks loop right when it finds the duplicate

                            }
                
                    }
                
                
                }
     
            }while(startOver == true);
            
        
            if(frontier.size() > maxQueue)
            {
                maxQueue = (int)frontier.size();
            }
            
        if(frontier.size() == 0) // another check to if we explored every possible state, therefore the frontier should be 0
        {                       // because we already explored it so it should of gotten popped off in the above IF

            cout << "\nFrontier is empty! Error. No goal found!\n\n";
            exit(-1);
        }
        
            
        Problem newObj = frontier.top();        // copy frontier top state into another object
        goalTest(newObj);                       // checks to see if that objects initial state(current state) is the desired state
        //explored.insert(frontier.top().init_state);
        frontier.pop();                                     // pops this state out of frontier
        //goalTest(newObj);
            
            
            cout << "\n\nThe best state to expand with g(n) = " << newObj.depth << " and h(n) = 0" << " is . . .\n";
            printState(newObj);
            
        if(goalCheck == true)
        {
            cout << "\n\n---------------\nGoal found!!!\n";
            printState(newObj);
            cout << "\nDepth: " << newObj.depth << endl << "Max Frontier queue size at one time: " << maxQueue << endl << endl;
            cout << "To solve this problem the search algorithm expanded a total of " << expandedNodes <<
            " Nodes.\n\n";
            //exit(0);
        }
        else{
            // Uses same object's initial state(current state) for all function below
            up(newObj);                         // run the Up function
            down(newObj);                       // run down function
            right(newObj);                      // run right function
            left(newObj);                       // run left funtion
            explored.insert(newObj.init_state);         // add the Node (newObj's initial state) into explored set)
            expandedNodes++;        // keep track of how many states we expanded
    
            
            }
            
        }while(goalCheck == false); // if no goal found yet we run this uniformCostSearch function again
        

    }
    
}

// -------------------
// MISPLACED TILES ALGORITHM BELOW
//
// -------------------
void misplacedTiles(Problem obj)
{
    
    if(frontier.size() == 0)            // Check if frontier is zero

    {
        cout << "\nERROR!\n\n";
        exit(1);
    }
    else
    {
        bool startOver = false;             // this variable will work with the next IF statement below
        
        do{
        
            
            do{
                
                startOver = false;
                
                
                if(!explored.empty() && !frontier.empty() && goalCheck == false)
                {
                    set <vector<int> > :: iterator it;              // iterator to got through the explored set

                    for(it = explored.begin(); it != explored.end(); it++)          // start from beginning of set to the end
                    {

                
                        if(*it == frontier.top().init_state)
                        {                                               // compares each vector in the explored set with the top in the frontier
                            frontier.pop();                         // if a vector in the frontier matches a vector in the explored set it deletes                                          it
                            startOver = true;                       // If it finds at least one that is the same, the for loop will start over
                            break;                                  // and do the same thing with the new top of the frontier
                                                                    // this turn to true so we can run the for loop again
                        }
                
                    }
                
                
                }
     
            }while(startOver == true);              // if found duplicated start for loop over again to check again
            
        
            if(frontier.size() > maxQueue)
            {
                maxQueue = (int)frontier.size();
            }
            
            
            
            
        if(frontier.size() == 0)
        {

            cout << "\nFrontier is empty! Error. No goal found!\n\n";
            exit(-1);
        }
        
            
        Problem newObj = frontier.top();        // copy frontier's top vector into another new object
        goalTest(newObj);                       // check to see if we've reach our desired state
        
        frontier.pop();                         // pops top vector in priority queue
        //goalTest(newObj);
            
            
        cout << "\n\nThe best state to expand with g(n) = " << newObj.depth << " and h(n) = " << newObj.value - newObj.depth << " is . . .\n";
        printState(newObj);
            
        if(goalCheck == true)           // if we have reach goal state, we print out GOAL FOUND and print the objeects current initial state state
        {
            cout << "\n\n---------------\nGoal found!!!\n";
            printState(newObj);
            cout << "\nDepth: " << newObj.depth << endl << "Max Frontier queue size at one time: " << maxQueue << endl << endl;
            cout << "To solve this problem the search algorithm expanded a total of " << expandedNodes <<
            " Nodes.\n\n";
            //exit(0);
        }
        else{
            
            
            up(newObj);
            down(newObj);
            right(newObj);
            left(newObj);
            explored.insert(newObj.init_state); // after we have expanded this state we put it in the explored set
            expandedNodes++;
            
        }
            
        }while(goalCheck == false);
        

    }
    
    
    
}


// EUCLEDIAN ALGORITHM

void eucledian(Problem obj)
{
    
    if(frontier.size() == 0)            // checks if frontier is empty
    {
        cout << "\nERROR!\n\n";
        exit(1);
    }
    else
    {
        bool startOver = false;         // variable used in IF statement below
        do{
        
            
            do{
                
                startOver = false; // if no elements in the frontier are found that are already in explored set, then it'll say false
                
                
                if(!explored.empty() && !frontier.empty() && goalCheck == false)
                {
                    set <vector<int> > :: iterator it;              // iterator to go through explored set

                    for(it = explored.begin(); it != explored.end(); it++)
                    {

                
                        if(*it == frontier.top().init_state)        // if a vector(state) from the explored matches the top of frontier then it pops it off
                            {                                       // explaination is the same as the ones above in other algorithms
                
                                frontier.pop();
                                startOver = true;       // if finds one duplicate it become true we can do the for loop again
                                //expandedNodes--;
                                break;

                            }
                
                    }
                
                
                }
     
            }while(startOver == true);
     
            
            if(frontier.size() > maxQueue)
            {
                maxQueue = (int)frontier.size();
            }
            
        
            
        if(frontier.size() == 0)            // If we explored every possible state and we havent found goal state
        {

            cout << "\nFrontier is empty! Error. No goal found!\n\n";
            exit(-1);
        }
        
            
        Problem newObj = frontier.top();                // explanation for the rest is exactly the same as the ones in the other two algorithms
        goalTest(newObj);                               // checks to see if this object has our desired state
        //explored.insert(frontier.top().init_state);
        frontier.pop();
            
        cout << "\n\nThe best state to expand with g(n) = " << newObj.depth << " and h(n) = " << newObj.value - newObj.depth << " is . . .\n";
        printState(newObj);         // print out for the trace
        
            //goalTest(newObj);
            
        if(goalCheck == true)           // if goal state (current state) found then it will print this message
        {
            
            cout << "\n\n---------------\nGoal found!!!\n";
            printState(newObj);
            cout << "\nDepth: " << newObj.depth << endl << "Max Frontier queue size at one time: " << maxQueue << endl << endl;
            cout << "To solve this problem the search algorithm expanded a total of " << expandedNodes <<
            " Nodes.\n\n";
            //exit(0);
        }
        else{
            
            up(newObj);
            down(newObj);
            right(newObj);
            left(newObj);
            explored.insert(newObj.init_state);             // add newObj to explored set
            expandedNodes++;
            
            
        }
            
        }while(goalCheck == false);
        

    }
    
    
    
}



int main() {
    
    Problem firstNode;
    firstNode.value = 0;
    //bool insolvable = false;
    

    int firstChoice;
    
    

    
    cout << "Welcome to 862131623 8 Puzzle Solver\n\n";
    
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle.\n\n";
    

    
    
    do{
    
        cout << "Choice: ";
        cin >> firstChoice;
    
        
    switch(firstChoice)
    {
        case 1:
            firstNode.init_state[0] = 1;            // our hard coded default puzzle state
            firstNode.init_state[1] = 2;
            firstNode.init_state[2] = 3;
            firstNode.init_state[3] = 5;
            firstNode.init_state[4] = 6;
            firstNode.init_state[5] = 0;
            firstNode.init_state[6] = 7;
            firstNode.init_state[7] = 8;
            firstNode.init_state[8] = 4;
            
            break;
        case 2:
            int one,two,three,four,five,six,seven,eight,nine;
            cout << "\nEnter your puzzle, use 0 to represent the blank.\n";
            cout << "Enter your first row, use space or tabs between numbers.\n";
            cin >> one >> two >> three;
            cout << "\nEnter your second row, use space or tabs between numbers.\n";
            cin >> four >> five >> six;
            cout << "\nEnter your third row, use space or tabs between numbers.\n";
            cin >> seven >> eight >> nine;
            
            firstNode.init_state[0] = one;              //initializes with values inputed by user
            firstNode.init_state[1] = two;
            firstNode.init_state[2] = three;
            firstNode.init_state[3] = four;
            firstNode.init_state[4] = five;
            firstNode.init_state[5] = six;
            firstNode.init_state[6] = seven;
            firstNode.init_state[7] = eight;
            firstNode.init_state[8] = nine;
            
            break;
        default:
            cout << "You didn't enter 1 or 2. Try again.\n";
            break;
    }
        
    }while((firstChoice != 1 && firstChoice != 2)); // if user didnt enter 1 or 2 then it re loops
    
    
    
    /*
    int count = 0;
    for(int i = 0; i < 2; i++)
    {
        for(int j = i+1; j < 3; j++)
        {
            if(firstNode.init_state[i] > firstNode.init_state[j])
            {
                count++;
            }
        }

    }
        
        for(int i = 3; i < 5; i++)
        {
            for(int j = i+1; j < 6; j++)
            {
                if(firstNode.init_state[i] > firstNode.init_state[j])
                {
                    count++;
                }
            }

        }
        
        for(int i = 6; i < 8; i++)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(firstNode.init_state[i] > firstNode.init_state[j])
                {
                    count++;
                }
            }

        }
        if(firstNode.init_state[8] == 0 || firstNode.init_state[2] == 0 || firstNode.init_state[5] == 0)
        {
            count -= 2;// we don't count zero if its left side digits are bigger.
        }
        if(firstNode.init_state[1] == 0 || firstNode.init_state[4] == 0 || firstNode.init_state[7] == 0)
        {
            count -= 1;// we don't count zero if its left side digits are bigger.
        }
        
        insolvable = false;
        
    if(count % 2 == 1)
    {
        cout << "\nINSOLVABLE!!!\nTry Again\n\n";
        insolvable = true;
        count=0;
        //exit(-1);
    }
    
 */
    
    
    
    
    
    cout << "\nEnter your choice of algorithm.\n\n";
    cout << "1) Uniform Cost Search.\n2) A* with the Misplaced Tile heuristic.\n3) A* with the Eucledian Distance heuristic.\n\n";
    
    do{
        cout << "Choice: ";
        cin >> secondChoice;
        
        switch(secondChoice)
        {
            case 1:
                //expandedNodes++;
                frontier.push(firstNode);           // adds initial first state into frontier
                uniformCostSearch(firstNode);       // run uniform cost algorithm
                break;
            case 2:
                //expandedNodes++;
                frontier.push(firstNode);
                misplacedTiles(firstNode);          // runs misplaced tiles algorithm
                break;
            case 3:
                //expandedNodes++;
                frontier.push(firstNode);           // runs eucledian distance algorith,
                eucledian(firstNode);
                break;
            
            default:
                cout << "You didn't enter 1 or 2 or 3. Try again.\n";
                break;
        }
        
        
        
        
    }while((secondChoice != 1 && secondChoice != 2 && secondChoice != 3));  // if user didn't enter any algorithm options, it re loops
    


    return 0;               // END
}