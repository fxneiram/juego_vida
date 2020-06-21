#include <allegro.h>
#include <math.h>

#define MAXFILAS 111
#define MAXCOLS 111

int velocidad = 500;

BITMAP *buffer;

BITMAP * borde;
BITMAP * negpo;
BITMAP * blapo;
BITMAP * vacio;
BITMAP * aleatorio;
BITMAP * mundo1;
BITMAP * mundo2;
BITMAP * mundo3;
BITMAP * mundo4;
BITMAP * mundo5;
BITMAP * dibujalo;
BITMAP * negro;
BITMAP * cursor;

char mapa[111][200], mapab[111][200];
void cargar();
void modo1();
void modo2();
void modo3();
void modo4();
void modo5();
void dibujar_mapa();
void jugar();
void pantalla();
void dibujar_mundo();



int main()
{
	allegro_init();
	install_keyboard();
	install_mouse();
	//

	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 700, 0, 0);

	buffer = create_bitmap(1000, 700); //cuadros
	negpo = load_bitmap("2.bmp", NULL);
	blapo = load_bitmap("1.bmp", NULL);
	borde = load_bitmap("3.bmp", NULL);
	//
	vacio = load_bitmap("menu\\0.BMP", NULL);
	aleatorio = load_bitmap("menu\\1.BMP", NULL);
	mundo1 = load_bitmap("menu\\2.BMP", NULL);
	mundo2 = load_bitmap("menu\\3.BMP", NULL);
	mundo3 = load_bitmap("menu\\4.BMP", NULL);
	mundo4 = load_bitmap("menu\\5.BMP", NULL);
	mundo5 = load_bitmap("menu\\6.BMP", NULL);
	dibujalo = load_bitmap("menu\\7.BMP", NULL);
	negro = load_bitmap("menu\\negro.bmp", NULL);
	cursor = load_bitmap("cursor.bmp", NULL);


	while (!key[KEY_ESC]){
		if (mouse_x > 285 && mouse_x < 755 &&	mouse_y > 231 && mouse_y < 284){
			blit(aleatorio, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				cargar();
				blit(negro,buffer,0,0,0,555,1000,700);
				dibujar_mapa();
				jugar();
			}
		}
		else if (mouse_x > 395 && mouse_x < 641 &&	mouse_y > 300 && mouse_y < 356){
			blit(mundo1, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				modo1();
				blit(negro,buffer,0,0,0,555,1000,700);
				dibujar_mapa();
				jugar();
			}
		}
		else if (mouse_x > 395 && mouse_x < 641 &&	mouse_y > 373 && mouse_y < 421){
			blit(mundo2, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				modo2();
				blit(negro,buffer,0,0,0,555,1000,700);
				dibujar_mapa();
				jugar();
			}
		}
		else if (mouse_x > 395 && mouse_x < 641 &&	mouse_y > 441 && mouse_y < 488){
			blit(mundo3, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				modo3();
				dibujar_mapa();
				jugar();
			}
		}
		else if (mouse_x > 395 && mouse_x < 641 &&	mouse_y > 506 && mouse_y < 560){
			blit(mundo4, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				modo4();
				blit(negro,buffer,0,0,0,555,1000,700);
				dibujar_mapa();
				jugar();
			}
		}
		else if (mouse_x > 395 && mouse_x < 641 &&	mouse_y > 578 && mouse_y < 626){
			blit(mundo5, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				modo5();
				blit(negro,buffer,0,0,0,555,1000,700);
				dibujar_mapa();
				jugar();
			}
		}
		else if (mouse_x > 399 && mouse_x < 640 &&	mouse_y > 645 && mouse_y < 694){
			blit(dibujalo, buffer, 0, 0, 0, 0, 1000, 700);
			if (mouse_b & 1){
				clear_keybuf();
				blit(negro,buffer,0,0,0,555,1000,700);
				dibujar_mundo();
			}

		}

		else blit(vacio, buffer, 0, 0, 0, 0, 1000, 700);

		//
		masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13, 22);
		blit(buffer, screen, 0, 0, 0, 0, 1000, 700);
	}
}
END_OF_MAIN();
void cargar(){
	for (int i = 1; i<110; i++){
		for (int j = 1; j<200; j++){
			mapa[i][j] = rand() % 2;
		}
	}
}

