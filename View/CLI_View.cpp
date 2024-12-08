#include "CLI_View.h"
#include <iostream>

void MediaInterface::gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void MediaInterface::displayMusicScreen() {
    gotoxy(20,0);
    std::cout<< "APP MUSIC C++ VERSION"<< std::endl;

    gotoxy(18,2);
    std::cout<< "========================"<< std::endl;

    // Draw the control box section
    gotoxy(0,4);
    std::cout<< "=======================CONTROL-BOX======================"<< std::endl;
    std::cout<<"| [0]: MENU      [1]: SHOW DATA                             |"<<std::endl;
    std::cout<<"| [2]: PREVIOUS  [3]: PLAY/PAUSE        [4]: NEXT           |" <<std::endl;
    std::cout<<"| [5]: ADD TO PLAYLIST                                      |"<<std::endl;
    std::cout<<" =============================================<Volume:     >|"<< std::endl;

    // Replace "[4]: NEXT" with "[4]: PLAY"
    gotoxy(34,7); // Move cursor to where "[4]: NEXT" is located
    std::cout<< "PLAY           "; // Overwrite with "[4]: PLAY" and add spaces to ensure full replacement

    // Move to the choose input section
    gotoxy(0,9);
    std::cout<<"-> CHOOSE: ";
}
