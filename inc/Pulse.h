#ifndef DIFF_PULSE_H
#define DIFF_PULSE_H

#include <stdlib.h>
#include <vector>

#include "DataObject.h"
using namespace std;

class Pulse:public DataObject{
	public:
		const uint64_t getPulseID() const {return m_pulseid; }
		void setPulseID(uint64_t pulseid) {m_pulseid = pulseid; }

		const uint32_t getTimeSec() const {return m_timesec; }
		void setTimeSec(uint32_t timesec) {m_timesec = timesec; }

		const uint32_t getTimeSub() const {return m_timesub; }
		void setTimeSub(uint32_t timesub) {m_timesub = timesub; }

	private:
		uint64_t m_pulseid;	
		uint32_t m_timesec;
		uint32_t m_timesub;

};

#endif
