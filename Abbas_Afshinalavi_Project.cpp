/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

//Rooms
enum Room {BEDROOM1 , BEDROOM2 , MAINHALL , RESTROOM};

//Declraring mpc type of variable
struct mpc{
    std::string name;
    char symbol;
    bool alive;
    int place;
};

//Declraring killer type of variable
struct killer{
    std::string name;
    char symbol;
    int place;
    int kill;
};

//Declraring player type of variable
struct player{
    char symbol;
    int guess;
    char guessN;
    int place;
    //player's turn 
    int turn;
};


//Function prototypes
char find_killer(const char arr[], int);
void hall(char array1[3][10] , char array2[8][3]);
void showEntrance(char arr[3][10]);
void showHall(char arr[8][3]);
void hall();
void bedRoom(char array[10][10]);
void showBedRoom(char arr[10][10] , int);
void mainHall(char array[10][20]);
void showMainHall(char arr[10][20]);
void restRoom(char array[6][10]);
void showRestRoom(char arr[6][10]);
void spawn(mpc arr1[5] , char arr2[10][10] , char arr3[10][10] , char arr4[10][20] , char arr5[6][10] , const char);
void killBedRoom(char array1[10][10] , mpc array2[4] , mpc array3[5] , killer &x, const char);
void killRestRoom(char arr1[6][10] , mpc arr2[4] , mpc arr3[5] , killer &x, const char);
void killMainHall(char arr1[10][20] , mpc arr2[4] , mpc arr3[5] , killer &x, const char);
void reset(char arr1[10][10] , char arr2[10][10] , char arr3[10][20] , char arr4[6][10] , const char);

