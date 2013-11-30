#include "Enemy.h"

class RandomMove : public MovingStyle
{
    public:
        RandomMove(Enemy* enemy)
        {
            enemy_ = enemy;
            nextDirChange_ = al_get_time();
        }
        void move()
        {
            if (al_get_time() > nextDirChange_)
            {
                nextDirChange_ = al_get_time() + rand()%3+2;
                int newDirection = rand()%4;
                switch (newDirection)
                {
                    case 0: enemy_->setSpeed(-1, 0); break;
                    case 1: enemy_->setSpeed(0, -1); break;
                    case 2: enemy_->setSpeed(1, 0); break;
                    case 3: enemy_->setSpeed(0, 1); break;
                }
            }
        }
        void bounceFromWall(Side side)
        {
            int newDirection;
            do
            {
                newDirection = rand()%4;
            } while (side == newDirection);
            switch (newDirection)
            {
                case 0: enemy_->setSpeed(-1, 0); break;
                case 1: enemy_->setSpeed(0, -1); break;
                case 2: enemy_->setSpeed(1, 0); break;
                case 3: enemy_->setSpeed(0, 1); break;
            }
        }
    private:
        Enemy* enemy_;
        double nextDirChange_;
};

Enemy::Enemy(int x, int y, int type, ALLEGRO_BITMAP* enemies, ALLEGRO_BITMAP* shots)
{
    posx_ = x;
    posy_ = y;
    posz_ = 0;
    fstream enemyFile;
    enemyFile.open("files/enemies.txt", ios::in);
    for (int i = 0; i < type; i++)
    {
        string s;
        getline(enemyFile, s);
    }
    enemyFile >> x;
    enemyFile >> y;
    int bitmapWidth, bitmapHeight;
    enemyFile >> bitmapWidth;
    enemyFile >> bitmapHeight;
    picture_ = al_create_sub_bitmap(enemies, x, y, bitmapWidth, bitmapHeight);
    enemyFile >> width_;
    enemyFile >> height_;
    enemyFile >> pic_width_;
    enemyFile >> pic_height_;
    animationState_ = 0;
    enemyFile >> animationTime_;
    lastAnimation_ = al_get_time() - animationTime_;
    enemyFile >> step_;
    enemyFile >> hp_;
    lastHurt_ = al_get_time() - 0.5;
    enemyFile.close();
    movingStyle_ = new RandomMove(this);
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::dispatchEvent(ALLEGRO_EVENT* event)
{
    if (event->type == ALLEGRO_EVENT_TIMER)
    {
        if (animationTime_ < al_get_time() - lastAnimation_)
        {
            animationState_++;
            lastAnimation_ = al_get_time();
            if (animationState_ == 4)
                animationState_ = 0;
            if (animationState_ == 8)
                animationState_ = 4;
            if (speedx_ < 0 && animationState_ < 4)
                animationState_ += 4;
            if (speedx_ > 0 && animationState_ > 3)
                animationState_ -= 4;
        }
        move();
        draw();
    }
}

void Enemy::move()
{
    Element::move();
    movingStyle_->move();
}

void Enemy::draw()
{
    al_draw_filled_ellipse(posx_+width_/2, posy_- height_/2+5, width_/2, height_/2, al_map_rgba(0,0,0,50));
    if (lastHurt_ + 0.5 < al_get_time())
        al_draw_bitmap_region(picture_, animationState_*pic_width_, 0, pic_width_, pic_height_, posx_, posy_ - pic_height_ - posz_, 0);
    else
        al_draw_tinted_bitmap_region(picture_, al_map_rgba(200,100,100,100), animationState_*pic_width_, 0, pic_width_, pic_height_, posx_, posy_ - pic_height_ - posz_, 0);
}

void Enemy::bounceFromWall(int borders[4])
{
    if (posx_ < borders[LEFT])
        movingStyle_->bounceFromWall(LEFT);
    if (posx_ + width_ > borders[RIGHT])
        movingStyle_->bounceFromWall(RIGHT);
    if (posy_ > borders[DOWN])
       movingStyle_->bounceFromWall(DOWN);
    if (posy_ - height_ < borders[UP])
        movingStyle_->bounceFromWall(UP);
}

int Enemy::handleCollision(Shot* shot)
{
    hp_ -= shot->damage_;
    lastHurt_ = al_get_time();
    return hp_ <= 0;
}
