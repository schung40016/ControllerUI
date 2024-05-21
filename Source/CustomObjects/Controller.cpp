#include "pch.h"
#include "Controller.h"

Controller::Controller()
{
    resourceManager = GameObjectManager::GetInstance();
}

Controller::Controller(float inp_size, std::string inp_controllerName, DirectX::SimpleMath::Vector2 inp_position)
{
    resourceManager = GameObjectManager::GetInstance();
    sControllerName = inp_controllerName;
    fSizeMultiplier = inp_size;

    GameObject parentObj = GameObject(sControllerName, { 150.f, 100.f }, fSizeMultiplier);
    GameObject& tempControllerObj = resourceManager->GetGameObj(sControllerName);

    controllerTitle = Text("controllerTitle", DirectX::Colors::Black, "ControllerUI", tempControllerObj, 0.f, -250.f);
    connectionTitle = Text("connectionTitle", DirectX::Colors::Black, "Controller Connection: ", tempControllerObj, -50.f, 250.f);
    connectionStatus = Text("connectionStatus", DirectX::Colors::Black, "Connected", tempControllerObj, 300.f, 250.f);

    // Create a higher tier object to act as the parent for all these objects.
    gamePad = Image("gamePad", DirectX::Colors::White, ".\\Images\\gamepad.png", EnumData::Descriptors::Controller, tempControllerObj, 0.f, 0.f, 1.f);   // xbox controller
    imgLeftTrigger = Image("imgLeftTrigger", DirectX::Colors::White, ".\\Images\\LeftTrigger.png", EnumData::Descriptors::LeftTrigger, tempControllerObj, -290.f, -140.f, 1.f);    // left trigger.
    imgRightTrigger = Image("imgRightTrigger", DirectX::Colors::White, ".\\Images\\RightTrigger.png", EnumData::Descriptors::RightTrigger, tempControllerObj, 290.f, -140.f, 1.f);  // right trigger.

    Image& temp_gamePad = resourceManager->GetImgObj("gamePad");
    Image& temp_imgLeftTrigger = resourceManager->GetImgObj("imgLeftTrigger");
    Image& temp_imgRightTrigger = resourceManager->GetImgObj("imgRightTrigger");


    a = Triangle("a", DirectX::Colors::HotPink, temp_gamePad, 1.f, 159.f, -38.f, 40.f, 40.f); // a
    b = Triangle("b", DirectX::Colors::HotPink, temp_gamePad, 1.f, 199.f, -80.f, 40.f, 40.f); // b
    x = Triangle("x", DirectX::Colors::HotPink, temp_gamePad, 1.f, 119.f, -80.f, 40.f, 40.f); // x
    y = Triangle("y", DirectX::Colors::HotPink, temp_gamePad, 1.f, 159.f, -120.f, 40.f, 40.f);    // y

    Triangle start = Triangle("start", DirectX::Colors::HotPink, temp_gamePad, 1.f, 51.f, -80.f, 40.f, 40.f);  // start
    Triangle view = Triangle("view", DirectX::Colors::HotPink, temp_gamePad, 1.f, -39.f, -80.f, 40.f, 40.f);  // view
    Triangle dPadUp = Triangle("dPadUp", DirectX::Colors::HotPink, temp_gamePad, 1.f, -72.f, -20.f, 40.f, 40.f); // dpadup
    Triangle dPadDown = Triangle("dPadDown", DirectX::Colors::HotPink, temp_gamePad, 1.f, -72.f, 50.f, 40.f, 40.f);   // dpaddown
    Triangle dPadLeft = Triangle("dPadLeft", DirectX::Colors::HotPink, temp_gamePad, 1.f, -109.f, 15.f, 40.f, 40.f);  // dpadright
    Triangle dPadRight = Triangle("dPadRight", DirectX::Colors::HotPink, temp_gamePad, 1.f, -39.f, 15.f, 40.f, 40.f);  // dpadlefft
    Triangle leftShoulder = Triangle("leftShoulder", DirectX::Colors::HotPink, temp_gamePad, 1.f, -149.f, -180.f, 40.f, 40.f); // left shoulder
    Triangle rightShoulder = Triangle("rightShoulder", DirectX::Colors::HotPink, temp_gamePad, 1.f, 151.f, -180.f, 40.f, 40.f);    // right shoulder
    Triangle leftTrigger = Triangle("leftTrigger", DirectX::Colors::HotPink, temp_imgLeftTrigger, 1.f, 1.f, 10.f, 40.f, 40.f);  // left trigger
    Triangle righTrigger = Triangle("rightTrigger", DirectX::Colors::HotPink, temp_imgRightTrigger, 1.f, 1.f, 10.f, 40.f, 40.f);    // right trigger
    Triangle leftStick = Triangle("leftStick", DirectX::Colors::HotPink, temp_gamePad, 1.f, -147.f, -80.f, 40.f, 40.f);    // left stick
    Triangle rightstick = Triangle("rightStick", DirectX::Colors::HotPink, temp_gamePad, 1.f, 83.f, 15.f, 40.f, 40.f);  // right stick
    
    Line leftStickDir = Line("leftStickDir", DirectX::Colors::HotPink, temp_gamePad, {-148.f, -78.f}, 1.f); // left stick direction
    Line rightStickDir = Line("rightStickDir", DirectX::Colors::HotPink, temp_gamePad, {80.f, 15.f}, 1.f);   // right stick direction

    // Create compmonent.
    std::string controllerUIName = inp_controllerName + "ControllerUI";

    ControllerUI controller_controllerUI = ControllerUI();
    resourceManager->AddControllerUI(controllerUIName, controller_controllerUI);
    tempControllerObj.SetComponents({
       &resourceManager->GetControllerUI(controllerUIName)
    });
}