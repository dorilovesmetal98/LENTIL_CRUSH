#ifndef START_SCREEN_H_
#define START_SCREEN_H_

#define WIDTH_STARTSCREEN_HOR 92
#define WIDTH_STARTSCREEN_VER 20

#define SPACE 5
#define TEXT_SPACE 5

static char intro[] = "Im Schloss des Königs findet heute ein Fest statt, das 3 Tage dauern soll.\n"
					  "Alle schönen Jungfrauen im Lande sind eingeladen, damit sich der Prinz eine Braut\n"
					  "aussuchen möchte.\n"
			   		  "Du möchtest unbedingt auch dahin und bist schon ganz aufgeregt.\n\n"
				      "Deine böse Stiefmutter hat aber Pläne mit dir.\n\n"
			          "»Da habe ich dir eine Schüssel Linsen in die Asche geschüttet, wenn du die\nLinsen in zwei Stunden wieder ausgelesen hast, so sollst du mitgehen.«\n\n"
			          "Also: sortiere die Linsen!\n"
					  "Tausche Linsen, um mindestens 3 in eine Reihe zu bringen.\n"
					  "Wenn du alle Punkte erreicht hast, darfst du mit zum Fest des Königs.\n\n\n"
			          "                               ARE YOU READY?\n\n"
					  "                | Y |  YES         | N |  NO         | ESC | Spiel beenden\n";
	
			
static char intro_count[] = "\n\n\n\n\n\n\n\n\n"
							"                               SPIEL STARTET IN ";;
					  
static char intro_rant[] = "\n\n\n\n\n\n\n"
						   "                       Leider hast du keine andere Wahl\n\n"
					       "                   Du MUSST die Linsen so oder so sortieren!\n\n\n"
						   "                               SPIEL STARTET IN ";;
						   
static char esc_rant[] = "\n\n\n\n\n\n"
						 "                            Es hilft dir alles nichts:\n\n"
						 "        Solange die Linsen nicht sortiert sind, bleibst du da, wo du bist!\n\n\n\n"
						 "                             SPIEL GEHT WEITER IN ";
						 
static char esc_rant2[] = "\n\n\n\n\n\n\n\n\n"
						  "                                       FUCK";
					
char* render_startscreen();

#endif