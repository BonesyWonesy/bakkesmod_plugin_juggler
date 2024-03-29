#include "Juggler.h"
#include "HelperFunctions.h"

Juggler::Juggler()
  : m_totalAttempts(0),
  m_totalHits(0),
  m_highestHits(0),
  m_secondsInAir(0),
  m_highestSecondsInAir(0),
  m_lastSecondsInAir(0),
  m_lastTotalHits(0),
  m_averageSecondsInAir(0),
  m_ballIsAirborne(false),
  m_cumulativeAirTimes(0) {
}

Juggler::~Juggler() {
  this->OnDestroy();
}

void Juggler::OnLoad() {
}

void Juggler::OnDestroy() {
  m_timer.Stop();
}

void Juggler::HitBall() {
  if (!m_timer.IsRunning()) {
    m_timer.Start();
  }

  m_ballIsAirborne = true;
  m_totalHits++;

  if (m_totalHits > m_highestHits) {
    m_highestHits = m_totalHits;
  }
}

void Juggler::Reset() {
  if (m_totalHits != m_lastTotalHits && m_totalHits != 0) {
    m_lastTotalHits = m_totalHits;
  }

  m_secondsInAir = m_timer.ElapsedSeconds();

  if (m_secondsInAir != m_lastSecondsInAir && m_secondsInAir != 0) {
    m_lastSecondsInAir = m_secondsInAir;

    if (m_secondsInAir > m_highestSecondsInAir) {
      m_highestSecondsInAir = m_secondsInAir;
    }

    ++m_totalAttempts;
    m_cumulativeAirTimes += m_secondsInAir;
    m_averageSecondsInAir = m_cumulativeAirTimes / m_totalAttempts;
  }

  if (m_totalHits != 0) {
    m_totalHits = 0;
  }

  if (m_secondsInAir != 0) {
    m_secondsInAir = 0;
  }

  m_ballIsAirborne = false;
  m_timer.Stop();
}

void Juggler::Pause() {
  if (m_ballIsAirborne) {
    m_timer.Pause();
  }
}

void Juggler::Unpause() {
  if (m_ballIsAirborne) {
    m_timer.Start();
  }
}

void Juggler::ResetHighestHits() {
  m_highestHits = 0;
}

void Juggler::ResetHighestAirTime() {
  m_highestSecondsInAir = 0;
}

void Juggler::ResetAverageAirTime() {
  m_cumulativeAirTimes = 0;
}

void Juggler::ResetAll() {
  m_totalAttempts = 0;
  m_totalHits = 0;
  m_highestHits = 0;
  m_secondsInAir = 0;
  m_highestSecondsInAir = 0;
  m_lastSecondsInAir = 0;
  m_lastTotalHits = 0;
  m_averageSecondsInAir = 0;
  m_cumulativeAirTimes = 0;
}

void Juggler::Render(CanvasWrapper& canvas, std::shared_ptr<GameWrapper>  gameWrapper, int xPos, int yPos) {

  auto screenSize = canvas.GetSize();

  Vector2 drawPosition = { xPos, yPos };
  canvas.SetPosition(drawPosition);
  canvas.SetColor(255, 255, 255, 255);

  canvas.DrawString(std::string("Juggle Count:"), 2.5f, 2.5f);

  drawPosition.Y += 38;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Current: ") + to_string(m_totalHits, 0), 2, 2);

  drawPosition.Y += 30;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Last: ") + to_string(m_lastTotalHits, 0), 2, 2);

  drawPosition.Y += 30;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Best: ") + to_string(m_highestHits, 0), 2, 2);

  drawPosition.Y += 44;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Ball Air Time:"), 2.5f, 2.5f);

  drawPosition.Y += 38;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Current: ") + to_string(m_timer.ElapsedSeconds(), 2), 2, 2);

  drawPosition.Y += 30;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Last: ") + to_string(m_lastSecondsInAir, 2), 2, 2);

  drawPosition.Y += 30;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Best: ") + to_string(m_highestSecondsInAir, 2), 2, 2);

  drawPosition.Y += 30;
  canvas.SetPosition(drawPosition);
  canvas.DrawString(std::string("Avg: ") + to_string(m_averageSecondsInAir, 2), 2, 2);
}