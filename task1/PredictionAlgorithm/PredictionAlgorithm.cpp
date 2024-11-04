// This file contains a template for the implementation of Robo prediction
// algorithm

#include "PredictionAlgorithm.hpp"
#include <cstdio> //using printf for testing purposes

struct RoboPredictor::RoboMemory {
  // Place your RoboMemory content here
  // Note that the size of this data structure can't exceed 64KiB!

  bool timeOfDay = 0, pPID; //time of day of previous planet and previous planet id
  unsigned int totalDay = 0, totalNight = 0, streakDay = 0, streakNight = 0; //total day and total night observed
  unsigned int highestStreakNight = 0; //used to track the highest streak of nights observed to try to slightly improve accuracy
  unsigned int switchDay = 0; //used to track the amount of switches
  unsigned int predDay = 0; //used to store the prediction for how many days before a switch would occur
  unsigned int planetIDPred[100][10][3] = {{{0}}}; //planet1 planet2 and whether the day switches when robo arrives 1 switches 0 does not switch
  unsigned int lastAdded = 0, found = 0, found2 = 0; //track what index the last planet was added on and see if planet is found
};

bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction) {
  // Robo can consult data structures in its memory while predicting.
  // Example: access Robo's memory with roboMemory_ptr-><your RoboMemory
  // content>

  if(roboMemory_ptr->totalNight < 9) //allows room for memory to be trained at initial stages albeit with minmal effect
  {
    return 0; //predicts night
  }

  unsigned int x = 0;
  while(x < roboMemory_ptr->lastAdded)
  {
    if(roboMemory_ptr->planetIDPred[x][0][0] == nextPlanetID || roboMemory_ptr->planetIDPred[x][0][0] == roboMemory_ptr->pPID)
    {      
      if(roboMemory_ptr->planetIDPred[x][0][0] == nextPlanetID)
      {
        for(int y = 0; y < 10; y++)
        {
          if(roboMemory_ptr->planetIDPred[x][y][1] == roboMemory_ptr->pPID)
          {
            if(roboMemory_ptr->planetIDPred[x][y][2] == 0)
            {
              return roboMemory_ptr->timeOfDay;
            }
            else
            {
              printf("2 ");
              return 1 - roboMemory_ptr->timeOfDay; //returns day if night and night if day on current planet
            }
          }
        }
      }
      else if(roboMemory_ptr->planetIDPred[x][0][0] == roboMemory_ptr->pPID)
      {
        for(int y = 0; y < 10; y++)
        {
          if(roboMemory_ptr->planetIDPred[x][y][1] == nextPlanetID)
          {
            if(roboMemory_ptr->planetIDPred[x][y][2] == 0)
            {
              return roboMemory_ptr->timeOfDay;
            }
            else
            {
              printf("2 ");
              return 1 - roboMemory_ptr->timeOfDay; //returns day if night and night if day on current planet
            }
          }
        }
      }
    }
    x++;
  }

  return 0;
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

  roboMemory_ptr->found = 0; //initialises found 
  roboMemory_ptr->found2 = 0; //initialises found2
  unsigned int count = 0; //to cycle through the unique planets discovered
  unsigned int count2 = 0; //for array indexing
  unsigned int firstPlanet = 0, secondPlanet = 0;
  unsigned int priPlanet = 0;

  if(roboMemory_ptr->pPID != 0)
  {
    if(roboMemory_ptr->pPID > nextPlanetID)
    {
      firstPlanet = roboMemory_ptr->pPID;
      secondPlanet = nextPlanetID;
    }
    else
    {
      firstPlanet = nextPlanetID;
      secondPlanet = roboMemory_ptr->pPID;
    }
  }

  while(roboMemory_ptr->lastAdded < 100 && count < roboMemory_ptr->lastAdded && roboMemory_ptr->found == 0)
  {
    if(roboMemory_ptr->planetIDPred[count][0][0] == firstPlanet || roboMemory_ptr->planetIDPred[count][0][0] == secondPlanet)
    {
      roboMemory_ptr->found = 1;
      if(roboMemory_ptr->planetIDPred[count][0][0] == firstPlanet)
      {
        priPlanet = firstPlanet;
        for(int x = 0; x < 10; x++)
        {
          if(roboMemory_ptr->planetIDPred[count][x][1] == secondPlanet)
          {
            roboMemory_ptr->found2 = 1;
          }
          if(roboMemory_ptr->planetIDPred[count][x][1] != 0)
          {
            count2 = x;
          }
        }
      }
      else if(roboMemory_ptr->planetIDPred[count][0][0] == secondPlanet)
      {
        priPlanet = secondPlanet;
        for(int x = 0; x < 10; x++)
        {
          if(roboMemory_ptr->planetIDPred[count][x][1] == firstPlanet)
          {
            roboMemory_ptr->found2 = 1;
          }
          if(roboMemory_ptr->planetIDPred[count][x][1] != 0)
          {
            count2 = x;
          }
        }
      }
    }
    count += 1;
  }

  if(roboMemory_ptr->lastAdded < 100 && roboMemory_ptr->found == 0 && secondPlanet != 0)
  {
    roboMemory_ptr->planetIDPred[roboMemory_ptr->lastAdded][0][0] = firstPlanet;
    roboMemory_ptr->planetIDPred[roboMemory_ptr->lastAdded][0][1] = secondPlanet;
    if(timeOfDayOnNextPlanet == roboMemory_ptr->timeOfDay) //checks if the time stays the same after traveling between these planets
    {
      roboMemory_ptr->planetIDPred[roboMemory_ptr->lastAdded][0][2] = 0; //time stays the same after arrival
    }
    else
    {
      roboMemory_ptr->planetIDPred[roboMemory_ptr->lastAdded][0][2] = 1; //time dose not stay the same after arrival
    }
    roboMemory_ptr->lastAdded += 1;
      //printf("Size: %d\n", sizeof(RoboPredictor::RoboMemory));
  }

  if(count2 < 10 && roboMemory_ptr->found == 1 && roboMemory_ptr->found2 == 0)
  {
    if(priPlanet == firstPlanet)
    {
      roboMemory_ptr->planetIDPred[count][count2][0] = firstPlanet;
      roboMemory_ptr->planetIDPred[count][count2][1] = secondPlanet;
    }
    else
    {
      roboMemory_ptr->planetIDPred[count][count2][0] = secondPlanet;
      roboMemory_ptr->planetIDPred[count][count2][1] = firstPlanet;
    }
    if(timeOfDayOnNextPlanet == roboMemory_ptr->timeOfDay) //checks if the time stays the same after traveling between these planets
      {
        roboMemory_ptr->planetIDPred[count][count2][2] = 0; //time stays the same after arrival
      }
    else
      {
        roboMemory_ptr->planetIDPred[count][count2][2] = 1; //time dose not stay the same after arrival
      }
  }

  if(timeOfDayOnNextPlanet == 0) //if it is night on the observed planet
  {

    if(roboMemory_ptr->timeOfDay == 1) //if it was day on the last planet
    {

      roboMemory_ptr->streakDay = 0; //it is no longer day on the observed planet, so streak resets
      roboMemory_ptr->switchDay += 1; //the amount of times it has 'switched' from day to night is incremented 

    }

    roboMemory_ptr->totalNight += 1; //increments the total amount of nights observed
    roboMemory_ptr->streakNight += 1; //increments the total amount of consecutive nights observed
  }
  else //if it is day on the observed planet
  {

    if(roboMemory_ptr->timeOfDay == 0) //if it was night on the last planet
    {

      if(roboMemory_ptr->streakNight > roboMemory_ptr->highestStreakNight) //checks if the consecutive nights observed is higher than previous records
      {
        roboMemory_ptr->highestStreakNight = roboMemory_ptr->streakNight; //updates the highest streak of consecutive nights observed
      }
      roboMemory_ptr->streakNight = 0; //it is no longer night on the observed planet, so streak resets

    }

    roboMemory_ptr->totalDay += 1; //increments the total amount of days observed
    roboMemory_ptr->streakDay += 1; //increments the total amount of consecutive days observed
  }
  

  roboMemory_ptr->timeOfDay = timeOfDayOnNextPlanet; //updates the time of day observed to be used for calculations on next planet
  roboMemory_ptr->pPID = nextPlanetID; //updates previous planet id to be used for calculations on next planet

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
