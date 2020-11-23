#include "NameGenerator.h"

// constants
constexpr static const char* s_kConstantants = "bcdfghklmnprstvwz";
constexpr static const u8 s_kNumConsts = 17;
constexpr static const char* s_kVowells = "aeiou";
constexpr static const u8 s_kNumVowells = 5;
constexpr static const float s_kSyllableChanceReduction = 0.40f;
constexpr static float s_kChanceOfNewWord = 0.05f;

void NameGenerator::Reset()
{
	m_generation = 0;
	m_state = "";
}

bool NameGenerator::NextGeneration(slth::Rng& rng)
{
	std::string newState = "";
	
	for (char ch : m_state)
	{
		if (ch == 'S')
		{
			float diceRoll = rng.RandFloat();
			if (diceRoll < m_chanceOfNewSyllable)
			{
				newState += "SS";
				m_chanceOfNewSyllable -= s_kSyllableChanceReduction;
			}
			else
			{
				newState += "CV";
			}
		}

		else if (ch == 'V')
		{
			int randVowell = rng.RandIntInRange(0, s_kNumVowells - 1);
			newState += s_kVowells[randVowell];
		}
		else if (ch == 'C')
		{
			int randConst = rng.RandIntInRange(0, s_kNumConsts - 1);
			newState += s_kConstantants[randConst];
		}
		else
		{
			newState += ch;
		}

		
		
	}
	m_state = newState;

	for (char ch : m_state)
	{
		if (ch == 'V' || ch == 'C' || ch == 'S')
			return true;
		
	}
	
	return false;
}

std::string NameGenerator::Generate(slth::Rng& rng)
{
	m_state = "SS";
	float roll = rng.RandFloatInRange(0.f, 1.f);
	if (roll < s_kChanceOfNewWord)
		m_state += " SS";

	while (NextGeneration(rng))
	{
		++m_generation;
	}

	//capitalize first letter of each word
	m_state[0] = std::toupper(m_state[0]);
	for (int i = 1; i < m_state.size() - 1; ++i)
	{
		if (m_state[i - 1] == ' ')
		{
			m_state[i] = std::toupper(m_state[i]);
		}
	}

	// store then reset the thing so it doesn't give the same name
	std::string newName = m_state;
	
	Reset();

	return newName;
}