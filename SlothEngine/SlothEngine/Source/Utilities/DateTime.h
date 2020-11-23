#pragma once
/** \file DateTime.h */

// Created by Myles Cardiff

#include <chrono>


//! \namespace Sloth Engine
namespace slth
{
/** \class DateTime */

class DateTime
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //

	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;

	
	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	DateTime();

	/** Default Destructor */
	~DateTime();

	static long long TickTimestamp()
	{
		auto duration = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	}

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};
}