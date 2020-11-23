#include "Grammar.h"
#include <Logger/Logger.h>


void Grammar::Run(slth::Rng& rng, GrammarData& grammarData)
{

	std::string output = m_startingState;
	bool hasNonTermintors = true;

	while (hasNonTermintors)
	{
		std::string work = "";
		hasNonTermintors = false;

		for (char ch : output)
		{
			// copy terminating symbols directly
			if (IsTermiatingCharacter(ch))
			{
				work += ch;
				continue;
			}

			// get valid rules for current symbol
			auto ruleIt = m_rules.equal_range(ch);

			// weight calculation 
			// NOTE: this could be cached, but you'd still need to go through them at some point
			// and the performance boost would be negligable in my case.
			float totalWeight = 0.f;
			for (auto it = ruleIt.first; it != ruleIt.second; ++it)
			{
				totalWeight += it->second.m_weight;
			}

			float randChoice = rng.RandFloat();
			for (auto it = ruleIt.first; it != ruleIt.second; ++it)
			{
				randChoice -= it->second.m_weight;
				if (randChoice <= 0.f)
				{
					work += it->second.m_successor;

					// check cached non terminator value
					if (it->second.m_hasNonTerminators)
					{
						hasNonTermintors = true;
					}

					break;
				}

			}

		}
		output = std::move(work);
		

	}
	grammarData.m_rawData = output;
	// translate the output into a string with the dictionary
	std::string translation;
	for (char ch : output)
	{
		auto rule = m_dictionary.find(ch);
		if (rule != m_dictionary.end())
			translation += rule->second;
		else
			translation += ch;

		translation += " ";
	}
	grammarData.m_translatedData = translation;

	
}

bool Grammar::IsTermiatingCharacter(char ch)
{
	for (char termChar : m_terminators)
	{
		if (termChar == ch)
			return true;
	}
	return false;
}

void Grammar::AddRule(const char ch, Rule rule)
{
	for (char ch : rule.m_successor)
	{
		if (!IsTermiatingCharacter(ch))
		{
			rule.m_hasNonTerminators = true;
			break;
		}
	}
	m_rules.emplace(ch, rule);
}
