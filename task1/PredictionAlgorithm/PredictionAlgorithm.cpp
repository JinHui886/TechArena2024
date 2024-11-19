// This file contains a template for the implementation of Robo prediction
// algorithm

#include "PredictionAlgorithm.hpp"
#include <cstdio> //using printf for testing purposes
#define arraySize 34
#define limit -1 //limit of (day - night) before a planet record is considered for deletion
#define requirement 3 //requirement to predict next planet to be day

struct RoboPredictor::RoboMemory {
  // Place your RoboMemory content here
  // Note that the size of this data structure can't exceed 64KiB!

  int dayCache[arraySize][2] = {{0}}; //cache to hold recent planets that have been day, if day increments [x][1] by 1, otherwise decrement,
                                      // if [x][1] < limit then remove from cache
  int dayCache2[arraySize][2] = {{0}}; //for second set of cache
  int dayCache3[arraySize][2] = {{0}}; //for third set of cache
  int dayCache4[arraySize][2] = {{0}}; //for fourth set of cache
  int dayCache5[arraySize][2] = {{0}}; //for fifth set of cache
  int dayCache6[arraySize][2] = {{0}}; //for sixth set of cache
  int dayCache7[arraySize][2] = {{0}}; //for seventh set of cache
  int dayCache8[arraySize][2] = {{0}}; //for eighth set of cache

  //this allows for way more planets to be cached than if only one buffer was used

  unsigned int dayCacheCount = 0; //used for indexing cache
  unsigned int removedIndex = 300; //used to take track of last removed index that hasnt been updated with new planet
  unsigned int missedRemoval = 0; //used to track amount of missed planets to remove due to needing a planet to get a score of -5 before it is deleted

  unsigned int dayCacheCount2 = 0;
  unsigned int removedIndex2 = 300;
  unsigned int missedRemoval2 = 0;

  unsigned int dayCacheCount3 = 0;
  unsigned int removedIndex3 = 300;
  unsigned int missedRemoval3 = 0;

  unsigned int dayCacheCount4 = 0;
  unsigned int removedIndex4 = 300;
  unsigned int missedRemoval4 = 0;

  unsigned int dayCacheCount5 = 0;
  unsigned int removedIndex5 = 300;
  unsigned int missedRemoval5 = 0;

  unsigned int dayCacheCount6 = 0;
  unsigned int removedIndex6 = 300;
  unsigned int missedRemoval6 = 0;

  unsigned int dayCacheCount7 = 0;
  unsigned int removedIndex7 = 300;
  unsigned int missedRemoval7 = 0;

  unsigned int dayCacheCount8 = 0;
  unsigned int removedIndex8 = 300;
  unsigned int missedRemoval8 = 0;

  unsigned int dayStreak = 0;
};

bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction) {
  // Robo can consult data structures in its memory while predicting.
  // Example: access Robo's memory with roboMemory_ptr-><your RoboMemory
  // content>

  int dayCount = 0; //stores the amount of times Robo has visited the next planet and it was day (within last (value of arraySize) journeys)
  int totalRecord = 0; //store the amount of times the planet has been visited in the last (value of arraySize) journeys

  if(roboMemory_ptr->dayStreak >= 3)
  {
    return 0;
  }

  if(nextPlanetID >= 500000)
  {
    if(nextPlanetID >= 750000)
    {
      if(nextPlanetID >= 875000)
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
      else
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache2[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache2[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
    }
    else
    {    
      if(nextPlanetID >= 625000)
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache3[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache3[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
      else
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache4[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache4[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
    }
  }
  else
  {
    if(nextPlanetID >= 750000)
    {
      if(nextPlanetID >= 875000)
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache5[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache5[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
      else
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache6[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache6[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
    }
    else
    {    
      if(nextPlanetID >= 625000)
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache7[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache7[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
      else
      {
        for(int x = 0; x < arraySize; x++)
        {
          if(nextPlanetID == roboMemory_ptr->dayCache8[x][0]) //checks if next planet is stored in possibly day cache
          {
            if(roboMemory_ptr->dayCache8[x][1] > requirement) //checks if it actually frequently day
            {
              return 1;
            }
          }
        }
      }
    }    
  }

  return 0; //as it is mostly night upon arrival, no useful predictions should predict night

  // Robo can perform computations using any data in its memory during
  // prediction. It is important not to exceed the computation cost threshold
  // while making predictions and updating RoboMemory. The computation cost of
  // prediction and updating RoboMemory is calculated by the playground
  // automatically and printed together with accuracy at the end of the
  // evaluation (see main.cpp for more details).

  // Simple prediction policy: follow the spaceship computer's suggestions
  return spaceshipComputerPrediction;
}

void RoboPredictor::observeAndRecordTimeofdayOnNextPlanet(
    std::uint64_t nextPlanetID, bool timeOfDayOnNextPlanet) {
  // Robo can consult/update data structures in its memory
  // Example: access Robo's memory with roboMemory_ptr-><your RoboMemory
  // content>
  
  bool change = 0;
  unsigned int indexOfChange = 300;

  if(nextPlanetID >= 500000)
  {
    if(nextPlanetID >= 750000)
    {
      if(nextPlanetID >= 875000)
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex != 300 || roboMemory_ptr->dayCacheCount < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex != 300)
            {
              roboMemory_ptr->dayCache[roboMemory_ptr->removedIndex][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache[roboMemory_ptr->removedIndex][1] = 1;
              roboMemory_ptr->dayCacheCount++;
              roboMemory_ptr->removedIndex = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache[roboMemory_ptr->dayCacheCount][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache[roboMemory_ptr->dayCacheCount][1] = 1;
              roboMemory_ptr->dayCacheCount++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache[x][1] <= limit)
              {
                roboMemory_ptr->dayCache[x][0] = 0; //removes record
                roboMemory_ptr->dayCache[x][1] = 0;
                roboMemory_ptr->removedIndex = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
      else
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount2; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache2[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache2[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount2; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache2[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache2[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache2[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex2 != 300 || roboMemory_ptr->dayCacheCount2 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex2 != 300)
            {
              roboMemory_ptr->dayCache2[roboMemory_ptr->removedIndex2][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache2[roboMemory_ptr->removedIndex2][1] = 1;
              roboMemory_ptr->dayCacheCount2++;
              roboMemory_ptr->removedIndex2 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache2[roboMemory_ptr->dayCacheCount2][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache2[roboMemory_ptr->dayCacheCount2][1] = 1;
              roboMemory_ptr->dayCacheCount2++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache2[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex2 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache2[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache2[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex2 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval2++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval2 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex2 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount2; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache2[x][1] <= limit)
              {
                roboMemory_ptr->dayCache2[x][0] = 0; //removes record
                roboMemory_ptr->dayCache2[x][1] = 0;
                roboMemory_ptr->removedIndex2 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval2--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
    }
    else
    {
      if (nextPlanetID >= 625000)
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount3; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache3[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache3[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount3; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache3[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache3[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache3[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex3 != 300 || roboMemory_ptr->dayCacheCount3 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex3 != 300)
            {
              roboMemory_ptr->dayCache3[roboMemory_ptr->removedIndex3][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache3[roboMemory_ptr->removedIndex3][1] = 1;
              roboMemory_ptr->dayCacheCount3++;
              roboMemory_ptr->removedIndex3 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache3[roboMemory_ptr->dayCacheCount3][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache3[roboMemory_ptr->dayCacheCount3][1] = 1;
              roboMemory_ptr->dayCacheCount3++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache3[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex3 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache3[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache3[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex3 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval3++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval3 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex3 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount3; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache3[x][1] <= limit)
              {
                roboMemory_ptr->dayCache3[x][0] = 0; //removes record
                roboMemory_ptr->dayCache3[x][1] = 0;
                roboMemory_ptr->removedIndex3 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval3--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
      else if (nextPlanetID >= 0)
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount4; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache4[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache4[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount4; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache4[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache4[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache4[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex4 != 300 || roboMemory_ptr->dayCacheCount4 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex4 != 300)
            {
              roboMemory_ptr->dayCache4[roboMemory_ptr->removedIndex4][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache4[roboMemory_ptr->removedIndex4][1] = 1;
              roboMemory_ptr->dayCacheCount4++;
              roboMemory_ptr->removedIndex4 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache4[roboMemory_ptr->dayCacheCount4][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache4[roboMemory_ptr->dayCacheCount4][1] = 1;
              roboMemory_ptr->dayCacheCount4++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache4[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex4 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache4[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache4[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex4 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval4++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval4 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex4 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount4; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache4[x][1] <= limit)
              {
                roboMemory_ptr->dayCache4[x][0] = 0; //removes record
                roboMemory_ptr->dayCache4[x][1] = 0;
                roboMemory_ptr->removedIndex4 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval4--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
    }
  }
  else
  {
    if(nextPlanetID >= 250000)
    {
      if(nextPlanetID >= 375000)
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount5; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache5[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache5[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount5; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache5[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache5[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache5[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex5 != 300 || roboMemory_ptr->dayCacheCount5 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex5 != 300)
            {
              roboMemory_ptr->dayCache5[roboMemory_ptr->removedIndex5][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache5[roboMemory_ptr->removedIndex5][1] = 1;
              roboMemory_ptr->dayCacheCount5++;
              roboMemory_ptr->removedIndex5 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache5[roboMemory_ptr->dayCacheCount5][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache5[roboMemory_ptr->dayCacheCount5][1] = 1;
              roboMemory_ptr->dayCacheCount5++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache5[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex5 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache5[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache5[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex5 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval5++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval5 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex5 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount5; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache5[x][1] <= limit)
              {
                roboMemory_ptr->dayCache5[x][0] = 0; //removes record
                roboMemory_ptr->dayCache5[x][1] = 0;
                roboMemory_ptr->removedIndex5 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval5--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
      else
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount6; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache6[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache6[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount6; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache6[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache6[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache6[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex6 != 300 || roboMemory_ptr->dayCacheCount6 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex6 != 300)
            {
              roboMemory_ptr->dayCache6[roboMemory_ptr->removedIndex6][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache6[roboMemory_ptr->removedIndex6][1] = 1;
              roboMemory_ptr->dayCacheCount6++;
              roboMemory_ptr->removedIndex6 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache6[roboMemory_ptr->dayCacheCount6][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache6[roboMemory_ptr->dayCacheCount6][1] = 1;
              roboMemory_ptr->dayCacheCount6++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache6[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex6 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache6[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache6[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex6 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval6++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval6 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex6 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount6; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache6[x][1] <= limit)
              {
                roboMemory_ptr->dayCache6[x][0] = 0; //removes record
                roboMemory_ptr->dayCache6[x][1] = 0;
                roboMemory_ptr->removedIndex6 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval6--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
    }
    else
    {
      if (nextPlanetID >= 125000)
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount7; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache7[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache7[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount7; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache7[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache7[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache7[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex7 != 300 || roboMemory_ptr->dayCacheCount7 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex7 != 300)
            {
              roboMemory_ptr->dayCache7[roboMemory_ptr->removedIndex7][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache7[roboMemory_ptr->removedIndex7][1] = 1;
              roboMemory_ptr->dayCacheCount7++;
              roboMemory_ptr->removedIndex7 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache7[roboMemory_ptr->dayCacheCount7][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache7[roboMemory_ptr->dayCacheCount7][1] = 1;
              roboMemory_ptr->dayCacheCount7++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache7[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex7 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache7[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache7[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex7 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval7++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval7 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex7 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount7; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache7[x][1] <= limit)
              {
                roboMemory_ptr->dayCache7[x][0] = 0; //removes record
                roboMemory_ptr->dayCache7[x][1] = 0;
                roboMemory_ptr->removedIndex7 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval7--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
      else
      {
        if(timeOfDayOnNextPlanet == 0) //stores the total nights and days observed
        {

          for(int x = 0; x < roboMemory_ptr->dayCacheCount8; x++) //loops to check if planet exist in cache
          {

            if(roboMemory_ptr->dayCache8[x][0] == nextPlanetID)
            {
              indexOfChange = x; //stores the index of where the value was decremented
              roboMemory_ptr->dayCache8[x][1]--; //decrements buffer used for predicting if a certain planet will be day
              change = 1; //note that a change has been made
              x = 300; //exits for loop

            }

          }

          roboMemory_ptr->dayStreak = 0;
          
        }
        else
        {

          roboMemory_ptr->dayStreak++;

          for(int x = 0; x < roboMemory_ptr->dayCacheCount8; x++) //loops to check if planet exists in cache
          {
            if(roboMemory_ptr->dayCache8[x][0] == nextPlanetID)
            {
              if(roboMemory_ptr->dayCache8[x][1] > -5) //to prevent inconsistent values, consider a planet deleted if it ever reaches -5, only adds to non 'deleted' planets
              {
                roboMemory_ptr->dayCache8[x][1]++; //increments buffer used for predicting if a certain planet will be day
                x = 300; //exits for loop
              }
              change = 1; //note that a change has been made, outside the loop to prevent adding this planet when it is considered for deletion
            }
          }
          if((roboMemory_ptr->removedIndex8 != 300 || roboMemory_ptr->dayCacheCount8 < arraySize) && change == 0) //used for adding new planet entry to cache
          {
            if(roboMemory_ptr->removedIndex8 != 300)
            {
              roboMemory_ptr->dayCache8[roboMemory_ptr->removedIndex8][0] = nextPlanetID; //updates record at index of previously removed record
              roboMemory_ptr->dayCache8[roboMemory_ptr->removedIndex8][1] = 1;
              roboMemory_ptr->dayCacheCount8++;
              roboMemory_ptr->removedIndex8 = 300; //makes it possible to remove another index again
            }
            else
            {
              roboMemory_ptr->dayCache8[roboMemory_ptr->dayCacheCount8][0] = nextPlanetID; //updates record at next free index
              roboMemory_ptr->dayCache8[roboMemory_ptr->dayCacheCount8][1] = 1;
              roboMemory_ptr->dayCacheCount8++;
            }
          }
        }

        if(indexOfChange != 300) //indexOfChange only changes if it is night and the planet is stored in cache, so if !=300 then we know the planet can be considered for deletion
        {
          if(roboMemory_ptr->dayCache8[indexOfChange][1] < limit) //(value of limit) being the limit before a planet is not considered for likely being day
          {
            if(roboMemory_ptr->removedIndex8 == 300) //if the removedIndex is 300 then there are currently no free indexes due to record deletion so it can proceed safely
            {

              roboMemory_ptr->dayCache8[indexOfChange][0] = 0; //removes record
              roboMemory_ptr->dayCache8[indexOfChange][1] = 0;
              roboMemory_ptr->removedIndex8 = indexOfChange; //stores which record was removed

            }
            else
            {
              roboMemory_ptr->missedRemoval8++; //increments the number of missed planet record deletion
            }
          }
        }

        if(roboMemory_ptr->missedRemoval8 > 0) //checks for missed planet record deletion
        {
          if(roboMemory_ptr->removedIndex8 == 300) //ready for deletion as new index can be stored
          {
            for(int x = 0; x < roboMemory_ptr->dayCacheCount8; x++) //loops to check if planet exists in cache
            {
              if(roboMemory_ptr->dayCache8[x][1] <= limit)
              {
                roboMemory_ptr->dayCache8[x][0] = 0; //removes record
                roboMemory_ptr->dayCache8[x][1] = 0;
                roboMemory_ptr->removedIndex8 = x; //keeps track of where next record should be added
                roboMemory_ptr->missedRemoval8--; //decrements missed records to be deleted
                x = 300; //exits for loop
              }
            }
          }
        }
      }
    }

  }

  // It is important not to exceed the computation cost threshold while making
  // predictions and updating RoboMemory. The computation cost of prediction and
  // updating RoboMemory is calculated by the playground automatically and
  // printed together with accuracy at the end of the evaluation (see main.cpp
  // for more details).

  // Simple prediction policy: do nothing
}


//------------------------------------------------------------------------------
// Please don't modify this file below
//
// Check if RoboMemory does not exceed 64KiB
static_assert(
    sizeof(RoboPredictor::RoboMemory) <= 65536,
    "Robo's memory exceeds 65536 bytes (64KiB) in your implementation. "
    "Prediction algorithms using so much "
    "memory are ineligible. Please reduce the size of your RoboMemory struct.");

// Declare constructor/destructor for RoboPredictor
RoboPredictor::RoboPredictor() {
  roboMemory_ptr = new RoboMemory;
}
RoboPredictor::~RoboPredictor() {
  delete roboMemory_ptr;
}