void dibujar_mapa(){

	for (int i = 0; i<200; i++){
		mapa[i][0] = 'r';
	}
	for (int i = 0; i<200; i++){
		mapa[110][i] = 'r';
	}
	for (int i = 0; i<200; i++){
		mapa[0][i] = 'r';
	}
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			if (mapa[i][j] == 0){
				draw_sprite(buffer, negpo, j * 5, i * 5);
			}
			if (mapa[i][j] == 1){
				draw_sprite(buffer, blapo, j * 5, i * 5);
			}
			if (mapa[i][j] == 'r'){
				draw_sprite(buffer, borde, j * 5, i * 5);
			}
		}
	}
	for (int i = 0; i<111; i++){
		mapa[i][199] = 'r';
		if (mapa[i][199] == 'r'){
			draw_sprite(buffer, borde, 199 * 5, i * 5);
		}
	}
	pantalla();
}
void jugar(){
	
	int acum = 0, vecino;
	textout_ex(screen, font, "Situacion inicial", 10, 1000, makecol(0, 255, 0), -1);
	textout_ex(screen, font, "Presione una tecla para continuar", 10, 570, makecol(0, 255, 0), -1);
	
	readkey();
	
	while (!key[KEY_Q]){
		//masked_blit(negro,screen,0,0,0,0,1000,700);
		acum++;
		for (int i = 1; i<110; i++){
			for (int j = 1; j<199; j++){
				vecino = 0;
				/// empezamos a contar vecinos
				if (mapa[i][j - 1] == 1)
					vecino += 1;
				if (mapa[i][j + 1] == 1)
					vecino += 1;
				if (mapa[i - 1][j] == 1)
					vecino += 1;
				if (mapa[i + 1][j] == 1)
					vecino += 1;
				if (mapa[i - 1][j - 1] == 1)
					vecino += 1;
				if (mapa[i - 1][j + 1] == 1)
					vecino += 1;
				if (mapa[i + 1][j - 1] == 1)
					vecino += 1;
				if (mapa[i + 1][j + 1] == 1)
					vecino += 1;

				//reglas
				if (mapa[i][j] == 1){
					if (vecino <= 1)
						mapab[i][j] = 0;
					if (vecino >= 2 && vecino <= 3)
						mapab[i][j] = 1;
					if (vecino >= 4)
						mapab[i][j] = 0;
				}
				if (mapa[i][j] == 0){
					if (vecino == 3){
						mapab[i][j] = 1;
					}
					else{
						mapab[i][j] = 0;
					}
				}
			}

		}
		for (int i = 1; i<110; i++){
			for (int j = 1; j<199; j++){
				if (mapab[i][j] == 0){
					draw_sprite(buffer, negpo, j * 5, i * 5);
				}
				else{
					draw_sprite(buffer, blapo, j * 5, i * 5);
				}
			}
		}
		for (int i = 0; i<110; i++){
			for (int j = 0; j<199; j++){
				mapa[i][j] = mapab[i][j];
			}
		}
		//masked_blit(negro,screen,0,0,0,0,1000,700);
		pantalla();
		//masked_blit(negro,screen,0,0,0,0,1000,700);
		textout_ex(screen, font, "P     Aumenta la velocidad de evolucion", 10, 560, makecol(255, 0, 0), -1);
		textout_ex(screen, font, "O     Disminuye la velocidad de evolucion", 10, 570, makecol(255, 0, 0), -1);
		textout_ex(screen, font, "Q     Vuelve al menu", 10, 580, makecol(255, 0, 0), -1);
		textprintf_ex(screen, font, 10, 610, makecol(0, 255, 0), -1, "Retrazo ecolutivo: ");
		textprintf_ex(screen, font, 10, 620, makecol(0, 255, 0), -1, "Iteraciones: ");
		
		textprintf_ex(screen, font, 170, 610, makecol(0, 0, 255), -1, "%d", velocidad);
		textprintf_ex(screen, font, 170, 620, makecol(0, 0, 255), -1, "%d", acum);

		if (key[KEY_P]){
			if (velocidad>50){
				velocidad -= 50;
			}
			if (velocidad<=50 && velocidad>1){
				velocidad-=1;
			}
		}
		if (key[KEY_O]){
			if (velocidad >= 50 && velocidad<1000){
				velocidad += 50;
			}
			if(velocidad>=1 && velocidad<=50){
				velocidad+=1;
			}
		}
		rest(velocidad);

	}
}

