#include "PlayList.h"

PlayList::PlayList(std::string _name) : Name(_name) {

}

bool PlayList::addMediaFile(const std::shared_ptr<MediaFile>& _mediafile) {
    auto it = std::find_if(MediaTrackList.begin(), MediaTrackList.end(), [&_mediafile](const auto& _file) {
        return _file->getPath() == _mediafile->getPath();
    });
    if (it == MediaTrackList.end()) {
        MediaTrackList.push_back(_mediafile);
        return true;
    }
    return false;
}

bool PlayList::removeMediaFile(const std::string& _path) {
    auto it = std::find_if(MediaTrackList.begin(), MediaTrackList.end(), [&_path](auto _file){
        return _file->getPath() == _path;
    });
    if (it != MediaTrackList.end()) {
        MediaTrackList.erase(it);
        return true;
    }
    else return false;
}

const std::shared_ptr<MediaFile> PlayList::getMediaFilebyPath(const std::string& _path) const {
    auto _check = std::find_if(MediaTrackList.begin(), MediaTrackList.end(), [&_path](auto _file){
        return _file->getPath() == _path;
    });
    return (_check != MediaTrackList.end()) ? *_check : nullptr;
}

const std::vector<std::shared_ptr<MediaFile>>& PlayList::getPlayList() const {
    return MediaTrackList;
}

void PlayList::setName(const std::string& _name) {
    Name = _name;
}

std::string PlayList::getName() const {
    return Name;
}

int PlayList::size() const {
    return MediaTrackList.size();
}

void PlayList::clear() {
    MediaTrackList.clear();
}