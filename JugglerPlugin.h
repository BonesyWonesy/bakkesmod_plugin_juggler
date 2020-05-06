#pragma once
#include <memory>
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "Juggler.h"

/**
	The base plugin logic for bindings to game events to be used with the Juggler module.
*/
class JugglerPlugin : public BakkesMod::Plugin::BakkesModPlugin
{

public:
	JugglerPlugin();
	~JugglerPlugin();

	/// <summary>
	/// Inhereted from BakkesModPlugin
	/// </summary>
	virtual void onLoad();

	/// <summary>
	/// Inhereted from BakkesModPlugin
	/// </summary>
	virtual void onUnload();

private:


	void OnFreeplayLoad(std::string eventName);
	void OnFreeplayDestroy(std::string eventName);
	void OnBallHitGround(std::string eventName);
	void OnCarHitBall(std::string eventName);
	void OnPauseMenu(std::string eventName);
	void OnUnpause(std::string eventName);

	virtual void Render(CanvasWrapper canvas);

	// Variables for standard plugin options:
	// - enabled
	// - showLogs
	// - saveSettings
	// 
	std::shared_ptr<bool> m_pluginEnabled;

	Juggler m_juggler;
	std::shared_ptr<int> m_jugglerPosX;
	std::shared_ptr<int> m_jugglerPosY;

	bool m_loaded;
	bool m_registeredRender;

	// Inhereted objects:
	// std::shared_ptr<GameWrapper> gameWrapper;
	// std::shared_ptr<CVarManagerWrapper> cvarManager;
};