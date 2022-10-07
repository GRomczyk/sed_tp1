[Top]
%en este test esperamos que no vea el medio por tener tiempo sillon 0
% su p deberia quedar constante
components : P1@Persona

out : info_out1
in : in_port1 info

Link : in_port1 inMedios@P1
Link : info infoRequest@P1

Link : outInfo@P1 info_out1

[P1]
p : 0.5
influenciabilidad : 0.9
poder_convencimiento : 0.2
tiempo_sillon : 0.0
grado : 1
periodo_medio : 60000000
