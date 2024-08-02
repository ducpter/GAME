#include "pipe.h"
#include "stdio.h"
#include <vector>
#include <cstdlib>

vector<position> posPipe;
vector<int> verticalSpeedPipe;
vector<int> verticalDirectionPipe;

bool pipe::init()
{
    posPipe.clear();
    verticalSpeedPipe.clear();
    verticalDirectionPipe.clear();

    for (signed char i = 0; i < TOTAL_PIPE; i++)
    {
        position temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
        int speed = (rand() % 2) ;
        verticalSpeedPipe.push_back(speed);
        int direction = (rand() % 2 == 0) ? 1 : -1;
        verticalDirectionPipe.push_back(direction);
    }

    if (isNULL())
    {
        if (Load("res/image/pipe.png", 1))
        {
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    free();
}

void pipe::render()
{
    for (signed char i = 0; i < TOTAL_PIPE; i++)
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -getWidth())
        {
            Render(posPipe[i].x, posPipe[i].y);
        }
        Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_SPACE, 180);
    }
}

void pipe::update()
{
    if (!die)
    {
        for (signed char i = 0; i < TOTAL_PIPE; i++)
        {
            if (posPipe[i].x < -getWidth())
            {
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE;
                //verticalSpeedPipe[i] = (rand() % 3) + 1;
                verticalSpeedPipe[i] = (rand() % 2);
                verticalDirectionPipe[i] = (rand() % 2 == 0) ? 1 : -1;
            }
            else
            {
                posPipe[i].x -= 3;
                posPipe[i].y += verticalSpeedPipe[i] * verticalDirectionPipe[i];
                if (posPipe[i].y < randMin || posPipe[i].y > randMax)
                {
                    verticalDirectionPipe[i] = -verticalDirectionPipe[i];
                }
            }
        }
    }
}
