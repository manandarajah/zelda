#include "chase_evade.hpp"

ChaseEvade::ChaseEvade(Mob* mob) :
        super(mob),
        direction_(Dir::random()),
        wander_(mob),
        period_duration_(50),
        current_duration_(0),
        alert(false)
{}

bool ChaseEvade::Detected(Entity* destiny_entity){
    float diffX = mob_->position().x-destiny_entity->position().x;
    float diffY = mob_->position().y-destiny_entity->position().y;
    float diffXaux = (diffX>0)?diffX:-diffX;
    float diffYaux = (diffY>0)?diffY:-diffY;

    const Dir aux = mob_->facing();
    if (aux.vector().x==1 && diffYaux > diffXaux && diffX < 0)
        return true;
    else if (aux.vector().x==-1 && diffYaux > diffXaux && diffX > 0)
        return true;
    else if (aux.vector().y==-1 && diffXaux > diffYaux && diffY > 0)
        return true;
    else if (aux.vector().y==1 && diffXaux > diffYaux && diffY < 0)
        return true;
    else
        return false;
}

bool ChaseEvade::Lost(Entity* destiny_entity){
    float diffX = mob_->position().x-destiny_entity->position().x;
    float diffY = mob_->position().y-destiny_entity->position().y;

    const Dir aux = mob_->facing();
    if (aux.vector().x==1 && diffX > 0)
        return true;
    else if (aux.vector().x==-1 && diffX < 0)
        return true;
    else if (aux.vector().y==-1 && diffY < 0)
        return true;
    else if (aux.vector().y==1 && diffY > 0)
        return true;
    else
        return false;
}

Dir ChaseEvade::Contrary(Dir aux){
    if (aux.vector().x==1)
        return Dir::LEFT;
    else if (aux.vector().x==-1)
        return Dir::RIGHT;
    else if (aux.vector().y==1)
        return Dir::UP;
    else return Dir::DOWN;
}

Dir ChaseEvade::Evade(Dir aux){
    if (aux.vector().x==1)
        return Dir::UP;
    else if (aux.vector().x==-1)
        return Dir::DOWN;
    else if (aux.vector().y==1)
        return Dir::LEFT;
    else return Dir::RIGHT;
}

void ChaseEvade::Update(double delta) {
    Entity* destiny_entity = mob_->SeekPlayer();
    float diffX = mob_->position().x-destiny_entity->position().x;
    float diffY = mob_->position().y-destiny_entity->position().y;
    float diffXaux = (diffX>0)?diffX:-diffX;
    float diffYaux = (diffY>0)?diffY:-diffY;

    if (mob_->Distance(destiny_entity) > 150 || (!alert && !Detected(destiny_entity)) || (alert && Lost(destiny_entity))){
        alert = false;
        wander_.Update(delta);
    }
    else{
        alert = true;
        if (current_duration_%10>0)
            --current_duration_;
        else if (current_duration_>0){
            if (diffYaux < mob_->height())
                direction_ = (diffX>0)?Dir::LEFT:Dir::RIGHT;
            else if (diffXaux < mob_->width())
                direction_ = (diffY>0)?Dir::UP:Dir::DOWN;
            --current_duration_;
        }
        else{
            if (diffYaux < mob_->height())
                direction_ = (diffX>0)?Dir::LEFT:Dir::RIGHT;
            else if (diffXaux < mob_->width())
                direction_ = (diffY>0)?Dir::UP:Dir::DOWN;
            else if (diffYaux > diffXaux/3.0f)
                direction_ = (diffY>0)?Dir::UP:Dir::DOWN;
            else
                direction_ = (diffX>0)?Dir::LEFT:Dir::RIGHT;
            current_duration_ = period_duration_;
        }

        if (!mob_->Move(direction_,delta)){
            //mob_->Move(Contrary(direction_),delta);
            mob_->Move(Evade(direction_),delta);
        }
    }
}

void ChaseEvade::Debug() const {

}
