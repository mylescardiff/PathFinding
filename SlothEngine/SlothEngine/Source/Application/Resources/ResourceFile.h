#pragma once
/** \file ResourceFile.h */

// Created by Myles Cardiff


#include <vector>
#include <unordered_map>
#include <fstream>
#include <Common.h>

//! \namespace Sloth Engine
namespace slth
{

	class ISystem;

/** \class ResourceFile */
/** Resource File  */
class ResourceFile
{
public:

	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	
	/** Default Constructor */
	SLTH_API ResourceFile();

	/** Default Destructor */
	SLTH_API ~ResourceFile();

	/** Add a resource to the file in memory */
	SLTH_API void AddResouce(std::string& path, std::vector<u8>& data);

	/** Commit the file in memory to a disk */
	SLTH_API void Save(const std::string& path);
	
	/** Load files from a compressed folder */
	SLTH_API void Load(std::string& path);

	/** Compress and save an entire folder to file (recursive) */
	SLTH_API bool CompressFolder(std::string& pathToCompress, std::string& outputLocation, ISystem* pSystem);


private:
	struct ResourceInfo
	{
		u32 m_compressed;
		u32 m_size;
		u32 m_offset;
	};

	std::unordered_map<std::string, ResourceInfo> m_infoMap;
	u32 m_currentOffset;
	std::vector<std::vector<u8>> m_pendingData;
	std::fstream m_file;

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