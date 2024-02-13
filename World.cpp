#include "pch.h"
#include "World.h"

World::World()
{
}

void World::Initialize()
{
    ground = GameObject({ 650.f, 800.f }, 1.f, {});
    groundShape = Quad(DirectX::Colors::DarkGray, ground, 1.f, 0, 0, 800.f, 200.f, true);

    // Create the player.
    player = GameObject({ 650.f, 650.f }, 1.f, {
        new PlayerController(player),
        new RigidBody(player, 10.f)
    });
    playerShape = Quad(DirectX::Colors::Aqua, player, 1.f, 0, 0, 50.f, 50.f, true);

    controller = GameObject({ 500.f, 500.f }, 1.f, {
        new Controller(controller)
    });          // this gets destroyed. We need to somehow keep it alive.

    std::cout << "hi";
}

//gameObjBank["Player"].SetComponents({
//    new PlayerController(gameObjBank["Player"]),
//    new RigidBody(gameObjBank["Player"], 10.f)
//    //Collider(gameObjBank["Player"], p2),  
//    //RigidBody(gameObjBank["Player"], {1, 0}, true, 10.f, 1.f),
//});

//shpObjBank.emplace_back(new Quad(DirectX::Colors::Aqua, gameObjBank["Player"], 1.f, 0, 0, 50.f, 50.f, true));

/* ask charles this:

    player.SetComponents({
        new PlayerController(player),
        new RigidBody(player, 10.f)
    });

    controller.SetComponents({
        new Controller(controller)
    });
*/