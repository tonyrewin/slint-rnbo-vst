#include "processor.h"
#include "controller.h"
#include "public.sdk/source/main/pluginfactory.h"
#include "pluginterfaces/base/ftypes.h"
#include "pluginterfaces/base/fplatform.h"

using namespace Steinberg;

#define VENDOR_NAME "YourCompany"
#define VENDOR_URL "http://www.yourcompany.com"
#define VENDOR_EMAIL "info@yourcompany.com"
#define FULL_VERSION_STR "1.0.0.0"

// Фабрика плагинов
BEGIN_FACTORY_DEF(VENDOR_NAME, VENDOR_URL, VENDOR_EMAIL)

    DEF_CLASS2(INLINE_UID_FROM_FUID(EffectProcessor::uid),
               PClassInfo::kManyInstances,
               kVstAudioEffectClass,
               "Effect VST",
               Vst::kDistributable,
               Vst::PlugType::kFx,
               FULL_VERSION_STR,
               kVstVersionString,
               EffectProcessor::createInstance)

END_FACTORY