#include "MediaFile.h"

MediaFile::MediaFile(const std::string& _path) : Path(_path), is_playing(false), is_paused(false) 
                                                ,volume(MIX_MAX_VOLUME / 2), muted(false), lastVolume(MIX_MAX_VOLUME / 2){}

MediaFile::~MediaFile() {
    //delete MusicFile;
}

void MediaFile::setPath(const std::string& _path) {
    Path = _path;
    loadMetadata();
}

std::string MediaFile::getPath() const {
    return Path;
}

// Load metadata using TagLib
void MediaFile::loadMetadata() {
    TagLib::FileRef file(Path.c_str());

    if (file.isNull()) {
        std::cerr << "Failed to open file: " << Path << std::endl;
        return;
    }

    if (!file.tag()) {
        std::cerr << "No tag information found in file: " << Path << std::endl;
        return;
    }

    TagLib::Tag* tag = file.tag();

    title = tag->title().to8Bit(true);
    artist = tag->artist().to8Bit(true);
    album = tag->album().to8Bit(true);
    genre = tag->genre().to8Bit(true);
    year = tag->year();
    trackNumber = tag->track();

    TagLib::AudioProperties *properties = file.audioProperties();
    TagLib::File *audioFile = file.file();

    if (properties) {
        fileSize = audioFile->length();      // File size in bytes
        duration = properties->length();     // Duration in seconds
        bitrate = properties->bitrate();     // Bitrate in kbps
        channels = properties->channels();   // Number of channels
        sampleRate = properties->sampleRate(); // Sampling rate in Hz
        writingLibrary = tag->comment().to8Bit(); // Writing library (if stored in a comment tag)
    } else {
        std::cerr << "Failed to retrieve audio properties for file: " << Path << std::endl;
    }

    std::cout << "Metadata loaded successfully from: " << Path << std::endl;
}

void MediaFile::init() {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void MediaFile::loadMusic() {
    MusicFile = Mix_LoadMUS(Path.c_str());
}

void MediaFile::load() {
    loadMetadata();
    init();
    loadMusic();
}

std::string MediaFile::getTitle() const {
    return title;
}

std::string MediaFile::getArtist() const {
    return artist;
}

std::string MediaFile::getAlbum() const {
    return album;
}

std::string MediaFile::getGenre() const {
    return genre;
}

unsigned int MediaFile::getYear() const {
    return year;
}

unsigned int MediaFile::getTrackNumber() const {
    return trackNumber;
}

unsigned long MediaFile::getFileSize() const {
    return fileSize;
}

int MediaFile::getDuration() const {
    return duration;
}

int MediaFile::getBitrate() const {
    return bitrate;
}

int MediaFile::getChannels() const {
    return channels;
}

int MediaFile::getSampleRate() const {
    return sampleRate;
}

std::string MediaFile::getWritingLibrary() const {
    return writingLibrary;
}

void MediaFile::play() {
    if (!is_playing) {
        if (is_paused) {
            Mix_ResumeMusic();
            is_paused = false;
        } else {
            std::cout<<"thongbaodachaynhac"<<std::endl;
            Mix_PlayMusic(MusicFile, -1); // -1 to loop infinitely
        }
        is_playing = true;
    }
}

void MediaFile::pause() {
    if (is_playing && !is_paused) {
        Mix_PauseMusic();
        is_playing = false;
        is_paused = true;
    }
}

void MediaFile::stop() {
    Mix_HaltMusic();
    is_playing = false;
    is_paused = false;
}

void MediaFile::decreaseVolume(){
    volume = std::max(MIN_VOLUME, volume - AMOUNT_OF_CHANGE_VOLUME); // Adjust volume range as needed
    Mix_VolumeMusic(volume);
    std::cout << "Volume decreased to: " << volume << std::endl;
}

void MediaFile::increaseVolume(){
    volume = std::min(MAX_VOLUME, volume + AMOUNT_OF_CHANGE_VOLUME); // Adjust volume range as needed
    Mix_VolumeMusic(volume);
    std::cout << "Volume increased to: " << volume << std::endl;
}

void MediaFile::getVolume() const{
    return volume;
}

void MediaFile::isMuted() const {
    return muted;
}

void MediaFile::toggleMute(){
    muted = !muted;
    if (muted) {
        lastVolume = volume;
        volume = 0;
        Mix_VolumeMusic(volume);
    } else {
        volume = lastVolume;
        Mix_VolumeMusic(volume);
    }
}

bool MediaFile::isPlaying() const{
    return is_playing;
}

bool MediaFile::isPaused() const{
    return is_paused;
}

void MediaFile::displayMetadata() const {
    std::cout << "Path: " << Path << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Album: " << album << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Track Number: " << trackNumber << std::endl;
    std::cout << "File Size: " << (fileSize / 1024.0 / 1024.0) << " MiB" << std::endl;
    std::cout << "Duration: " << (duration / 60) << " min " << (duration % 60) << " s" << std::endl;
    std::cout << "Bitrate: " << bitrate << " kb/s" << std::endl;
    std::cout << "Channels: " << channels << std::endl;
    std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
    //std::cout << "Writing Library: " << writingLibrary << std::endl;
}

