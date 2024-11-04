#pragma once
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "controller.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

class EffectProcessor : public AudioEffect {
public:
    static FUnknown* createInstance(void*) { return (IAudioProcessor*)new EffectProcessor(); }
    
    EffectProcessor();
    
    tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns,
                                        SpeakerArrangement* outputs, int32 numOuts) SMTG_OVERRIDE;
    tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE;
    
    static FUID uid;
}; 