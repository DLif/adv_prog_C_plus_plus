#include "VirtIO_t.h"

VirtIO_t::VirtIO_t(string filePath,size_t openMode) :path(filePath),mode(openMode),bufferPoint(NULL)
{
	file_descriptor=fopen(path.c_str(),modeTranslation(mode).c_str());//open file
	if(file_descriptor==NULL){
		file_status=cant_open_file_e;
		comma_read_or_write=no_set_e;
		return;
	}
	
	file_status=ok_e;

	//set preknowlagde on file operations
	if ((mode & input) && !(mode & output)){
		comma_read_or_write=read_e;
	}
	else if (!(mode & input) && (mode & output)){
		comma_read_or_write=write_e;
	}

}

inline VirtIO_t& VirtIO_t::operator>>(void* Buf)
{
	bufferPoint=Buf;
	comma_read_or_write=read_e;
}

inline VirtIO_t& VirtIO_t::operator<<(const void* Buf)
{
	bufferPoint=(void* )Buf;//const off- thgis is a bit dengarous
	comma_read_or_write=write_e;
}

inline void VirtIO_t::clear(size_t set=ok_e){
	mode=set;
}

inline const string VirtIO_t::get_file_path() const{
	return path;
}

inline const size_t VirtIO_t::get_file_access_mode() const{
	return mode;
}

inline bool VirtIO_t::is_ok_e() const{
	return file_status == ok_e;//ok_e is zero so check equal
}

inline bool VirtIO_t::is_cant_open_file_e() const{
	return file_status & cant_open_file_e;
}

inline bool VirtIO_t::is_bad_access_e() const{
	return file_status & bad_access_e;
}

inline bool VirtIO_t::is_writeErr_e() const{
	return file_status & writeErr_e;
}

inline bool VirtIO_t::is_readErr_e() const{
	return file_status & readErr_e;
}

inline bool VirtIO_t::operator!() const{
	return file_status != ok_e;
}