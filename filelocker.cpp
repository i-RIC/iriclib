#include "filelocker.h"
#include "private/filelocker_impl.h"

#include <sys/stat.h>

#ifndef _MSC_VER
#include <unistd.h>
#include <sys/file.h>
#define _stat stat
#endif

FileLocker::Impl::Impl(const std::string& filename) :
#ifdef _MSC_VER
	m_handle {NULL},
#else
	m_fd {0},
#endif
	m_filename (filename),
	m_isLocked {false}
{}

FileLocker::FileLocker(const std::string& filename) :
	impl {new Impl {filename}}
{}

FileLocker::~FileLocker()
{
	unlock();
	delete impl;
}

bool FileLocker::lockFileExists() const
{
	struct _stat fileStat;
	int result;

	result = _stat(impl->m_filename.c_str(), &fileStat);
	return result == 0;
}

bool FileLocker::isLocked() const
{
	return impl->m_isLocked;
}

bool FileLocker::lock()
{
	if (impl->m_isLocked) {
		return true;
	}

#ifdef _MSC_VER
	// implementation for windows
	impl->m_handle = ::CreateFileA(impl->m_filename.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
	if (impl->m_handle == INVALID_HANDLE_VALUE) {
		return false;
	}
	OVERLAPPED overlapped;

	BOOL result = LockFileEx(impl->m_handle, LOCKFILE_EXCLUSIVE_LOCK, 0, 10, 0, &overlapped);
	if (! result) {
		return false;
	}
	impl->m_isLocked = true;
	return true;

#else
	// implementation for linux
	impl->m_fd = open(impl->m_filename.c_str(), O_WRONLY | O_CREAT, S_IRWXU);
	if (impl->m_fd == -1) {
		return false;
	}

	int result = flock(impl->m_fd, LOCK_EX);
	if (result != 0){
		return false;
	}
	impl->m_isLocked = true;
	return true;

#endif
}

void FileLocker::unlock()
{
	if (! impl->m_isLocked) {
		return;
	}

#ifdef _MSC_VER
	// implementation for windows

	CloseHandle(impl->m_handle);
	impl->m_handle = NULL;

#else
	// implementation for linux

	close(impl->m_fd);
	impl->m_fd = -1;

#endif
	remove(impl->m_filename.c_str());

	impl->m_isLocked = false;
}
