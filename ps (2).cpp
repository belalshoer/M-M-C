#include<iostream>
#include <queue>
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
class Customer{
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
    Customer customerBeingServed;
    bool free;
    float business_time = 0;

public:
    Teller()
    {
        free = true;

    }

    void addCustomer()
    {

        free = false;
    }


};

Teller teller1;
Teller teller2;
queue<Customer> customerQueue;
deque<Customer> qw;
float z = 0;
float counter = 0;
float total_waiting = 0;
void recursedwait() {
    while ((customerQueue.back().arrivalTime >= 0) && (z <= 70)) {
        z++;
        if ((customerQueue.back().arrivalTime == 0)) {
            qw.push_back(customerQueue.back());
        }
        if (qw.size() > 0) {
            if (teller1.free) {
                teller1.free = false;
                teller1.business_time = qw.front().serviceTime;
                total_waiting = qw.front().waiting_time;
                counter += 1;
                qw.pop_front();
                
            }
            if (teller2.free) {
                if (qw.size() > 0) {
                    teller2.free = false;
                    teller2.business_time = qw.front().serviceTime;
                    total_waiting = qw.front().waiting_time;
                    counter += 1;
                    qw.pop_front();
                    
                }
            }
        }
        for (int j = 0; j < qw.size(); j++) {
            qw[j].waiting_time+=1;
            
        }
        
        teller1.business_time--;
        teller2.business_time--;
        if (teller1.business_time == 0) {
            teller1.free = true;
        }
        if (teller2.business_time == 0) {
            teller2.free = true;
        }
        


        if (customerQueue.back().arrivalTime == 0) {
                Customer rcustomer;
               
                customerQueue.push(rcustomer);  
                recursedwait();
            }
        customerQueue.back().arrivalTime--;
       
        }
    

    
        
}
int main()
{
    Customer customer;
    customerQueue.push(customer);
    recursedwait();
}


/*
queue<Customer> secondq;
int service() {
    for (int i = 0; i < 1000; i++) {
        if (teller1.free  || teller2.free ) {
            if (teller1.free) {
                if (customerQueue.front().arrivalTime == 0) {
                    teller1.free = false;
                    teller1.bt = customerQueue.front().serviceTime;

                }
            }

            if (teller2.free ) {
                if (customerQueue.front().arrivalTime == 0) {
                    teller2.free = false;
                    teller2.bt = customerQueue.front().serviceTime;

                }
            }

        }
        else {
            if (customerQueue.front().arrivalTime == 0) {
                secondq.push(customerQueue.front());
                customerQueue.front().waiting_time += 1;


            }
        }
    }
}

void recursedservice(int &waiting_time) {
    while (!((customerQueue.front().serviceTime <= 0) && ((teller1.free == false)))) {
        --customerQueue.front().serviceTime;
            int i = 0;
            waiting_time += ((customerQueue.size()-1) * i);
        if (customerQueue.front().serviceTime == 0) {
            teller1.addCustomer();
            customerQueue.pop();
            recursedservice(waiting_time);
        }
        cout << waiting_time;
        ++i;





    }
}
*/
    /*const int M = 2; // Number of tellers
    const int N = 20; // Simulation time in minutes
    queue<Customer> customerQueue;
    Teller tellers[M];
    int totalWait = 0, numCustServed = 1;
    cout<<"Customer No. Arrival time Waiting time in queue"<<endl;
    cout<<"------------ ------------ ---------------------"<<endl;
    Customer customer(randwait());
    customerQueue.push(customer);

    for (currentTime = 0; currentTime < N; currentTime++)
    {
        if (customer.arrivalTime == currentTime)
        {
            
            Customer customer(randwait());
            customerQueue.push(customer);
            cout<<"      "<<numCustServed<<"             "<<currentTime<<"               "<<totalWait/numCustServed<<endl;
        }
        for (int t = 0; t < M; t++)
        {
            if (tellers[t].isFree() && (!customerQueue.empty()))
            {
                Customer customer = customerQueue.front();
                tellers[t].addCustomer(customer);
                totalWait = totalWait + (currentTime - customer.getArrivalTime());
                customerQueue.pop();
                numCustServed++;
            }

        }
        // end of for teller
    } // end of for current time

    cout << "\nTotal waiting time : " << totalWait << endl;
    cout << "Number of Customers served : "<< numCustServed<<endl;
    cout << "Average waiting time : " << totalWait/numCustServed<<endl;
    cout << "After service the number of customers left in queue : "<< customerQueue.size()<<endl;


    cout<<"==================================================================================================================="<<endl;
    cout<<"\n\n\nCustomer No. Arrival time Waiting time in queue"<<endl;
    cout<<"------------ ------------ ---------------------"<<endl;

    //while (customerQueue.size()>0)
    //{
    //if (1+rand()%10 <= left)
    //{
    //Customer customer(currentTime);
    //cout<<" "<<numCustServed<<" "<<currentTime<<" "<<totalWait/numCustServed<<endl;
    //}

    int t = M;
    while (customerQueue.size()>0)
    {
        for (int t = 0; t < M; t++)
            if (tellers[t].isFree() && (!customerQueue.empty()))
            {
                Customer customer = customerQueue.front();
                customerQueue.pop();
                cout<<"      "<<numCustServed<<"         "<<currentTime<<"              "<<totalWait/numCustServed<<endl;
                t++;
                numCustServed++;
            }
    }
    cout << "\nTotal waiting time : " << totalWait << endl;
    cout << "Number of Customers served : "<< numCustServed<<endl;
    cout << "Average waiting time : " << totalWait/numCustServed<<endl;
    cout << "After service the number of customers left in queue : "<< customerQueue.size()<<endl;

    // end of for telle
    // end of for current time


    return 0;

}
*/
