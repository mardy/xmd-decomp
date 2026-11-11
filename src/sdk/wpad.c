#include "wpad.h"

void *WPADSetSamplingCallback(int chan, void *callback)
{
    void *old_cb;
    _wpadcb_data_t *wpad;

    wpad = (&__rvl_p_wpadcb)[chan];
    if (_wpadUsedCallback != 0) {
        OSReport(lbl_80788630);
        OSReport(lbl_80788664);
    }
    OSDisableInterrupts();
    old_cb = wpad->sampling_cb;
    wpad->sampling_cb = callback;
    OSRestoreInterrupts();
    return old_cb;
}
