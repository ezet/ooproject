#include "stdafx.h"
#include "service\storage\file\SystemFileService.h"
#include "lib\TCollection.h"
#include "lib\ErrorHandler.h"
#include "model\Player.h"
#include "model\Sport.h"

///
/// Constructor, defaultk
///
SystemFileService::SystemFileService() {

}

///
/// Constructor, takes a filename and openmode
///
SystemFileService::SystemFileService(const std::string fname,
                    const std::ios::openmode mode)
    : BaseFileService(fname, mode) {
}

///
/// Constructor, takes an existing filestream
///
SystemFileService::SystemFileService(std::fstream& file) : BaseFileService(file) {

}

///
/// Destructor
///
SystemFileService::~SystemFileService() {

}