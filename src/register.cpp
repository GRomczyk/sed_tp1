#include "pmodeladm.h" 
#include "register.h"

#include "Medio.h"
#include "Persona.h" // class ModelName

void register_atomics_on(ParallelModelAdmin &admin)
{
	admin.registerAtomic(NewAtomicFunction< Medio >(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction< Persona >(), ATOMIC_MODEL_NAME); // Register custom models
}

