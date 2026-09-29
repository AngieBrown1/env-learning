#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

int main() {
    bn::core::init();

    bn::backdrop::set_color(bn::color(20, 20, 30));

    auto dot = bn::sprite_items::bun.create_sprite(0, 0);

    bn::fixed speed = 1.5;

    bn::fixed dy = 0;
    bn::fixed gravity = 0.5;

    bn::fixed jump_strength = 1.3;

    while(true) {
        if(bn::keypad::left_held()) {
            dot.set_x(dot.x() - speed);
        }
        if(bn::keypad::right_held()) {
            dot.set_x(dot.x() + speed);
        }

        bool isCharging = true;
        double charge;
        if(bn::keypad::a_held() && !isCharging){
            isCharging = true;
            charge = 0;
        }
        if(bn::keypad::a_held() && isCharging){
            charge += 0.3;
        }
        if(bn::keypad::a_released() && isCharging){
            isCharging = false;
            jump_strength = charge;
            dy -= jump_strength;
        }
        else if (bn::keypad::a_pressed()) {
            isCharging = false;
            dy -= jump_strength;    
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);

        if(dot.y() > FLOOR) {
            dot.set_y(FLOOR);
            dy = 0;
        }
        bn::core::update();

      

    }
}