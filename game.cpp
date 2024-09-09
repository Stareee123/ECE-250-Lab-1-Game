#include "game.h"
#include <string>
#include <iostream>
#include <cmath>

// implement classes' member functions here...

// Constructor of a linked list
LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
};

// Destructor of a linked list
LinkedList::~LinkedList(){
    Node* current = head;
    Node* nextNode;
    bool loop_until = true;

    //while loop will continue to execute till current is nullptr
    while (loop_until){
        if (current != nullptr){            //freeing current node if current contains some address
            nextNode = current->next;
            delete current;
            current = nextNode;
        }else{                              //setting tail to nullptr and exit the destructor loop
            tail = nullptr;
            loop_until = false;
        };
    };
    tail = nullptr;
    head = nullptr;
};

// Stating function spawn
void LinkedList::spawn(double x, double y){

    //if linked list is empty & input is in first quadrant
    if ( x > 0 && y > 0 && head == nullptr){            //comparing rather both x and y values are in first quadrant
        Node* add = new Node(x, y);                     //creating new node with new input values
        head = add;                                     //setting head and tail to a new node since linked list will be completely empty at this point of time
        tail = add;
        std::cout << "success" << std::endl;

        //add player num
        player = player + 1;                            //incrementing player number
    
    //if linked list is not empty & input is in first quadrant
    }else if (x > 0 && y > 0 && head != nullptr){       //comparing rather both x and y values are in first quadrant
        Node* add = new Node(x, y);                     //creating new node with new input values
        add->next = head;                               //adding new node at the start of the linked list by connecting it to head and reassigning head pointer
        head = add;
        std::cout << "success" << std::endl;

        //add player num
        player = player + 1;                            //incrementing player number

    //if input is not in the first quadrant
    }else{
        std::cout << "failure" << std::endl;
    };
};

// Stating function time
void LinkedList::time(double t){
    Node* fake_head = head;                             //stating a pointer named fake_head that will be used like current node in the lecutre examples / named as fake_head since I've beening using that name from ECE 150
    Node* prev = head;                                  //stating a pointer named prev that will be pointing the node right before the fake_head
    Node* x = nullptr;                                  //stating a pointer named x that will be used to store the address that needs to be deleted. double free error was caused without this pointer
    int counter = 0;                                    //stating a int named counter that will be used afterwards - more description later

    while (fake_head != nullptr){

        //getting x & y value stored in the node
        double x_in_node = fake_head->x_value;
        double y_in_node = fake_head->y_value;

        //setting new x & y value / equation was given in the lab instruction
        double new_x = x_in_node - t * cos(atan2(y_in_node, x_in_node));
        double new_y = y_in_node - t * sin(atan2(y_in_node, x_in_node));
        
        //when the node that we are trying to check is the head of the linked list
        if (fake_head == head){

            //if the input node is still on first quadrant after shifting
            if (new_x > 0 && new_y > 0){
                Node* newNode = new Node(new_x, new_y);     //creating new node with new input values
                newNode->next = fake_head->next;            //connecting new node to the node that is after the head
                fake_head = newNode;                        //moving both fake_head and prev to new node since it will be the new head of the linked list
                prev = fake_head;                           // ""

                x = head;                                   //setting x to be equal to the node that needs to be deleted - prevent double free error
                
                if (counter == 0){                          //when time function is initially called, head needs to be reassigned to fake_head to make head to point to correct node
                    head = fake_head;
                    counter = counter + 1;
                };

                fake_head = fake_head->next;                //moving fake_head to the next node

                delete x;                                   //freeing x to prevent memory leak

            //if the input node is not on the first quadrant after shifting
            }else{
                head = fake_head->next;                     //moving head & fake_head to next node / preparing to delete original head node
                fake_head = head;                           //""

                x = prev;                                   //setting x to be equal to the node that needs to be deleted - prevent double free error
                
                prev = head;                                //""

                delete x;                                   //freeing x to prevent memory leak

                player = player - 1;                        //decrementing player number since one player has been removed for cheating
            };
        
        //when the node that we are trying to check is not the head of the linked list
        }else{

            //if the input node is still on first quadrant after shifting
            if (new_x > 0 && new_y > 0){                    
                Node* newNode = new Node(new_x, new_y);     //creating new node with new x & y values
                newNode->next = fake_head->next;            //connecting new node to existing nodes
                prev->next = newNode;                       //""

                x = fake_head;                              //assigning x to the node that needs to be deleted

                fake_head = newNode->next;                  //reassigning fake_head to next of new node
                prev = newNode;                             //reassigning prev to new node

                delete x;                                   //freeing x to prevent momory leak

            //if the input node is not on the first quadrant after shifting
            }else{                                          
                prev->next = fake_head->next;               //connecting connecting prev node to the next node of fake_head node to prepare to remove the current fake_head node

                x = fake_head;                              //assigning x to the node that needs to be deleted

                fake_head = prev->next;                     //reassigning fake_head to next of prev node

                delete x;                                   //freeing x to prevent memory leak

                player = player - 1;                        //decrementing player number
            };
        };
        
    };

    std::cout << "num of players: " << player << std::endl;
};


