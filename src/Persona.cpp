/** include files **/
#include <random>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "message.h" // class ExternalMessage, InternalMessage
#include "parsimu.h" // ParallelMainSimulator::Instance().getParameter( ... )
#include "real.h"
#include "tuple_value.h"
#include "distri.h"        // class Distribution
#include "strutil.h"
#include "realfunc.h"

#include "Persona.h" 

using namespace std;

#define VERBOSE false

/* #define PRINT_TIMES(f) {\
 	cout << f << "@" << msg.time() <<\
 		" - timeleft: " << timeleft <<\
 		" - elapsed: " << elapsed <<\
 		" - sigma: " << sigma << endl;\
}*/

/** public functions **/

/*******************************************************************
* Function Name: [#MODEL_NAME#]
* Description: constructor
********************************************************************/
Persona::Persona( const string &name ) : 
	Atomic( name ),
	inPort1(addInputPort("inPort1")),
	inPort2(addInputPort("inPort2")),
	inPort3(addInputPort("inPort3")),
	inPort4(addInputPort("inPort4")),
	inPort5(addInputPort("inPort5")),
	inMedios(addInputPort("inMedios")),
	outPort1(addOutputPort("outPort1")),
	outPort2(addOutputPort("outPort2")),
	outPort3(addOutputPort("outPort3")),
	outPort4(addOutputPort("outPort4")),
	outPort5(addOutputPort("outPort5")),
	infoRequest(addInputPort("infoRequest")),
	outInfo(addOutputPort("outInfo")),

	//estoyRespondiendo(false),
	//esperandoRespuesta(false),

	generator(random_device()()),
	distMiroNoticia(0.0,1.0)

	// TODO: add ports here if needed (Remember to add them to the .h file also). Each in a new line.

