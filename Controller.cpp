#include "pch.h"
#include "Controller.h"

Controller::Controller(GameObject& inp_parentObj)
{
    parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
   
    //gameObjBank["Controller"] = GameObject({ (horizontal / 10.f), (vertical / 9.0f) }, 2500.f);

    controllerTitle = Text("controllerTitle", DirectX::Colors::Black, "ControllerUI", inp_parentObj, 0.f, -250.f);
    connectionTitle = Text("connectionTitle", DirectX::Colors::Black, "Controller Connection: ", inp_parentObj, -50.f, 250.f);
    connectionStatus = Text("connectionStatus", DirectX::Colors::Black, "Connected", inp_parentObj, 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    gamePad = Image("gamePad", DirectX::Colors::White, ".\\Images\\gamepad.png", EnumData::Descriptors::Controller, inp_parentObj, 0.f, 0.f, 1.f);   // xbox controller
    imgLeftTrigger = Image("imgLeftTrigger", DirectX::Colors::White, ".\\Images\\LeftTrigger.png", EnumData::Descriptors::LeftTrigger, inp_parentObj, -290.f, -140.f, 1.f);    // left trigger.
    imgRightTrigger = Image("imgRightTrigger", DirectX::Colors::White, ".\\Images\\RightTrigger.png", EnumData::Descriptors::RightTrigger, inp_parentObj, -290.f, -140.f, 1.f);  // right trigger.

    a = Triangle("a", DirectX::Colors::HotPink, gamePad, 1.f, 159.f, -38.f, 40.f, 40.f); // a
    b = Triangle("b", DirectX::Colors::HotPink, gamePad, 1.f, 199.f, -80.f, 40.f, 40.f); // b
    x = Triangle("x", DirectX::Colors::HotPink, gamePad, 1.f, 119.f, -80.f, 40.f, 40.f); // x
    y = Triangle("y", DirectX::Colors::HotPink, gamePad, 1.f, 159.f, -120.f, 40.f, 40.f);    // y

    Triangle start = Triangle("start", DirectX::Colors::HotPink, gamePad, 1.f, 51.f, -80.f, 40.f, 40.f);  // start
    Triangle view = Triangle("view", DirectX::Colors::HotPink, gamePad, 1.f, -39.f, -80.f, 40.f, 40.f);  // view
    Triangle dPadUp = Triangle("dPadUp", DirectX::Colors::HotPink, gamePad, 1.f, -72.f, -20.f, 40.f, 40.f); // dpadup
    Triangle dPadDown = Triangle("dPadDown", DirectX::Colors::HotPink, gamePad, 1.f, -72.f, 50.f, 40.f, 40.f);   // dpaddown
    Triangle dPadLeft = Triangle("dPadLeft", DirectX::Colors::HotPink, gamePad, 1.f, -109.f, 15.f, 40.f, 40.f);  // dpadright
    Triangle dPadRight = Triangle("dPadRight", DirectX::Colors::HotPink, gamePad, 1.f, -39.f, 15.f, 40.f, 40.f);  // dpadlefft
    Triangle leftShoulder = Triangle("leftShoulder", DirectX::Colors::HotPink, gamePad, 1.f, -149.f, -180.f, 40.f, 40.f); // left shoulder
    Triangle rightShoulder = Triangle("rightShoulder", DirectX::Colors::HotPink, gamePad, 1.f, 151.f, -180.f, 40.f, 40.f);    // right shoulder
    Triangle leftTrigger = Triangle("leftTrigger", DirectX::Colors::HotPink, imgLeftTrigger, 1.f, 1.f, 10.f, 40.f, 40.f);  // left trigger
    Triangle righTrigger = Triangle("rightTrigger", DirectX::Colors::HotPink, imgRightTrigger, 1.f, 1.f, 10.f, 40.f, 40.f);    // right trigger
    Triangle leftStick = Triangle("leftStick", DirectX::Colors::HotPink, gamePad, 1.f, -147.f, -80.f, 40.f, 40.f);    // left stick
    Triangle rightstick = Triangle("rightStick", DirectX::Colors::HotPink, gamePad, 1.f, 83.f, 15.f, 40.f, 40.f);  // right stick
    
    //Line leftStickDir = Line("leftStickDir", DirectX::Colors::HotPink, gamePad, {-148.f, -78.f}, 1.f); // left stick direction
    //Line rightStickDir = Line("rightStickDir", DirectX::Colors::HotPink, gamePad, {80.f, 15.f}, 1.f);   // right stick direction
}

void Controller::Update(float deltaTime)
{
    connectionStatus.SetText(inputManager->isConnected ? "On" : "Off");

    // Update resource data manager triangles not here.
    GameObjectManager* resourceManager = GameObjectManager::GetInstance();
    std::unordered_map<std::string, Triangle>& refTriangleBank = resourceManager->GetTriObjBank();

    refTriangleBank["a"].SetDisplay(inputManager->a);
    refTriangleBank["b"].SetDisplay(inputManager->b);
    refTriangleBank["x"].SetDisplay(inputManager->x);
    refTriangleBank["y"].SetDisplay(inputManager->y);
    refTriangleBank["start"].SetDisplay(inputManager->start);
    refTriangleBank["view"].SetDisplay(inputManager->view);

    refTriangleBank["dPadUp"].SetDisplay(inputManager->dPadUp);
    refTriangleBank["dPadDown"].SetDisplay(inputManager->dPadDown);
    refTriangleBank["dPadLeft"].SetDisplay(inputManager->dPadLeft);
    refTriangleBank["dPadRight"].SetDisplay(inputManager->dPadRight);

    refTriangleBank["leftShoulder"].SetDisplay(inputManager->leftShoulder);
    refTriangleBank["rightShoulder"].SetDisplay(inputManager->rightShoulder);
    refTriangleBank["leftStick"].SetDisplay(inputManager->leftTrigger);
    refTriangleBank["rightStick"].SetDisplay(inputManager->rightTrigger);

    leftStick.SetDisplay(inputManager->leftStick);
    rightStick.SetDisplay(inputManager->rightStick);

    leftStickDir.SetPoint2(inputManager->leftStickPos.x, inputManager->leftStickPos.y);
    rightStickDir.SetPoint2(inputManager->rightStickPos.x, inputManager->rightStickPos.y);
}

/*
    gameObjBank["Controller"] = GameObject({ (horizontal / 10.f), (vertical / 9.0f) }, 2500.f);

    txtObjBank["Title"] = Text(DirectX::Colors::Black, "ControllerUI", gameObjBank["Controller"], 0.f, -250.f);
    txtObjBank["Connection"] = Text(DirectX::Colors::Black, "Controller Connection: ", gameObjBank["Controller"], -50.f, 250.f);
    txtObjBank["Status"] = Text(DirectX::Colors::Black, "Connected", gameObjBank["Controller"], 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    imgObjBank["Gamepad"] = Image(DirectX::Colors::White, ".\\Images\\gamepad.png", EnumData::Descriptors::Controller, gameObjBank["Controller"], 0.f, 0.f, 1.f);
    imgObjBank["LeftTrigger"] = Image(DirectX::Colors::White, ".\\Images\\LeftTrigger.png", EnumData::Descriptors::LeftTrigger, gameObjBank["Controller"], -290.f, -140.f, 1.f);
    imgObjBank["RightTrigger"] = Image(DirectX::Colors::White, ".\\Images\\RightTrigger.png", EnumData::Descriptors::RightTrigger, gameObjBank["Controller"], 290.f, -140.f, 1.f);

    triObjBank["A"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 159.f, -38.f, 40.f, 40.f);
    triObjBank["B"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 199.f, -80.f, 40.f, 40.f);
    triObjBank["X"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 119.f, -80.f, 40.f, 40.f);
    triObjBank["Y"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 159.f, -120.f, 40.f, 40.f);

    triObjBank["Start"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 51.f, -80.f, 40.f, 40.f);
    triObjBank["View"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -39.f, -80.f, 40.f, 40.f);
    triObjBank["DPadUp"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -72.f, -20.f, 40.f, 40.f);
    triObjBank["DPadDown"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -72.f, 50.f, 40.f, 40.f);
    triObjBank["DPadLeft"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -109.f, 15.f, 40.f, 40.f);
    triObjBank["DPadRight"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -39.f, 15.f, 40.f, 40.f);
    triObjBank["LeftShoulder"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -149.f, -180.f, 40.f, 40.f);
    triObjBank["RightShoulder"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 151.f, -180.f, 40.f, 40.f);
    triObjBank["LeftTrigger"] = Triangle(DirectX::Colors::HotPink, imgObjBank["LeftTrigger"], 1.f, 1.f, 10.f, 40.f, 40.f);
    triObjBank["RightTrigger"] = Triangle(DirectX::Colors::HotPink, imgObjBank["RightTrigger"], 1.f, 1.f, 10.f, 40.f, 40.f);
    triObjBank["LeftStick"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, -147.f, -80.f, 40.f, 40.f);
    triObjBank["RightStick"] = Triangle(DirectX::Colors::HotPink, imgObjBank["Gamepad"], 1.f, 83.f, 15.f, 40.f, 40.f);

    lnObjBank["LeftStick"] = Line(DirectX::Colors::HotPink, imgObjBank["Gamepad"], {-148.f, -78.f}, 1.f);
    lnObjBank["RightStick"] = Line(DirectX::Colors::HotPink, imgObjBank["Gamepad"], { 80.f, 15.f }, 1.f);
*/