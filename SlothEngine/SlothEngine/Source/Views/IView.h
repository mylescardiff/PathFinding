#pragma once
/** \file IView.h */

// Created by Myles Cardiff

//#include <Application/ApplicationLayer.h>
#include <Common.h> //Use this include.

//! \namespace Sloth Engine
namespace slth
{

	class IGameLayer;
/** \class IView */

class ApplicationLayer;

	class IView
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SLTH_API IView();

		/** Default Destructor */
		SLTH_API virtual ~IView();

		SLTH_API virtual bool Init(IGameLayer* pGameLayer) = 0;
		SLTH_API virtual void Update(float deltaTime) = 0;
		SLTH_API virtual void ViewScene() = 0;
		

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