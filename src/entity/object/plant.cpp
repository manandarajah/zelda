#include "plant.hpp"
#include "../item/rupee.hpp"
#include "../../audio/sound.hpp"

sf::SoundBuffer* Plant::CUT_SOUND;

void Plant::Load() {
    CUT_SOUND = Sound::Buffer("plant/cut.wav");
}

Plant::Plant(Sprite* sprite, float x, float y) :
        super(sprite, x, y)
{
    health_ = 1;
    type_ = PLANT;
    die_sound_ = CUT_SOUND;
}

void Plant::Dead() {
    if(rand() % 100 < 80)
        return;

    const vec2f& pos = center();
    level_->AddEntity(Rupee::Random(pos.x, pos.y));
}