void pantalla() {
	blit(buffer, screen, 0, 0, 0, 0, 1000, 700);
}
void modo1(){
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			mapa[i][j] = 0;
		}
	}
	mapa[14][19] = 1;
	mapa[15][19] = 1;
	mapa[16][19] = 1;
	mapa[17][19] = 1;
	mapa[18][19] = 1;
	mapa[19][19] = 1;
	mapa[20][19] = 1;
	mapa[21][19] = 1;
	mapa[22][19] = 1;
	mapa[23][19] = 1;
	mapa[24][19] = 1;
	//
	mapa[19][14] = 1;
	mapa[19][15] = 1;
	mapa[19][16] = 1;
	mapa[19][17] = 1;
	mapa[19][18] = 1;
	mapa[19][19] = 1;
	mapa[19][20] = 1;
	mapa[19][21] = 1;
	mapa[19][22] = 1;
	mapa[19][23] = 1;
	mapa[19][24] = 1;
	
	mapa[23][18] = 1;
	mapa[22][17] = 1;
	mapa[21][16] = 1;
	mapa[20][15] = 1;
	
	mapa[23][20] = 1;
	mapa[22][21] = 1;
	mapa[21][22] = 1;
	mapa[20][23] = 1;
	
	mapa[18][23] = 1;
	mapa[17][22] = 1;
	mapa[16][21] = 1;
	mapa[15][20] = 1;
	
	mapa[18][15] = 1;
	mapa[17][16] = 1;
	mapa[16][17] = 1;
	mapa[15][18] = 1;
}
void modo2(){
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			mapa[i][j] = 0;
		}
	}
	mapa[3][3] = 1;
	mapa[3][4] = 1;
	mapa[3][5] = 1;

	mapa[3][31] = 1;
	mapa[3][32] = 1;
	mapa[3][33] = 1;

	mapa[33][31] = 1;
	mapa[33][32] = 1;
	mapa[33][33] = 1;

	mapa[33][3] = 1;
	mapa[33][4] = 1;
	mapa[33][5] = 1;



}
void modo3(){
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			mapa[i][j] = 0;
		}
	}
	mapa[20][12] = 1;
	mapa[21][13] = 1;
	mapa[21][11] = 1;
	mapa[22][14] = 1;
	mapa[22][10] = 1;
	
	mapa[20][24] = 1;
	mapa[21][25] = 1;
	mapa[21][23] = 1;
	mapa[22][26] = 1;
	mapa[22][22] = 1;
	
	mapa[17][18] = 1;
	mapa[18][19] = 1;
	mapa[18][17] = 1;
	mapa[19][20] = 1;
	mapa[19][16] = 1;
	
	mapa[20][18] = 1;
	mapa[21][19] = 1;
	mapa[21][17] = 1;
	mapa[22][20] = 1;
	mapa[22][16] = 1;
	
	mapa[23][18] = 1;
	mapa[24][19] = 1;
	mapa[24][17] = 1;
	mapa[25][20] = 1;
	mapa[25][16] = 1;

}
void modo4(){
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			mapa[i][j] = 0;
		}
	}
	mapa[15][18] = 1;
	mapa[16][19] = 1;
	mapa[16][17] = 1;
	mapa[17][20] = 1;
	mapa[17][16] = 1;
	mapa[18][15] = 1;
	mapa[18][21] = 1;
	mapa[19][14] = 1;
	mapa[19][22] = 1;
	mapa[20][15] = 1;
	mapa[20][21] = 1;
	mapa[21][15] = 1;
	mapa[21][21] = 1;

	mapa[19][18] = 1;
	mapa[19][17] = 1;
	mapa[19][19] = 1;
	
	mapa[24][18] = 1;
	mapa[23][19] = 1;
	mapa[23][17] = 1;
	mapa[22][20] = 1;
	mapa[22][16] = 1;
	mapa[21][15] = 1;
	mapa[21][21] = 1;
	
}
void modo5(){
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			mapa[i][j] = 0;
		}
	}


	mapa[9][13] = 1;
	mapa[9][15] = 1;
	mapa[9][17] = 1;
	mapa[9][19] = 1;
	mapa[9][21] = 1;
	mapa[9][23] = 1;

	mapa[10][12] = 1;
	mapa[10][14] = 1;
	mapa[10][16] = 1;
	mapa[10][18] = 1;
	mapa[10][20] = 1;
	mapa[10][22] = 1;
	mapa[10][24] = 1;

	mapa[24][13] = 1;
	mapa[24][15] = 1;
	mapa[24][17] = 1;
	mapa[24][19] = 1;
	mapa[24][21] = 1;
	mapa[24][23] = 1;

	mapa[25][12] = 1;
	mapa[25][14] = 1;
	mapa[25][16] = 1;
	mapa[25][18] = 1;
	mapa[25][20] = 1;
	mapa[25][22] = 1;
	mapa[25][24] = 1;
}
void dibujar_mundo(){
	masked_blit(negro,buffer,0,0,0,555,1000,700);
	blit(buffer, screen, 0, 0, 0, 0, 1000, 700);
	
	while (!key[KEY_Q]){
		
		
		for (int i = 0; i<200; i++){
		mapa[i][0] = 'r';
	}
	for (int i = 0; i<200; i++){
		mapa[110][i] = 'r';
	}
	for (int i = 0; i<200; i++){
		mapa[0][i] = 'r';
	}
	for (int i = 0; i<111; i++){
		for (int j = 0; j<200; j++){
			if (mapa[i][j] == 0){
				draw_sprite(buffer, negpo, j * 5, i * 5);
			}
			if (mapa[i][j] == 1){
				draw_sprite(buffer, blapo, j * 5, i * 5);
			}
			if (mapa[i][j] == 'r'){
				draw_sprite(buffer, borde, j * 5, i * 5);
			}
		}
	}
	for (int i = 0; i<111; i++){
		mapa[i][199] = 'r';
		if (mapa[i][199] == 'r'){
			draw_sprite(buffer, borde, 199 * 5, i * 5);
		}
	}
	//pantalla();
		//
		textout_ex(screen, font, "Clic izquierdo para dar vida", 10, 560, makecol(0, 0, 255), -1);
		textout_ex(screen, font, "Clic derecho para quitar la vida", 10, 570, makecol(0, 0, 255), -1);
		textout_ex(screen, font, "I para iniciar el juego", 10, 580, makecol(0, 0, 255), -1);
		textout_ex(screen, font, "V Llenalo todo", 10, 590, makecol(0, 0, 255), -1);
		textout_ex(screen, font, "M Borralo todo", 10, 600, makecol(0, 0, 255), -1);

		if (mouse_x > 3 && mouse_x < 997 &&	mouse_y > 3 && mouse_y < 550){
			//masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 5, 5);
			stretch_sprite ( buffer , cursor, mouse_x ,mouse_y , 5, 5 ) ;
			if (mouse_b & 1){
				int x = floor(mouse_x / 5);
				int y = floor(mouse_y / 5);
				mapa[y][x] = 1;
			}
			if (mouse_b & 2){
				int x = floor(mouse_x / 5);
				int y = floor(mouse_y / 5);
				mapa[y][x] = 0;
			}
		}
		if (key[KEY_I]){
			clear_keybuf();;
			dibujar_mapa();
			jugar();
		}
		if (key[KEY_V]){
			clear_keybuf();
			for (int i = 1; i<110; i++){
				for (int j = 1; j<200; j++){
					mapa[i][j] = 1;
				}
			}
		}
		if (key[KEY_M]){
			clear_keybuf();
			for (int i = 1; i<110; i++){
				for (int j = 1; j<200; j++){
					mapa[i][j] = 0;
				}
			}
		}
		blit(buffer, screen, 0, 0, 0, 0, 1000, 555);
	}
}
