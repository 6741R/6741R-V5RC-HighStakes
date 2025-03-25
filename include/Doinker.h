#pragma once
#ifndef DOINKER_H
#define DOINKER_H

/**
 * @class Mogo_Clamp
 * @brief Controls the clamping mechanism of the mobile goal (mogo) clamp.
 */
class Doinker {

    public:

        /**
         * @brief Constructor for Mogo_Clamp.
         * Initializes the clamp to an unclamped state.
         */
         Doinker();

        /**
         * @brief Engages the clamp to hold the mobile goal.
         */
        void Lower();

        /**
         * @brief Releases the clamp to let go of the mobile goal.
         */
        void Raise();

    private:
        bool isLowered; ///< Indicates whether the clamp is currently engaged.
};

#endif