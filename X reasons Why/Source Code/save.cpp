#include"save.h"


//written by felix
int chapter;
int page = 1;


//reads savefile
//saves per chapter
void opensave() {
    std::ifstream rp("savefile.txt");
    while (rp >> chapter) {

    }
    rp.close();
    switch (chapter) {

    case 0:
        page = 1;
        break;
    case 1:
        page = 66;
        break;
    case 2:
        page = 95;
        break;
    case 3:
        page = 102;
        break;
    case 4:
        page = 131;
        break;
    }
}

void savegame() {
    std::ofstream fp("savefile.txt");
    //checks if savefile.txt is found
    if (!fp)
    {
        int result = MessageBox(0, L"Savefile not found!", L"", MB_RETRYCANCEL | MB_SYSTEMMODAL);
        if (result == IDRETRY) {
            return savegame();//retry to save
        }
        else {
            exit(0);//quits
        }

    }
    //saves game
    else {
        fp << chapter;

    }
    fp.close();
}

//continues the progress
void continuesave() {
    opensave();
    if (chapter > 0) {
        int result1 = MessageBox(0, L"Do you want to continue your progress?", L"", MB_YESNO | MB_SYSTEMMODAL);
        if (!(result1 == IDYES)) {
            int result2 = MessageBox(0, L"Do you want to start over?", L"", MB_YESNO | MB_SYSTEMMODAL);
            if (!(result2 == IDYES)) {
                return continuesave();
            }

            chapter = 0;
            savegame();
            page = 1;
        }
    }
}