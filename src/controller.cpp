#include "controller.h"

tresult PLUGIN_API EffectController::initialize(FUnknown* context) {
    tresult result = EditController::initialize(context);
    if (result != kResultOk) return result;
    
    return kResultOk;
}

// Исправляем FUID
FUID EffectController::uid(0x23456789, 0xABCD, 0xEF01, 0x00000002); 