(
var out;
s = Server.local;
out=0;
s.quit;
s.boot;
s.doWhenBooted({
    SynthDef("CentroidBing", {
        arg freq=660.0,dip=0,rake=0,mag=1.0,pan=0,frel=0.1,panlag=0.3,gate=0;
        var e,y,k;
        var v;
        v=(mag)*(mag);
        y=0.05*SinOsc.ar(27+(50/(0.01+(mag**2))*(1+((10.0/(freq+0.01))*(SinOsc.ar(0.1+rake*27)+SinOsc.ar(0.1+dip*27))))));
        Out.ar(out,PanAz.ar(2,y*(mag**0.5)*10*EnvGen.ar(Env.perc(0.0, 2.1*(mag**2.2), 1, -8), 1, doneAction: 2),pan));
    }).load(s);
});
)

