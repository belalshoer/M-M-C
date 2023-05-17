#include<iostream>
#include <queue>
#include <deque>
#include <time.h>
#include <random>
using namespace std;

float get_random()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

float randwait() {
    float x = get_random();
    return  log(1 - x) / (static_cast<float>(-1) / 20);
}

float randservice() {
    float x = get_random();
    return  log(1 - x) / (static_cast<float>(-1) / 25);
}

class Customer {
public:
    float arrivalTime;
    float serviceTime;
    float waiting_time = 0;

public:
    Customer()
    {
        arrivalTime = randwait();
        serviceTime = randservice();
    }
    float getArrivalTime()
    {
        return arrivalTime;
    }
};

class Teller
{
public:
    Customer* customerBeingServed;
    bool free;
    float business_time = 0;
    float serviceTime;

public:
    Teller()
    {
        free = true;
        customerBeingServed = nullptr;
    }

    void addCustomer(Customer* customer)
    {
        serviceTime = randservice();
        free = false;
        customerBeingServed = customer;
    }
};


int main()
{
    Teller teller1;
    Teller teller2;
    deque<Customer> customerQueue;
    int z = 0;
    float counter = 0;
    float total_waiting = 0;


    while (z <= 200) {
        z++;
        Customer rcustomer;
        customerQueue.push_back(rcustomer);
        if (teller1.free && !customerQueue.empty()) {
            teller1.addCustomer(&customerQueue.front());
            customerQueue.pop_front();
            teller1.free = false;
            teller1.business_time = (*teller1.customerBeingServed).serviceTime;
            counter += 1;
            total_waiting += ( *teller1.customerBeingServed).waiting_time;

        }

        if (teller2.free && !customerQueue.empty()) {
            teller2.addCustomer(&customerQueue.front());
            customerQueue.pop_front();
            teller2.free = false;
            teller2.business_time = (*teller2.customerBeingServed).serviceTime;
            counter += 1;
            total_waiting += (*teller2.customerBeingServed).waiting_time;
        }
        if (teller1.business_time <= 0) {
            teller1.free = true;
        }
        else {
            teller1.business_time -= 1;
        }

        if (teller2.business_time <= 0) {
            teller2.free = true;
        }
        else {
            teller2.business_time -= 1;
        }


        for (size_t i = 0; i < customerQueue.size(); ++i) {
            customerQueue[i].waiting_time += 1;
            total_waiting += 1;
        }
    }

    float avg_waiting_time = total_waiting / counter;

    cout << "Total customers served: " << counter << '\n';
    cout << "Average waiting time: " << avg_waiting_time << " seconds" << '\n';

    return 0;
}