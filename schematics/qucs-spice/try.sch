<Qucs Schematic 0.0.19>
<Properties>
  <View=-125,21,1769,1186,0.909091,88,60>
  <Grid=10,10,1>
  <DataSet=try.dat>
  <DataDisplay=try.dpl>
  <OpenDisplay=1>
  <Script=try.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <GND * 1 890 240 0 0 0 0>
  <Lib IRLZ44N 1 750 340 8 -26 0 0 "NMOSFETs" 0 "IRLZ44N" 0>
  <R R1 1 750 230 15 -26 0 1 "2" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <IProbe Pr1 1 800 100 -26 16 1 2>
  <Lib OP4 1 450 390 -12 23 1 2 "Ideal" 0 "OpAmp" 0 "1E6" 0 "106" 0 "75" 0 "3.3" 0 "0" 0>
  <R R3 1 570 390 -26 15 0 0 "1k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R4 1 440 470 -26 15 0 0 "15k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 540 270 0 0 0 0>
  <R R5 1 490 300 15 -26 0 1 "10k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <C C1 1 450 560 -26 17 0 0 "100n" 1 "" 0 "neutral" 0>
  <Vdc V4 1 890 180 18 -26 0 1 "7" 1>
  <GND * 1 750 550 0 0 0 0>
  <R R2 1 750 490 15 -26 0 1 "0.1" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <.TR TR1 1 -40 50 0 65 0 0 "lin" 1 "5ms" 1 "6 ms" 1 "2000" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <R R6 1 400 160 -29 -57 0 0 "86k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 340 250 0 0 0 0>
  <GND * 1 550 180 0 0 0 0>
  <Vdc V5 1 340 190 18 -26 0 1 "3" 1>
  <C C2 1 590 150 -26 17 0 0 "10 nF" 1 "" 0 "neutral" 0>
</Components>
<Wires>
  <750 370 750 390 "" 0 0 0 "">
  <750 260 750 310 "" 0 0 0 "">
  <750 100 750 200 "" 0 0 0 "">
  <750 100 770 100 "" 0 0 0 "">
  <600 390 750 390 "" 0 0 0 "">
  <540 390 540 400 "" 0 0 0 "">
  <480 400 540 400 "" 0 0 0 "">
  <480 400 480 470 "" 0 0 0 "">
  <470 470 480 470 "" 0 0 0 "">
  <410 390 410 470 "" 0 0 0 "">
  <410 390 420 390 "" 0 0 0 "">
  <480 380 490 380 "" 0 0 0 "">
  <490 330 490 340 "" 0 0 0 "">
  <490 270 540 270 "" 0 0 0 "">
  <490 340 490 380 "" 0 0 0 "">
  <720 340 720 360 "" 0 0 0 "">
  <410 360 620 360 "" 0 0 0 "">
  <410 360 410 390 "" 0 0 0 "">
  <830 100 890 100 "" 0 0 0 "">
  <410 470 410 560 "" 0 0 0 "">
  <410 560 420 560 "" 0 0 0 "">
  <480 470 480 560 "" 0 0 0 "">
  <890 210 890 240 "" 0 0 0 "">
  <890 100 890 150 "" 0 0 0 "">
  <750 520 750 550 "" 0 0 0 "">
  <750 390 750 460 "" 0 0 0 "">
  <430 340 490 340 "" 0 0 0 "">
  <430 160 430 340 "" 0 0 0 "">
  <340 220 340 250 "" 0 0 0 "">
  <340 160 370 160 "" 0 0 0 "">
  <550 150 550 180 "" 0 0 0 "">
  <550 150 560 150 "" 0 0 0 "">
  <620 360 720 360 "" 0 0 0 "">
  <620 150 620 360 "" 0 0 0 "">
  <720 340 720 340 "gate" 640 240 0 "">
  <750 460 750 460 "SHUNT" 780 430 0 "">
</Wires>
<Diagrams>
  <Rect 70 1110 1623 370 3 #c0c0c0 1 00 1 0.005 5e-05 0.006 0 0 20 2 1 -1 0.2 1 315 0 225 "" "" "">
	<"ngspice/tran.i(pr1)" #ff00ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
