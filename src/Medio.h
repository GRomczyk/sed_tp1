/*******************************************************************
*
*  DESCRIPTION: class Medio
*
*  DATE: 02/20/2022
*
*******************************************************************/


#ifndef __MEDIO_H__
#define __MEDIO_H__

#include <string>

/** include files **/
#include "atomic.h"     	// class Atomic
#include "atomicstate.h"	// class AtomicState
#include "except.h"     	// class InvalidMessageException
#include "real.h"
#include "tuple_value.h"

#include "VTime.h"

#define ATOMIC_MODEL_NAME_MEDIO "Medio"


/** forward declarations **/
class Distribution ;

/** declarations **/
class Medio : public Atomic {

	public :

		Medio( const std::string &name = ATOMIC_MODEL_NAME_MEDIO); // Default constructor

		~Medio(); 
    
	protected:
		Model &initFunction() ;

		//Model &externalFunction( const ExternalMessage & );

		Model &internalFunction( const InternalMessage & );

		Model &outputFunction( const CollectMessage & );

    

	private:
		// [(!) TODO: declare ports, distributions and other private varibles here]
		/***********      Example declarations   **********************************
		* Port &out ;   	// this is an output port named 'out'
		* Distribution *distIntervaloDeEmision ;
		* Distribution &distribution()	{ return *dist; }
		**************************************************************************/

		float P;
		Real PoderDeConvencimiento;
		Port &out ;

		int periodo;
            
		Distribution *randomP;
};	// class Medio

#endif   //__MEDIO_H 