/*******************************************************************
*
*  DESCRIPTION: class Medio
*
*  DATE: 02/10/2022
*
*******************************************************************/

/** include files **/
#include "Medio.h"         // base header
#include "message.h"       // class InternalMessage 
#include "parsimu.h"       // class Simulator
#include "distri.h"        // class Distribution 
#include "strutil.h"       // str2Value( ... )
#include "realfunc.h"

using namespace std;

/*******************************************************************
* CLASS Medio
*********************************************************************/

/*******************************************************************
* Function Name: Medio
* Description: constructor
********************************************************************/
Medio::Medio(const string &name)
	: Atomic( name ),
	out(addOutputPort("out"))
{         
	P = str2float( ParallelMainSimulator::Instance().getParameter( description(), "P" ) );

	PoderDeConvencimiento = str2Real( ParallelMainSimulator::Instance().getParameter( description(), "Poder_de_convencimiento" ) );         

	periodo= str2Int( ParallelMainSimulator::Instance().getParameter( description(), "Periodo_de_emision" ) );

	randomP = Distribution::create( "normal" ); 
 	randomP -> setVar(0,this -> P); // media = P
	if(P != 0){    
		randomP -> setVar(1, 0.1); // varianaza = 0.1
	} else { // P == 0   
		randomP -> setVar(1, 0.5); // varianza = 0.5
	}
    
}


/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Medio::initFunction()
{

	holdIn(AtomicState::active, VTime(0,periodo,0,0));
	return *this ;
}


/*******************************************************************
* Function Name: externalFuntion
********************************************************************/
/*
Model &Medio::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == this->infoRequest){
		this->pidieronInfo = true;
		holdIn(AtomicState::active, VTime::Zero);
	}      

	return *this;
}
*/
/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Medio::internalFunction(const InternalMessage &msg )
{
	holdIn(AtomicState::active, VTime(periodo,0,0,0));
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Medio::outputFunction(const CollectMessage &msg )
{
    
	Real randomN = this->randomP->get();
    
	if(this-> P == 0.0){  // Medio neutral                  
		if( randomN > 1.0 ) randomN =1;
		if( randomN < -1.0 ) randomN =-1;
		Tuple<Real> out_value{ randomN , this -> PoderDeConvencimiento };    
		sendOutput(msg.time(), out, out_value);
	} else if (this -> P > 0.0){// Medio a favor
		if( randomN>1.0 ) randomN =1;
		if( randomN < 0.0) randomN = 0;
		Tuple<Real> out_value{ randomN , this -> PoderDeConvencimiento };
		sendOutput( msg.time(), out, out_value );
	} else {                    //Medio en contra
		if( randomN>0.0  ) randomN = 0.0;
		if( randomN < -1.0 ) randomN =-1;
		Tuple<Real> out_value{ randomN , this -> PoderDeConvencimiento };
		sendOutput( msg.time(), out, out_value );    
	}    
    
	return *this ;
    
}
Medio::~Medio()
{
	delete randomP;    
}
