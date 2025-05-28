#include<iostream>
#include<ctime>
using namespace std;

bool isSent(){
    return ((rand() % 100) < 50);
}

int main(){

    
    srand(time(0));

    int total = 10;
    int windowSize = 3;

    int sender[total] = {1,2,3,4,5,6,7,8,9,10};
    int recever[total] = {0};
    bool ack[total] = {0};

    cout << endl;
    cout << "Sending Array : { ";
    for(int i: sender){
        cout << i << " ";
    }
    cout<<"}" << endl;
    cout << endl;

    while(1){

        int limit = windowSize;
        for(int i = 0; i < total; i++){
            if(ack[i] == 0){
                cout << "Sending Frame : " << sender[i] << endl;
                limit--;
            }
            if(limit == 0)
                break;
        }
        if(limit == windowSize){
            break;
        }
        cout<<endl;
        
        limit = windowSize;
        for(int i = 0; i < total; i++){
            if(ack[i] == 0){
                cout << "Reciving Frame : " << sender[i];
                limit--;

                if(isSent()){
                    cout << " [Sucess]" << endl;
                    ack[i] = 1;
                    recever[i] = sender[i];
                }
                else{
                    cout << " [Failure]" << endl;
                }
            }
            
            if(limit == 0)
            break;
        }
        cout<<endl;
    }

    cout << endl;
    cout << "Recived Array : { ";
    for(int i: recever){
        cout << i << " ";
    }
    cout<<"}" << endl;
    cout << endl;


    return 0;
}



