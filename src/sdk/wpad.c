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
