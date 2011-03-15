/*
 * vs.h
 *
 *  Created on: 2 févr. 2011
 *      Author: garfield
 */

#ifndef VS_H_
#define VS_H_

#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>


namespace Robot {

class vs {
protected:
	boost::interprocess::managed_shared_memory segment_;
public:
	vs() : segment_(boost::interprocess::open_or_create, "VariableService", 65535) {}
	virtual ~vs() {}
	template <typename T> T* createVariable(string varName)
	{
		segment.construct<T>(varName);
	}
	template <typename T> T* importVariable(string varName)
	{

	}
	virtual void deleteVariable(variable *varHandle);
};

}

#endif /* VS_H_ */
