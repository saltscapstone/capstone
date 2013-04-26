%Initialization Code

junk = instrfind;
fclose(junk);
delete(junk);

scope = visa ('agilent','GPIB0::7::INSTR'); % open GPIB connection to scope
set (scope,'InputBufferSize', 1.024E6); % hold 1 meg of data in memory
if ( strcmp (scope.Status,'open') == 1 )
fprintf (' Scope already open - closing first ...\n');
fclose (scope)
end
fopen (scope)
if (scope.Status~='open')
fprintf ('Error opening GPIB connection to oscilloscope \n');
output = [0,0]; % error flags set
return;
end
fprintf (scope,':TIMEBASE:MODE MAIN'); % required for deep memory transfer
fprintf (scope,':TIMEBASE:RANGE 5E-4'); % set scope time window to 5 ms width
fprintf (scope,':TIMEBASE:REFERENCE LEFT'); % put start of window at left
fprintf (scope,':TIMEBASE:DELAY 0'); % change for delay
fprintf (scope,':CHANNEL1:RANGE 2.0'); % set vertical sensitivity of channel 1
fprintf (scope,':CHANNEL1:COUPLING DC'); % coupling to DC
fprintf (scope,':TRIG:SOURCE EXT'); % trigger on sync from function generator
fprintf (scope,':TRIG:SLOPE POSITIVE'); % sync output goes low when pulse starts
fprintf (scope,':TRIG:LEVEL 1'); % trigger on 1V point

fungen = visa ('agilent','GPIB0::10::INSTR'); % open GPIB connection to function generator
if ( strcmp (fungen.Status,'open') == 1 )
fprintf ('Function Generator already open - closing first ...\n');
fclose (fungen)
end
fopen (fungen)
if (fungen.Status~='open')
fprintf ('Error opening GPIB connection to function generator \n');
output = 0; % error flag set
return;
end
fprintf (fungen,'*RST');% initialze function generator to a known state
fprintf (fungen,':FUNC:SHAPE SIN'); % set function generator to a sine wave
fprintf (fungen,':FREQ 8E+3'); % 8 MHz output frequency
fprintf (fungen,':VOLT 0.5'); % set amplitude to 0.1V peak-to-peak
fprintf (fungen,':OUTPUT:STATE ON'); % turn on the pulse
fclose (fungen)
fprintf (scope,':AUT');
fclose (scope) % disconnect GPIB scope object

%End Initialization Code

%Set Parameters
%Signal Generator set to 20ns, 10v pulse every 11s
fopen(fungen)
fprintf(fungen,'*RST');% initialze function generator to a known state
fprintf(fungen,':FUNC:SHAPE PULSE');	% set function generator to a sine wave
fprintf(fungen,':FREQ .09090909');
fprintf(fungen,':PULS:WIDT 20E-9');
fprintf(fungen,':VOLT 10'); % set peak-to-peak amplitude
fclose(fungen)

%Scope set to trigger on ch1
fopen(scope)
fprintf (scope,':CHANNEL1:RANGE 20'); % set vertical sensitivity of channel 1
fprintf (scope,':CHANNEL2:RANGE 20');
fprintf (scope,':CHANNEL1:COUPLING DC'); % coupling to DC
fprintf (scope,':CHANNEL2:COUPLING DC');
fprintf (scope,':TRIG:SOURCE EXT'); % trigger on sync from function generator
fprintf (scope,':TRIG:SLOPE POSITIVE'); % sync output goes low when pulse starts
fprintf (scope,':TRIG:LEVEL 1'); % trigger on 1V point
fprintf (scope,':TIMEBASE:RANGE 10');
fclose (scope)
%End Set Parameters

%Fire Pulse
fopen (fungen)
fprintf(fungen,':OUTPUT:STATE ON');
fclose (fungen)