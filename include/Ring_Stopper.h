#pragma once
#ifndef RING_STOPPER_H
#define RING_STOPPER_H

/**
 * @class Mogo_Clamp
 * @brief Controls the clamping mechanism of the mobile goal (mogo) clamp.
 */
class Ring_Stopper {

    public:

        /**
         * @brief Constructor for Mogo_Clamp.
         * Initializes the clamp to an unclamped state.
         */
        Ring_Stopper();

        /**
         * @brief Engages the clamp to hold the mobile goal.
         */
        void Lower();

        /**
         * @brief Releases the clamp to let go of the mobile goal.
         */
        void Raise();

        /**
         * @brief Checks if the clamp is currently engaged.
         * 
         * @return True if the clamp is engaged, false otherwise.
         */
        bool GetIsLowered() const;

    private:
        bool isLowered; ///< Indicates whether the clamp is currently engaged.
};

#endif