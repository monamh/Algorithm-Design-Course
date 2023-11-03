#include <iostream>
#include <limits>

using namespace std;

//the arguments are two sorted subarrays from indices s to m and m+1 to e
long merge_and_count(int arr[],int s,int m,int e){
    long c=0;
    int n1=m-s+1; int n2=e-m;
    int left[n1+1];
    int right[n2+1];
    for(int i=0; i<n1; i++)
        left[i]=arr[s+i];
    for(int j=0; j<n2; j++)
        right[j]=arr[m+1+j];
    left[n1]=numeric_limits<int>::max();
    right[n2]=numeric_limits<int>::max();
    int i=0; int j=0;
    for(int k=s; k<=e; k++){
        if(left[i]<=right[j]){
            arr[k]=left[i];
            i++;
        }
        else{
            //if(left[i]!=numeric_limits<int>::max())
                c+=(long)n1-i;
            arr[k]=right[j];
            j++;
        }
    }
    return c;
}

long count_inversions(int arr[],int s,int e){
    if(s>=e)
        return 0;
    else{
        int q=(s+e)/2;
        return count_inversions(arr,s,q)+count_inversions(arr,q+1,e)+merge_and_count(arr,s,q,e);
    }
}

int main()
{
    int arr[200000]; int n;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>arr[i];
    cout<<count_inversions(arr,0,n-1)%100000;//<<endl;
    return 0;
}
