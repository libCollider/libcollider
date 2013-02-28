
//Write all synthdefs to .scsyndef files
//Execute as one block by selecting everything inside the two outermost parantheses
(

 var path = "/your/path";

SynthDef(\SoundFile_Loop_Mono, {| out = 0, bufnum = 0, looping = 1, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(1, bufnum, scaledRate , trig, 0, loop:looping, doneAction:0);
	Out.ar(out, soundFilePlayer*amp)
}).writeDefFile(path);

SynthDef(\SoundFile_Event_Mono, {| out = 0, bufnum = 0, looping = 0, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(1, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Loop_Stereo, {| out = 0, bufnum = 0, looping = 1, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, 0, loop:looping, doneAction:0);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Event_Stereo, {| out = 0, bufnum = 0, looping = 0, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);


//Stutter stuff
SynthDef(\SoundFile_Stutter_Loop_Mono, {| out = 0, bufnum = 0, looping = 1, rate = 1, stutterRate = 2, amp = 1 |
	var scaledRate, soundFilePlayer, trig;
	trig = Dust.ar(stutterRate);
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(1, bufnum, scaledRate , trig, 0, loop:looping, doneAction:0);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Stutter_Loop_Stereo, {| out = 0, bufnum = 0, looping = 1, rate = 1, stutterRate = 2, amp = 1 |
	var scaledRate, soundFilePlayer, trig;
	trig = Dust.ar(stutterRate);
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, 0, loop:looping, doneAction:0);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Stutter_Event_Mono, {| out = 0, bufnum = 0, looping = 0, rate = 1, stutterRate = 2, amp = 1 |
	var scaledRate, soundFilePlayer, trig;
	trig = Dust.ar(stutterRate);
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(1, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Stutter_Event_Stereo, {| out = 0, bufnum = 0, looping = 0, rate = 1, stutterRate = 2, amp = 1 |
	var scaledRate, soundFilePlayer, trig;
	trig = Dust.ar(stutterRate);
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);


//BandStop Whitenoise mouse controlled
SynthDef(\FilteredWhiteNoise_Mouse_Control,{| out = 0, amp = 1 |
	var instrument;
	instrument = BBandStop.ar(WhiteNoise.ar ! 2,MouseX.kr(20, 20000,
		             \exponential),MouseY.kr(0.0, 10.0, \linear), 0.1);
	Out.ar(out, instrument*amp)
}).writeDefFile(path);


SynthDef(\TGrain2, { |out = 0, bufnum = 0|
	var trate, dur, clk, pos, pan, grainOut;
	trate = MouseY.kr(8, 150,1);
	dur = 12/trate;
	clk = Impulse.kr(trate);
	pos = MouseX.kr(0,BufDur.kr(bufnum)) + TRand.kr(0, 0.01, clk);
    pan = WhiteNoise.kr(0.6);
	grainOut = TGrains.ar(2, clk, bufnum, 1, pos, dur, pan, 0.1);
	Out.ar(out, grainOut)
}).writeDefFile(path);

SynthDef(\TGrain3, { |out = 0, bufnum = 0|
	var trate, dur, clk, pos, pan, grainOut;
	trate = MouseY.kr(8, 150,1);
	dur = 12/trate;
	clk = Impulse.kr(trate);
	pos = MouseX.kr(0,BufDur.kr(bufnum)) + TRand.kr(0, 0.01, clk);
    pan = WhiteNoise.kr(0.6);
	grainOut = TGrains.ar(3, clk, bufnum, 1, pos, dur, pan, 0.1);
	Out.ar(out, grainOut)
}).writeDefFile(path);

SynthDef(\TGrain4, { |out = 0, bufnum = 0|
	var trate, dur, clk, pos, pan, grainOut;
	trate = MouseY.kr(8, 150,1);
	dur = 12/trate;
	clk = Impulse.kr(trate);
	pos = MouseX.kr(0,BufDur.kr(bufnum)) + TRand.kr(0, 0.01, clk);
    pan = WhiteNoise.kr(0.6);
	grainOut = TGrains.ar(4, clk, bufnum, 1, pos, dur, pan, 0.1);
	Out.ar(out, grainOut)
}).writeDefFile(path);

SynthDef(\TGrain5, { |out = 0, bufnum = 0|
	var trate, dur, clk, pos, pan, grainOut;
	trate = MouseY.kr(8, 150,1);
	dur = 12/trate;
	clk = Impulse.kr(trate);
	pos = MouseX.kr(0,BufDur.kr(bufnum)) + TRand.kr(0, 0.01, clk);
    pan = WhiteNoise.kr(0.6);
	grainOut = TGrains.ar(5, clk, bufnum, 1, pos, dur, pan, 0.1);
	Out.ar(out, grainOut)
}).writeDefFile(path);

SynthDef(\TGrain6, { |out = 0, bufnum = 0|
	var trate, dur, clk, pos, pan, grainOut;
	trate = MouseY.kr(8, 150,1);
	dur = 12/trate;
	clk = Impulse.kr(trate);
	pos = MouseX.kr(0,BufDur.kr(bufnum)) + TRand.kr(0, 0.01, clk);
    pan = WhiteNoise.kr(0.6);
	grainOut = TGrains.ar(6, clk, bufnum, 1, pos, dur, pan, 0.1);
	Out.ar(out, grainOut)
}).writeDefFile(path);

SynthDef(\CentroidBing, {
        arg freq=660.0,dip=0,rake=0,mag=1.0,pan=0,frel=0.1,panlag=0.3,gate=0;
        var e,y,k;
        var v;
        v=(mag)*(mag);
        y=0.05*SinOsc.ar(27+(50/(0.01+(mag**2))*(1+((10.0/(freq+0.01))*(SinOsc.ar(0.1+rake*27)+SinOsc.ar(0.1+dip*27))))));
        Out.ar(0,PanAz.ar(2,y*(mag**0.5)*10*EnvGen.ar(Env.perc(0.0, 2.1*(mag**2.2), 1, -8), 1, doneAction: 2),pan));
}).writeDefFile(path);

)



