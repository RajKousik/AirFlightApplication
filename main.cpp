#include <iostream>
#include <vector>
#include <string>
#include "flight.h"

using namespace std;

#define NO_OF_FLIGHTS 2

vector<Flight> flights;

void printDetails()
{
    for(Flight &f : flights)
    {
        f.printFlightDetails();
        f.printPassengerDetails();
    }
}

void bookTickets(Flight* passengerFlight, int passengerID, int noOfTickets, string name, int age)
{

    string passengerDetails;
    passengerDetails = "PassengerID = " + to_string(passengerID) + "\nNo. Of Tickets Booked = " + to_string(noOfTickets) + "\n";

    passengerDetails += "Name: " + name + "\nAge: " + to_string(age) + "\n";

    passengerFlight->setDetails(passengerDetails, passengerID, noOfTickets);

    passengerFlight->printPassengerDetails();
}


void getDetails()
{
    int passengerFlightID;
    cout<<"Enter the Flight ID: ";
    cin>>passengerFlightID;

    if( passengerFlightID <= 0 || passengerFlightID > flights.size())
    {
        cout<<"Invalid Flight ID! \nTry Again!"<<endl<<endl;
        return;
    }

    Flight* passengerFlight;

    for(Flight &f : flights)
    {
        if(f.getFlightID() == passengerFlightID)
        {
            passengerFlight = &f;
            break;
        }
    }

    passengerFlight->printFlightDetails();

    if(passengerFlight->getTicketsAvailable() == 0)
    {
        cout<<"Oops! No tickets Available at the moment! Try Another Flight!"<<endl<<endl;
        return;
    }

    int noOfTickets;

    cout<<"Number of Tickets Needed: ";
    cin>>noOfTickets;


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


    int age;
    cout<<"Enter Your Age: ";
    cin>>age;

    bookTickets(passengerFlight, passengerFlight->getPassengerID(), noOfTickets, name, age);

    (passengerFlight->incrementPassengerID());

}

void cancelTickets(Flight* cancelingFlight, int passengerIdToBeCancelled)
{
    bool isSuccessful = cancelingFlight->cancellingTickets(passengerIdToBeCancelled);

    if(isSuccessful)
    {
        cancelingFlight->printFlightDetails();
        cancelingFlight->printPassengerDetails();
    }

}

void getCancelDetails()
{
    int flightIdToBeCancelled;
    cout<<"Enter the Flight ID : ";
    cin>>flightIdToBeCancelled;

    if(flightIdToBeCancelled > flights.size())
    {
        cout<<"Invalid Flight ID!"<<endl<<endl;
        return;
    }


    Flight* cancellingFlight;

    for(Flight &flight : flights)
    {
        if(flight.getFlightID() == flightIdToBeCancelled)
        {
            cancellingFlight = &flight;
            break;
        }
    }

    if(cancellingFlight->getTicketsAvailable() == 50)
    {
        cout<<"No Booking is done so for!..Canceling Operation is failed!"<<endl<<endl;
        return;
    }

    int passengerIdToBeCancelled;
    cout<<"Enter the passenger ID to be canceled : ";
    cin>>passengerIdToBeCancelled;

    cancelTickets(cancellingFlight, passengerIdToBeCancelled);
    return;
}


int main()
{


    for(int i=0; i<NO_OF_FLIGHTS; i++)
    {
        flights.push_back(Flight());
    }

    while(true)
    {
        cout<<"------------WELCOME TO RK AIRLINES------------"<<endl;
        cout<<"1. Book Tickets"<<endl;
        cout<<"2. Cancel Tickets"<<endl;
        cout<<"3. Print Details"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter Your Choice: "<<endl;

        int choice;

        cin>>choice;

        switch(choice)
        {
            case 1:
                getDetails();
                break;
            case 2:
                getCancelDetails();
                break;
            case 3:
                printDetails();
                break;
            case 4:
                cout<<"Thanks for using!!!"<<endl;
                exit(-1);
            default:
                cout<<"Invalid Choice!!"<<endl;
                break;
        }

    }


    return 0;
}
