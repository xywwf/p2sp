/*
 * workers.h
 *
 *  Created on: 2015年12月23日
 *      Author: wrb00_000
 */

#ifndef CUBE_SERVICE_TCP_CLIENT_IOCP_WORKERS_H_
#define CUBE_SERVICE_TCP_CLIENT_IOCP_WORKERS_H_
#include <list>
#include <vector>

#include "cube/service/stdns.h"
#include "cube/service/tcp/client/handler.h"
#include "cube/service/tcp/client/iocp/worker.h"

BEGIN_SERVICE_TCP_NS
class workers{
public:
	workers();
	virtual ~workers();

	/**
	 * start workers by specified worker number
	 *@param num: worker number in workers
	 *@return:
	 *	0-success, otherwise for failed.
	 */
	int start(int num);

	/**
	 * dispatch a handler to workers
	 */
	void dispatch(handler *hdr);

	/**
	 * stop workers
	 */
	int stop();

private:
	//worker number
	int _wnum;
	//next dispatch worker position
	int _pos;
	//worker list
	std::vector<worker*> _workers;
};

workers::workers():_wnum(0), _pos(0){

}
workers::~workers(){

}

int workers::start(int num){
	if(num < 1){
		return -1;
	}
	_wnum = num;

	for(int i=0; i<_wnum; i++){
		worker* pworker = new worker();
		if(pworker->start() != 0){
			return -1;
		}
		_workers.push_back(pworker);
	}
	return 0;
}

void workers::dispatch(handler *hdr){
	_workers[_pos++%_wnum]->dispatch(hdr);
}

int workers::stop(){
	for(int i=0; i<_wnum; i++){
		_workers[i]->stop();
		delete _workers[i];
	}
	_workers.clear();
	return 0;
}
END_SERVICE_TCP_NS
#endif /* CUBE_SERVICE_TCP_CLIENT_IOCP_WORKERS_H_ */