{
	// TODO: add initialization code here. (reading parameters, initializing private vars, etc)
	// Code templates for reading parameters:
	
	p_inicial = str2Real( ParallelMainSimulator::Instance().getParameter( description(), "p" ));
	
	influenciabilidad = str2Real( ParallelMainSimulator::Instance().getParameter( description(), "influenciabilidad" ));
	poderConvencimiento = str2Real( ParallelMainSimulator::Instance().getParameter( description(), "poder_convencimiento" ));
	tiempoSillon = str2Real( ParallelMainSimulator::Instance().getParameter( description(), "tiempo_sillon" ));

	grado = str2Int( ParallelMainSimulator::Instance().getParameter( description(), "grado" ));

	string parameter( ParallelMainSimulator::Instance().getParameter( description(), "periodo_medio") ) ;

	distAQuienHablo = std::uniform_int_distribution<int>(1,grado);

	periodoMedio = strtof( ParallelMainSimulator::Instance().getParameter( description(), "periodo_medio" ).c_str(), nullptr );
	
	distCuandoHablo = Distribution::create("exponential");
	distCuandoHablo->setVar(0, str2Value( parameter ) );

}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Persona::initFunction()
{

 	// TODO: add init code here. (setting first state, etc)
 	this->p = this->p_inicial;
	this->estoyRespondiendo = false;
	this->esperandoRespuesta = false;
	this->pidieronInfo = false;
 	// set next transition
	if(this->grado > 0){
 		holdIn( AtomicState::active, VTime( static_cast< float >( this->distCuandoHablo->get())));
	} else {
		passivate();
	}
	return *this ;

}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &Persona::externalFunction( const ExternalMessage &msg )
{

// #if VERBOSE
// 	PRINT_TIMES("dext");
// #endif
	if (msg.port() == this->infoRequest){
		this->pidieronInfo = true;
		holdIn(AtomicState::active, VTime::Zero);

	} else {
		Tuple<Real> values = Tuple<Real>::from_value(msg.value());
		Real pMensaje = values[0];
		Real pcMensaje = values[1];
		//si no estoy respondiendo, proceso el mensaje
		if(!this->estoyRespondiendo){
			if(this->esperandoRespuesta){
				//si estaba esperando respuesta, y el mensaje vino por el puerto correcto, lo proceso
				if(msg.port() == *(puertoEntrada(this->puertoDeConexion))){
					this->p = nuevoP(pMensaje, pcMensaje);
					this->esperandoRespuesta = false;
					holdIn(AtomicState::active, VTime( static_cast< float >( this->distCuandoHablo->get())));
				}
			} else if(msg.port() == this->inMedios){
				//si el mensaje vino por el puerto de medios, me fijo si lo veo o no
				bool veoNoticia = Real(this->distMiroNoticia(generator)) < probabilidadDeMirarNoticia(pMensaje);
				if(veoNoticia){
					this->p = nuevoP(pMensaje, pcMensaje);
				}
				if(this->grado > 0){
					holdIn( AtomicState::active, VTime( static_cast< float >( this->distCuandoHablo->get())));
				} else {
					passivate();
				}
			} else {
				// si no estaba esperando respuesta y el mensaje es de una persona, proceso y respondo
				this->pGuardado = this->p;
				
				this->puertoDeConexion = puertoConexion(&(msg.port()));
				this->p = nuevoP(pMensaje, pcMensaje);
				this->estoyRespondiendo = true;
				holdIn(AtomicState::active, VTime::Zero);
			} 
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* The new state and TA should be set.
********************************************************************/
Model &Persona::internalFunction( const InternalMessage &msg )
{

// #if VERBOSE
// 	PRINT_TIMES("dint");
// #endif
	if(this->pidieronInfo){
		this->pidieronInfo = false;
		//agregado mantenimiento
		this->esperandoRespuesta = false;
		this->estoyRespondiendo = false;
		
		if(this->grado > 0){
			holdIn( AtomicState::active, VTime( static_cast< float >( this->distCuandoHablo->get())));
		} else {
			passivate();
		}

	} else if(this->estoyRespondiendo){
		//si la transicion vino pq estaba respondiendo, el oputput ya salio, por lo que espero tiempo 
		//exponencial para volver a hablar
		this->estoyRespondiendo = false;

		//agregado - mantenimiento
		this->esperandoRespuesta = false;
		this->pidieronInfo = false;
		holdIn( AtomicState::active, VTime( static_cast< float >( this->distCuandoHablo->get())));
	} else if(!this->esperandoRespuesta){
		// en este caso, vengo de iniciar una conversacion, por lo que actualizo la variable 
		//esperando respuesta y espero un tiempo por la misma
		this->esperandoRespuesta = true;

		//agregado mantenimeinto
		this->estoyRespondiendo = false;
		this->pidieronInfo = false;
		holdIn(AtomicState::active, VTime( 0,0,0,1 ));
		
	} else {
		// en este caso, esperando respuesta = true, pero paso el tiempo de espera de la misma 
		// (puede no llegar porque la otra persona estaba ocupada, en cuyo caso desestima mi msj)
		this->esperandoRespuesta = false;

		//agregado mantenimeinto
		this->estoyRespondiendo = false;
		this->pidieronInfo = false;

		holdIn(AtomicState::active, VTime( static_cast< float >( this->distCuandoHablo->get())));
	}

	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
* Output values can be send through output ports
********************************************************************/
Model &Persona::outputFunction( const CollectMessage &msg )
{
	
	const Port *puerto;
	if(this->pidieronInfo){
		sendOutput(msg.time(), this->outInfo, this->p);
	} else if(this->estoyRespondiendo){
		puerto = puertoSalida(this->puertoDeConexion);
		
		Tuple<Real> out_value{this->pGuardado, this->poderConvencimiento};
		sendOutput(msg.time(), *puerto, out_value);
	} else if(!this->esperandoRespuesta){
		Tuple<Real> out_value{this->p, this->poderConvencimiento};
		this->puertoDeConexion = this->distAQuienHablo(this->generator);
		puerto = puertoSalida(this->puertoDeConexion);

		sendOutput(msg.time(), *puerto, out_value);

	}
	
	return *this;

}

Real Persona::triCube(Real dist){
	return power(Real(1.0) - power((dist/2),Real(3.0)),Real(3.0));
}

Real Persona::nuevoP(Real pAjeno, Real poderConvencimientoAjeno){
	return this->p + this->influenciabilidad * poderConvencimientoAjeno * triCube(abs(this->p - pAjeno)) * (pAjeno - this->p);
}
Real Persona::probabilidadDeMirarNoticia(Real pNoticia){
	return this->tiempoSillon * triCube(abs(this->p - pNoticia));
}

Persona::~Persona()
{
	delete distCuandoHablo;
}


int Persona::puertoConexion(const Port* puertoEntrada){
	int puerto;
	if(puertoEntrada == &(this->inPort1)){
		puerto = 1;
	} else if(puertoEntrada == &(this->inPort2)){
		puerto = 2;
	} else if(puertoEntrada == &(this->inPort3)){
		puerto = 3;
	} else if(puertoEntrada == &(this->inPort4)){
		puerto = 4;
	} else if(puertoEntrada == &(this->inPort5)){
		puerto = 5;
	} else {
		cout << "Puerto de entrada no correspondia a personas \n";
		puerto = 1;
	}
	return puerto;
}

Port* Persona::puertoSalida(int puerto){
	Port *puertoSalida;
	switch(puerto){
		case 1:
			puertoSalida = &(this->outPort1);
			break;
		case 2:
			puertoSalida = &(this->outPort2);
			break;
		case 3:
			puertoSalida = &(this->outPort3);
			break;
		case 4:
			puertoSalida = &(this->outPort4);
			break;
		case 5:
			puertoSalida = &(this->outPort5);
			break;
		default:
			cout<<"Error: puerto de conexion salida incorrecto\n";
			cout<<"Grado " <<grado<<"\n";
			puertoSalida = &(this->outPort1);
			break;
		
	}
	return puertoSalida;
}

const Port* Persona::puertoEntrada(int puerto){
	const Port *puertoEntrada;
	switch(puerto){
		case 1:
			puertoEntrada = &(this->inPort1);
			break;
		case 2:
			puertoEntrada = &(this->inPort2);
			break;
		case 3:
			puertoEntrada = &(this->inPort3);
			break;
		case 4:
			puertoEntrada = &(this->inPort4);
			break;
		case 5:
			puertoEntrada = &(this->inPort5);
			break;
		default:
			cout<<"Error: puerto de conexion entrada incorrecto\n";
			cout<<"Grado " <<grado<<"\n"; 
			puertoEntrada = &(this->inPort1);
			break;
		
	}
	
	return puertoEntrada;
}

