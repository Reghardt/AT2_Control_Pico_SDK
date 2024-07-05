#include "FrameManager.h"

FrameManager::FrameManager(SH1106 *oled)
{
    this->frame = NULL;
    this->oled = oled;
}

FrameManager::~FrameManager()
{
}

void FrameManager::begin()
{

    gpio_set_function(BUTTON_0, GPIO_FUNC_SIO);
    gpio_set_function(BUTTON_1, GPIO_FUNC_SIO);
    gpio_set_function(BUTTON_2, GPIO_FUNC_SIO);
    gpio_set_function(BUTTON_3, GPIO_FUNC_SIO);
    gpio_set_dir(BUTTON_0, GPIO_IN);
    gpio_set_dir(BUTTON_1, GPIO_IN);
    gpio_set_dir(BUTTON_2, GPIO_IN);
    gpio_set_dir(BUTTON_3, GPIO_IN);

    lastPress = time_us_32();
}

void FrameManager::setFrame(Frame *frame)
{
    if (this->frame != NULL)
    {
        delete this->frame;
    }

    this->frame = frame;
    this->frame->render();
}

void FrameManager::tick()
{
    // frame->update();

    if (shouldUpdate)
    {
        frame->render();
        shouldUpdate = false;
        return;
    }
    uint32_t currentTime = time_us_32();
    if (currentTime - lastPress >= 400000) // 0.4 seconds
    {
        if (gpio_get(BUTTON_0) == true)
        {
            printf("Button 0 pressed\n");
            frame->button0();
            lastPress = currentTime;
        }
        else if (gpio_get(BUTTON_1) == true)
        {
            printf("Button 1 pressed\n");
            frame->button1();
            lastPress = currentTime;
        }
        else if (gpio_get(BUTTON_2) == true)
        {
            printf("Button 2 pressed\n");
            frame->button2();
            lastPress = currentTime;
        }
        else if (gpio_get(BUTTON_3) == true)
        {
            printf("Button 3 pressed\n");
            frame->button3();
            lastPress = currentTime;
        }
    }
}

void FrameManager::update()
{
    // frame->update();
    shouldUpdate = true;
}