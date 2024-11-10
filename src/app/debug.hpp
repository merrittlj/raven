#ifndef APP_DEBUG_HPP
#define APP_DEBUG_HPP

namespace App
{
    class Debug_Controller
    {
        private:
            void SetCPU2GpioConfig();
            void BleDtbCfg();

        public:
            Debug_Controller();
            ~Debug_Controller();

            void Init();
            void EnableCPU2();
    }
}

#endif /* APP_DEBUG_HPP */
