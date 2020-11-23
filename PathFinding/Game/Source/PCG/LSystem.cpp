#include "LSystem.h"
#include <math.h>

void SierpinskiTriangle::NextGeneration()
{
	std::string newState = "";

	for (char ch : m_state)
	{
		if (ch == 'A')
			newState += "B-A-B";
		else if (ch == 'B')
			newState += "A+B+A";
		else
			newState += ch;
	}

	m_state = newState;

	++m_generation;
}

void SierpinskiTriangle::Draw(slth::IGraphics* pGraphics)
{
	slth::Vector2 currentPosition = { 0, 0 };
	float currentAngle = 0.f; // straight up?

	for (int i = 0; i < m_state.length(); ++i)
	{
		if (m_state[i] == 'A' || m_state[i] == 'B')
		{
			// draw line forward by kLineDistance
			// need a vector with magnitude kLineDistace that is angled by the currentAngle from where we are
			slth::Vector2 newPosition = currentPosition;
			newPosition.x = currentPosition.x + cos(currentAngle * 3.14159265f / 180.f) * m_lineDistance;
			newPosition.y = currentPosition.y + sin(currentAngle* 3.14159265f / 180.f) * m_lineDistance;

			pGraphics->DrawLine(currentPosition, newPosition, slth::Color::White());
			
			currentPosition = newPosition;
		}
		else if (m_state[i] == '+')
		{
			// turn left by kAngle
			currentAngle += kAngle;
		}
		else if (m_state[i] == '-')
		{
			// turn right by kAngle
			currentAngle -= kAngle;
		}
	}
	
}

void FractalLightning::NextGeneration(slth::Rng& rng)
{
	std::string newState = "";

	// stop if the branch has reached the ground
	if (m_currentPosition.m_position.y < m_endPosition.y)
	{
		for (char ch : m_state)
		{
			float diceRoll = rng.RandFloat();

			if (ch == 'L')
			{
				newState += "L";

				if (diceRoll < kBranchChance && m_numBranches < kMaxBranches)
				{
					newState += "[+B][-B]";
					++m_numBranches;
				}
				else if (diceRoll < kJitterChance) // jitter = change direction
				{
					if (rng.RandBool()) // random left / right direction
						newState += '-';
					else
						newState += '+';
				}
				else
				{
					newState += 'L';
				}
			}
			else if (ch == 'B')
			{
				if (diceRoll < kBranchChance && m_numBranches < kMaxBranches)
				{
					newState += "[+B][-B]";

				}
				else
				{
					newState += "+B-B";
				}
			}
			else
			{
				newState += ch;
			}
		}

		m_state = newState;

		++m_generation;
	}

	

}

void FractalLightning::CreateLineList(slth::Rng& rng)
{
	std::stack<Transform> transformList;
	
	for (int i = 0; i < m_state.length(); ++i)
	{
		if (m_state[i] == 'L' || m_state[i] == 'B')
		{
			// figure out end point
			Transform newState = m_currentPosition;

			slth::Color lineColor = slth::Color::White();
			float lineDistance = m_lineDistance;
			if (m_state[i] == 'B')
			{
				lineColor = slth::Color::MediumGray();
			}
			else
			{
				lineDistance *= 2.f;
			}

			newState.m_position.x = newState.m_position.x + cos(newState.m_angle * kPi / 180.f) * lineDistance;
			newState.m_position.y = newState.m_position.y + sin(newState.m_angle * kPi / 180.f) * lineDistance;

			m_lineList.push_back({ m_currentPosition.m_position, newState.m_position, lineColor });

			m_currentPosition = newState;
		}
		else if (m_state[i] == '+')
		{
			m_currentPosition.m_angle = rng.RandFloatInRange(m_currentPosition.m_angle, m_currentPosition.m_angle + kAngleChange);
		}
		else if (m_state[i] == '-')
		{
			m_currentPosition.m_angle = rng.RandFloatInRange(m_currentPosition.m_angle - kAngleChange, m_currentPosition.m_angle);
		}
		else if (m_state[i] == '[')
		{
			transformList.push(m_currentPosition);
		}
		else if (m_state[i] == ']')
		{
			m_currentPosition = transformList.top();
			transformList.pop();
		}

		// correct for overall trend angle
		float downAngle = slth::Vector2::AngleBetween(m_startPosition, m_endPosition) * 180.f / kPi;
		if (abs(m_currentPosition.m_angle - downAngle) >= kMaxAngleDeviation)
		{
			m_currentPosition.m_angle = downAngle;
		}

	}
}

void FractalLightning::Draw(slth::IGraphics* pGraphics)
{
	for (LineData& line : m_lineList)
	{
		pGraphics->DrawLine(line.m_start, line.m_end, line.m_color);
	}
}

void FractalLightning::SetStartEndPositions(slth::Vector2 start, slth::Vector2 end)
{
	m_state = "L";
	m_startPosition = start;
	m_endPosition = end;
	m_currentPosition.m_position = start;
	m_currentPosition.m_angle = slth::Vector2::AngleBetween(start, end) * 180.f / kPi;
	m_lineList.clear();
	m_numBranches = 0;
	
}

void LSystem::SetStartPosition(slth::Vector2 position)
{
	m_startPosition = position;
	m_state = "A";
}

