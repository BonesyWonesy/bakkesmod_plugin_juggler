#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "Timer.h"

class Juggler
{
public:
  Juggler();
  ~Juggler();

  virtual void Render(CanvasWrapper& canvas, std::shared_ptr<GameWrapper>  gameWrapper, int xPos, int yPos);
  void OnLoad();
  void OnDestroy();

  void ResetHighestHits();
  void ResetHighestAirTime();
  void ResetAll();

  void HitBall();
  void Reset();
  void Pause();
  void Unpause();

private:
  unsigned m_totalAttempts;

  unsigned m_totalHits;
  unsigned m_highestHits;

  unsigned m_lastTotalHits;
  double m_lastSecondsInAir;

  double m_secondsInAir;
  double m_highestSecondsInAir;
  double m_averageSecondsInAir;

  Timer m_timer;
};

#pragma once
