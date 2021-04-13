#include <iostream>
#include <string>
using namespace std;



int main()
{
    int choice1;
    cout << "Welcome to 862131623 8 puzzle solver." << endl;

    cout << "Type \"1\" too use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> choice1;


    cout << "Enter your choice of algorithm." << endl; 
    cout << "\nUniform Cost Search\nA* with the Misplaced Tile heuristic\nA* with the Eucledian distance heuristic\n";


    return 0;
}