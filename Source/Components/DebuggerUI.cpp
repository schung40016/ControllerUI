#include "pch.h"
#include "DebuggerUI.h"
#include "cmath"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Game/GameObject.h"
#include "Source/UI_Objects/Text.h"
#include "Source/UI_Objects/Line.h"
#include "Source/Managers/InputManager.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "sstream"

DebuggerUI::DebuggerUI()
{
    resourceManager = GameObjectManager::GetInstance();
}

DebuggerUI::DebuggerUI(std::string inp_parentObjName, std::string inp_objectFocusName)
{
    sParentObjName = inp_parentObjName;
    sObjectFocusName = inp_objectFocusName;
    resourceManager = GameObjectManager::GetInstance();
}

void DebuggerUI::Awake()
{
    inputManager = InputManager::GetInstance();
    GameObject& refPlayerObj = resourceManager->GetGameObj(sObjectFocusName);
    rb = refPlayerObj.GetComponent<RigidBody>();
    bc = refPlayerObj.GetComponent<BoxCollider>();

    for (int i = 0; i < 5; i++)
    {
        qFrameDesc.push("--");
    }

    std::unordered_map<std::string, Text>& refTextBank = resourceManager->GetTxtObjBank();

    refTextBank[sParentObjName + "_velocity_num"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_acceleration_num"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_position_num"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_displacement_num"].SetDisplay(bOn);

    refTextBank[sParentObjName + "_velocity"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_acceleration"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_position"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_displacement"].SetDisplay(bOn);

    refTextBank[sParentObjName + "_frame_desc_1"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_frame_desc_2"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_frame_desc_3"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_frame_desc_4"].SetDisplay(bOn);
    refTextBank[sParentObjName + "_frame_desc_5"].SetDisplay(bOn);
}

void DebuggerUI::Update(float deltaTime)
{
    std::unordered_map<std::string, Text> &refTextBank = resourceManager->GetTxtObjBank();
    Line& lnVelocity = resourceManager->GetLnObj(sParentObjName + "_VelocityLine");

    GameObject &refPlayerObj = resourceManager->GetGameObj(sObjectFocusName);
    const DirectX::SimpleMath::Vector2 playerPos = refPlayerObj.GetPositionActual();
    Text &velocityNum = refTextBank[sParentObjName + "_velocity_num"];
    Text &accelerationNum = refTextBank[sParentObjName + "_acceleration_num"];
    Text &positionNum = refTextBank[sParentObjName + "_position_num"];
    Text &displacementNum = refTextBank[sParentObjName + "_displacement_num"];
    DirectX::SimpleMath::Vector2 tempVelocity = { roundToDecimal(rb->GetVelocity().x), roundToDecimal(rb->GetVelocity().y) };
    DirectX::SimpleMath::Vector2 tempAcceleration = { roundToDecimal(rb->GetAcceleration().x), roundToDecimal(rb->GetAcceleration().y) };
    DirectX::SimpleMath::Vector2 tempDisplacement = { roundToDecimal(bc->GetDisplacement().x), roundToDecimal(bc->GetDisplacement().y) };

    std::string sTempVelocity = "{" + removeTrailingZeroes(tempVelocity.x) + ", " + removeTrailingZeroes(tempVelocity.y) + "}";
    std::string sTempAccelration = "{" + removeTrailingZeroes(tempAcceleration.x) + ", " + removeTrailingZeroes(tempAcceleration.y) + "}";
    std::string sTempPosition = "{" + removeTrailingZeroes(playerPos.x) + ", " + removeTrailingZeroes(playerPos.y) + "}";
    std::string sTempDisplacement = "{" + removeTrailingZeroes(tempDisplacement.x) + ", " + removeTrailingZeroes(tempDisplacement.y) + "}";

    if (frameCount % frameCaptureRate == 0)
    {
        updateFrameByFrameDebugger(refTextBank, sTempDisplacement, sTempAccelration);
    }

    velocityNum.SetText(sTempVelocity);
    accelerationNum.SetText(sTempAccelration);
    positionNum.SetText(sTempPosition);
    displacementNum.SetText(sTempDisplacement);

    lnVelocity.SetPoint2(tempVelocity.x * 10.f, tempVelocity.y * 10.f);

    frameCount++;
}

void DebuggerUI::updateFrameByFrameDebugger(std::unordered_map<std::string, Text>& refTextBank, std::string displacement, std::string acceleration)
{
    // Frame by frame text boxes.
    Text& frameDesc1 = refTextBank[sParentObjName + "_frame_desc_1"];
    Text& frameDesc2 = refTextBank[sParentObjName + "_frame_desc_2"];
    Text& frameDesc3 = refTextBank[sParentObjName + "_frame_desc_3"];
    Text& frameDesc4 = refTextBank[sParentObjName + "_frame_desc_4"];
    Text& frameDesc5 = refTextBank[sParentObjName + "_frame_desc_5"];

    frameDesc1.SetDisplay(bOn);
    frameDesc2.SetDisplay(bOn);
    frameDesc3.SetDisplay(bOn);
    frameDesc4.SetDisplay(bOn);
    frameDesc5.SetDisplay(bOn);

    // Pop a frame description.
    qFrameDesc.pop();

    // Create frame desc.
    std::string currentFrameDesc = "Frame #" + std::to_string(frameCount) + ": Dis - " + displacement + ", Acc - " + acceleration;

    // Add frame desc to q.
    qFrameDesc.push(currentFrameDesc);

    // Update frameDesc textboxes based on queue contents.

    std::queue<std::string> tempQueue = qFrameDesc;
    std::vector<std::string> tempVector;

    while (!tempQueue.empty())
    {
        tempVector.emplace_back(tempQueue.front());
        tempQueue.pop();
    }

    frameDesc1.SetText(tempVector[0]);
    frameDesc2.SetText(tempVector[1]);
    frameDesc3.SetText(tempVector[2]);
    frameDesc4.SetText(tempVector[3]);
    frameDesc5.SetText(tempVector[4]);
}

float DebuggerUI::roundToDecimal(float input, float upTo)
{
    float multiplyBy = std::pow(10, upTo);
    return std::round(input * multiplyBy) / multiplyBy;
}

std::string DebuggerUI::removeTrailingZeroes(float value) {
    std::ostringstream stream;
    stream << std::defaultfloat << value;
    return stream.str();
}