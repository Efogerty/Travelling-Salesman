#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <tuple>
#include <ctime>
#include <cmath>

using namespace std;
//global size variable
int N=50;
//x and y coordinates for each of the 50 points
struct Coordinate {
  double first;
  double second;
};

//vectors
  vector<Coordinate> V(N);
  //vector to refer to coordinate array's indexes
  vector<int> integers(N);
  vector<int> shortestRoute(N);

//distance comparison
double dist(int a, int b)
{
  double dx = V[a].first - V[b].first, dy = V[a].second - V[b].second;
  return sqrt(dx*dx + dy*dy);
}

//distance of the whole coordinate vector with the index order of int array
double tourlen(void)
{
  double total = 0.0;
  for (int i=0; i<N; i++)
  {
    int a = integers[i];
    int b = integers[(i+1)%N];
    total += dist(a,b);
  }
  return total;
}

//reverse function
void changeOrder(vector<int> &intArray, int firstPosition, int secondPosition) {
    while (firstPosition < secondPosition) {
        swap(intArray[firstPosition], intArray[secondPosition]);
        firstPosition++;
        secondPosition--;
    }
}

int main()
{
  //seed
  srand(time(NULL));
  //load in integers
int i;
  for(i=0;i<N;i++)
  {
    integers[i]=i;
  }
  i=0;
  //starting variables, shortest is high so any number will be better
  double x, y;
  double shortestDistance=9999999999;
  double tourLength=0;
  //read in coordinates
  ifstream wordfile("tsp_points.txt");
  while (wordfile >>x >>y)
  {
    V[i].first=x;
    V[i].second=y;
    i++;
  }
  wordfile.close();
//shuffle array 1000 times and refine it
  for(i=0;i<1000;i++)
  {
    tourLength = 0;
    random_shuffle(integers.begin(),integers.end());
    for(int i=0;i<300;i++)
    {
      for(int j=1;j<N;j++)
      {
        //find a random seed and swap coordinates if new distances are better
        int randomSeed = (rand() % j);
        double initialDist = dist(integers[j],integers[(j+1)%N])+dist(integers[randomSeed],integers[randomSeed-1]);
        double finalDist =dist(integers[j],integers[randomSeed-1])+dist(integers[(j+1)%N],integers[randomSeed]);
        if(finalDist<initialDist)
        {
            changeOrder(integers,randomSeed,j);
        }
      }
    }
    //update shortest every iteration
    if(tourlen()<shortestDistance)
    {
      shortestDistance = tourlen();
      shortestRoute = integers;
    }
  }
//display shortest
  cout <<"Shortest Distance: "<<shortestDistance<<endl<<"Coordinates: ";
  for(int i=0;i<N;i++)
  {
    cout<<shortestRoute[i]<<" ";
  }
  cout<<endl;
}
