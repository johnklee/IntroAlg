#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Rtv{
  int left;
  int right;
  int sum;
};

Rtv* FIND_MAX_CROSSING_SUBARRAY(vector<int> &A, int low, int mid, int high)
{
  Rtv *rtv = new Rtv;
  int left_sum = INT_MIN, right_sum = INT_MIN;
  int sum = 0, i=0, max_left=-1, max_right=-1;
  for(i=mid; i>=low; i--)
    {
      sum+=A[i];
      if(sum > left_sum)
	{
	  left_sum = sum;
	  max_left = i;
	}
    }
  sum = 0;
  for(i=mid+1; i<=high; i++)
    {
      sum+=A[i];
      if(sum > right_sum)
	{
	  right_sum = sum;
	  max_right = i;
	}
    }
  rtv->left = max_left;
  rtv->right = max_right;
  rtv->sum = left_sum + right_sum;
  return rtv;
};

Rtv* FIND_MAXIMUM_SUBARRAY(vector<int> &A, int low, int high)
{
  Rtv *rtv = new Rtv;
  if(low == high)
    {
      rtv->left = low;
      rtv->right = low;
      rtv->sum = A[low];
      return rtv;
    }
  else
    {
      int mid = (low+high) / 2;
      Rtv *left_rtv = FIND_MAXIMUM_SUBARRAY(A, low, mid);
      Rtv *right_rtv = FIND_MAXIMUM_SUBARRAY(A, mid+1, high);
      Rtv *cross_rtv = FIND_MAX_CROSSING_SUBARRAY(A, low, mid, high);

      if(left_rtv->sum >= right_rtv->sum && left_rtv->sum >= cross_rtv->sum)
	{
	  rtv->left = left_rtv->left;
	  rtv->right = left_rtv->right;
	  rtv->sum = left_rtv->sum;
	}
      else if(right_rtv->sum >= left_rtv->sum && right_rtv->sum >= cross_rtv->sum)
	{
	  rtv->left = right_rtv->left;
	  rtv->right = right_rtv->right;
	  rtv->sum = right_rtv->sum;
	}
      else
	{
	  rtv->left = cross_rtv->left;
	  rtv->right = cross_rtv->right;
	  rtv->sum = cross_rtv->sum;
	}
      delete left_rtv;
      delete right_rtv;
      delete cross_rtv;
      return rtv;
    }
};

int main()
{
  vector<int> A;
  A.push_back(13);
  A.push_back(-3);
  A.push_back(-25);
  A.push_back(20);
  A.push_back(-3);
  A.push_back(-16);
  A.push_back(-23);
  A.push_back(18);
  A.push_back(20);
  A.push_back(-7);
  A.push_back(12);
  A.push_back(-5);
  A.push_back(-22);
  A.push_back(15);
  A.push_back(-4);
  A.push_back(7);
  Rtv *rtv = FIND_MAXIMUM_SUBARRAY(A, 0, A.size()-1);
  cout << "Maximum Sub Array is from indices("
       << rtv->left << ","
       << rtv->right << ") to have sum="
       << rtv->sum << endl;
  delete rtv;
  return 0;
}
