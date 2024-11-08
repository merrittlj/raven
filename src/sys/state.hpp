#ifndef STATE_HPP
#define STATE_HPP


namespace Sys
{
    class State
    {
        private:
            /* Component index of the Red LED */
            uint32_t LED_Red_Index;
            /* Component index of the Green LED */
            uint32_t LED_Green_Index;
            /* Component index of the Blue LED */
            uint32_t LED_Blue_Index;
        public:
            State();
            ~State();

            void Register_LED_Red(uint32_t pIndex);
            uint32_t Fetch_LED_Red();

            void Register_LED_Green(uint32_t pIndex);
            uint32_t Fetch_LED_Green();

            void Register_LED_Blue(uint32_t pIndex);
            uint32_t Fetch_LED_Blue();
    };
}


#endif /* STATE_HPP */
