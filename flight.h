#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_TICKETS 50
#define INITIAL_TICKET_PRICE 5000

using namespace std;

class Flight
{
private:

    static int tempId;

    int passengerID = 1;
    int ticketsAvailable;
    int flightID;
    int ticketPrice;

    vector<int> passengerIDList;
    vector<int> ticketPriceOfEachPassengersList;
    vector<int> ticketsBookedByPassengersList;
    vector<string> passengersDetailsList;

public:

    //constructor
    Flight()
    {
        ticketsAvailable = MAX_TICKETS;
        ticketPrice = INITIAL_TICKET_PRICE;
        tempId = tempId + 1;
        flightID =  tempId;
    }

    //getters and setters
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

    void incrementPassengerID()
    {
        passengerID++;
    }

    //actual functions
    void setDetails(string passengerDetails, int passengerID, int noOfTickets)
    {

        passengerDetails += "Total Cost = " + to_string(noOfTickets * ticketPrice) + "\n";

        passengerIDList.push_back(passengerID);
        ticketPriceOfEachPassengersList.push_back(noOfTickets * ticketPrice);
        ticketsBookedByPassengersList.push_back(noOfTickets);
        passengersDetailsList.push_back(passengerDetails);

        ticketPrice += 200 * noOfTickets;

        ticketsAvailable -= noOfTickets;

        cout<<"Booked Successfully!"<<endl<<endl;
    }

    void printPassengerDetails()
    {
        cout<<"------------Passenger Details------------"<<endl;
        if(passengersDetailsList.size() == 0)
        {
            cout<<"No Details to show!"<<endl<<endl;
            return;
        }

        for(auto &details : passengersDetailsList)
        {
            cout<<details<<endl;
        }
    }

    void printFlightDetails()
    {
        cout<<endl<<"------------FlightDetails------------"<<endl;
        cout<<"FlightID : "<<flightID<<endl;
        cout<<"No of Tickets Available : "<<ticketsAvailable<<endl;
        cout<<"Cost of Ticket : "<<ticketPrice<<endl<<endl;
    }

    bool cancellingTickets(int passengerIdToBeCancelled)
    {
        auto indexPtr = std::find(passengerIDList.begin(), passengerIDList.end(), passengerIdToBeCancelled);

        if(indexPtr == passengerIDList.end())
        {
            cout<<"Passenger ID not found!"<<endl;
            cout<<"Canceling Operation Failed!"<<endl<<endl;
            return false;
        }

        int indexToBeRemoved = indexPtr - passengerIDList.begin();

        //updating
        int noOfTicketsToCancel = ticketsBookedByPassengersList[indexToBeRemoved];

        ticketsAvailable += noOfTicketsToCancel;
        ticketPrice -= 200 * noOfTicketsToCancel;

        cout<<endl<<"Refund Amount of Rs." + to_string(ticketPriceOfEachPassengersList[indexToBeRemoved]) + " Successfully credited!"<<endl;

        passengerIDList.erase(passengerIDList.begin() + indexToBeRemoved);
        ticketPriceOfEachPassengersList.erase(ticketPriceOfEachPassengersList.begin() + indexToBeRemoved);
        ticketsBookedByPassengersList.erase(ticketsBookedByPassengersList.begin() + indexToBeRemoved);
        passengersDetailsList.erase(passengersDetailsList.begin() + indexToBeRemoved);

        cout<<"Tickets Canceled Successfully!"<<endl<<endl;

        return true;
    }
};

//initializing the static variable
int Flight::tempId=0;
