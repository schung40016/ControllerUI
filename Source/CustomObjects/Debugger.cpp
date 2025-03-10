#include "pch.h"
#include "Debugger.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Components/DebuggerUI.h"

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
	GameObject& refPlayerObj = resourceManager->GetGameObj("player");


	tVelocity = Text(sDebuggerName + "_velocity", DirectX::Colors::Black, "Velocity: ", tempDebuggerObj, 0.f, 400.f);
	tAcceleration = Text(sDebuggerName + "_acceleration", DirectX::Colors::Black, "Acceleration: ", tempDebuggerObj, 0.f, 350.f);
	tPosition = Text(sDebuggerName + "_position", DirectX::Colors::Black, "Position: ", tempDebuggerObj, 0.f, 300.f);
	tDisplacement = Text(sDebuggerName + "_displacement", DirectX::Colors::Black, "Displacement: ", tempDebuggerObj, 0.f, 250.f);

	tVelocityNum = Text(sDebuggerName + "_velocity_num", DirectX::Colors::Black, "0.0", tempDebuggerObj, 500.f, 400.f);
	tAccelerationNum = Text(sDebuggerName + "_acceleration_num", DirectX::Colors::Black, "0.0", tempDebuggerObj, 500.f, 350.f);
	tPositionNum = Text(sDebuggerName + "_position_num", DirectX::Colors::Black, "{0.0, 0.0}", tempDebuggerObj, 500.f, 300.f);
	tDisplacementNum = Text(sDebuggerName + "_displacement_num", DirectX::Colors::Black, "{0.0, 0.0}", tempDebuggerObj, 500.f, 250.f);

	tFrameDesc1 = Text(sDebuggerName + "_frame_desc_1", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 200.f);
	tFrameDesc2 = Text(sDebuggerName + "_frame_desc_2", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 150.f);
	tFrameDesc3 = Text(sDebuggerName + "_frame_desc_3", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 100.f);
	tFrameDesc4 = Text(sDebuggerName + "_frame_desc_4", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 50.f);
	tFrameDesc5 = Text(sDebuggerName + "_frame_desc_5", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 0.f);

	lnVelocity = Line(sDebuggerName + "_VelocityLine", DirectX::Colors::Red, refPlayerObj, { 0.f, 0.f }, 1.f);

	DebuggerUI debuggerUI = DebuggerUI(sDebuggerName, sObjectFocusName);
	resourceManager->AddDebuggerUI(sDebuggerUIName, debuggerUI);
	tempDebuggerObj.SetComponents({
		&resourceManager->GetDebuggerUI(sDebuggerUIName)
	});
}
