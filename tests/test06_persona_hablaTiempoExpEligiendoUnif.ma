[Top]
%En este test esperamos que la persona hable en tiempo exponencial de media 60 segundos, eligiendo uniformemente el puerto de salida
components : P1@Persona
out : out_port1 out_port2 out_port3 out_port4 out_port5
in : in_port1 in_port2 in_port3 in_port4 in_port5 

Link : in_port1 inPort1@P1
Link : in_port2 inPort2@P1
Link : in_port3 inPort3@P1
Link : in_port4 inPort4@P1
Link : in_port5 inPort5@P1

Link : outPort1@P1 out_port1
Link : outPort2@P1 out_port2
Link : outPort3@P1 out_port3
Link : outPort4@P1 out_port4
Link : outPort5@P1 out_port5


[P1]
p : 1.0
influenciabilidad : 0.0
poder_convencimiento : 0.2
tiempo_sillon : 1.0
grado : 5
periodo_medio : 60
