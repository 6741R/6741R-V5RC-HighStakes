#include "pros/apix.h"
#include "Brain_UI.h"

// Imports the image data for the field and logo images.
#include "High_Stakes_Field_Image.h"
#include "Logo_Image.h"

using namespace pros;

// Holds the selected autonomous mode.
int Brain_UI::selectedAuton;

// Initialize autonomous buttons and their corresponding labels.
lv_obj_t * leftSideBlueButton;
lv_obj_t * rightSideBlueButton;
lv_obj_t * leftSideRedButton;
lv_obj_t * rightSideRedButton;
lv_obj_t * leftSideBlueButtonLabel;
lv_obj_t * rightSideBlueButtonLabel;
lv_obj_t * leftSideRedButtonLabel;
lv_obj_t * rightSideRedButtonLabel;
lv_obj_t * selectedAutonLabel;

// Initialize the LVGL styles for each button
lv_style_t redAutoButtonStyle;
lv_style_t blueAutoButtonStyle;
lv_style_t buttonPressedStyle;

// Initialize image object
LV_IMG_DECLARE(HighStakesFieldImage);
LV_IMG_DECLARE(LogoImage);


/**
 * @brief Callback function for handling button presses.
 * 
 * This function is triggered when any of the autonomous selection buttons 
 * are pressed. It updates the `selectedAutonLabel` text based on the button 
 * pressed and sets the corresponding autonomous mode.
 * 
 * @param btn The LVGL object (button) that was clicked.
 * @return LV_RES_OK to indicate the event was handled successfully.
 */
lv_res_t Brain_UI::btn_click_action(lv_obj_t * btn) {
    uint8_t id = lv_obj_get_free_num(btn);
	
    // Set the autonomous mode and update label based on the button ID
    switch(id) {
        case 0:
            lv_label_set_text(selectedAutonLabel, "Blue Alliance Left");
            selectedAuton = 1;
            break;
        case 1:
            lv_label_set_text(selectedAutonLabel, "Blue Alliance Right");
            selectedAuton = 0;
            break;
        case 2:
            lv_label_set_text(selectedAutonLabel, "Red Alliance Left");
            selectedAuton = 2;
            break;
        case 3:
            lv_label_set_text(selectedAutonLabel, "Red Alliance Right");
            selectedAuton = 3;
            break;
    }
    return LV_RES_OK;
}

/**
 * @brief Displays the match image (logo) on the screen.
 */
void Brain_UI::DisplayMatchImage() {
    // Draw the logo image
    lv_obj_t * img2 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img2, &LogoImage);  // Use the LogoImage descriptor here
    lv_obj_align(img2, NULL, LV_ALIGN_CENTER, 0, 0);  // Center the image on the screen
}

/**
 * @brief Displays the autonomous selector UI on the brain screen.
 */
void Brain_UI::DisplayAutonSelectorUI() {

    // Set default autonomous mode
    selectedAuton = 4;

    // Draw the field image on the brain screen
    lv_obj_t * img = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img, &HighStakesFieldImage);  // Use the HighStakesFieldImage descriptor here
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);  // Center the image

    // Set red side auto button appearance
    lv_style_copy(&redAutoButtonStyle, &lv_style_plain);
    redAutoButtonStyle.body.main_color = LV_COLOR_MAKE(200, 0, 0);
    redAutoButtonStyle.body.grad_color = LV_COLOR_MAKE(100, 0, 0);
    redAutoButtonStyle.body.radius = 0;
    redAutoButtonStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

    // Set blue side auto button appearance
    lv_style_copy(&blueAutoButtonStyle, &lv_style_plain);
    blueAutoButtonStyle.body.main_color = LV_COLOR_MAKE(0, 0, 200);
    blueAutoButtonStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 100);
    blueAutoButtonStyle.body.radius = 0;
    blueAutoButtonStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

    // Set pressed button appearance
    lv_style_copy(&buttonPressedStyle, &lv_style_plain);
    buttonPressedStyle.body.main_color = LV_COLOR_MAKE(255, 255, 255);
    buttonPressedStyle.body.grad_color = LV_COLOR_MAKE(255, 255, 255);
    buttonPressedStyle.body.radius = 0;
    buttonPressedStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

    // Create Left Blue Auto button
    leftSideBlueButton = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(leftSideBlueButton, 0);
    lv_btn_set_action(leftSideBlueButton, LV_BTN_ACTION_CLICK, btn_click_action);
    lv_btn_set_style(leftSideBlueButton, LV_BTN_STYLE_REL, &blueAutoButtonStyle);
    lv_btn_set_style(leftSideBlueButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(leftSideBlueButton, 100, 100);
    lv_obj_align(leftSideBlueButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    leftSideBlueButtonLabel = lv_label_create(leftSideBlueButton, NULL);
    lv_label_set_text(leftSideBlueButtonLabel, "Left Blue");

    // Create Right Blue Auto button
    rightSideBlueButton = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(rightSideBlueButton, 1);
    lv_btn_set_action(rightSideBlueButton, LV_BTN_ACTION_CLICK, btn_click_action);
    lv_btn_set_style(rightSideBlueButton, LV_BTN_STYLE_REL, &blueAutoButtonStyle);
    lv_btn_set_style(rightSideBlueButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(rightSideBlueButton, 100, 100);
    lv_obj_align(rightSideBlueButton, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);
    rightSideBlueButtonLabel = lv_label_create(rightSideBlueButton, NULL);
    lv_label_set_text(rightSideBlueButtonLabel, "Right Blue");

    // Create Left Red Auto button
    leftSideRedButton = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(leftSideRedButton, 2);
    lv_btn_set_action(leftSideRedButton, LV_BTN_ACTION_CLICK, btn_click_action);
    lv_btn_set_style(leftSideRedButton, LV_BTN_STYLE_REL, &redAutoButtonStyle);
    lv_btn_set_style(leftSideRedButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(leftSideRedButton, 100, 100);
    lv_obj_align(leftSideRedButton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
    leftSideRedButtonLabel = lv_label_create(leftSideRedButton, NULL);
    lv_label_set_text(leftSideRedButtonLabel, "Left Red");

    // Create Right Red Auto button
    rightSideRedButton = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(rightSideRedButton, 3);
    lv_btn_set_action(rightSideRedButton, LV_BTN_ACTION_CLICK, btn_click_action);
    lv_btn_set_style(rightSideRedButton, LV_BTN_STYLE_REL, &redAutoButtonStyle);
    lv_btn_set_style(rightSideRedButton, LV_BTN_STYLE_PR, &buttonPressedStyle);
    lv_obj_set_size(rightSideRedButton, 100, 100);
    lv_obj_align(rightSideRedButton, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10);
    rightSideRedButtonLabel = lv_label_create(rightSideRedButton, NULL);
    lv_label_set_text(rightSideRedButtonLabel, "Right Red");

    // Create selectedAutonLabel
    selectedAutonLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(selectedAutonLabel, "Selected Auton: None");
    lv_obj_align(selectedAutonLabel, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -20);
}
