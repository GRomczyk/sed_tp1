#ifndef __PERSONA_H // cambiar nombre
#define __PERSONA_H // cambiar nombre

/** include files **/
#include <random>
#include "atomic.h"  // class Atomic
#include "VTime.h"

#define ATOMIC_MODEL_NAME_PERSONA "Persona" // cambiar nombre

/** forward declarations **/
//TODO: add distribution class declaration here if needed
class Distribution ;


/** declarations **/
class Persona: public Atomic {
	public:
		Persona( const string &name = ATOMIC_MODEL_NAME_PERSONA ); // Default constructor
		~Persona(); // Destructor
		virtual string className() const {return ATOMIC_MODEL_NAME_PERSONA;}
	
	protected:
		Model &initFunction();	
		Model &externalFunction( const ExternalMessage & );
		Model &internalFunction( const InternalMessage & );
		Model &outputFunction( const CollectMessage & );
	
	private:
		// [(!) TODO: declare ports, distributions and other private varibles here]
		/***********      Example declarations   **********************************/
		// const Port &in;	// this is an input port named 'in'
		// Port &out ;   	// this is an output port named 'out'
		// Distribution *dist ;
		// Distribution &distribution()	{ return *dist; }
		/**************************************************************************/
	
		
		const Port &inPort1;
		const Port &inPort2;
		const Port &inPort3;
		const Port &inPort4;
		const Port &inPort5;

		const Port &inMedios;

		Port &outPort1;
		Port &outPort2;
		Port &outPort3;
		Port &outPort4;
		Port &outPort5;

		Port &infoRequest;
		Port &outInfo;

		int grado;
		
		int puertoDeConexion;
		//Port* puertoEntradaEsperado;
		//Port* puertoSalidaRespuesta;

		bool esperandoRespuesta;
		bool estoyRespondiendo;
		bool pidieronInfo;

		Real p_inicial;

		Real p;
		Real influenciabilidad;
		Real poderConvencimiento;
		Real tiempoSillon;

		Real pGuardado;

		float periodoMedio; // cada cuanto hablo en promedio en horas

		Distribution *distCuandoHablo ;

		std::default_random_engine generator;
		
		std::uniform_real_distribution<float> distMiroNoticia;
		std::uniform_int_distribution<int> distAQuienHablo;

    	
		Real nuevoP(Real pAjeno, Real poderConvencimientoAjeno);
		Real probabilidadDeMirarNoticia(Real pNoticia);
		Real triCube(Real dist);

		Port* puertoSalida(int puerto);
		const Port* puertoEntrada(int puerto);
		int puertoConexion(const Port *puertoEntrada);
		

	

};	// class ModelTemplate


#endif   //__MODELTEMPLATE_H 
