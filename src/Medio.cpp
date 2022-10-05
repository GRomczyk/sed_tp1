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
/*
		if( ParallelMainSimulator::Instance().existsParameter( description(), "P" ) )
			P= str2Int( ParallelMainSimulator::Instance().getParameter( description(), "P" ) );
		else{
			P = 0;
		}    */    
                
        
	P= str2Int( ParallelMainSimulator::Instance().getParameter( description(), "P" ) ); 

	periodo= str2Int( ParallelMainSimulator::Instance().getParameter( description(), "Periodo_de_emision" ) );
	//this -> frequency_time(0.0,periodo,0);
        
	if(P == 0){
		randomP = Distribution::create( "normal" );    
		randomP -> setVar(-1,1);
	}
        
}


/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Medio::initFunction()
{

	holdIn(AtomicState::active, VTime(0,0,periodo,0));
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
	holdIn(AtomicState::active, VTime(0,0,periodo,0));
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Medio::outputFunction(const CollectMessage &msg )
{
    
	
	if(this-> P == 2){
		Real randomN = this->randomP->get();
		Real ent = round(randomN);                     // entero mas cercano
		if( randomN>1 || ent == 1 ) randomN =1;
		if( randomN < -1 || ent == -1 ) randomN =-1;
		sendOutput(msg.time(), out, randomN);
	} else {
		sendOutput( msg.time(), out, this->P );
	}     
	return *this ;
    
}
Medio::~Medio()
{
	delete randomP;    
}