//Main function
int main() {
    
    //Bedrooms
    char b1[10][10] , b2[10][10];
    bedRoom(b1);
    bedRoom(b2);
    
    //Hall and entrance 
    char e[3][10], h[8][3];
    hall(e, h);
    
    //Main hall 
    char mh[10][20];
    mainHall(mh);
    
    //Rest room 
    char rr[6][10];
    restRoom(rr);
    
    //Dead body
    const char body = 'X';
    
    //Player 
    player p;
    p.symbol = '*';
    p.guess = 0;
    p.turn = 0;
    p.place = 0;
    
    //Guests
	mpc guest1[5] = {{"Zoe",'Z',true} , {"Sebastian",'S',true} , {"Annabelle",'A',true} , 
	    {"Moundo",'M',true} , {"Patrick",'P',true}
	};
	
	//Randomly find the killer 
	killer k;
	k.kill = 0;
	srand(time(0));
	int x = (rand() % 5);
	switch (x){
	    case 0:
            k.name = guest1[0].name;
            k.symbol = guest1[0].symbol;
            break;
        case 1:
            k.name = guest1[1].name;
            k.symbol = guest1[1].symbol;
            break;
        case 2:
            k.name = guest1[2].name;
            k.symbol = guest1[2].symbol;
            break;
        case 3:
            k.name = guest1[3].name;
            k.symbol = guest1[3].symbol;
            break;
        case 4:
            k.name = guest1[4].name;
            k.symbol = guest1[4].symbol;
            break;
	}
	
	
	//Separating guests with the killer 
	mpc guest2[4];
	
	int i = 0;
	int j = 0;
	while(j < 4) {
	    if(guest1[i].name != k.name) {
	        guest2[j] = guest1[i];
	        i++;
	        j++;
	    }
	    else {
	        i++;
	    }
	}
    
	
	std::cout << std::setw(80) << "Welcome to the Christmas party!" << std::endl;
	std::cout << std::setw(100)<< "Please enjoy the food, the music, and the warm holiday vibes."<< std::endl;
	std::cout << std::setw(93) << "But remember one thing… coming here was your choice." << std::endl;
	std::cout << std::setw(58) << "Leaving won’t be." << std::endl;
	std::cout << std::setw(92) << "A supernatural force is wandering through this house." << std::endl;
    std::cout << std::setw(94) << "When you enter a room, if you see an upside-down cross ";
    std::cout << "or smell something rotten," << std::endl;
    std::cout << std::setw(57) << "leave immediately." << std::endl;
    std::cout << std::setw(85) << "If you ever find a body, report it right away." << std::endl;
    std::cout << std::setw(87) << "You have two chances to guess who the killer is." << std::endl;
    std::cout << std::setw(61) << "If you choose wrong…" << std::endl;
    std::cout << std::setw(67) << "you’ll be the next victim." << std::endl;
    std::cout << std::setw(49) << "Good luck." << std::endl;
	
	
	bool win = false;
	spawn(guest1 , b1 , b2 , mh , rr , body);
	while(k.kill < 3 && p.guess < 2 && !win) {
	    if(p.place == 0) {
	        h[0][1] = p.symbol;
	        showEntrance(e);
	        showHall(h);
	        std::cout << "Number of your guesses: " << p.guess << std::endl;
	        std::cout << "You are located in the Hall.\n";
	        std::cout << "You can enter Bedroom1, Bedroom2, or the Main Hall.\n";
	        std::cout << "Press 1 to enter Bedroom1, 2 to enter Bedroom2, and 3 to enter the Main Hall: ";
	        std::cin >> p.place;
	        //Input validation
	        while(p.place != 1 && p.place != 2 && p.place != 3) {
	            std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	            std::cin >> p.place;
	        }
	        p.turn++;
	        if((p.turn % 5) == 0) {
	            killBedRoom(b1 , guest2 , guest1 , k , body);
	            killBedRoom(b2 , guest2 , guest1 , k , body);
	            killRestRoom(rr , guest2 , guest1 , k , body);
	            killMainHall(mh , guest2 , guest1 , k , body);
	            if(k.kill >= 3) {
	                std::cout << "\nThe demon has killed three people, and you are still\n";
	                std::cout << "lost in your delusions. Now just run because the next soul\n";
	                std::cout << "he drags to hell will be YOURS...";
	            }
	            else {
	                reset(b1 , b2 , mh , rr , body);
	                spawn(guest1 , b1 , b2 , mh , rr , body);
	            }
	        }
	        else {
	            reset(b1 , b2 , mh , rr , body);
	            spawn(guest1 , b1 , b2 , mh , rr , body);
	        }
	        
	    }
	    else if(p.place == 1) {
	        b1[5][7] = p.symbol;
	        showBedRoom(b1 , 1);
	        std::cout << "Number of your guesses: " << p.guess << std::endl;
	        std::cout << "You are located in the Bedroom1.\n";
	        if(b1[2][2] == body || b1[2][5] == body || b1[2][8] == body) {
	            if(b1[2][2] == body)
	                b1[2][2] = ' ';
	            else if(b1[2][5] == body)
	                b1[2][5] = ' ';
	            else if(b1[2][8] == body)
	                b1[2][8] = ' ';
	            char g;
	            std::cout << "\nThere is a corpase here that has been brutally mutilated.\n";
	            std::cout << "Do you want to guess who the killer is?\n";
	            std::cout << "place answer with Y(yes) or N(no): ";
	            std::cin >> g;
	            //Input validation
	            while(g != 'Y' && g != 'N') {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                std::cin >> g;
	            }
	            if(g == 'Y') {
	                std::cout << "Please enter your guess by typing the uppercase first letter of ";
	                std::cout << "the guest's name(Z , S , A , M , P): ";
	                std::cin >> p.guessN;
	                //Input validation
	                bool valid = false;
	                for(int i = 0 ; i < 5 ; i++) {
	                    if(guest1[i].symbol == p.guessN) {
	                        valid = true;
	                    }
	                }
	                while(!valid) {
	                    std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                    std::cin >> p.guessN;
	                    for(int i = 0 ; i < 5 ; i++) {
	                        if(guest1[i].symbol == p.guessN) {
	                            valid = true;
	                        }
	                    }
	                }
	                if(p.guessN == k.symbol) {
	                    std::cout << "\nCongratulations! You have successfully identified the\n";
	                    std::cout << "demonic crature and cleansed the house of supernatural\n";
	                    std::cout << "forces. However, DO NOT ENTER a party uninvited. You were lucky this time,\n";
	                    std::cout << "and you may not be so fortuate in the future...";
	                    win = true;
	                }
	                else {
	                    p.guess++;
	                    if(p.guess >= 2) {
	                        std::cout << "\nYou have exhausted all your chances. There is no escape.\n";
	                        std::cout << "There is nowhere to hide. He will eventually find you and\n";
	                        std::cout << "drag your soul to hell\n";
	                        std::cout << "MAY GOD HAVE MERCY ON YOUR SOUL.";
	                    }
	                    else {
	                        std::cout << "\nYou guessed wrong. You now have only one chance left.\n";
	                        std::cout << "Be careful, there won't ve another.\n";
	                        std::cout << "You now return to the hall";
	                        p.place = 0;
	                        p.turn++;
	                        if((p.turn % 5) == 0) {
	                            killBedRoom(b1 , guest2 , guest1 , k , body);
	                            killBedRoom(b2 , guest2 , guest1 , k , body);
	                            killRestRoom(rr , guest2 , guest1 , k , body);
	                            killMainHall(mh , guest2 , guest1 , k , body);
	                            if(k.kill >= 3) {
	                                std::cout << "\nThe demon has killed three people, and you are still\n";
	                                std::cout << "lost in your delusions. Now just run because the next soul\n";
	                                std::cout << "he drags to hell will be YOURS...";
	                            }
	                            else {
	                                reset(b1 , b2 , mh , rr , body);
	                                spawn(guest1 , b1 , b2 , mh , rr , body);
	                            }
	                       }
	                       else {
	                           reset(b1 , b2 , mh , rr , body);
	                           spawn(guest1 , b1 , b2 , mh , rr , body);
	                       }
	                    }
	                }
	            }
	            else {
	                std::cout << "\nYou kept your choice, now you go back to the hall.\n";
	                std::cout << "Staying in this room is DANGEROUS!";
	                p.place = 0;
	                p.turn++;
	                if((p.turn % 4) == 0) {
	                    killBedRoom(b1 , guest2 , guest1 , k , body);
	                    killBedRoom(b2 , guest2 , guest1 , k , body);
	                    killRestRoom(rr , guest2 , guest1 , k , body);
	                    killMainHall(mh , guest2 , guest1 , k , body);
	                    if(k.kill >= 3) {
	                        std::cout << "\nThe demon has killed three people, and you ate still\n";
	                        std::cout << "lost in your delusions. Now just run because the next soul\n";
	                        std::cout << "he drags to hell will be YOURS...";
	                    }
	                    else {
	                        reset(b1 , b2 , mh , rr , body);
	                        spawn(guest1 , b1 , b2 , mh , rr , body);
	                    }
	                }
	                else {
	                   reset(b1 , b2 , mh , rr , body);
	                   spawn(guest1 , b1 , b2 , mh , rr , body);
	                }
	            }
	        }
	        else {
	            std::cout << "Now, after carefully examining Bedroom 1 and observing\n";
	            std::cout << "all the guest, press Enter to return to the hall: ";
	            //Input validation
	            std::string e;
	            std::cin.ignore();
	            getline(std::cin , e);
	            while(e.length() > 0) {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                getline(std::cin , e);
	            }
	            p.place = 0;
	            p.turn++;
	            if((p.turn % 3) == 0) {
	                killBedRoom(b1 , guest2 , guest1 , k , body);
	                killBedRoom(b2 , guest2 , guest1 , k , body);
	                killRestRoom(rr , guest2 , guest1 , k , body);
	                killMainHall(mh , guest2 , guest1 , k , body);
	                if(k.kill >= 3) {
	                    std::cout << "\nThe demon has killed three people, and you ate still\n";
	                    std::cout << "lost in your delusions. Now just run because the next soul\n";
	                    std::cout << "he drags to hell will be YOURS...";
	                }
	               else {
	                   reset(b1 , b2 , mh , rr , body);
	                   spawn(guest1 , b1 , b2 , mh , rr , body);
	               }
	            }
	        }
	    }
	    else if(p.place == 2) {
	        b2[5][7] = p.symbol;
	        showBedRoom(b2 , 2);
	        std::cout << "Number of your guesses: " << p.guess << std::endl;
	        std::cout << "You are located in the Bedroom2.\n";
	        if(b2[2][2] == body || b2[2][5] == body || b2[2][8] == body) {
	            if(b2[2][2] == body)
	                b2[2][2] = ' ';
	            else if(b2[2][5] == body)
	                b2[2][5] = ' ';
	            else if(b2[2][8] == body)
	                b2[2][8] = ' ';
	            char g;
	            std::cout << "\nThere is a corpase here that has been brutally mutilated.\n";
	            std::cout << "Do you want to guess who the killer is?\n";
	            std::cout << "place answer with Y(yes) or N(no): ";
	            std::cin >> g;
	            //Input validation
	            while(g != 'Y' && g != 'N') {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                std::cin >> g;
	            }
	            if(g == 'Y') {
	                std::cout << "Please enter your guess by typing the uppercase first letter of ";
	                std::cout << "the guest's name(Z , S , A , M , P): ";
	                std::cin >> p.guessN;
	                //Input validation
	                bool valid = false;
	                for(int i = 0 ; i < 5 ; i++) {
	                    if(guest1[i].symbol == p.guessN) {
	                        valid = true;
	                    }
	                }
	                while(!valid) {
	                    std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                    std::cin >> p.guessN;
	                    for(int i = 0 ; i < 5 ; i++) {
	                        if(guest1[i].symbol == p.guessN) {
	                            valid = true;
	                        }
	                    }
	                }
	                if(p.guessN == k.symbol) {
	                    std::cout << "\nCongratulations! You have successfully identified the\n";
	                    std::cout << "demonic crature and cleansed the house of supernatural\n";
	                    std::cout << "forces. However, DO NOT ENTER a party uninvited. You were lucky this time,\n";
	                    std::cout << "and you may not be so fortuate in the future...";
	                    win = true;
	                }
	                else {
	                    p.guess++;
	                    if(p.guess >= 2) {
	                        std::cout << "\nYou have exhausted all your chances. There is no escape.\n";
	                        std::cout << "There is nowhere to hide. He will eventually find you and\n";
	                        std::cout << "drag your soul to hell\n";
	                        std::cout << "MAY GOD HAVE MERCY ON YOUR SOUL.";
	                    }
	                    else {
	                        std::cout << "\nYou guessed wrong. You now have only one chance left.\n";
	                        std::cout << "Be careful, there won't ve another.\n";
	                        std::cout << "You now return to the hall";
	                        p.place = 0;
	                        p.turn++;
	                        if((p.turn % 5) == 0) {
	                            killBedRoom(b1 , guest2 , guest1 , k , body);
	                            killBedRoom(b2 , guest2 , guest1 , k , body);
	                            killRestRoom(rr , guest2 , guest1 , k , body);
	                            killMainHall(mh , guest2 , guest1 , k , body);
	                            if(k.kill >= 3) {
	                                std::cout << "\nThe demon has killed three people, and you ate still\n";
	                                std::cout << "lost in your delusions. Now just run because the next soul\n";
	                                std::cout << "he drags to hell will be YOURS...";
	                            }
	                            else {
	                                reset(b1 , b2 , mh , rr , body);
	                                spawn(guest1 , b1 , b2 , mh , rr , body);
	                            }
	                                
	                       }
	                       else {
	                           reset(b1 , b2 , mh , rr , body);
	                           spawn(guest1 , b1 , b2 , mh , rr , body);
	                       }
	                    }
	                }
	            }
	            else if(g == 'N') {
	                std::cout << "\nYou kept your choice, now you go back to the hall.\n";
	                std::cout << "Staying in this room is DANGEROUS!\n";
	                p.place = 0;
	                p.turn++;
	                if((p.turn % 5) == 0) {
	                    killBedRoom(b1 , guest2 , guest1 , k , body);
	                    killBedRoom(b2 , guest2 , guest1 , k , body);
	                    killRestRoom(rr , guest2 , guest1 , k , body);
	                    killMainHall(mh , guest2 , guest1 , k , body);
	                    if(k.kill >= 3) {
	                        std::cout << "\nThe demon has killed three people, and you ate still\n";
	                        std::cout << "lost in your delusions. Now just run because the next soul\n";
	                        std::cout << "he drags to hell will be YOURS...";
	                    }
	                    else {
	                        reset(b1 , b2 , mh , rr , body);
	                        spawn(guest1 , b1 , b2 , mh , rr , body);
	                    }
	                }
	                else {
	                    reset(b1 , b2 , mh , rr , body);
	                    spawn(guest1 , b1 , b2 , mh , rr , body);
	                }
	            }
	        }
	        else {
	            std::cout << "Now, after carefully examining Bedroom 2 and observing\n";
	            std::cout << "all the guest, press Enter to return to the hall: ";
	            //Input validation
	            std::string e;
	            std::cin.ignore();
	            getline(std::cin , e);
	            while(e.length() > 0) {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                getline(std::cin , e);
	            }
	            p.place = 0;
	            p.turn++;
	            if((p.turn % 5) == 0) {
	                killBedRoom(b1 , guest2 , guest1 , k , body);
	                killBedRoom(b2 , guest2 , guest1 , k , body);
	                killRestRoom(rr , guest2 , guest1 , k , body);
	                killMainHall(mh , guest2 , guest1 , k , body);
	                if(k.kill >= 3) {
	                    std::cout << "\nThe demon has killed three people, and you are still\n";
	                    std::cout << "lost in your delusions. Now just run because the next soul\n";
	                    std::cout << "he drags to hell will be YOURS...";
	                }
	               else {
	                   reset(b1 , b2 , mh , rr , body);
	                   spawn(guest1 , b1 , b2 , mh , rr , body); 
	               }
	                 
	            }
	            else {
	                reset(b1 , b2 , mh , rr , body);
	                spawn(guest1 , b1 , b2 , mh , rr , body);
	            }
	        }
	    }
	    else if(p.place == 3) {
	        mh[1][16] = p.symbol;
	        showMainHall(mh);
	        std::cout << "Number of your guesses: " << p.guess << std::endl;
	        std::cout << "You are located in the Main Hall.\n";
	        if(mh[8][14] == body || mh[3][3] == body || mh[5][11] == body || mh[5][13] == body) {
	            if(mh[8][14] == body)
	                mh[8][14] = ' ';
	            else if(mh[3][3] == body)
	                mh[3][3] = ' ';
	            else if(mh[5][11] == body)
	                mh[5][11] = ' ';
	            else if(mh[5][13] == body)
	                mh[5][13] = ' ';
	            char g;
	            std::cout << "\nThere is a corpase here that has been brutally mutilated.\n";
	            std::cout << "Do you want to guess who the killer is?\n";
	            std::cout << "place answer with Y(yes) or N(no): ";
	            std::cin >> g;
	            //Input validation
	            while(g != 'Y' && g != 'N') {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                std::cin >> g;
	            }
	            if(g == 'Y') {
	                std::cout << "Please enter your guess by typing the uppercase first letter of ";
	                std::cout << "the guest's name(Z , S , A , M , P): ";
	                std::cin >> p.guessN;
	                //Input validation
	                bool valid = false;
	                for(int i = 0 ; i < 5 ; i++) {
	                    if(guest1[i].symbol == p.guessN) {
	                        valid = true;
	                    }
	                }
	                while(!valid) {
	                    std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                    std::cin >> p.guessN;
	                    for(int i = 0 ; i < 5 ; i++) {
	                        if(guest1[i].symbol == p.guessN) {
	                            valid = true;
	                        }
	                    }
	                }
	                if(p.guessN == k.symbol) {
	                    std::cout << "\nCongratulations! You have successfully identified the\n";
	                    std::cout << "demonic crature and cleansed the house of supernatural\n";
	                    std::cout << "forces. However, DO NOT ENTER a party uninvited. You were lucky this time,\n";
	                    std::cout << "and you may not be so fortuate in the future...";
	                    win = true;
	                }
	                else {
	                    p.guess++;
	                    if(p.guess >= 2) {
	                        std::cout << "\nYou have exhausted all your chances. There is no escape.\n";
	                        std::cout << "There is nowhere to hide. He will eventually find you and\n";
	                        std::cout << "drag your soul to hell\n";
	                        std::cout << "MAY GOD HAVE MERCY ON YOUR SOUL.";
	                    }
	                    else {
	                        int d;
	                        std::cout << "\nYou guessed wrong. You now have only one chance left.\n";
	                        std::cout << "Be careful, there won't ve another.\n";
	                        std::cout << "Press 4 to enter the Restroom, or press 0 to enter the Hall: ";
	                        std::cin >> d;
	                        //Input validation
	                        while(d != 0 && d != 0) {
	                            std::cout << "! Input is invalid ! Please make sure you are using one of the specified"; 
	                            std::cout << "opions: ";
	                            std::cin >> d;
	                        }
	                        p.place = d;
	                        p.turn++;
	                        if((p.turn) % 5 == 0) {
	                            killBedRoom(b1 , guest2 , guest1 , k , body);
	                            killBedRoom(b2 , guest2 , guest1 , k , body);
	                            killRestRoom(rr , guest2 , guest1 , k , body);
	                            killMainHall(mh , guest2 , guest1 , k , body);
	                            if(k.kill >= 3) {
	                                std::cout << "\nThe demon has killed three people, and you are still\n";
	                                std::cout << "lost in your delusions. Now just run because the next soul\n";
	                                std::cout << "he drags to hell will be YOURS...";
	                            }
	                            else {
	                                reset(b1 , b2 , mh , rr , body);
	                                spawn(guest1 , b1 , b2 , mh , rr , body);
	                            }
	                                
	                        }
	                        else {
	                            reset(b1 , b2 , mh , rr , body);
	                            spawn(guest1 , b1 , b2 , mh , rr , body);
	                        }
	                    }
	                }
	            }
	            else if(g == 'N') {
	                int t;
	                std::cout << "\nYou kept your choice, now exit the Main Hall immediately!\n";
	                std::cout << "press 0 to enter the Hall, or press 4 to enter the Restroom: ";
	                std::cin >> t;
	                //Input validation
	                while(t != 0 && t != 4) {
	                    std::cout << "! Input is invalid ! Please make sure you are using one of the specified"; 
	                    std::cout << "opions: ";
	                    std::cin >> t;
	                }
	                p.place = t;
	                p.turn++;
	                if((p.turn % 5) == 0) {
	                    killBedRoom(b1 , guest2 , guest1 , k , body);
	                    killBedRoom(b2 , guest2 , guest1 , k , body);
	                    killRestRoom(rr , guest2 , guest1 , k , body);
	                    killMainHall(mh , guest2 , guest1 , k , body);
	                    if(k.kill >= 3) {
	                        std::cout << "\nThe demon has killed three people, and you are still\n";
	                        std::cout << "lost in your delusions. Now just run because the next soul\n";
	                        std::cout << "he drags to hell will be YOURS...";
	                    }
	                    else {
	                       reset(b1 , b2 , mh , rr , body);
	                       spawn(guest1 , b1 , b2 , mh , rr , body);
	                    }
	                }
	                else {
	                    reset(b1 , b2 , mh , rr , body);
	                    spawn(guest1 , b1 , b2 , mh , rr , body);
	                }
	            }
	        }
	        else {
	            int e;
	            std::cout << "Now, after carefully examining the Main Hall and observing\n";
	            std::cout << "all the guest, you can enter the restroom by pressing 4, or return ot \n";
	            std::cout << "the Hall by pressing 0 : ";
	            std::cin >> e;
	            //Input validation
	            while(e != 4 && e != 0) {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                std::cin >> e;
	            }
	            p.place = e;
	            p.turn++;
	            if((p.turn % 5) == 0) {
	                killBedRoom(b1 , guest2 , guest1 , k , body);
	                killBedRoom(b2 , guest2 , guest1 , k , body);
	                killRestRoom(rr , guest2 , guest1 , k , body);
	                killMainHall(mh , guest2 , guest1 , k , body);
	                if(k.kill >= 3) {
	                    std::cout << "\nThe demon has killed three people, and you are still\n";
	                    std::cout << "lost in your delusions. Now just run because the next soul\n";
	                    std::cout << "he drags to hell will be YOURS...";
	                }
	                else {
	                    reset(b1 , b2 , mh , rr , body);
	                
	                    spawn(guest1 , b1 , b2 , mh , rr , body);
	                }
	                    
	            }
	            else {
	               reset(b1 , b2 , mh , rr , body);
	               spawn(guest1 , b1 , b2 , mh , rr , body);
	            }
	        }
	    }
	    else if(p.place == 4) {
	        rr[1][7] = p.symbol;
	        showRestRoom(rr);
	        std::cout << "Number of your guesses: " << p.guess << std::endl;
	        std::cout << "You are located in the Restroom.\n";
	        if(rr[4][2] == body || rr[4][4] == body) {
	            if(rr[4][2] == body)
	                rr[4][2] = ' ';
	            else if(rr[4][4] == body)
	                rr[4][4] = ' ';
	            char o;
	            std::cout << "\nThere is a corpase here that has been brutally mutilated.\n";
	            std::cout << "Do you want to guess who the killer is?\n";
	            std::cout << "place answer with Y(yes) or N(no): ";
	            std::cin >> o;
	            //Input validation
	            while(o != 'Y' && o != 'N') {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                std::cin >> o;
	            }
	            if(o == 'Y') {
	                std::cout << "Please enter your guess by typing the uppercase first letter of ";
	                std::cout << "the guest's name(Z , S , A , M , P): ";
	                std::cin >> p.guessN;
	                //Input validation
	                bool valid = false;
	                for(int i = 0 ; i < 5 ; i++) {
	                    if(guest1[i].symbol == p.guessN) {
	                        valid = true;
	                    }
	                }
	                while(!valid) {
	                    std::cout << "! Input is invalid ! Please make sure you are using one of the specified ";
	                    std::cout << "opions: ";
	                    std::cin >> p.guessN;
	                    for(int i = 0 ; i < 5 ; i++) {
	                        if(guest1[i].symbol == p.guessN) {
	                            valid = true;
	                        }
	                    }
	                }
	                if(p.guessN == k.symbol) {
	                    std::cout << "\nCongratulations! You have successfully identified the\n";
	                    std::cout << "demonic crature and cleansed the house of supernatural\n";
	                    std::cout << "forces. However, DO NOT ENTER a party uninvited. You were lucky this time,\n";
	                    std::cout << "and you may not be so fortuate in the future...";
	                    win = true;
	                }
	                else {
	                   p.guess++;
	                   if(p.guess >= 2) {
	                       std::cout << "\nYou have exhausted all your chances. There is no escape.\n";
	                       std::cout << "There is nowhere to hide. He will eventually find you and\n";
	                       std::cout << "drag your soul to hell\n";
	                       std::cout << "MAY GOD HAVE MERCY ON YOUR SOUL.";
	                   }
	                   else {
	                       std::cout << "\nYou guessed wrong. You now have only one chance left.\n";
	                       std::cout << "Be careful, there won't ve another.\n";
	                       std::cout << "Now you go back to the Main Hall.";
	                       std::cout << "Staying in the Restroom is DANGEROUS!";
	                       p.place = 3;
	                       p.turn++;
	                       if((p.turn % 5) == 0) {
	                           killBedRoom(b1 , guest2 , guest1 , k , body);
	                           killBedRoom(b2 , guest2 , guest1 , k , body);
	                           killRestRoom(rr , guest2 , guest1 , k , body);
	                           killMainHall(mh , guest2 , guest1 , k , body);
	                           if(k.kill >= 3) {
	                               std::cout << "\nThe demon has killed three people, and you are still\n";
	                               std::cout << "lost in your delusions. Now just run because the next soul\n";
	                               std::cout << "he drags to hell will be YOURS...";
	                           }
	                           else {
	                              reset(b1 , b2 , mh , rr , body);
	                              spawn(guest1 , b1 , b2 , mh , rr , body);
	                           }
	                       }
	                       else {
	                           reset(b1 , b2 , mh , rr , body);
	                           spawn(guest1 , b1 , b2 , mh , rr , body);
	                       }
	                   }
	                }
	            }
	            else if(o == 'N') {
	                std::cout << "\nYou kept your choice, now you go back to the Main Hall.\n";
	                std::cout << "Staying in this room is DANGEROUS!";
	                p.place = 3;
	                p.turn++;
	                if((p.turn % 4) == 0) {
	                    killBedRoom(b1 , guest2 , guest1 , k , body);
	                    killBedRoom(b2 , guest2 , guest1 , k , body);
	                    killRestRoom(rr , guest2 , guest1 , k , body);
	                    killMainHall(mh , guest2 , guest1 , k , body);
	                    if(k.kill >= 3) {
	                        std::cout << "\nThe demon has killed three people, and you are still\n";
	                        std::cout << "lost in your delusions. Now just run because the next soul\n";
	                        std::cout << "he drags to hell will be YOURS...";
	                    }
	                    else {
	                        reset(b1 , b2 , mh , rr , body);
	                        spawn(guest1 , b1 , b2 , mh , rr , body);
	                    }
	                }
	                else {
	                   reset(b1 , b2 , mh , rr , body);
	                   spawn(guest1 , b1 , b2 , mh , rr , body);
	                }
	            }
	        }
	        else {
	            std::cout << "Now, after carefully examining the Restroom and observing\n";
	            std::cout << "all the guest, press Enter to return to the Main hall: ";
	            std::string u;
	            std::cin.ignore();
	            getline(std::cin , u);
	            while(u.length() > 0) {
	                std::cout << "! Input is invalid ! Please make sure you are using one of the specified opions: ";
	                getline(std::cin , u);
	            }
	            p.place = 3;
	            p.turn++;
	            if((p.turn % 5) == 0) {
	               killBedRoom(b1 , guest2 , guest1 , k , body);
	               killBedRoom(b2 , guest2 , guest1 , k , body);
	               killRestRoom(rr , guest2 , guest1 , k , body);
	               killMainHall(mh , guest2 , guest1 , k , body);
	               if(k.kill >= 3) {
	                   std::cout << "\nThe demon has killed three people, and you are still\n";
	                   std::cout << "lost in your delusions. Now just run because the next soul\n";
	                   std::cout << "he drags to hell will be YOURS...";
	               }
	               else {
	                  reset(b1 , b2 , mh , rr , body);
	                  spawn(guest1 , b1 , b2 , mh , rr , body);
	               }
	            }
	            else {
	                reset(b1 , b2 , mh , rr , body);
	                spawn(guest1 , b1 , b2 , mh , rr , body);
	            }
	        }
	    }
	} 
	
	
	return 0;
}

