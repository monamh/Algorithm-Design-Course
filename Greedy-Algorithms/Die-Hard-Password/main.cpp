#include <iostream>
#include <cmath>

using namespace std;

bool isPrimary(int n){
    for(int i=2; i<=n/2; i++)
        if(n%i==0)
        return false;
    return true;
}
void addDigit_or_print(int pn,int digits){
    int up_bound=pow(10,digits); int low_bound=pow(10,digits-1);
    if(pn<up_bound && pn>=low_bound)
        cout<<pn<<endl;
    else{
        for(int j=1 ;j<=9 ;j+=2){ //digits added from right can be 1,3,5,7,9
            int n=pn*10+j;
            if(isPrimary(n))
                addDigit_or_print(pn*10+j,digits);
        }
    }

    return;
}


void print_numbers(int digits){
    for(int i=2; i<9; i++){ //MSB has to be primary
        if(isPrimary(i))
            addDigit_or_print(i,digits);
        }
    return;
}


int main()

{
    int n;
    cin>>n;
    print_numbers(n);
    return 0;
}
