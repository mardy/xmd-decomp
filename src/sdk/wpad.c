

#if 0
#include "wpad.h"
void *WPADSetSamplingCallback(int chan, void *callback)
{
    _wpadcb_data_t *wpad;
    void *old_cb;
    BOOL enabled;

    wpad = __rvl_p_wpadcb[chan];
    if (_wpadUsedCallback != 0) {
        OSReport(lbl_80788630);
        OSReport(lbl_80788664);
    }
    enabled = OSDisableInterrupts();
    old_cb = wpad->sampling_cb;
    wpad->sampling_cb = callback;
    OSRestoreInterrupts(enabled);
    return old_cb;
}
#else
#include <revolution/wpad/WPAD.h>
#include "RVL_SDK/src/wpad/WPAD.h"

#include <revolution/os/OSAssert.h>

extern wpad_cb_st *__rvl_p_wpadcb[WPAD_MAX_CONTROLLERS];
extern BOOL _wpadUsedCallback;
//static BOOL _wpadUsedCallback;

inline BOOL WPADIsUsedCallbackByKPAD(void) { return _wpadUsedCallback; }

WPADSamplingCallback *
WPADSetSamplingCallback(WPADChannel chan, WPADSamplingCallback *cb) {
    wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

    OSAssert_Line(3371, (0 <= chan) && (chan < WPAD_MAX_CONTROLLERS));

    if (WPADIsUsedCallbackByKPAD()) {
        // clang-format off
		OSReport("WARNING: Overwritten the callback needed by KPAD.\n");
		OSReport("         Please call KPADSetSamplingCallback instead of "
		                  "WPADSetSamplingCallback.\n");
        // clang-format on
    }

    WPADSamplingCallback *old;
    BOOL intrStatus = OSDisableInterrupts();

    old = p_wpd->samplingCB;
    p_wpd->samplingCB = cb;

    OSRestoreInterrupts(intrStatus);

    return old;
}

WPADConnectCallback *WPADSetConnectCallback(WPADChannel chan, WPADConnectCallback *cb) {
    wpad_cb_st *p_wpd = __rvl_p_wpadcb[chan];

    OSAssert_Line(3402, (0 <= chan) && (chan < WPAD_MAX_CONTROLLERS));

    if (WPADIsUsedCallbackByKPAD()) {
        // clang-format off
		OSReport("WARNING: Overwritten the callback needed by KPAD.\n");
		OSReport("         Please call KPADSetConnectCallback instead of "
		                  "WPADSetConnectCallback.\n");
        // clang-format on
    }

    WPADConnectCallback *old;
    BOOL intrStatus = OSDisableInterrupts();

    old = p_wpd->connectCB;
    p_wpd->connectCB = cb;

    OSRestoreInterrupts(intrStatus);

    return old;
}
#endif