//Fucntion that shows the restroom 
void showRestRoom(char arr[6][10]) {
    std::cout << std::setw(22) << "Restroom" << std::endl;
    for(int i = 0 ; i < 6 ; i++) {
        for(int j = 0 ; j < 10 ; j++) {
            std::cout << arr[i][j] << "   ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }    
}

//Function that shows the entrance 
void showEntrance(char arr[3][10]) {
    for(int i = 0 ; i < 3 ; i++) {
        for(int j = 0 ; j < 10 ; j++) {
            std::cout << arr[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

//Function that shows the hall 
void showHall(char arr[8][3]) {
    std::cout << std::setw(19) << "Hall" << std::endl;
    for(int i = 0 ; i < 8 ; i++) {
        std::cout << "              ";
        for(int j = 0 ; j < 3 ; j++) {
            std::cout << arr[i][j] << ' '; 
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

//Function that shows a bedroom 
void showBedRoom(char arr[10][10] , int i) {
    std::cout << std::setw(18) << "Bedroom " << i << std::endl;
    for(int i = 0 ; i < 10 ; i++) {
        for(int j = 0 ; j < 10 ; j++) {
            std::cout << arr[i][j] << "  ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    } 
}

//Function that shows the main hall 
void showMainHall(char arr[10][20]) {
    std::cout << std::setw(45) << "Main Hall" << std::endl;
    for(int i = 0 ; i < 10 ; i++) {
        for(int j = 0 ; j < 20 ; j++) {
            std::cout << arr[i][j] << "   ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

//Map - Hall
void hall(char array1[3][10] , char array2[8][3]) {
    //Entrance
    char enter[8] = {'E' , 'n' , 't' , 'r' , 'a' , 'n' , 'c' , 'e'};
    for(int i = 0 ; i < 10 ; i++) {
        array1[0][i] = '-';
    }
    
    array1[1][0] = '|';
    array1[1][9] = '|';
    for(int i = 1 ; i < 9 ; i++) {
        array1[1][i] = enter[i - 1];
    }
    
    for(int i = 0 ; i < 10 ; i++) {
        array1[2][i] = '-';
    }
    
    //Hall 
    array2[2][0] = '?';
    for(int i = 0 ; i < 8 ; i++) {
        if(i != 2) {
            array2[i][0] = '|';
        }
    }
    
    array2[7][1] = '?';
    for(int i = 0 ; i < 8 ; i++) {
        if(i != 7) {
            array2[i][1] = ' ';
        }
    }
    
    array2[5][2] = '?';
    for(int i = 0 ; i < 8 ; i++) {
        if(i != 5) {
            array2[i][2] = '|';
        }
    }
    
    /*
    showEntrance(array1);
    std::cout << std::endl;
    showHall(array2);
    */
}

//Map - Bedroom 1 and 2 
void bedRoom(char array[10][10]) {
    for(int i = 0 ; i < 10 ; i++) {
        for(int j = 0 ; j < 10 ; j++) {
            if((i == 0) || (i == 9)) {
                array[i][j] = '_';
            }
            else if((j == 0) || (j == 9)) {
                array[i][j] = '|';
            }
            else {
                array[i][j] = ' ';
            }
        }
    }
    //array[2][2] = '&' , array[2][5] = '&' , array[2][8] = '&';
    //array[5][7] = '*';
    
    //std::cout << std::setw(18) << "Bedroom " << i << std::endl;
    //showBedRoom(array);
}

//Map - Main Hall 
void mainHall(char array[10][20]) {
    char bar[3] = {'B' , 'a' , 'r'};
    char piano[5] = {'p' , 'i' , 'a' , 'n' , 'o'};
    
    for(int i = 0 ; i < 10 ; i++) {
        for(int j = 0 ; j < 20 ; j++) {
            if(i == 0 || i == 9) {
                array[i][j] = '_';
            }
            else if(j == 0 || j == 19) {
                array[i][j] = '|';
            }
            else {
                array[i][j] = ' ';
            }
        }
    }
    int brow = 2 , bcolumn = 2;
    for(int i = 0 ; i < 3 ; i++) {
        array[brow][bcolumn + i] = bar[i]; 
    }
    int prow = 7 , pcolumn = 12;
    for(int j = 0 ; j < 5 ; j++) {
        array[prow][pcolumn + j] = piano[j];
    }
    /*
    array[8][14] = '&', array[3][3] = '&', array[5][11] = '&' , array[5][13] = '&';
    array[1][16] = '*';
    std::cout << std::setw(45) << "Main Hall" << std::endl;
    showMainHall(array);
    */
}

//Map - Restroom
void restRoom(char array[6][10]) {
    for(int i = 0 ; i < 6 ; i++) {
        for(int j = 0 ; j < 10 ; j++) {
            if(i == 0 || i == 5) {
                array[i][j] = '_';
            }
            else if(j == 0 || j == 9) {
                array[i][j] = '|';
            }
            else {
                array[i][j] = ' ';
            }
        }
    }
    /*
    array[4][2] = '&' , array[4][4] = '&';
    array[1][7] = '*';
    std::cout << std::setw(22) << "Restroom" << std::endl;
    showRestRoom(array);
    */
}

//Function that randomly spawns mpcs
void spawn(mpc arr1[5] , char arr2[10][10] , char arr3[10][10] , char arr4[10][20] , char arr5[6][10] , const char y) {
    
    //Making sure that the capacity of each room is respected
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;
    int r4 = 0;
    
    //We should check if there is a body in a room and increase it's capacity
    int i1 = 2;
    while(i1 <= 8) {
        if(arr2[2][i1] == y) {
            r1++;
        }
        i1 += 3;
    }
    int i2 = 2;
    while(i2 <= 8) {
        if(arr3[2][i2] == y) {
            r2++;
        }
        i2 += 3;
    }
    
    if(arr4[8][14] == y)
        r3++;
    else if(arr4[3][3] == y)
        r3++;
    else if(arr4[5][11] == y)
        r3++;
    else if(arr4[5][13] == y)
        r3++;
    
    if(arr5[4][2] == y)
        r4++;
    else if(arr5[4][4] == y)
        r4++;
    
    for(int i = 0 ; i < 5 ; i++) {
        
        bool b = false;
        while(!b) {
            int room = rand() % 4;
            if(room == BEDROOM1 && r1 < 3) {
                arr1[i].place = room;
                r1++;
                b = true;
            }
            else if(room == BEDROOM2 && r2 < 3) {
                arr1[i].place = room;
                r2++;
                b = true;
            }
            else if(room == MAINHALL && r3 < 4) {
                arr1[i].place = room;
                r3++;
                b = true;
            }
            else if(room == RESTROOM && r4 < 2) {
                arr1[i].place = room;
                r4++;
                b = true;
            }
        }
    }
     
	        
	for(int j = 0 ; j < 5 ; j++) {
	    if(arr1[j].alive) {
	        if(arr1[j].place == BEDROOM1) {
	            if(arr2[2][2] == ' ') {
	                arr2[2][2] = arr1[j].symbol;
	            }
	            else if(arr2[2][5] == ' ') {
	                arr2[2][5] = arr1[j].symbol;
	            }
	            else if(arr2[2][8] == ' ') {
	                arr2[2][8] = arr1[j].symbol;
	            }
	        }
	        else if(arr1[j].place == BEDROOM2) {
	            if(arr3[2][2] == ' ') {
	                arr3[2][2] = arr1[j].symbol;
	            }
	            else if(arr3[2][5] == ' ') {
	                arr3[2][5] = arr1[j].symbol;
	            }
	            else if(arr3[2][8] == ' ') {
	                arr3[2][8] = arr1[j].symbol;
	            }
	        }
	        else if(arr1[j].place == MAINHALL) {
	            if(arr4[8][14] == ' ') {
	                arr4[8][14] = arr1[j].symbol;
	            }
	            else if(arr4[3][3] == ' ') {
	                arr4[3][3] = arr1[j].symbol;
	            }
	            else if(arr4[5][11] == ' ') {
	                arr4[5][11] = arr1[j].symbol;
	            }
	            else if(arr4[5][13] == ' ') {
	                arr4[5][13] = arr1[j].symbol;
	            }
	        }
	        else if(arr1[j].place == RESTROOM) {
	            if(arr5[4][2] == ' ') {
	                arr5[4][2] = arr1[j].symbol;
	            }
	            else if(arr5[4][4] == ' ') {
	                arr5[4][4] = arr1[j].symbol;
	            }
	        }
	    }
	}
}


//Kill mechanic in bedrooms 
void killBedRoom(char array1[10][10] , mpc array2[4] , mpc array3[5] , killer &x , const char y) {
    if(!(array1[2][2] != ' ' && array1[2][5] != ' ' && array1[2][8] != ' ')) {
        if(array1[2][2] == x.symbol || array1[2][5] == x.symbol || array1[2][8] == x.symbol) {
            for(int i = 0 ; i < 4 ; i++) {
                if(array1[2][2] == array2[i].symbol) {
                    array2[i].symbol = y;
                    array2[i].alive = false;
                    array1[2][2] = array2[i].symbol;
                    for(int j = 0 ; j < 5 ; j++) {
                        if(array3[j].name == array2[i].name)
                            array3[j].alive = false;
                    }
                    x.kill++;
                }
                else if(array1[2][5] == array2[i].symbol) {
                    array2[i].symbol = y;
                    array2[i].alive = false;
                    array1[2][5] = array2[i].symbol;
                    for(int j = 0 ; j < 5 ; j++) {
                        if(array3[j].name == array2[i].name)
                            array3[j].alive = false;
                    }
                    x.kill++;
                }
                else if(array1[2][8] == array2[i].symbol) {
                    array2[i].symbol = y;
                    array2[i].alive = false;
                    array1[2][8] = array2[i].symbol;
                    for(int j = 0 ; j < 5 ; j++) {
                        if(array3[j].name == array2[i].name)
                            array3[j].alive = false;
                    }
                    x.kill++;
                }
            }
        }
    }
}

//Kill mechanic in restroom 
void killRestRoom(char arr1[6][10] , mpc arr2[4] , mpc arr3[5] , killer &x , const char y) {
    for(int i = 0 ; i < 4 ; i++) {
        if(arr1[4][2] == arr2[i].symbol && arr1[4][4] == x.symbol) {
            arr2[i].symbol = y;
            arr2[i].alive = false;
            arr1[4][2] = y;
            for(int j = 0 ; j < 5 ; j++) {
                if(arr3[j].name == arr2[i].name)
                    arr3[j].alive = false;
            }
            x.kill++;
        }
        else if(arr1[4][4] == arr2[i].symbol && arr1[4][2] == x.symbol) {
            arr2[i].symbol = y;
            arr2[i].alive = false;
            arr1[4][4] = y;
            for(int j = 0 ; j < 5 ; j++) {
                if(arr3[j].name == arr2[i].name)
                    arr3[j].alive = false;
            }
            x.kill++;
        }
    }
}


//Kill mechanic in main hall 
void killMainHall(char arr1[10][20] , mpc arr2[4] , mpc arr3[5] , killer &x , const char y) {
    
    const int mainHallSpots = 4;
    int mainHallR[mainHallSpots] = {8 , 3 , 5 , 5};
    int mainHallC[mainHallSpots] = {14 , 3 , 11 , 13};
    
    int noEmpye = 0;
    for(int i = 0 ; i < mainHallSpots ; i++) {
        if(arr1[mainHallR[i]][mainHallC[i]] != ' ') {
            noEmpye++;
        }
    }
    
    bool killerInMain = false;
    for(int i = 0 ; i < mainHallSpots ; i++) {
        if(arr1[mainHallR[i]][mainHallC[i]] == x.symbol) {
            killerInMain = true;
        }
    }
    
    std::string victim;
    if(killerInMain && (noEmpye == 2)) {
        for(int i = 0 ; i < 4 ; i++) {
            for(int j = 0 ; j < mainHallSpots ; j++) {
                if(arr2[i].symbol == arr1[mainHallR[j]][mainHallC[j]]) {
                    arr2[i].symbol = y;
                    arr2[i].alive = false;
                    arr1[mainHallR[j]][mainHallC[j]] = y;
                    x.kill++;
                    victim = arr2[i].name;
                }
            }
        }
    }
    
    for(int i = 0 ; i < 5 ; i++) {
        if(arr3[i].name == victim) {
            arr3[i].alive = false;
        }
    }
}
//Reset the map before the new spawn 
void reset(char arr1[10][10] , char arr2[10][10] , char arr3[10][20] , char arr4[6][10] , const char y) {
    //Bedroom 1
    if(arr1[2][2] != y) {
        arr1[2][2] = ' ';
    }
    if(arr1[2][5] != y) {
        arr1[2][5] = ' ';
    }
    if(arr1[2][8] != y) {
        arr1[2][8] = ' ';
    }
    
    //Bedroom 2   
    if(arr2[2][2] != y) {
        arr2[2][2] = ' ';
    }
    if(arr2[2][5] != y) {
        arr2[2][5] = ' ';
    }
    if(arr2[2][8] != y) {
        arr2[2][8] = ' ';
    }
    
    //Main hall 
    if(arr3[8][14] != y) {
        arr3[8][14] = ' ';
    }
    if(arr3[3][3] != y) {
        arr3[3][3] = ' ';
    }
    if(arr3[5][11] != y) {
        arr3[5][11] = ' ';
    }
    if(arr3[5][13] != y) {
        arr3[5][13] = ' ';
    }
    
    //Restroom 
    if(arr4[4][2] != y) {
        arr4[4][2] = ' ';
    }
    if(arr4[4][4] != y) {
        arr4[4][4] = ' ';
    }
    
}