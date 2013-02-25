
//Write all synthdefs to .scsyndef files
(

 var path;

//"/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/"

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


SynthDef(\TGrain, { |out = 0, bufnum = 0, amp = 1|
	var trate, dur, clk, pos, pan, grainOut;
	trate = MouseY.kr(8, 150,1);
	dur = 12/trate;
	clk = Impulse.kr(trate);
	pos = MouseX.kr(0,BufDur.kr(b)) + TRand.kr(0, 0.01, clk);
    pan = WhiteNoise.kr(0.6);
	grainOut = TGrains.ar(2, clk, bufnum, 1, pos, dur, pan, 0.1);
	Out.ar(out, grainOut*amp)
}).writeDefFile(path);


)



