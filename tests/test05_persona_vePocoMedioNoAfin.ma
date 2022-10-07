[Top]
%en este test esperamos que la frecuencia con la que la persona ve una %noticia, dependa de su afinidad
components : P1@Persona

out : info_out1
in : in_port1 info

Link : in_port1 inMedios@P1
Link : info infoRequest@P1

Link : outInfo@P1 info_out1

[P1]
p : 1.0
influenciabilidad : 1.0
poder_convencimiento : 0.2
tiempo_sillon : 1.0
grado : 1
periodo_medio : 60000000
