#include "pch.h"
#include "Controller.h"

Controller::Controller(GameObject& inp_parentObj)
{
    parentObj = std::shared_ptr<GameObject>(&inp_parentObj, [](GameObject*) {});
   
    //gameObjBank["Controller"] = GameObject({ (horizontal / 10.f), (vertical / 9.0f) }, 2500.f);

    controllerTitle = Text(DirectX::Colors::Black, "ControllerUI", *parentObj, 0.f, -250.f);
    connectionTitle = Text(DirectX::Colors::Black, "Controller Connection: ", *parentObj, -50.f, 250.f);
    connectionStatus = Text(DirectX::Colors::Black, "Connected", *parentObj, 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    gamePad = Image(DirectX::Colors::White, ".\\Images\\gamepad.png", EnumData::Descriptors::Controller, *parentObj, 0.f, 0.f, 1.f);   // xbox controller
    imgLeftTrigger = Image(DirectX::Colors::White, ".\\Images\\LeftTrigger.png", EnumData::Descriptors::LeftTrigger, *parentObj, -290.f, -140.f, 1.f);    // left trigger.
    imgRightTrigger = Image(DirectX::Colors::White, ".\\Images\\RightTrigger.png", EnumData::Descriptors::RightTrigger, *parentObj, 290.f, -140.f, 1.f);  // right trigger.

    a = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 159.f, -38.f, 40.f, 40.f); // a
    b = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 199.f, -80.f, 40.f, 40.f); // b
    x = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 119.f, -80.f, 40.f, 40.f); // x
    y = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 159.f, -120.f, 40.f, 40.f);    // y

    Triangle start = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 51.f, -80.f, 40.f, 40.f);  // start
    Triangle view = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -39.f, -80.f, 40.f, 40.f);  // view
    Triangle dPadUp = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -72.f, -20.f, 40.f, 40.f); // dpadup
    Triangle dPadDown = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -72.f, 50.f, 40.f, 40.f);   // dpaddown
    Triangle dPadLeft = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -109.f, 15.f, 40.f, 40.f);  // dpadright
    Triangle dPadRight = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -39.f, 15.f, 40.f, 40.f);  // dpadlefft
    Triangle leftShoulder = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -149.f, -180.f, 40.f, 40.f); // left shoulder
    Triangle rightShoulder = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 151.f, -180.f, 40.f, 40.f);    // right shoulder
    Triangle leftTrigger = Triangle(DirectX::Colors::HotPink, imgLeftTrigger, 1.f, 1.f, 10.f, 40.f, 40.f);  // left trigger
    Triangle righTrigger = Triangle(DirectX::Colors::HotPink, imgRightTrigger, 1.f, 1.f, 10.f, 40.f, 40.f);    // right trigger
    Triangle leftStick = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, -147.f, -80.f, 40.f, 40.f);    // left stick
    Triangle rightstick = Triangle(DirectX::Colors::HotPink, gamePad, 1.f, 83.f, 15.f, 40.f, 40.f);  // right stick
    
    Line leftStickDir = Line(DirectX::Colors::HotPink, gamePad, { -148.f, -78.f }, 1.f); // left stick direction
    Line rightStickDir = Line(DirectX::Colors::HotPink, gamePad, { 80.f, 15.f }, 1.f);   // right stick direction
}

void Controller::Update(float deltaTime)
{
    connectionStatus.SetText(inputManager->isConnected ? "On" : "Off");

    a.SetDisplay(true);
    b.SetDisplay(inputManager->b);
    x.SetDisplay(inputManager->x);
    y.SetDisplay(inputManager->y);
    start.SetDisplay(inputManager->start);
    view.SetDisplay(inputManager->view);

    dPadUp.SetDisplay(inputManager->dPadUp);
    dPadDown.SetDisplay(inputManager->dPadDown);
    dPadLeft.SetDisplay(inputManager->dPadLeft);
    dPadRight.SetDisplay(inputManager->dPadRight);

    leftShoulder.SetDisplay(inputManager->leftShoulder);
    rightShoulder.SetDisplay(inputManager->rightShoulder);
    leftTrigger.SetDisplay(inputManager->leftTrigger);
    righTrigger.SetDisplay(inputManager->rightTrigger);

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