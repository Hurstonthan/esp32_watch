SET(SOURCES screens/ui_Screen1.c
    screens/ui_Function_Screen.c
    screens/ui_HomeAutomation.c
    screens/ui_AlarmClock.c
    screens/ui_Alarmcheck.c
    screens/ui_AlarmDisplay.c
    screens/ui_ringRing.c
    screens/ui_StopWatchSD.c
    screens/ui_TabStop.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_1258245280.c)

add_library(ui ${SOURCES})
