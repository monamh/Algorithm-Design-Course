#include <iostream>
#include <limits>

using namespace std;

struct maxIndex{
    int sum;
    int start_index;
    int end_index;
};

struct maxIndex maximum_crossing_subarray(int arr[],int start,int mid,int e){
    int sum=0; int p; int q;
    int left_sum=(-1)*numeric_limits<int>::max(); int right_sum=(-1)*numeric_limits<int>::max();
    for(int i=mid; i>=start; i--){
       sum+=arr[i];
       if(sum>left_sum){
            left_sum=sum;
            p=i;
       }
    }
    sum=0;
    for(int j=mid+1; j<=e; j++){
        sum+=arr[j];
        if(sum>right_sum){
            right_sum=sum;
            q=j;
        }
    }

    maxIndex mi={left_sum+right_sum,p,q};

    /*int sum=arr[mid]+arr[mid+1];
    int p=mid;int q=mid+1;
    for(int i=mid-1; i>=start; i--)
        if((arr[i]+sum)>=sum){
            sum+=arr[i];
            p=i;
        }
    for(int j=mid+2; j<=e; j++)
        if((arr[j]+sum)>=sum){
            sum+=arr[j];
            q=j;
        }
    maxIndex mi={sum,p,q};
    */
    return mi;
}

struct maxIndex find_maximum_subarray(int arr[],int start,int e){
    maxIndex ms;
    int mid=(start+e)/2;
    maxIndex left,right;
    if(start==e){
        //ms={arr[start],start,e};
        ms.sum=arr[start];
        ms.start_index=start;
        ms.end_index=e;
    }
    else{
        ms=maximum_crossing_subarray(arr,start,mid,e);
        left=find_maximum_subarray(arr,start,mid);
        right=find_maximum_subarray(arr,mid+1,e);
        if(left.sum>=ms.sum)
            ms=left;
        if(right.sum>=ms.sum)
            ms=right;
    }

    return ms;

}


int main()
{
    int n; int arr[100000];
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>arr[i];
    maxIndex mi=find_maximum_subarray(arr,0,n-1);
    cout<<mi.start_index<<endl<<mi.end_index<<endl;
    return 0;
}
