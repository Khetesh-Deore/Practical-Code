#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

bool isSent(){
    return ((rand() % 100) < 70);
}

int main() {

    srand(time(0));
    int total = 10;
    int windowSize = 3;

    int sender[total] = {1,2,3,4,5,6,7,8,9,10};
    int recever[total] = {0};

    int lastSent = -1;

    cout << endl << "Sending Array : { ";
    for(int i: sender){
        cout << i << " ";
    }
    cout<<"}" << endl << endl;

    while(lastSent < total - 1){

        for(int i = 0; i < 3 && i + lastSent + 1 < total; i++){
            cout << "Sending Frame : "<< sender[i + lastSent + 1] << endl;
        }
        cout << endl;
        
        bool error = 0;
        int last = lastSent;
        for(int i = 0; i < 3; i++){

            int curr = last + i + 1;
            if(curr >= total){
                break;
            }

            cout << "Reciveing Frame : "<< sender[curr];

            if(isSent()){
                cout << " [Sucess]" <<endl;
                if(!error){
                    lastSent = curr;
                    recever[curr] = sender[curr];
                }
            }
            else{
                error = 1;
                cout << " [Failure]" <<endl;
            }

        }
        cout << endl;

    }

    cout << endl << "Recived Array : { ";
    for(int i: recever){
        cout << i << " ";
    }
    cout<<"}" << endl << endl;

    return 0;
}