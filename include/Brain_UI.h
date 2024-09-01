#pragma once
#ifndef BRAIN_UI_H
#define BRAIN_UI_H

#include "api.h"
#include "pros/apix.h"

/**
 * @class Brain_UI
 * @brief Manages the user interface displayed on the robot's Brain screen.
 *
 * The Brain_UI class provides methods for displaying and interacting with the autonomous
 * selection user interface (UI) on the robot's Brain screen. It handles button actions
 * and UI updates for selecting different autonomous modes.
 */
class Brain_UI {
    public:

        /**
         * @brief Callback function for button click actions.
         * 
         * @param btn Pointer to the button object that was clicked.
         * 
         * @return LV_RES_OK if the action was successful.
         *
         * This static method is called when a button is clicked on the UI. It updates the
         * selected autonomous mode based on the button that was pressed.
         */
        static lv_res_t btn_click_action(lv_obj_t* btn);

        /**
         * @brief Displays the autonomous mode selection UI on the Brain screen.
         *
         * This static method creates and configures the UI elements for selecting different
         * autonomous modes. It includes buttons for various modes and updates the screen
         * with the selected mode.
         */
        static void DisplayAutonSelectorUI();

        /**
         * @brief Stores the index of the currently selected autonomous mode.
         *
         * This static variable holds the selected autonomous mode, which is updated based
         * on user interactions with the UI buttons.
         */
        static int selectedAuton;
};

#endif