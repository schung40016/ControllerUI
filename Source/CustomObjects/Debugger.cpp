#include "pch.h"
#include "Debugger.h"
#include "Source/Managers/GameObjectManager.h"
#include "Source/Components/DebuggerUI.h"
#include "Source/Constants/DefaultValues.h"

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
	GameObject& tempDebuggerObj = resourceManager->Get<GameObject>(sDebuggerName);
	GameObject& refPlayerObj = resourceManager->Get<GameObject>("player");


	tVelocity = Text(sDebuggerName + "_velocity", DirectX::Colors::Black, "Velocity: ", tempDebuggerObj, 0.f, 400.f, true, DefaultValues::Z_GUI);
	tAcceleration = Text(sDebuggerName + "_acceleration", DirectX::Colors::Black, "Acceleration: ", tempDebuggerObj, 0.f, 350.f, true, DefaultValues::Z_GUI);
	tPosition = Text(sDebuggerName + "_position", DirectX::Colors::Black, "Position: ", tempDebuggerObj, 0.f, 300.f, true, DefaultValues::Z_GUI);
	tDisplacement = Text(sDebuggerName + "_displacement", DirectX::Colors::Black, "Displacement: ", tempDebuggerObj, 0.f, 250.f, true, DefaultValues::Z_GUI);

	tVelocityNum = Text(sDebuggerName + "_velocity_num", DirectX::Colors::Black, "0.0", tempDebuggerObj, 500.f, 400.f, true, DefaultValues::Z_GUI);
	tAccelerationNum = Text(sDebuggerName + "_acceleration_num", DirectX::Colors::Black, "0.0", tempDebuggerObj, 500.f, 350.f, true, DefaultValues::Z_GUI);
	tPositionNum = Text(sDebuggerName + "_position_num", DirectX::Colors::Black, "{0.0, 0.0}", tempDebuggerObj, 500.f, 300.f, true, DefaultValues::Z_GUI);
	tDisplacementNum = Text(sDebuggerName + "_displacement_num", DirectX::Colors::Black, "{0.0, 0.0}", tempDebuggerObj, 500.f, 250.f, true, DefaultValues::Z_GUI);

	tFrameDesc1 = Text(sDebuggerName + "_frame_desc_1", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 200.f, true, DefaultValues::Z_GUI);
	tFrameDesc2 = Text(sDebuggerName + "_frame_desc_2", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 150.f, true, DefaultValues::Z_GUI);
	tFrameDesc3 = Text(sDebuggerName + "_frame_desc_3", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 100.f, true, DefaultValues::Z_GUI);
	tFrameDesc4 = Text(sDebuggerName + "_frame_desc_4", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 50.f, true, DefaultValues::Z_GUI);
	tFrameDesc5 = Text(sDebuggerName + "_frame_desc_5", DirectX::Colors::Black, "Frame #: ", tempDebuggerObj, 300.f, 0.f, true, DefaultValues::Z_GUI);

	lnVelocity = Line(sDebuggerName + "_VelocityLine", DirectX::Colors::Red, refPlayerObj, { 0.f, 0.f }, 1.f);

	DebuggerUI debuggerUI = DebuggerUI(sDebuggerName, sObjectFocusName);
	resourceManager->Add<DebuggerUI>(sDebuggerUIName, debuggerUI);
	tempDebuggerObj.SetComponents({
		&resourceManager->Get<DebuggerUI>(sDebuggerUIName)
	});
}
