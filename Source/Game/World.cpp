#include "pch.h"
#include "World.h"

World::World()
{
}

void World::Initialize()
{
    editor.Initialize();
}

void World::Update(float elapsedTime)
{
	editor.Update();
}

/*
SPRITE INFORMATION

{ left, top, right, bottom}

IDLE:
    RECT rectIdle = { 100, 400, 250, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 76.f, 110.f };
    spriteIdle.sourceRect = rectIdle;


JUMP:
    RECT rectJump = { 170, 725, 360, 1200 };
    Sprite spriteJump;
    spriteJump.sName = jumpSpriteName + "_1";
    spriteJump.origin = { 100.f, 115.f };
    spriteJump.sourceRect = rectJump;

RUN:
    RECT rectIdle = { 375, 400, 550, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 90.f, 110.f };
    spriteIdle.sourceRect = rectIdle;

    RECT rectIdle = { 555, 400, 695, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 70.f, 110.f };
    spriteIdle.sourceRect = rectIdle;

    RECT rectIdle = { 700, 400, 850, 600 };
    Sprite spriteIdle;
    spriteIdle.sName = idleSpriteName + "_1";
    spriteIdle.origin = { 75.f, 110.f };
    spriteIdle.sourceRect = rectIdle;
*/