#include "MediaLibrary.h"

MediaLibrary::MediaLibrary() : CurrentPlayList(nullptr), CurrentMediaFile(nullptr) {
    // Constructor implementation
}

MediaLibrary::~MediaLibrary() {
    // Destructor implementation
}

bool MediaLibrary::addNewMediaFile(const std::string& _path) {
    if (MediaFileList.insert(std::make_pair(_path, std::make_shared<MediaFile>(_path))).second) {
      saveFile(_path);
      return true;
    }
    return false;
}

bool MediaLibrary::removeMediaFilebyPath(const std::string& _path) {
    return MediaFileList.erase(_path) > 0;
}

std::shared_ptr<MediaFile> MediaLibrary::getMediaFilebyPath(const std::string& _path) {
    auto it = MediaFileList.find(_path);
    return (it != MediaFileList.end()) ? it->second : nullptr;
}

const std::map<std::string, std::shared_ptr<MediaFile>>& MediaLibrary::getAllMediaFiles() const {
    return MediaFileList;
}

bool MediaLibrary::addNewPlayList(const std::string& _name) {
    if (PlayListList.find(_name) == PlayListList.end()) {
        PlayListList[_name] = std::make_shared<PlayList>(_name);
        return true;
    }
    return false;
}

bool MediaLibrary::removePlayList(const std::string& _name) {
    return PlayListList.erase(_name) > 0;
}

const std::map<std::string, std::shared_ptr<PlayList>>& MediaLibrary::getAllPlayList() const {
    return PlayListList;
}

bool MediaLibrary::addMediaFiletoPlayList(const std::string& _playlistname, const std::string& _filepath) {
    auto playlist = PlayListList.find(_playlistname);
    auto mediaFile = MediaFileList.find(_filepath);
    if (playlist != PlayListList.end() && mediaFile != MediaFileList.end()) {
        return playlist->second->addMediaFile(mediaFile->second);
    }
    return false;
}

bool MediaLibrary::removeMediaFilefromPlayList(const std::string& _playlistname, const std::string& _filepath) {
    auto playlist = PlayListList.find(_playlistname);
    if (playlist != PlayListList.end()) {
        return playlist->second->removeMediaFile(_filepath);
    }
    return false;
}

std::shared_ptr<PlayList> MediaLibrary::getPlayListbyName(const std::string& _name) {
    auto it = PlayListList.find(_name);
    return (it != PlayListList.end()) ? it->second : nullptr;
}

void MediaLibrary::setCurrentMediaFile(const std::string& _path){
  CurrentMediaFile = getMediaFilebyPath(_path);
  if(CurrentMediaFile == nullptr){
    std::cerr <<"Media file not found in Media library" << std::endl;
  }
}

std::shared_ptr<MediaFile> MediaLibrary::getCurrentMediaFile() const{
  return CurrentMediaFile;
};

bool MediaLibrary::settoNextMediaFileinLibrary(){
  if (CurrentMediaFile == nullptr) return false;
  auto it = MediaFileList.find(CurrentMediaFile->getPath());
  if(it != MediaFileList.end()) {
    auto nextIt = std::next(it);
    if (nextIt != MediaFileList.end()) {
      CurrentMediaFile = nextIt->second;
      return true;
    }
  }
  return false;
}; // not yet

bool MediaLibrary::settoPrevMediaFileinLibrary(){
  if (CurrentMediaFile == nullptr) return false;

  auto it = MediaFileList.find(CurrentMediaFile->getPath());
  if (it != MediaFileList.end() && it != MediaFileList.begin()) {
      CurrentMediaFile = std::prev(it)->second;
      return true;
  }
  return false;
}; // not yet 

void MediaLibrary::setCurrentPlayList(const std::string& _name){
  auto it = PlayListList.find(_name);
  if(it != PlayListList.end()){
    CurrentPlayList = it->second;
    CurrentMediaFile = nullptr; // reset current media file 
  }else{
    std::cerr<< "PLaylist not found" << std::endl;
  }
};

std::shared_ptr<PlayList> MediaLibrary::getCurrentPlayList() const{
  return CurrentPlayList;
};

bool MediaLibrary::settoNextMediaFileinPlayList(){
  if(!CurrentPlayList || !CurrentMediaFile) return false;
  auto& trackList = CurrentPlayList->getPlayList();
  //get current mediaFile in tracklist 
  auto it = std::find_if(trackList.begin(), trackList.end(), [this](const std::shared_ptr<MediaFile>& file) {
    return file->getPath() == CurrentMediaFile->getPath();
  });
  //get next mediaFile in playlist 
  if (it != trackList.end()) {
      auto nextIt = std::next(it);
      if (nextIt != trackList.end()) {
        CurrentMediaFile = *nextIt;
        return true;
      }
  }
  return false;
}; // not yet

bool MediaLibrary::settoPrevMediaFileinPlayList(){
  if (!CurrentPlayList || !CurrentMediaFile) return false;

  auto& trackList = CurrentPlayList->getPlayList();
  auto it = std::find_if(trackList.begin(), trackList.end(), [this](const std::shared_ptr<MediaFile>& file) {
      return file->getPath() == CurrentMediaFile->getPath();
  });

  if (it != trackList.end() && it != trackList.begin()) {
      CurrentMediaFile = *std::prev(it);
      return true;
  }
  return false;
}; // not yet
   //

void MediaLibrary::saveFile(std::string _path) {
    std::ofstream outfile("data.txt", std::ios_base::app); // Mở file ở chế độ ghi thêm
        if (outfile.is_open()) {
            outfile << _path << std::endl; // Ghi đường dẫn vào file
            outfile.close();
        } else {
            std::cerr << "Unable to open file for writing\n";
        }
}

void MediaLibrary::getData() {
        std::ifstream infile("data.txt");
        if (!infile.is_open()) {
            std::cerr << "Unable to open file for reading\n";
            return;
        }

        std::string _path;
        while (std::getline(infile, _path)) {
            if (!_path.empty()) { // Kiểm tra nếu đường dẫn không trống
               MediaFileList[_path] = std::make_shared<MediaFile>(_path); 
            }
        }

        infile.close();
}
