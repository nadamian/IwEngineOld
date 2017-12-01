#include "Directory.h"
#include "Path.h"

namespace filesystem = std::experimental::filesystem::v1;
using namespace IwUtility::IO;

IWUTILITY_API std::string* IwUtility::IO::Directory::GetFiles(const char* directoryPath, bool recurse) {
	size_t throwAwayErrorCode;
	return GetFiles(directoryPath, recurse, throwAwayErrorCode);
}

IWUTILITY_API std::string* IwUtility::IO::Directory::GetFiles(const char* directoryPath, bool recurse, size_t& fileCount) {
	typedef filesystem::recursive_directory_iterator RDI;
	typedef filesystem::directory_iterator DI;

	fileCount = GetFileCount(directoryPath, recurse);
	std::string* filePaths = new std::string[fileCount];

	if (recurse) {
		RDI rdi = RDI(directoryPath);
		for (size_t i = 0; i < fileCount; i++) {
			std::string str = rdi->path().string();
			if (Path::IsFile(str)) {
				filePaths[i] = str;
			} else {
				i--;
			}

			rdi++;
		}
	} else {
		DI rdi = DI(directoryPath);
		for (size_t i = 0; i < fileCount; i++) {
			filePaths[i] = rdi->path().string();
			rdi++;
		}
	}

	return filePaths;
}

IWUTILITY_API size_t IwUtility::IO::Directory::GetFileCount(const char * directoryPath, bool recurse) {
	typedef filesystem::recursive_directory_iterator RDI;
	typedef filesystem::directory_iterator DI;

	if (recurse) {
		RDI rdi = RDI(directoryPath);
		size_t i = 0;
		for (auto& file : rdi) {
			if (Path::IsFile(file.path().string())) {
				i++;
			}
		}

		return i;
	} else {
		DI rdi = DI(directoryPath);
		return std::distance(rdi, DI());
	}
}

IWUTILITY_API bool IwUtility::IO::Directory::Exists(const char * directoryPath) {
	return filesystem::is_directory(directoryPath);
}
















//std::string* Directory::GetFiles(const char* directoryPath, bool recurse) {
//	std::error_code errorCode;
//	size_t fileCount;
//	return Directory::GetFiles(directoryPath, recurse, errorCode, fileCount);
//}
//
//std::string* Directory::GetFiles(const char* directoryPath, bool recurse, std::error_code& errorCode) {
//	size_t fileCount;
//	return Directory::GetFiles(directoryPath, recurse, errorCode, fileCount);
//}
//
//std::string* Directory::GetFiles(const char* directoryPath, bool recurse, size_t& fileCount) {
//	std::error_code errorCode;
//	return Directory::GetFiles(directoryPath, recurse, errorCode, fileCount);
//}
//
//std::string* Directory::GetFiles(const char* directoryPath, bool recurse, std::error_code& errorCode, size_t& fileCount) {
//	typedef filesystem::directory_iterator DirItr;
//
//	DirItr itr = DirItr(directoryPath, errorCode);
//	std::string* files = nullptr;
//
//	if (!errorCode) {
//		fileCount = Directory::GetFileCount(directoryPath, recurse);
//		files = new std::string[fileCount];
//		for (std::size_t i = 0; i < fileCount; i++) {
//			files[i] = itr->path().string();
//			itr++;
//		}
//	}
//
//	return files;
//}
//
//std::size_t Directory::GetFileCount(const char* directoryPath, bool recurse) {
//	std::error_code errorCode;
//	return Directory::GetFileCount(directoryPath, recurse, errorCode);
//}
//
//std::size_t Directory::GetFileCount(const char* directoryPath, bool recurse, std::error_code& errorCode) {
//	if (recurse) {
//		typedef filesystem::recursive_directory_iterator DirIttr;
//		return std::distance(DirIttr(directoryPath, errorCode), DirIttr());
//	} else {
//		typedef filesystem::directory_iterator DirIttr;
//		return std::distance(DirIttr(directoryPath, errorCode), DirIttr());
//	}
//}
//
//bool Directory::Exists(const char* directoryPath) {
//	std::error_code errorCode;
//	return Directory::Exists(directoryPath, errorCode);
//}
//
//bool Directory::Exists(const char* directoryPath, std::error_code& errorCode) {
//	return filesystem::is_directory(directoryPath, errorCode);
//}
