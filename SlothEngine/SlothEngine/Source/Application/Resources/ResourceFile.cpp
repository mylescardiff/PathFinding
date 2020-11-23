#include "ResourceFile.h"

#if _WIN64
#include <zlib.h>
#endif
#include <algorithm>
#include <Logger/Logger.h>
#include <Application/Systems/ISystem.h>
#include <fstream>

using slth::ResourceFile;

ResourceFile::ResourceFile()
{
	//
}

ResourceFile::~ResourceFile()
{
	//
}

void slth::ResourceFile::AddResouce(std::string& path, std::vector<u8>& data)
{
#if _WIN64
	// normalize the path
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);
	std::replace(path.begin(), path.end(), '\\', '/');

	ResourceInfo info;
	info.m_size = (u32)data.size();
	info.m_offset = m_currentOffset;

	std::vector<u8> compressedData;
	compressedData.resize(data.size());

	// using the z-stream
	z_stream stream;
	memset(&stream, 0, sizeof(stream)); // sets everything to zero (old skool)

	stream.avail_in = (uInt)data.size();
	stream.next_in = reinterpret_cast<u8*>(data.data()); // take this and treat it as a u8 address
	stream.avail_out = (uInt)compressedData.size();
	stream.next_out = reinterpret_cast<u8*>(compressedData.data());

	int result = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
	if (result != Z_OK)
	{
		_LOGE("Failed to start zlib deflate");
		return;
	}

	result = deflate(&stream, Z_FINISH);

	// check for successful 
	if (result == Z_STREAM_END &&
		stream.total_out < info.m_size &&
		stream.avail_in == 0)
	{
		compressedData.resize(stream.total_out);
	}
	else
	{
		// the compressed size is larger than the uncompressed
		compressedData = std::move(data);
	}

	deflateEnd(&stream);

	info.m_compressed = (u32)compressedData.size();
	m_currentOffset += info.m_compressed;
	m_infoMap[path] = info;

	m_pendingData.push_back(std::move(compressedData));
#endif
	

}

void slth::ResourceFile::Save(const std::string& path)
{
	// building the doc
	XmlDoc doc;
	XmlData* pRoot = doc.NewElement("ResourceFile");
	doc.InsertFirstChild(pRoot);

	for (auto& info : m_infoMap)
	{
		XmlData* pElement = doc.NewElement("Resource");
		pElement->SetAttribute("Path", info.first.c_str());
		pElement->SetAttribute("Compressed", info.first.c_str());
		pElement->SetAttribute("Size", info.second.m_size);
		pElement->SetAttribute("Offset", info.second.m_offset);

		pRoot->InsertEndChild(pElement);

	}

	// write it to file
	tinyxml2::XMLPrinter print;
	doc.Print(&print);

	m_file.open(path.c_str(), std::ios_base::out | std::ios_base::binary);
	if (m_file.is_open())
	{
		for (auto& data : m_pendingData)
		{
			
			char* rawData = reinterpret_cast<char*>(data.data());
			size_t rawSize = data.size(); // this has a size, but it's in the hundreds, the byte size of these files is waaaay larger
			m_file.write(rawData, rawSize);
		}
		m_file.write(print.CStr(), print.CStrSize());
		int size = print.CStrSize();
		m_file.write(reinterpret_cast<char*>(&size), sizeof(int)); // take the memory address of size, reinterp to a single byte, then write 4 bytes

		m_pendingData.clear();
		m_infoMap.clear();
		m_file.close();
	}
}

void slth::ResourceFile::Load(std::string & path)
{
	//
}

bool slth::ResourceFile::CompressFolder(std::string& pathToCompress, std::string& outputLocation, ISystem* pSystem)
{
	_LOGI("To Compress: " + pathToCompress);
	_LOGI("Output Loc: " + outputLocation);
	
	auto files = pSystem->GetFilesInFolder(pathToCompress, true);

	slth::ResourceFile resources;
	for (auto& file : files)
	{
		std::string resourcePath = pathToCompress + "/" + file;
		std::fstream resourceFile;
		resourceFile.open(file.c_str(), std::ios_base::in | std::ios_base::binary);

		if (resourceFile.is_open())
		{
			resourceFile.seekg(0, resourceFile.end);
			size_t fileSize = static_cast<size_t>(resourceFile.tellg());
			resourceFile.seekg(0, resourceFile.beg);
			std::vector<u8> data(fileSize);
			resourceFile.read(reinterpret_cast<char*>(data.data()), fileSize);
			resources.AddResouce(file, data);
		}
	}

	resources.Save(outputLocation.c_str());
	return true;
}
