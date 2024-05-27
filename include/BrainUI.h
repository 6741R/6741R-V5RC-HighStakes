#include "api.h"
#include "pros/apix.h"

#pragma once
#ifndef BRAINUI_H
#define BRAINUI_H

class BrainUI {
    public:
        static lv_res_t btn_click_action(lv_obj_t*);
        static void DisplayAutonSelectorUI();
        static int selectedAuton;
};

#endif