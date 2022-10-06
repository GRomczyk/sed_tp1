[Top]
components : P1@Persona
out : out_port1 info_out1
in : in_port1 info

Link : in_port1 inPort1@P1
Link : info infoRequest@P1

Link : outPort1@P1 out_port1
Link : outInfo@P1 info_out1

[P1]
p : 1.0
influenciabilidad : 1.0
poder_convencimiento : 0.2
tiempo_sillon : 1.0
grado : 1
periodo_medio : 600000
