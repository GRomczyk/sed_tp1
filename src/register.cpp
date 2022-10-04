#include "pmodeladm.h" 
#include "register.h"

#include "Persona.h" // class ModelName

void register_atomics_on(ParallelModelAdmin &admin)
{
	admin.registerAtomic(NewAtomicFunction< Persona >(), ATOMIC_MODEL_NAME); // Register custom models
}

