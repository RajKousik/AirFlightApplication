#include <iostream>
#include <vector>
#include <string>
#include "flight.h"

using namespace std;

//for simplicity, number of flights is considered to be 2
#define NO_OF_FLIGHTS 2

//a vector array of flight class, which stores the details of the flight and the passengers
vector<Flight> flights;

//printing the details
void printDetails()
{
    for(Flight &f : flights)        //loop thriugh each flight, and print the flight details
    {
        f.printFlightDetails();     //prints the flight details
        f.printPassengerDetails();      //prints the passengers details
    }
}

void bookTickets(Flight* passengerFlight, int passengerID, int noOfTickets, string name, int age)
{

    string passengerDetails;        //stores the information of the passengers
    
    passengerDetails = "PassengerID = " + to_string(passengerID) + "\nNo. Of Tickets Booked = " + to_string(noOfTickets) + "\n";

    passengerDetails += "Name: " + name + "\nAge: " + to_string(age) + "\n";

    passengerFlight->setDetails(passengerDetails, passengerID, noOfTickets);        //updating the information

    passengerFlight->printPassengerDetails();
}


void getDetails()
{
    
    int passengerFlightID;
    cout<<"Enter the Flight ID: ";
    cin>>passengerFlightID;     //get input about in which flight the user want to book the ticket 

       //if invalid, return error
    if( passengerFlightID <= 0 || passengerFlightID > flights.size())
    {
        cout<<"Invalid Flight ID! \nTry Again!"<<endl<<endl;
        return;
    }
    
    //creating the object
    Flight* passengerFlight;
    
    //loop through every flight, and find the user flight by checking the id
    for(Flight &f : flights)
    {
        if(f.getFlightID() == passengerFlightID)
        {
            passengerFlight = &f;
            break;
        }
    }

    passengerFlight->printFlightDetails();
    
    //if no tickets availabe in the flight, return error
    if(passengerFlight->getTicketsAvailable() == 0)
    {
        cout<<"Oops! No tickets Available at the moment! Try Another Flight!"<<endl<<endl;
        return;
    }

    int noOfTickets;
    
    //get the number of tickets the user wants to book
    cout<<"Number of Tickets Needed: ";
    cin>>noOfTickets;

    
    //if no of tickets is greater than the available one, return error
    if(noOfTickets > (passengerFlight->getTicketsAvailable()))
    {

        cout<<"Sorry! Not enough seats available!"<<endl<<endl;
        return;
    }
    
    /* for getting name with spaces */
    string name;
    cout<<"Enter Your Name: ";
    cin.ignore();
    getline(cin, name);

    //get the user age
    int age;
    cout<<"Enter Your Age: ";
    cin>>age;
    
    //calling the book tickets function
    bookTickets(passengerFlight, passengerFlight->getPassengerID(), noOfTickets, name, age);
    
    //increment the passenger ID for next passenger
    (passengerFlight->incrementPassengerID());

}

void cancelTickets(Flight* cancelingFlight, int passengerIdToBeCancelled)
{
    //calling the cancellingtickets function with the passenger ID to be cancelled
    bool isSuccessful = cancelingFlight->cancellingTickets(passengerIdToBeCancelled);
    
    //if succesfully cancelled, print the details
    if(isSuccessful)
    {
        cancelingFlight->printFlightDetails();
        cancelingFlight->printPassengerDetails();
    }

}

void getCancelDetails()
{
    //the flight ID in which the tickets need to be canceled
    
    int flightIdToBeCancelled;
    cout<<"Enter the Flight ID : ";
    cin>>flightIdToBeCancelled;

    //if invalid, return error
    if(flightIdToBeCancelled > flights.size())
    {
        cout<<"Invalid Flight ID!"<<endl<<endl;
        return;
    }

    //create a object
    Flight* cancellingFlight;
    
    //find the flight ID
    for(Flight &flight : flights)
    {
        if(flight.getFlightID() == flightIdToBeCancelled)
        {
            cancellingFlight = &flight;
            break;
        }
    }
    
    //if full tickets are available, then no one booked, so cannot be cancelled
    if(cancellingFlight->getTicketsAvailable() == 50)
    {
        cout<<"No Booking is done so for!..Canceling Operation is failed!"<<endl<<endl;
        return;
    }
    
    //get the passenger ID to be cancelled
    int passengerIdToBeCancelled;
    cout<<"Enter the passenger ID to be canceled : ";
    cin>>passengerIdToBeCancelled;
    
    //call the canceltickets function
    cancelTickets(cancellingFlight, passengerIdToBeCancelled);
    return;
}


int main()
{

    //creating the object for the flight class
    for(int i=0; i<NO_OF_FLIGHTS; i++)
    {
        flights.push_back(Flight());
    }
    
    //non-stop loop
    while(true)
    {
        //basic functionalities display
        cout<<"------------WELCOME TO RK AIRLINES------------"<<endl;
        cout<<"1. Book Tickets"<<endl;
        cout<<"2. Cancel Tickets"<<endl;
        cout<<"3. Print Details"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter Your Choice: "<<endl;
    
        int choice;

        cin>>choice;
        
        //based on the choice, calling the appropriate functions
        switch(choice)
        {
            case 1:
                getDetails();       //for booking tickets, details should be brought from the user
                break;
            case 2:
                getCancelDetails();     //for cancelling tickets
                break;
            case 3:
                printDetails();     //printing the details of the user
                break;
            case 4:
                cout<<"Thanks for using!!!"<<endl;      
                exit(-1);       //exiting from the function
            default:
                cout<<"Invalid Choice!!"<<endl;     //for invalid input
                break;
        }

    }


    return 0;
}
