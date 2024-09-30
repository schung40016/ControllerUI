#pragma once

#include "pch.h"
#include "Debugger.h"

Debugger::Debugger()
{
	resourceManager = GameObjectManager::GetInstance();
}

Debugger::Debugger(float inp_size, std::string inp_debuggerName, std::string inp_objectFocusName, DirectX::SimpleMath::Vector2 inp_position)
{
	resourceManager = GameObjectManager::GetInstance();
	sDebuggerName = inp_debuggerName;
	fSizeMultiplier = inp_size;
	sObjectFocusName = inp_objectFocusName;

	std::string sDebuggerUIName = sDebuggerName + "_DebuggerUI";

	GameObject parentObj = GameObject(sDebuggerName, inp_position, fSizeMultiplier);
	GameObject& tempDebuggerObj = resourceManager->GetGameObj(sDebuggerName);


	tVelocity = Text(sDebuggerName + "_velocity", DirectX::Colors::Black, "Velocity: ", tempDebuggerObj, 0.f, 0.f);
	tAcceleration = Text(sDebuggerName + "_acceleration", DirectX::Colors::Black, "Acceleration: ", tempDebuggerObj, 0.f, 50.f);
	tPosition = Text(sDebuggerName + "_position", DirectX::Colors::Black, "Position: ", tempDebuggerObj, 0.f, 100.f);

	tVelocityNum = Text(sDebuggerName + "_velocity_num", DirectX::Colors::Black, "0.0", tempDebuggerObj, 400.f, 0.f);
	tAccelerationNum = Text(sDebuggerName + "_acceleration_num", DirectX::Colors::Black, "0.0", tempDebuggerObj, 400.f, 50.f);
	tPositionNum = Text(sDebuggerName + "_position_num", DirectX::Colors::Black, "{0.0, 0.0}", tempDebuggerObj, 400.f, 100.f);

	DebuggerUI debuggerUI = DebuggerUI(sDebuggerName, sObjectFocusName);
	resourceManager->AddDebuggerUI(sDebuggerUIName, debuggerUI);
	tempDebuggerObj.SetComponents({
		&resourceManager->GetDebuggerUI(sDebuggerUIName)
		});
}
