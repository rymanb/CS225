/* File header
 * ===========
 * file:       print_queue.cpp
 * author:     Ryman Barnett
 * email:      ryman.b@digipen.edu
 * course:     CS225
 * section:    A
 * assignment: 5
 * date:       11/25/2022
 *
 * file content:
 * this is a source file for print_queue to handle the printers queue, requires print_queue.h
 */

#include "print_queue.h"

////////////////////////////////////////////////////////////
/* PrintQueue implementation */
////////////////////////////////////////////////////////////

/* constructor 
 * pointer to a simulator that's running it
 */ 
PrintQueue::PrintQueue(Simulator* _psim) : 
	psim(_psim), num_available_printers(0), printer_status(), jobs_in_queue() 
{}


/* to use a printer we need to register it with the print queue first */
void PrintQueue::RegisterPrinter(int ID, double speed) {
	/* pair of (ID and a pair (available, speed) ) */
//	printer_status.insert( 
//			std::make_pair<int,std::pair<bool,double> >
//			         (ID,std::make_pair<bool,double>(true,speed) ) 
//			);
//next line is equivalent to the above insert
	printer_status[ ID ] = std::make_pair<bool,double&>(true,speed);
	//printer is available by default
	++num_available_printers;
}

/* implements 2) from PrintQueue */
void PrintQueue::JobFinished( double current_time, int printerID, PrintJob job)
{
	ID2pair::iterator it = printer_status.find( printerID );

	if ( it == printer_status.end() ) throw "invalid printerID";

	std::cout << "Printer " << printerID << " finished job " 
		<< job.jobID << " at time " << current_time << std::endl;


	if ( !jobs_in_queue.empty() ) { //immediately assign another job
		//...
		
		//get the next job from the queue
		PrintJob new_job = jobs_in_queue.top().first;
		//remove it from the queue
		jobs_in_queue.pop();
		//assign it to the printer
		std::cout << "Printer " << printerID << " assigned new job " 
			<< new_job.jobID << " at time " << current_time << std::endl;
		//schedule the job to be finished
		psim->AddEvent(
			new EventJobFinished(
				current_time + new_job.size / it->second.second,
				printerID, new_job, this)
		);

	} else { // no jobs in the queue - printer rests
		++num_available_printers;
		it->second.first = true;
	}
}

/* implements 3) from PrintQueue */
void PrintQueue::NewJobArrived( double current_time, PrintJob job )
{
	std::cout << "New job " << job.jobID 
		<< " at time " << current_time << std::endl;

	if ( num_available_printers>0 ) { //self-explanatory
		//find an available printer
		ID2pair::iterator it = printer_status.begin();
		while ( it != printer_status.end() && it->second.first==false ) {++it;}

		//if condition holds, we have a problem with data: 
		//num_available_printers>0 but no printer seem to be available
		if (it==printer_status.end()) throw "corrupted data";

		//...
		//assign the job to the printer
		std::cout << "Job assigned to printer " << it->first
			<< " at time " << current_time << std::endl;
		
		//printer is no longer available
		it->second.first = false;
		--num_available_printers;

		//schedule the event of finishing the job
		psim->AddEvent(new EventJobFinished(current_time + job.size / it->second.second,
			it->first, job, this));
		
		
	} else { 
		std::cout << "No available printers - put in print queue\n";
		//...
		//put the job in the queue
		jobs_in_queue.push(std::make_pair(job, current_time));
		
	
	}
}

////////////////////////////////////////////////////////////
/* EventJobFinished implementation */
////////////////////////////////////////////////////////////

/* constructor */
EventJobFinished::EventJobFinished(double _time, int _printerID, PrintJob _job, PrintQueue* _pqueue) 
	: printerID(_printerID), job(_job), p_print_queue(_pqueue)
{
	SetWhen(_time); //set the time of the event
}

/* execute the job finished function */
void EventJobFinished::Execute()
{
	p_print_queue->JobFinished(When(), printerID, job);
}


////////////////////////////////////////////////////////////
/* EventNewJobArrived implementation */
////////////////////////////////////////////////////////////

/* constructor */
EventNewJobArrived::EventNewJobArrived(double when, const PrintJob& _job, PrintQueue* _p_print_queue, void(PrintQueue::* _p_method)(double, PrintJob))
	: job(_job), p_print_queue(_p_print_queue), p_method(_p_method)
{
	SetWhen(when); //set the time of the event
}

/* execute the stored job function */
void EventNewJobArrived::Execute()
{
	(p_print_queue->*p_method)(When(), job);
}

