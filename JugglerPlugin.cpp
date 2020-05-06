#include "JugglerPlugin.h"

BAKKESMOD_PLUGIN(JugglerPlugin, "Juggler", "1.0", PLUGINTYPE_FREEPLAY | PLUGINTYPE_CUSTOM_TRAINING)

JugglerPlugin::JugglerPlugin() {
	m_loaded = false;
	m_registeredRender = false;
}

JugglerPlugin::~JugglerPlugin() {
}

void JugglerPlugin::onLoad() {
	m_pluginEnabled = make_shared<bool>(true);
	cvarManager->registerCvar("cl_juggler_plugin_enabled", "0", "Enable plugin", true, true, 0.f, true, 1.f, true).bindTo(m_pluginEnabled);

	m_jugglerPosX = make_shared<int>(0);
	m_jugglerPosY = make_shared<int>(0);
	cvarManager->registerCvar("cl_juggler_plugin_posx", "0", "Juggler Position X", true, true, 0, true, 10000).bindTo(m_jugglerPosX);
	cvarManager->registerCvar("cl_juggler_plugin_posy", "0", "Juggler Position Y", true, true, 0, true, 10000).bindTo(m_jugglerPosY);

	cvarManager->registerNotifier("JugglerResetHitCount", [this](std::vector<string> commands) {
		m_juggler.ResetHighestHits();
		}, "", 0);

	cvarManager->registerNotifier("JugglerResetAirTime", [this](std::vector<string> commands) {
		m_juggler.ResetHighestAirTime();
		}, "", 0);


	// Game is started
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Init", bind(&JugglerPlugin::OnFreeplayLoad, this, std::placeholders::_1));

	// Game is cleaning up
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", bind(&JugglerPlugin::OnFreeplayDestroy, this, std::placeholders::_1));

	// Ball hits ground
	gameWrapper->HookEvent("Function TAGame.Ball_TA.EventHitGround", bind(&JugglerPlugin::OnBallHitGround, this, std::placeholders::_1));

	// Car hits ball
	gameWrapper->HookEvent("Function TAGame.Car_TA.EventHitBall", bind(&JugglerPlugin::OnCarHitBall, this, std::placeholders::_1));

	// Pause menu
	gameWrapper->HookEvent("Function TAGame.PlayerController_TA.OnOpenPauseMenu", bind(&JugglerPlugin::OnPauseMenu, this, std::placeholders::_1));

	// On Unpause
	gameWrapper->HookEvent("Function ProjectX.GameInfo_X.RemovePauser", bind(&JugglerPlugin::OnUnpause, this, std::placeholders::_1));
}

void JugglerPlugin::OnCarHitBall(std::string eventName) {

	if (*m_pluginEnabled) {
		m_juggler.HitBall();
	}
}

void JugglerPlugin::OnBallHitGround(std::string eventName) {
	m_juggler.Reset();
}

void JugglerPlugin::OnPauseMenu(std::string eventName) {
	m_juggler.Pause();
}

void JugglerPlugin::OnUnpause(std::string eventName) {
	m_juggler.Unpause();
}

void JugglerPlugin::OnFreeplayLoad(std::string eventName) {
	if (m_registeredRender) {
		return;
	}

	m_juggler.OnLoad();
	m_registeredRender = true;
	gameWrapper->RegisterDrawable(std::bind(&JugglerPlugin::Render, this, std::placeholders::_1));
}

void JugglerPlugin::OnFreeplayDestroy(std::string eventName) {
	m_juggler.OnDestroy();
	m_registeredRender = false;
	gameWrapper->UnregisterDrawables();
}

/*
	Rendering
*/
void JugglerPlugin::Render(CanvasWrapper canvas)
{
	if (!gameWrapper->IsInGame() || (!gameWrapper->IsInFreeplay() && !gameWrapper->IsInCustomTraining())) {
		return;
	}

	if (*m_pluginEnabled) {
		m_juggler.Render(canvas, gameWrapper, *m_jugglerPosX, *m_jugglerPosY);
	}
}

/*
	Clean up everything on unload
*/
void JugglerPlugin::onUnload()
{
	m_juggler.OnDestroy();
	m_registeredRender = false;
	m_loaded = false;
}

