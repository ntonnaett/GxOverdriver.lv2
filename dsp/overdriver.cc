// generated from file './/overdriver.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace overdriver {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec1[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec3[2];
	double 	fRec4[6];
	double 	fRec2[6];
	FAUSTFLOAT 	fsliderV0;
	FAUSTFLOAT 	*fsliderV0_;
	double 	fRecV0[2];
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "@plugindef.id";
	name = N_("@plugindef.name");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<6; i++) fRec4[i] = 0;
	for (int i=0; i<6; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRecV0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fsliderV0 (*fsliderV0_)
	double 	fSlowV0 = (0.0010000000000000009 * double(fsliderV0));

	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (1 - double(fslider1)));
	double 	fSlow2 = (4.748558434412966e-05 * (exp((5 * (1 - double(fslider2)))) - 1));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (0.13182269918938 + ((fRec0[0] * (0 - (0.0681328270558068 + (0.0389313298317898 * fRec0[0])))) + (fRec1[0] * (2.76448254267148 + ((fRec0[0] * (0.244424506278205 - (1.97167740915359 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (1.4838517391189 + (0.243912835017344 * fRec0[0]))) - 1.94254877817226)))))));
		double fTemp1 = (1.7218443055321 * fRec0[0]);
		fRec3[0] = ((0.993 * fRec3[1]) + fSlow2);
		double fTemp2 = (0.0382025543945746 + (1.92359489121085 * fRec3[0]));
		fRec4[0] = ((double)input0[i] - ((((((fRec4[1] * (0 - (0.189599238018845 + (7.90156145744962 * fRec3[0])))) + (fRec4[2] * (0.376554377012712 + (12.372426207412 * fRec3[0])))) + (fRec4[3] * (0 - (0.37409285266714 + (8.94385790208967 * fRec3[0]))))) + (fRec4[4] * (0.185906754518686 + (2.75870855573217 * fRec3[0])))) + (fRec4[5] * (0 - (0.036971595239983 + (0.209310294815704 * fRec3[0]))))) / fTemp2));
		fRec2[0] = ((0.3183098861837907 * atan((((((((fRec4[0] * (1.00916372515974 + (2.32757253300253 * fRec3[0]))) + (fRec4[1] * (0 - (3.02414828580507 + (6.97740623209635 * fRec3[0]))))) + (fRec4[2] * (2.00723747853779 + (4.6380526221921 * fRec3[0])))) + (fRec4[3] * (2.03154046022688 + (4.67455420855471 * fRec3[0])))) + (fRec4[4] * (0 - (3.03401883864428 + (6.99150402031297 * fRec3[0]))))) + (fRec4[5] * (1.01022546052493 + (2.32873088865998 * fRec3[0])))) / fTemp2))) - ((((((fRec2[1] * (((fRec0[0] * (0.342300562385798 + (0.172710525510542 * fRec0[0]))) + (fRec1[0] * (((fRec0[0] * ((9.85513140731259 * fRec0[0]) - 1.22040526981159)) + (fRec1[0] * (9.70954613281066 + (fRec0[0] * (0 - (7.4193882814809 + (1.21787156291584 * fRec0[0]))))))) - 13.818483484256))) - 0.627143655442408)) + (fRec2[2] * (1.19061146333974 + ((fRec0[0] * (0 - (0.68800151731608 + (0.301607063355195 * fRec0[0])))) + (fRec1[0] * (27.6291105109405 + ((fRec0[0] * (2.43737610953334 - (19.703751575228 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (14.8390357722482 + (2.43235790148993 * fRec0[0]))) - 19.4126987788341))))))))) + (fRec2[3] * (((fRec0[0] * (0.691529498936688 + (0.257871114498178 * fRec0[0]))) + (fRec1[0] * (((fRec0[0] * ((19.6972403733444 * fRec0[0]) - 2.43394177243437)) + (fRec1[0] * (19.406307321322 + (fRec0[0] * (0 - (14.8392950190481 + (2.42897267714817 * fRec0[0]))))))) - 27.6212560540001))) - 1.12719905989927))) + (fRec2[4] * (0.532024855823474 + ((fRec0[0] * (0 - (0.347592560193365 + (0.10710649181399 * fRec0[0])))) + (fRec1[0] * (13.8067017988454 + ((fRec0[0] * (1.21525376412406 - (9.84536460448721 * fRec0[0]))) + (fRec1[0] * ((fRec0[0] * (7.41977715168079 + (1.21279372640321 * fRec0[0]))) - 9.6999589465229))))))))) + (fRec2[5] * (((fRec0[0] * (0.0698968432427652 + (0.017063244992255 * fRec0[0]))) + (fRec1[0] * (((fRec0[0] * ((1.9684218082118 * fRec0[0]) - 0.242707337689643)) + (fRec1[0] * (1.93935304939665 + (fRec0[0] * (0 - (1.48398136251887 + (0.242220222846465 * fRec0[0]))))))) - 2.76055531420128))) - 0.10011630301091))) / fTemp0));
		double fTemp3 = (8.61074866229953 * fRec0[0]);
		double fTemp4 = (17.2245515938772 * fRec0[0]);
		double fTemp5 = (17.2276058631553 * fRec0[0]);
		double fTemp6 = (8.61533006621669 * fRec0[0]);
		double fTemp7 = (1.72337144017115 * fRec0[0]);
		output0[i] = (FAUSTFLOAT)(((((((fRec2[0] * (((fRec0[0] * ((1.7318648883714 * fRec0[0]) - 1.8386382119672)) + (fRec1[0] * (0.740812854276582 + ((fRec0[0] * (0.000473161159221102 - fTemp7)) + (fRec1[0] * (0.0790496090066116 + fTemp7)))))) - 0.828670794721597)) + (fRec2[1] * (4.1331046489266 + ((fRec0[0] * (9.15346210245012 - (8.639813064 * fRec0[0]))) + (fRec1[0] * (((fRec0[0] * (fTemp6 - 0.00241822521539553)) + (fRec1[0] * (0 - (0.395161942132817 + fTemp6)))) - 3.70339744853995)))))) + (fRec2[2] * (((fRec0[0] * ((17.2406192820481 * fRec0[0]) - 18.2276870505644)) + (fRec1[0] * (7.405461251394 + ((fRec0[0] * (0.00494128505018926 - fTemp5)) + (fRec1[0] * (0.790151680574743 + fTemp5)))))) - 8.24572831853298))) + (fRec2[3] * (8.22526499984671 + ((fRec0[0] * (18.1486704909598 - (17.2016283458583 * fRec0[0]))) + (fRec1[0] * (((fRec0[0] * (fTemp4 - 0.00504611545040561)) + (fRec1[0] * (0 - (0.789979478993444 + fTemp4)))) - 7.40412760570809)))))) + (fRec2[4] * (((fRec0[0] * ((8.58132665971527 * fRec0[0]) - 9.03493718019078)) + (fRec1[0] * (3.70139698001109 + ((fRec0[0] * (0.00257547081572006 - fTemp3)) + (fRec1[0] * (0.394903639760867 + fTemp3)))))) - 4.10240966619313))) + (fRec2[5] * (0.81843913067439 + ((fRec0[0] * (1.79912984931251 - (1.71236942027649 * fRec0[0]))) + (fRec1[0] * (((fRec0[0] * (fTemp1 - 0.000525576359329276)) + (fRec1[0] * (0 - (0.0789635082159616 + fTemp1)))) - 0.740146031433626)))))) / fTemp0);
		// post processing
		for (int i=5; i>0; i--) fRec2[i] = fRec2[i-1];
		for (int i=5; i>0; i--) fRec4[i] = fRec4[i-1];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}
	for (int i=0; i<count; i++) {
		fRecV0[0] = ((0.999 * fRecV0[1]) + fSlowV0);
		output0[i] = (FAUSTFLOAT)((double)output0[i] * fRecV0[0]);
		// post processing
		fRecV0[1] = fRecV0[0];
	}

#undef fsliderV0 
#undef fslider0
#undef fslider1
#undef fslider2
}
		
void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case DRIVE: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case VOLUME: 
		fsliderV0_ = (float*)data; // , 0.5, 0.0, 1, 0.01 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   BASS, 
   DRIVE, 
   TREBLE, 
   VOLUME,
} PortIndex;
*/

} // end namespace overdriver
