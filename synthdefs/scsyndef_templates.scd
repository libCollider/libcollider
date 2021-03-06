
//Write all synthdefs to .scsyndef files
//Execute as one block by selecting everything inside the two outermost parantheses
(

 //var path = "/your/path";
 var path = "/Users/administrator/git/collider/synthdefs/mac";

SynthDef(\SoundFile_Loop_Mono, {| outpos1 = 0, bufnum = 0, looping = 1, trig = -1, rate = 1, amp = 1, startpos = 0 |
	var scaledRate, soundFilePlayer, curpos;
	scaledRate = rate*BufRateScale.kr(bufnum);
	curpos = startpos*BufFrames.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(1, bufnum, scaledRate , trig, curpos, loop:looping, doneAction:0);
	Out.ar(outpos1, soundFilePlayer*amp)
}).writeDefFile(path);

SynthDef(\SoundFile_Event_Mono, {| out = 0, bufnum = 0, looping = 0, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(1, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Loop_Stereo, {| outpos1 = 0, outpos2 = 1, bufnum = 0, looping = 1, trig = -1, rate = 1, amp = 1, startpos = 0 |
	var scaledRate, soundFilePlayer, curpos;
	scaledRate = rate*BufRateScale.kr(bufnum);
	curpos = startpos*BufFrames.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, curpos, loop:looping, doneAction:0);
	Out.ar(outpos1, soundFilePlayer*amp);
    Out.ar(outpos2, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Event_Stereo, {| out = 0, bufnum = 0, looping = 0, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	Out.ar(out, soundFilePlayer*amp)

}).writeDefFile(path);

SynthDef(\SoundFile_Event_Stereo_81, {| out = 0, bufnum = 0, looping = 0, trig = -1, rate = 1, amp = 1 |
	var scaledRate, soundFilePlayer, sig;
	scaledRate = rate*BufRateScale.kr(bufnum);
	soundFilePlayer = PlayBuf.ar(2, bufnum, scaledRate , trig, 0, loop:looping, doneAction:2);
	sig=[0,0,0,0,0,0,0,0,0,0,0,0,soundFilePlayer.at(0),0,0,0,0,0,0,soundFilePlayer.at(1)];
	Out.ar(out, sig*amp)

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
SynthDef(\CentroidBing24, {
        arg freq=660.0,dip=90,rake=90,mag=1.0,frel=0.1,panlag=0.3,gate=0,vpan=0,hpan=0;
        var e,y,k;
        var v,a,b,c,out,sig;
        y=0.05*SinOsc.ar(27+(50/(0.01+(mag**2))*(1+((10.0/(freq+0.01))*(SinOsc.ar(0.1+rake*27)+SinOsc.ar(0.1+dip*27))))));
		//y=0.01*ClipNoise.ar;
		v=PanAz.ar(4,y,vpan);
		a=PanAz.ar(12,v.at(0),hpan,0.5,2.0);
		b=PanAz.ar(8,v.at(1),hpan-(2.0/12.0),0.5,2.0);
		c=PanAz.ar(4,v.at(2),hpan-(0.25)-(2.0/12.0),0.5,2.0);
		out=a.addAll(b).addAll(c);
		Out.ar(0,out*10*EnvGen.ar(Env.perc(0.0, 2.1*(mag**2.2), 1, -8), 1, doneAction: 2));
}).writeDefFile(path);

SynthDef("grainlet",
{ arg out=0, freq=440, dur=0.05;
var env;
env = EnvGen.kr(Env.perc(0.01, dur, 0.3), doneAction:2); Out.ar(out, SinOsc.ar(freq, 0, env))
}).writeDefFile(path);

)



