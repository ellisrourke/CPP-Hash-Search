#include <iostream>
#include <cstdlib>
#include <string>
#include <tuple>
#include <ctime>
#include <algorithm>
#include <ostream>
#include <fstream>

using namespace std;
string names[100][2] =
        {
                {	"Liam"		,	"Emma"	}	,
                {	"Noah"		,	"Olivia"	}	,
                {	"William"	,	"Ava"	}	,
                {	"James"		,	"Isabella"	}	,
                {	"Oliver"	,	"Sophia"	}	,
                {	"Benjamin"	,	"Charlotte"	}	,
                {	"Elijah"	,	"Mia"	}	,
                {	"Lucas"		,	"Amelia"	}	,
                {	"Mason"		,	"Harper"	}	,
                {	"Logan"		,	"Evelyn"	}	,
                {	"Alexander"	,	"Abigail"	}	,
                {	"Ethan"		,	"Emily"	}	,
                {	"Jacob"		,	"Elizabeth"	}	,
                {	"Michael"	,	"Mila"	}	,
                {	"Daniel"	,	"Ella"	}	,
                {	"Henry"		,	"Avery"	}	,
                {	"Jackson"	,	"Sofia"	}	,
                {	"Sebastian"	,	"Camila"	}	,
                {	"Aiden"		,	"Aria"	}	,
                {	"Matthew"	,	"Scarlett"	}	,
                {	"Samuel"	,	"Victoria"	}	,
                {	"David"		,	"Madison"	}	,
                {	"Joseph"	,	"Luna"	}	,
                {	"Carter"	,	"Grace"	}	,
                {	"Owen"		,	"Chloe"	}	,
                {	"Wyatt"		,	"Penelope"	}	,
                {	"John"		,	"Layla"	}	,
                {	"Jack"		,	"Riley"	}	,
                {	"Luke"		,	"Zoey"	}	,
                {	"Jayden"	,	"Nora"	}	,
                {	"Dylan"		,	"Lily"	}	,
                {	"Grayson"	,	"Eleanor"	}	,
                {	"Levi"		,	"Hannah"	}	,
                {	"Isaac"		,	"Lillian"	}	,
                {	"Gabriel"	,	"Addison"	}	,
                {	"Julian"	,	"Aubrey"	}	,
                {	"Mateo"		,	"Ellie"	}	,
                {	"Anthony"	,	"Stella"	}	,
                {	"Jaxon"		,	"Natalie"	}	,
                {	"Lincoln"	,	"Zoe"	}	,
                {	"Joshua"	,	"Leah"	}	,
                {	"Christopher"	,	"Hazel"	}	,
                {	"Andrew"	,	"Violet"	}	,
                {	"Theodore"	,	"Aurora"	}	,
                {	"Caleb"		,	"Savannah"	}	,
                {	"Ryan"		,	"Audrey"	}	,
                {	"Asher"		,	"Brooklyn"	}	,
                {	"Nathan"	,	"Bella"	}	,
                {	"Thomas"	,	"Claire"	}	,
                {	"Leo"		,	"Skylar"	}	,
                {	"Isaiah"	,	"Lucy"	}	,
                {	"Charles"	,	"Paisley"	}	,
                {	"Josiah"	,	"Everly"	}	,
                {	"Hudson"	,	"Anna"	}	,
                {	"Christian"	,	"Caroline"	}	,
                {	"Hunter"	,	"Nova"	}	,
                {	"Connor"	,	"Genesis"	}	,
                {	"Eli"		,	"Emilia"	}	,
                {	"Ezra"		,	"Kennedy"	}	,
                {	"Aaron"		,	"Samantha"	}	,
                {	"Landon"	,	"Maya"	}	,
                {	"Adrian"	,	"Willow"	}	,
                {	"Jonathan"	,	"Kinsley"	}	,
                {	"Nolan"		,	"Naomi"	}	,
                {	"Jeremiah"	,	"Aaliyah"	}	,
                {	"Easton"	,	"Elena"	}	,
                {	"Elias"		,	"Sarah"	}	,
                {	"Colton"	,	"Ariana"	}	,
                {	"Cameron"	,	"Allison"	}	,
                {	"Carson"	,	"Gabriella"	}	,
                {	"Robert"	,	"Alice"	}	,
                {	"Angel"		,	"Madelyn"	}	,
                {	"Maverick"	,	"Cora"	}	,
                {	"Nicholas"	,	"Ruby"	}	,
                {	"Dominic"	,	"Eva"	}	,
                {	"Jaxson"	,	"Serenity"	}	,
                {	"Greyson"	,	"Autumn"	}	,
                {	"Adam"		,	"Adeline"	}	,
                {	"Ian"		,	"Hailey"	}	,
                {	"Austin"	,	"Gianna"	}	,
                {	"Santiago"	,	"Valentina"	}	,
                {	"Jordan"	,	"Isla"	}	,
                {	"Cooper"	,	"Eliana"	}	,
                {	"Brayden"	,	"Quinn"	}	,
                {	"Roman"		,	"Nevaeh"	}	,
                {	"Evan"		,	"Ivy"	}	,
                {	"Ezekiel"	,	"Sadie"	}	,
                {	"Xavier"	,	"Piper"	}	,
                {	"Jose"		,	"Lydia"	}	,
                {	"Jace"		,	"Alexa"	}	,
                {	"Jameson"	,	"Josephine"	}	,
                {	"Leonardo"	,	"Emery"	}	,
                {	"Bryson"	,	"Julia"	}	,
                {	"Axel"		,	"Delilah"	}	,
                {	"Everett"	,	"Arianna"	}	,
                {	"Parker"	,	"Vivian"	}	,
                {	"Kayden"	,	"Kaylee"	}	,
                {	"Miles"		,	"Sophie"	}	,
                {	"Sawyer"	,	"Brielle"	}	,
                {	"Jason"		,	"Madeline"	}
        };

string subjects[4] = {"Physics","Mathematics","Chemistry","Biology"};

tuple<int,int,int,int> marks[200*4];	// nameid, boy/girl, subject, mark

int getdata()
{
    std::ofstream file("data.txt");


    srand (time(NULL));
    int n = rand()% 50 + 50;
    for(int i = 0; i < n; ++i)	// name id
        for(int j = 0; j < 2; ++j)		// boy or girl
            for(int k = 0; k < 4; ++k)	// subject
                marks[i*8 + j * 4 + k] = make_tuple(i,j,k,rand() % 50 + 50);

    random_shuffle(marks +0, marks + 2 * n * 4);
    for(int k = 0; k < 2 * n * 4; ++k)
        cout << names[get<0>(marks[k])][get<1>(marks[k])] << " " << subjects[get<2>(marks[k])] << " " << get<3>(marks[k]) << endl;
    return 0;
}