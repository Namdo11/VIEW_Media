#include "MediaInterface.h"

void MediaInterface::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void MediaInterface::gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void MediaInterface::displayMusicScreen() {
    clearScreen();
    gotoxy(20,0);
    std::cout<< "APP MUSIC C++ VERSION"<< std::endl;
    gotoxy(18,2);
    std::cout<< "========================"<< std::endl;
    std::cout<< "=======================CONTROL-BOX======================"<< std::endl;
    std::cout<<"| [0]: MENU      [1]: SHOW DATA                             |"<<std::endl;
    std::cout<<"| [2]: PREVIOUS  [3]: PLAY/PAUSE        [4]: NEXT           |" <<std::endl;
    std::cout<<"| [5]: ADD TO PLAYLIST                                      |"<<std::endl;
    std::cout<<" =============================================<Volume:     >|"<< std::endl;
    std::cout<<"-> CHOOSE: ";
}

void MediaInterface::displayMenuInter() {
    clearScreen();
    gotoxy(20,0);
    std::cout<< "APP MUSIC C++ VERSION"<< std::endl;
    gotoxy(18,2);
    std::cout<< "========================"<< std::endl;
    std::cout<< "=======================SELECT MODE======================"<< std::endl;
    std::cout<<"1. DISPLAY LIBRARY"<<std::endl;
    std::cout<<"2. MY PLAYLIST"<<std::endl;
    std::cout<<"3. MANAGE LIBRARY"<<std::endl;
    std::cout<<"4. MANAGE PLAYLIST"<<std::endl;
    std::cout<<"4. EXIT"<<std::endl;
    std::cout<<"-> CHOOSE: ";
}

void MediaInterface::displayLibManager() {
    clearScreen();
    gotoxy(20,0);
    std::cout<< "APP MUSIC C++ VERSION"<< std::endl;
    gotoxy(18,2);
    std::cout<< "========================"<< std::endl;
    std::cout<< "=======================LIBRARY MANAGER======================"<< std::endl;
    std::cout<<"1. ADD NEW FILE"<<std::endl;
    std::cout<<"2. REMOVE FILE"<<std::endl;
    std::cout<<"3. INFO"<<std::endl;
    std::cout<<"4. EXIT"<<std::endl;
    std::cout<<"-> CHOOSE: ";
}

void MediaInterface::displayLibrary(){
    clearScreen();
    std::cout<< "=======================ALL MEDIA======================"<< std::endl;
}

void MediaInterface::displayPlaylist(){
    clearScreen();
    std::cout<< "=======================PLAYLIST======================"<< std::endl;
}