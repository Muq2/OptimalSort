#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include <deque>

void sortStrings(std::deque<std::string> &v) //first attempt 
{
  
  int smallest = 0;

  for(int i = 0; i < v.size(); i++) 
    {
      smallest = i;
      
      for(int j = i+1; j < v.size(); j++) 
	{
          //if(v[j].compare(v[smallest]) > 0) // A value < 0 : if v[j] is shorter than v[smallest] or, first character that doesn't match is smaller than v[smallest]. - ASCII
	  if(strcasecmp(v[j].c_str(), v[smallest].c_str()) > 0)
	    smallest = j;
	}

      // swap
      std::string temp = v[smallest];
      
      v.erase(v.begin()+smallest);
      v.push_front(temp);
      
    }
  
}

void sortStrings2(std::deque<std::string> &v) //discovered merging
{
  if (v.size() <= 1)
    return;

  auto iter = v.begin() + v.size() / 2;
  std::deque<std::string> v1(v.begin(), iter);
  std::deque<std::string> v2(iter, v.end());

  //divide the original deque multiple times until we get the two-element deques
  sortStrings2(v1);
  sortStrings2(v2);

  v.clear();
  std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v)); //merged into four-element deques and so on until the final level of recursion returns
}

const int ch_MAX = 26;
std::deque<std::string> randomStrings(int wordCount) //create random words for testing
{
  char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z' };
  std::deque<std::string> strings;
  
  for (int i = 0; i < wordCount; i++)
    {
      std::string string = "";
      for (int j = 0; j < rand() % 15 + 3; j++)
	{
	  string = string + alpha[rand() % ch_MAX];
	}
     
      strings.push_back(string);
    }
  
  return strings;
}


int main()
{
  std::string i; //input string
  std::string t; //temp string
  std::deque<std::string> vs; //vector of strings

  int stringsNum = 1000;
  //vs = randomStrings(stringsNum); //random word testing

  //print each word on a new line
  /*
  for(std::string w : vs)
    std::cout << w << std::endl;

  std::cout << "\n";
  */
  
  //put each word into the vector
  while(std::getline(std::cin, t))
    {
      if(t == "")
    	break;
      
      vs.emplace_back(t);
    }
  
    
  stringsNum = vs.size();

  auto start = std::chrono::high_resolution_clock::now(); //startpoint

  //sort the vector
  //std::sort(vs.begin(), vs.end()); //Time taken to sort 1000 strings: 526 microseconds;
  sortStrings(vs);                 //Time taken to sort 1000 strings: 88844 microseconds; 
  //sortStrings2(vs);                  //Time taken to sort 1000 strings: 2809 microseconds;
  
  auto stop = std::chrono::high_resolution_clock::now(); //endpoint

  //print each word on a new line
  for(std::string w : vs)
    std::cout << w << std::endl;

  // Get duration. Substart timepoints to
  // get duration. To cast it to proper unit
  // use duration cast method
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
 
  std::cout << "Time taken to sort " << stringsNum << " strings: " << duration.count() << " microseconds" << std::endl;

  
  return 0;
}