//Stating function lunch
void LinkedList::lunch(){
    Node* fake_head = head;
    Node* prev = head;
    Node* x = nullptr;
    double distance = 0;                                    //double named distance that will store the node's distance to the wolf

    while (fake_head != nullptr){
        
        //getting x & y value stored in the node
        double x_in_node = fake_head->x_value;
        double y_in_node = fake_head->y_value;

        //calculating the distance using pythagorean theorem
        double root = ((x_in_node * x_in_node) + (y_in_node * y_in_node));
        distance = sqrt(root);

        //when the node that we are trying to check is the head of the linked list
        if(fake_head == head){

            //if the calculated distance value is less than 1
            if(distance < 1){
                fake_head = fake_head->next;                //reassigning fake_head & prev
                prev = fake_head;

                x = head;                                   //assigning x to the node that needs to be deleted

                head = fake_head;                           //reassigning head since the original head node needs to be deleted
                player = player - 1;                        //decrementing player number since one player had be killed(?) by wolf

                if (fake_head != nullptr){                  //shifting fake_head to its next node till fake_head is at the tail
                   fake_head = fake_head->next; 
                };

                delete x;                                   //freeing x to prevent memory leak

            //if the calculated distance value is larger than 1
            }else{
                fake_head = fake_head->next;
            };

        //when the node that we are trying to check is not the head of the linked list
        }else{

            //if the calculated distance value is less than 1
            if (distance < 1){
                prev->next = fake_head->next;               //connecting prev node to the node next to the node that needs to be deleted

                x = fake_head;                              //assigning x to the node that needs to be deleted

                fake_head = prev->next;                     //shifting fake_head to next node of original fake_head
                
                delete x;                                   //freeing x to prevent memory leak

                player = player - 1;                        //decrementing player number since one player had be killed(?) by wolf

            //if the calculated distance value is larger than 1
            }else{
                fake_head = fake_head->next;
                prev = prev->next;
            };
        };
        
    };

    std::cout << "num of players: " << player << std::endl;
};

//Stating function num
void LinkedList::num(){

    //printing the number of players left in the game
    std::cout << "num of players: " << player << std::endl;
};

//Stating function prt
void LinkedList::prt(double d){
    Node* fake_head = head;
    double distance = 0;
    double d_player = 0;                                    //double named d_player that will store the number of players within the inputted distance

    while (fake_head != nullptr){

        //getting x & y value stored in the node
        double x_in_node = fake_head->x_value;
        double y_in_node = fake_head->y_value;

        //getting the distance value of the node
        double root = ((x_in_node * x_in_node) + (y_in_node * y_in_node));
        distance = sqrt(root);

        //printing the node's x & y cordinate if distance is less than d
        if (distance < d){
            std::cout << x_in_node << " " << y_in_node << " ";
            d_player = d_player + 1;
        };
        fake_head = fake_head->next;
    };

    //printing out error statement when there is no player in the d value
    if (d_player == 0){
        std::cout << "no players found" << std::endl;
    }else{
        std::cout <<'\n';
    };
};

//Stating function over
void LinkedList::over(){

    //determine rather player or wolf wins
    if (player == 0){
        std::cout << "wolf wins" << std::endl;
    }else{
        std::cout << "players win" << std::endl;
    };
};
