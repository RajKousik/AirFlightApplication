#include <iostream>
#include <vector>
#include <algorithm>

//for simplicity, maximum available tickets is 50, and starting price is 5000

#define MAX_TICKETS 50
#define INITIAL_TICKET_PRICE 5000

using namespace std;

class Flight
{
private:
    
    //static varibale, which will be used for setting the flightID
    static int tempId;
    
    
    int passengerID = 1;   //used to set the initial passenger ID
    int ticketsAvailable;
    int flightID;
    int ticketPrice;

    vector<int> passengerIDList;        //stores the passengersID
    vector<int> ticketPriceOfEachPassengersList;        //stores the ticketP price of each passenger
    vector<int> ticketsBookedByPassengersList;      //stores the no of tickets booked details by a passenger
    vector<string> passengersDetailsList;       //contains the passenger details

public:

    //constructor
    Flight()
    {
        ticketsAvailable = MAX_TICKETS;
        ticketPrice = INITIAL_TICKET_PRICE;
        tempId = tempId + 1;        //initialize the static ID
        flightID =  tempId;         //initialze the flightID
    }

    //getters and setters for private data members
    int getFlightID()
    {
        return flightID;
    }

    int getTicketsAvailable()
    {
        return ticketsAvailable;
    }

    int getPassengerID()
    {
        return passengerID;
    }
    
    //to increment the passengerID
    void incrementPassengerID()
    {
        passengerID++;
    }

    //actual functions
    
    
    void setDetails(string passengerDetails, int passengerID, int noOfTickets)
    {

        passengerDetails += "Total Cost = " + to_string(noOfTickets * ticketPrice) + "\n";  //string which Contains passengers details

        passengerIDList.push_back(passengerID);         //push the passenger ID to the list
        ticketPriceOfEachPassengersList.push_back(noOfTickets * ticketPrice);           //push the ticketprice
        ticketsBookedByPassengersList.push_back(noOfTickets);       //push the no of tickets booked
        passengersDetailsList.push_back(passengerDetails);      //push the details

        ticketPrice += 200 * noOfTickets;       //increase the price of after booking

        ticketsAvailable -= noOfTickets;        //reduce the available tickets

        cout<<"Booked Successfully!"<<endl<<endl;
    }

    void printPassengerDetails()
    {
        cout<<"------------Passenger Details------------"<<endl;
        
        //if no passengers
        if(passengersDetailsList.size() == 0)
        {
            cout<<"No Details to show!"<<endl<<endl;
            return;
        }
        
        //loop through passengerDetailsList and print one by one
        for(auto &details : passengersDetailsList)
        {
            cout<<details<<endl;
        }
    }
    
    //printing the flight details
    void printFlightDetails()
    {
        cout<<endl<<"------------FlightDetails------------"<<endl;
        cout<<"FlightID : "<<flightID<<endl;
        cout<<"No of Tickets Available : "<<ticketsAvailable<<endl;
        cout<<"Cost of Ticket : "<<ticketPrice<<endl<<endl;
    }
    
    //on successfull cancellation, it returns true
    bool cancellingTickets(int passengerIdToBeCancelled)
    {
        //find the index of passenger ID whose tickets needs to be cancelled 
        auto indexPtr = std::find(passengerIDList.begin(), passengerIDList.end(), passengerIdToBeCancelled);

        //if it points to the end, no such ID exists(invalid passengerID)
        //so no cancelling operation is done, return false
        if(indexPtr == passengerIDList.end())
        {
            cout<<"Passenger ID not found!"<<endl;
            cout<<"Canceling Operation Failed!"<<endl<<endl;
            return false;
        }
        
        //find the index from the pointer
        int indexToBeRemoved = indexPtr - passengerIDList.begin();

        //no of tickets booked by that passenger
        int noOfTicketsToCancel = ticketsBookedByPassengersList[indexToBeRemoved];
        
        //update the available tickets,
        //decrease the price
        ticketsAvailable += noOfTicketsToCancel;
        ticketPrice -= 200 * noOfTicketsToCancel;
        
        //print the refund amount
        cout<<endl<<"Refund Amount of Rs." + to_string(ticketPriceOfEachPassengersList[indexToBeRemoved]) + " Successfully credited!"<<endl;
        
        //remove all the elements of that passenger
        passengerIDList.erase(passengerIDList.begin() + indexToBeRemoved);
        ticketPriceOfEachPassengersList.erase(ticketPriceOfEachPassengersList.begin() + indexToBeRemoved);
        ticketsBookedByPassengersList.erase(ticketsBookedByPassengersList.begin() + indexToBeRemoved);
        passengersDetailsList.erase(passengersDetailsList.begin() + indexToBeRemoved);

        cout<<"Tickets Canceled Successfully!"<<endl<<endl;
    
        //return true
        return true;
    }
};

//initializing the static variable
int Flight::tempId=0;
