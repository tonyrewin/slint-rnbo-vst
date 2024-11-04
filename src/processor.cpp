#include "processor.h"

EffectProcessor::EffectProcessor() {
    setControllerClass(EffectController::uid);
}

tresult PLUGIN_API EffectProcessor::initialize(FUnknown* context) {
    tresult result = AudioEffect::initialize(context);
    if (result != kResultOk) return result;
    
    addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
    addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
    
    return kResultOk;
}

tresult PLUGIN_API EffectProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns,
                                                     SpeakerArrangement* outputs, int32 numOuts) {
    if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo) {
        return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
    }
    return kResultFalse;
}

tresult PLUGIN_API EffectProcessor::process(ProcessData& data) {
    if (data.numInputs == 0 || data.numOutputs == 0) return kResultOk;
    
    // Просто копируем входной сигнал на выход
    for (int32 i = 0; i < data.numSamples; i++) {
        data.outputs[0].channelBuffers32[0][i] = data.inputs[0].channelBuffers32[0][i];
        data.outputs[0].channelBuffers32[1][i] = data.inputs[0].channelBuffers32[1][i];
    }
    
    return kResultOk;
}

// Определяем FUID для процессора
FUID EffectProcessor::uid(0x12345678, 0x9ABC, 0xDEF0, 0x00000001); 