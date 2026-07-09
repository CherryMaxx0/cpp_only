#include <iostream>

using namespace std;
int main(void) {
    int t;
    cout<<"Enter time in seconds: ";
    cin>>t;

    int hours=t/3600, minutes=(t%3600)/60, seconds=(t%60);
    cout<<"\n"<<hours<<"hrs "<<minutes<<"mins "<<seconds<<"secs ";
    
}