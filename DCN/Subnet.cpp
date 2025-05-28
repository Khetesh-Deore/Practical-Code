#include <iostream>
#include <cmath>

using namespace std;

void calculateSubnet(int cidr, int subnetMask[4])
{
    for(int i=0; i<4; i++)
    {
        if(cidr >= 8){
            subnetMask[i] = 255;
            cidr -= 8;
        }
        else{
            subnetMask[i] = 256 - pow(2, 8 - cidr);  
            cidr = 0;
        }
    }
}

int main()
{
    int IP[4];
    int cidr;
    int user_cidr;
    int subnetMask[4] = {0,0,0,0};
    
    cout << "Enter the IP address (Each number separately):" << endl;
    for (int i = 0; i < 4; i++)
    {
        cin >> IP[i];
    }

    cout << "Enter the CIDR value: ";
    cin >> user_cidr;

    if (IP[0] < 0 || IP[0] > 255)
    {
        cout << "Invalid IP address. Each number should be between 0 and 255." << endl;
        return 0;
    }

    for (int i = 1; i < 4; i++)
    {
        if (IP[i] < 0 || IP[i] > 255)
        {
            cout << "Invalid IP address. Each number should be between 0 and 255." << endl;
            return 0;
        }
    }

    cout << "IP Address: " << IP[0] << "." << IP[1] << "." << IP[2] << "." << IP[3] << endl;
    
    if (0 <= IP[0] && IP[0] <= 126)
    {
        cout << "It belongs to Class A" << endl;
        cout << "Default Subnet Mask: 255.0.0.0" << endl;
        cidr = 8;
    }
    else if (128 <= IP[0] && IP[0] <= 191)
    {
        cout << "It belongs to Class B" << endl;
        cout << "Default Subnet Mask: 255.255.0.0" << endl;
        cidr = 16;
    }
    else if (192 <= IP[0] && IP[0] <= 223)
    {
        cout << "It belongs to Class C" << endl;
        cout << "Default Subnet Mask: 255.255.255.0" << endl;
        cidr = 24;
    }
    else if (224 <= IP[0] && IP[0] <= 239)
    {
        cout << "It belongs to Class D" << endl;
        return 0;
    }
    else if (240 <= IP[0] && IP[0] <= 255)
    {
        cout << "It belongs to Class E" << endl;
        return 0;
    }

    int borrow = user_cidr - cidr;
    if (borrow >= 0)
    {
        int numSubnets = pow(2, borrow);
        int totalHosts = pow(2, 8 - borrow);
        int usableHosts = totalHosts - 2; 

        cout << "Number of Subnets (Networks): " << numSubnets << endl;
        cout << "Number of IP addresses per subnet: " << totalHosts << endl;
        cout << "Number of Host addresses per subnet: " << usableHosts << endl;

        
        calculateSubnet(user_cidr, subnetMask);
        cout << "New Subnet Mask: " << subnetMask[0] << "." << subnetMask[1] << "." << subnetMask[2] << "." << subnetMask[3] << endl;
        
       
        cout << "\nSubnet Details:\n";
        for (int i = 0; i < numSubnets; i++) {
            int networkID = i * totalHosts;
            int broadcastID = networkID + totalHosts - 1;

            cout << "\nSubnet " << i + 1 << ":" << endl;
            cout << "Network ID: " << IP[0] << "." << IP[1] << "." << IP[2] << "." << networkID << endl;
            cout << "Broadcast ID: " << IP[0] << "." << IP[1] << "." << IP[2] << "." << broadcastID << endl;
            cout << "Host addresses range from: " 
                 << IP[0] << "." << IP[1] << "." << IP[2] << "." << networkID + 1 
                 << " to " 
                 << IP[0] << "." << IP[1] << "." << IP[2] << "." << broadcastID - 1 << endl;
        }
    }
    else
    {
        cout << "Invalid CIDR value. It must be greater than or equal to " << cidr << "." << endl;
    }

    return 0;
}
