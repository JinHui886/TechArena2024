// This file contains a template for the implementation of Robo prediction
// algorithm

#include "PredictionAlgorithm.hpp"
#define arrayLimit 12

struct RoboPredictor::RoboMemory {
  // Place your RoboMemory content here
  // Note that the size of this data structure can't exceed 64KiB!

  int last12days[arrayLimit] = {0};
  int lastTag = -1;
  int tagStreak = 0;
  int dayStreak = 0, nightStreak = 0;
};

bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction,
    int nextPlanetGroupTag) {
  // Robo can consult data structures in its memory while predicting.
  // Example: access Robo's memory with roboMemory_ptr-><your RoboMemory
  // content>

  int dayCount = 0; //stores the amount of times Robo has visited the next planet and it was day (within last (value of arraySize) journeys)
  int totalRecord = 0; //store the amount of times the planet has been visited in the last (value of arraySize) journeys

  if(nextPlanetGroupTag == roboMemory_ptr->lastTag) //checks if next planet group tag matches previous planet
  {
    roboMemory_ptr->tagStreak++; // increments tag streak
  }
  else
  {
    roboMemory_ptr->tagStreak = 0; //resets tag streak
  }

  if(nextPlanetGroupTag == 0) //group tag of 0 refers to day is rarely if ever observed on this planet
  {
    return 0;
  }

  if(roboMemory_ptr->tagStreak >= 4 && nextPlanetGroupTag != roboMemory_ptr->lastTag && roboMemory_ptr->dayStreak != 0)
  { //if 5 or more consecutive nights had the same tag, then predict day on the next planet if the tag is different
    roboMemory_ptr->lastTag = nextPlanetGroupTag; //updates previous planet tag for next planet calculations
    return 1;
  }
    roboMemory_ptr->lastTag = nextPlanetGroupTag; //updates previous planet tag for next planet calculations

  if(nextPlanetGroupTag > 520) //planet is likely to be day on arrival if group tag above 520
  {
    return 1;
  }
  else if(nextPlanetGroupTag < 420) //planet is likely to be night on arrival if group tag is less than 50
  {
    return 0;
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

  for(int x = 0; x < arrayLimit - 1; x++)
  {
    roboMemory_ptr->last12days[arrayLimit - x] = roboMemory_ptr->last12days[arrayLimit - x - 1]; //right shifts all records, indexes 0 - 12 for newest to oldest
  }
  roboMemory_ptr->last12days[0] = timeOfDayOnNextPlanet; // index 0 was not updated to prevent out of bounds error in the for loop above

  if(timeOfDayOnNextPlanet == 0)
  {
    roboMemory_ptr->dayStreak = 0; // night observed so day streak ends
    roboMemory_ptr->nightStreak++; // increments consecutive nights observed
  }
  else
  {
    roboMemory_ptr->nightStreak = 0; // day observed so night streak ends
    roboMemory_ptr->dayStreak++; // increments consecutive days observed
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
