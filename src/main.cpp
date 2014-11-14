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
	Pulse* pulse = dynamic_cast<Pulse*>(data);
	std::cout << "obj: " << data  << " type "<<  typeid(data).name() << std::endl;
	std::cout << "pls: " << pulse << " type "<<  typeid(pulse).name() << std::endl;

	// leaf event
	std::cout << "====================== Event" << std::endl;
	Event* evt = new Event();
	std::cout << "new event: " << evt << std::endl;
	datastore->registObj("/pulse/event", evt);
	Event* event = datastore->getObj<Event*>("/pulse/event");
	std::cout << "get event: "  << event << " type "<<  typeid(event).name() << std::endl;

	DataStore* pulsedir = datastore->find("/pulse");
	pulsedir->getObj<Event*>("event");
	std::cout << "form /pulse direction get event: "  << event << " type "<<  typeid(event).name() << std::endl;

	return 1;
}
