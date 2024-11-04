// This file contains a template for the implementation of Robo prediction
// algorithm

#include "PredictionAlgorithm.hpp"

struct RoboPredictor::RoboMemory {
  // Place your RoboMemory content here
  // Note that the size of this data structure can't exceed 64KiB!

  bool timeOfDay = 0; //time of day of previous planet
  unsigned int totalDay = 0, totalNight = 0, streakDay = 0, streakNight = 0; //total day and total night observed
  unsigned int highestStreakNight = 0; //used to track the highest streak of nights observed to try to slightly improve accuracy
  unsigned int switchDay = 0; //used to track the amount of switches
  unsigned int predDay = 0; //used to store the prediction for how many days before a switch would occur

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

  if(roboMemory_ptr->timeOfDay == 1)
  {

    roboMemory_ptr->predDay = (roboMemory_ptr->totalDay / roboMemory_ptr->switchDay) / 1; //calculates the average for how many consecutive days will appear
    
    if(roboMemory_ptr->streakDay < roboMemory_ptr->predDay || roboMemory_ptr->streakNight == roboMemory_ptr->highestStreakNight)
    { //if the current consecutive amount of days observed is less than measured average or if observed consecutive nights has reached record high then predict day
      return 1; //predicts day
    }

    return 0; //predicts night

  }
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

  if(timeOfDayOnNextPlanet == 0) //if it is night on the observed planet
  {

    if(roboMemory_ptr->timeOfDay == 1) //if it was day on the last planet
    {

      roboMemory_ptr->streakDay = 0; //it is no longer day on the observed planet, so streak resets
      roboMemory_ptr->switchDay += 1; //the amount of times it has 'switched' from day to night is incremented 

    }

    roboMemory_ptr->totalNight += 1; //increments the total amount of nights observed
    roboMemory_ptr->streakNight += 1; //increments the total amount of consecutive nights observed

    roboMemory_ptr->timeOfDay = 0; //updates the time of day observed to be used for calculations on next planet

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
    
    roboMemory_ptr->timeOfDay = 1; //updates the time of day observed to be used for calculations on next planet

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
