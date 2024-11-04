#pragma once
#include "public.sdk/source/vst/vsteditcontroller.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

class EffectController : public EditController {
public:
    static FUnknown* createInstance(void*) { return (IEditController*)new EffectController(); }
    
    tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
    
    static FUID uid;
}; 