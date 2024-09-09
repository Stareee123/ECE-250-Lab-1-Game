// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "game.h"


int main(){

    // variable used to run a while loop that runs till function over is called
    bool program_run = true;

    //setting up variables that will be used to intake the inputs by the user
    std::string command = " ";
    double x = 0;
    double y = 0;
    double t = 0;
    double d = 0;


    LinkedList linkedobject;

    while (program_run){
        std::cin >> command;
        if (command == "SPAWN"){
            std::cin >> x >> y;             //getting inputs for spawn function
            linkedobject.spawn (x, y);      //calling function spawn

        }else if (command == "TIME"){
            std::cin >> t;                  //getting inputs for time function
            linkedobject.time (t);          //calling function time

        }else if (command == "LUNCH"){
            linkedobject.lunch();           //calling function lunch

        }else if (command == "NUM"){
            linkedobject.num();             //calling function num

        }else if (command == "PRT"){
            std::cin >> d;                  //getting inputs for prt function
            linkedobject.prt(d);            //calling function prt

        }else if (command == "OVER"){
            linkedobject.over();            //calling function over

            program_run = false;            //setting bool variable program_run to false to exit the program
        };
    };
};