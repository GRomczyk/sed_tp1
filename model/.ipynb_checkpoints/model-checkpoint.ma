[Top]
components : Sociedad
in: infoRequest
out : info_out0
out : info_out1
out : info_out2
out : info_out3
out : info_out4
Link : infoRequest infoRequest@Sociedad
Link : info_out0@Sociedad info_out0
Link : info_out1@Sociedad info_out1
Link : info_out2@Sociedad info_out2
Link : info_out3@Sociedad info_out3
Link : info_out4@Sociedad info_out4

[Sociedad]
components: Persona0@Persona
components: Persona1@Persona
components: Persona2@Persona
components: Persona3@Persona
components: Persona4@Persona
in : infoRequest medios
out : info_out0
out : info_out1
out : info_out2
out : info_out3
out : info_out4
Link : outInfo@Persona0 info_out0
Link : infoRequest infoRequest@Persona0
Link : outInfo@Persona1 info_out1
Link : infoRequest infoRequest@Persona1
Link : outInfo@Persona2 info_out2
Link : infoRequest infoRequest@Persona2
Link : outInfo@Persona3 info_out3
Link : infoRequest infoRequest@Persona3
Link : outInfo@Persona4 info_out4
Link : infoRequest infoRequest@Persona4
Link : outPort1@Persona0 inPort1@Persona1
Link : outPort1@Persona1 inPort1@Persona0
Link : outPort2@Persona1 inPort1@Persona4
Link : outPort1@Persona4 inPort2@Persona1
Link : outPort3@Persona1 inPort1@Persona3
Link : outPort1@Persona3 inPort3@Persona1
Link : outPort1@Persona2 inPort2@Persona3
Link : outPort2@Persona3 inPort1@Persona2
Link : outPort3@Persona3 inPort2@Persona4
Link : outPort2@Persona4 inPort3@Persona3

[Persona0]
p : 0.6133041527094315
influenciabilidad : 0.3790464474283574
poder_convencimiento : 0.45564614742216636
tiempo_sillon : 0.8092931856335026
periodo_medio : 596.1483544418352
grado : 1

[Persona1]
p : -0.35417414256625174
influenciabilidad : 0.15812387524727511
poder_convencimiento : 0.5414513368020069
tiempo_sillon : 0.395301560363448
periodo_medio : 411.9380525889213
grado : 3

[Persona2]
p : 0.3040592513260093
influenciabilidad : 0.6725670143150383
poder_convencimiento : 0.6826726991141001
tiempo_sillon : 0.12516557822125013
periodo_medio : 610.7088647325155
grado : 1

[Persona3]
p : -1.0
influenciabilidad : 0.6001167836150334
poder_convencimiento : 0.5207358777636734
tiempo_sillon : 0.6113955889175027
periodo_medio : 460.32834252140367
grado : 3

[Persona4]
p : -0.5771650856559954
influenciabilidad : 0.6956094483510719
poder_convencimiento : 0.581169630454836
tiempo_sillon : 0.3741568611764671
periodo_medio : 448.9095166856023
grado : 2
