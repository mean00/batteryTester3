<Qucs Schematic 0.0.19>
<Properties>
  <View=-125,-149,1852,1167,0.909091,0,0>
  <Grid=10,10,1>
  <DataSet=new_version.dat>
  <DataDisplay=new_version.dpl>
  <OpenDisplay=1>
  <Script=new_version.m>
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
  <GND * 1 750 550 0 0 0 0>
  <R R2 1 750 490 15 -26 0 1 "0.1" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Lib OP5 1 530 450 -12 23 1 2 "Ideal" 0 "OpAmp" 0 "1E6" 0 "106" 0 "75" 0 "3.3" 0 "0" 0>
  <GND * 1 590 550 0 0 0 0>
  <R R7 1 590 490 15 -26 0 1 "820" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Lib OP4 1 350 450 -12 23 1 2 "Ideal" 0 "OpAmp" 0 "1E6" 0 "106" 0 "75" 0 "3.3" 0 "0" 0>
  <Lib OP6 1 140 440 -12 23 1 2 "Ideal" 0 "OpAmp" 0 "1E6" 0 "106" 0 "75" 0 "3.3" 0 "0" 0>
  <R R9 1 250 450 -26 15 0 0 "1k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R13 1 530 340 -26 -53 0 2 "10k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 480 340 0 0 0 0>
  <Vdc V4 1 890 180 18 -26 0 1 "4" 1>
  <.TR TR1 1 -20 0 0 63 0 0 "lin" 1 "0" 1 "10ms" 1 "1000" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <R R8 1 520 510 -26 15 0 0 "22k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Vdc V5 1 410 340 -26 -56 0 2 "2" 1>
  <R R11 1 280 340 -26 15 0 0 "1k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 280 250 0 0 0 0>
  <GND * 1 510 130 0 0 0 0>
  <C C1 1 580 120 -26 17 0 0 "100nf" 1 "" 0 "neutral" 0>
  <R R14 1 220 250 -26 15 0 0 "10k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R10 1 130 530 -26 15 0 0 "10k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
</Components>
<Wires>
  <750 260 750 310 "" 0 0 0 "">
  <750 100 750 200 "" 0 0 0 "">
  <750 100 770 100 "" 0 0 0 "">
  <830 100 890 100 "" 0 0 0 "">
  <890 210 890 240 "" 0 0 0 "">
  <890 100 890 150 "" 0 0 0 "">
  <750 520 750 550 "" 0 0 0 "">
  <750 440 750 460 "" 0 0 0 "">
  <560 440 750 440 "" 0 0 0 "">
  <560 460 590 460 "" 0 0 0 "">
  <590 520 590 550 "" 0 0 0 "">
  <490 450 500 450 "" 0 0 0 "">
  <490 440 490 450 "" 0 0 0 "">
  <380 440 490 440 "amp" 470 410 52 "">
  <380 460 380 510 "" 0 0 0 "">
  <320 510 380 510 "" 0 0 0 "">
  <320 450 320 510 "" 0 0 0 "">
  <280 450 320 450 "" 0 0 0 "">
  <170 450 180 450 "" 0 0 0 "">
  <160 530 180 530 "" 0 0 0 "">
  <180 450 220 450 "" 0 0 0 "">
  <180 450 180 530 "" 0 0 0 "">
  <100 440 100 530 "" 0 0 0 "">
  <100 440 110 440 "" 0 0 0 "">
  <170 430 190 430 "" 0 0 0 "">
  <100 210 100 440 "" 0 0 0 "">
  <100 210 610 210 "" 0 0 0 "">
  <620 210 620 340 "" 0 0 0 "">
  <620 340 720 340 "" 0 0 0 "">
  <750 370 750 440 "" 0 0 0 "">
  <480 340 500 340 "" 0 0 0 "">
  <560 340 620 340 "" 0 0 0 "">
  <560 460 560 510 "" 0 0 0 "">
  <550 510 560 510 "" 0 0 0 "">
  <490 450 490 510 "" 0 0 0 "">
  <440 340 480 340 "" 0 0 0 "">
  <310 340 380 340 "" 0 0 0 "">
  <190 340 190 430 "" 0 0 0 "">
  <190 340 250 340 "" 0 0 0 "">
  <250 250 280 250 "" 0 0 0 "">
  <190 250 190 340 "" 0 0 0 "">
  <510 120 550 120 "" 0 0 0 "">
  <610 210 620 210 "" 0 0 0 "">
  <610 120 610 210 "" 0 0 0 "">
  <510 120 510 130 "" 0 0 0 "">
  <750 460 750 460 "SHUNT" 780 430 0 "">
  <180 450 180 450 "plus" 210 420 0 "">
</Wires>
<Diagrams>
  <Rect 70 1110 1623 370 3 #c0c0c0 1 00 1 0 0.0005 0.01 1 -1 0.2 1 1 0.395488 0.5 3.55225 315 0 225 "" "" "">
	<"ngspice/tran.i(pr1)" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>