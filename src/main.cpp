#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
using namespace std;

#include "DynamicTreeNode.h"
#include "Pulse.h"
#include "Event.h"

int main(int argc, char *argv[]) {

	typedef DynamicTree<DataObject> DataStore;


	// tree
	DataStore* datastore = new DataStore();
	std::cout << "root datastore: " << datastore->path() << std::endl;
	std::cout << "/  " << datastore->find("/") << " datastore " << datastore << std::endl;
	std::cout << "new branch " << datastore->branch("pulse") << std::endl;
	std::cout << datastore->find("/pulse")->path() << std::endl;
	datastore->find("/pulse")->branch("event");
	std::cout << datastore->find("pulse/event")->path() << std::endl;

	// leaf pulse
	std::cout << "====================== Pulse" << std::endl;
	datastore->find("/pulse")->registObj(new Pulse());
	DataObject* data = datastore->find("/pulse")->getObj();
	std::cout << "obj: " << data  << " type "<<  typeid(data).name() << std::endl;
	datastore->getObj1<Pulse*>("pulse");
	//Pulse* data2= datastore->getObj1<Pulse*>("pulse");
	//std::cout << "obj: " << data2  << " type "<<  typeid(data2).name() << std::endl;
	dynamic_cast<Pulse*>(data);

	// leaf event
	std::cout << "====================== Event" << std::endl;
	Event* evt = new Event();
	std::cout << "new event: " << evt << std::endl;
	datastore->find("/pulse/event")->registObj(evt);
	DataObject* event = datastore->find("/pulse/event")->getObj();
	std::cout << "get event: "  << event << std::endl;
	dynamic_cast<Event*>(event);


	return 1;
}
