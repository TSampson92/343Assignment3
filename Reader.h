#ifndef READER_H
#define READER_H

#include "Galaxy.h"
#include <map>
#include <fstream>
#include "TravelTimes.h"

class Reader {
public:
  Reader(Travel_Times* constraints);
  //Because the reader class is allocating pointers, will only clear all the structures, will not deallocate.
  //Deallocation will be handled by the Galaxy object. re
  ~Reader();
  Galaxy* load();
  void dumpPreLoadStructures();

private:
  static const int MIN_LAYOVER_TIME;
  //Read next leg of ship's route
  bool get_record();
  void dumpCurrentLeg();
  void dumpPreviousLeg();
  void dumpPlanets();
  void dumpEdges();
  void dumpShips();
  //Verify that that current leg is a valid continuation of the
  //previous leg or the beginning of the route for another ship.
  bool validate();
  bool validateTravelTime();
  bool validateEdges();
  bool validateDeparturePlanet();

  //Data structure holding the travel times between planets.
  Travel_Times* fConstraints;

  //Input string representing a single leg.
  std::string fCurrent_input_line;

  //Previous leg information for validation.
  std::string fPreviousShipName;
  Ship_ID fPrevious_ship_id;
  Planet* fPrevious_destination_planet;
  int previous_arrival_time;

  //Read in line
  std::string fCurrentLine;

  //Current leg information
  std::string fShipName;
  Ship_ID fShip_ID;
  Planet* fDeparture_Planet;
  Time fDeparture_Time;
  Planet* fDestination_Planet;
  Time fArrival_Time;

  //Planet name to planet object
  std::map<std::string, Planet*> fPlanets;

  //Planet-name pair to edge object
  std::map<const Planet*, std::map<const Planet*, Edge*> > fEdges;

  //Ship name to id.
  std::map<std::string, Ship_ID> fShips;

  //Route structure under construction.
  Galaxy* fGalaxy;

  
};

#endif