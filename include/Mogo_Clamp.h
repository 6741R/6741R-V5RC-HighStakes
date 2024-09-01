#pragma once
#ifndef MOGO_CLAMP_H
#define MOGO_CLAMP_H

/**
 * @class Mogo_Clamp
 * @brief Controls the clamping mechanism of the mobile goal (mogo) clamp.
 */
class Mogo_Clamp {

    public:

        /**
         * @brief Constructor for Mogo_Clamp.
         * Initializes the clamp to an unclamped state.
         */
        Mogo_Clamp();

        /**
         * @brief Engages the clamp to hold the mobile goal.
         */
        void Clamp();

        /**
         * @brief Releases the clamp to let go of the mobile goal.
         */
        void Unclamp();

        /**
         * @brief Checks if the clamp is currently engaged.
         * 
         * @return True if the clamp is engaged, false otherwise.
         */
        bool GetIsClamped() const;

    private:
        bool isClamped; ///< Indicates whether the clamp is currently engaged.
};

#endif