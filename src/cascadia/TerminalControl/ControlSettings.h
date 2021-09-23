/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.
--*/
#pragma once
#include "../../inc/cppwinrt_utils.h"
#include "../../inc/ControlProperties.h"

#include <DefaultSettings.h>
#include <conattrs.hpp>
#include "ControlAppearance.h"

using IFontFeatureMap = winrt::Windows::Foundation::Collections::IMap<winrt::hstring, uint32_t>;
using IFontAxesMap = winrt::Windows::Foundation::Collections::IMap<winrt::hstring, float>;

namespace winrt::Microsoft::Terminal::Control::implementation
{
    struct ControlSettings
    {
#define SETTINGS_GEN(type, name, ...) WINRT_PROPERTY(type, name, __VA_ARGS__);
        CORE_SETTINGS(SETTINGS_GEN)
        CONTROL_SETTINGS(SETTINGS_GEN)
#undef SETTINGS_GEN

    private:
        winrt::com_ptr<ControlAppearance> _unfocusedAppearance{ nullptr };
        winrt::com_ptr<ControlAppearance> _focusedAppearance{ nullptr };

    public:
        ControlSettings(Control::IControlSettings settings, Control::IControlAppearance unfocusedAppearance)
        {
            _focusedAppearance = winrt::make_self<implementation::ControlAppearance>(settings);
            _unfocusedAppearance = unfocusedAppearance ?
                                       winrt::make_self<implementation::ControlAppearance>(unfocusedAppearance) :
                                       _focusedAppearance;

#define COPY_SETTING(type, name, ...) _##name = settings.name();
            CORE_SETTINGS(COPY_SETTING)
            CONTROL_SETTINGS(COPY_SETTING)
#undef COPY_SETTING
        }

        winrt::com_ptr<ControlAppearance> UnfocusedAppearance() { return _unfocusedAppearance; }
        winrt::com_ptr<ControlAppearance> FocusedAppearance() { return _focusedAppearance; }
    };
}
