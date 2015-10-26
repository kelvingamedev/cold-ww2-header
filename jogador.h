
// Representa o jogador do game em um dos dois avatares
// (Churchill ou Stallin)
struct Jogador{
	
	/*=========================
			Constantes
	===========================*/
	static const int DINHEIRO = 70;

	
	/*=========================
			Propriedades
	===========================*/

	// Cabe�a da lista encadeada de soldados do jogador
	Soldado *soldado0;
	
	// Caeb�a da lista encadeada de torres do jogador
	Torre *torre0;
	
	// Vida do jogador
	int vida;
	
	// Lado do jogador
	char* lado;
	
	// Marcador de tempo de envio de soldados
	TDelay envioSold;
	
	// Marcador de tempo para espera de inimigos
	TDelay esperaIni;
	
	// Dinheiro do jogador
	int dinheiro;
	
	// Avatar do jogador (Roosevalt, Stallin ou Hitler)
	Lider meuLider;	
	
	// Flag para indicar que ele est� colocando uma torre
	bool flagTorre;
	
	// Torre tempor�ria do jogador (GUI)
	Torre torreGUI;
	
	// Soldado tempor�rio do jogador (GUI)
	Soldado soldGUI;
	
	// Coordenadas para GUI
	int guiSoldX, guiSoldY, guiDinX, guiDinY,
	guiNameSoldX,guiNameSoldY,guiSoldTextX,guiSoldTextY,
	guiCircleX,guiCircleY;
	
	/*===========================
				Fun��es
	==============================*/
	
	void MostraGUI();
	void InputGUI();
	void NovoIni();
	void EnviaIni();
	void ArrastaTorre(CampoJogo meuCampo);
	void ColocaTorre(int meuX, int meuY);

		
	// "Construtores"
	void Init();
	void Init(char* meuLado);
	
};

//==================================================================
// Mostra a interface com o usu�rio do jogador
void Jogador::MostraGUI(){
		
	char textDin[19] = "Dinheiro: ";
	char buffer[8];
	
	settextjustify(LEFT_TEXT,TOP_TEXT);

	// Dinheiro
	itoa(dinheiro,buffer,10);
	strcat(textDin,buffer);
	setcolor(GREEN);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	outtextxy(guiDinX,guiDinY,textDin );

	// GUI da Torre
	torreGUI.MostraTorre();
	
	// GUI do Soldado
	soldGUI.Show();	
	
	// "Colocar Torre" (GUI)
	setcolor(LIGHTBLUE);
	settextstyle(BOLD_FONT,HORIZ_DIR,2);
	outtextxy(TORRE_TEXT_X,TORRE_TEXT_Y,"Colocar");
	outtextxy(TORRE_TEXT_X + 12,TORRE_TEXT_Y + 32,"Torre");

	
	// "Enviar Soldado" (GUI)
	setcolor(WHITE);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
	outtextxy(guiNameSoldX,guiNameSoldY,lado);
	
	// Texto do Soldado
	setcolor(LIGHTRED);
	settextstyle(BOLD_FONT,HORIZ_DIR,2);
	outtextxy(guiSoldTextX,guiSoldTextY,"Enviar Soldado");
	
	// C�rculo em volta do soldado
	setcolor(BLACK);	
	circle(guiCircleX ,guiCircleY,16);	
	

	
}

//=====================================================================
// Trabalha com a intera��o com a GUI
void Jogador::InputGUI(){
	
	int mouseX, mouseY;
	
	if(GetKeyState(VK_LBUTTON) & 0x80){
					
		mouseX = mousex();
		mouseY = mousey();
		
		if(mouseX >= guiSoldX && mouseX <= guiSoldX + TILE_W &&
		mouseY >= guiSoldY && mouseY <= guiSoldY + TILE_H) {
			
			if(envioSold.PassouDelay(ESPERA_DELAY) == true){
				
				envioSold.Atualiza();	
			
				if (soldado0->Compra(&dinheiro) == true)				
 					soldado0->Insere(soldado0,lado);				
			}
		}
		
		// Verifica input de coloca��o de torre
		if(mouseX >= TORRE1_X && mouseX <= TORRE1_X + TORRE_W &&
		mouseY >= TORRE1_Y && mouseY <= TORRE1_Y + TORRE_H){
			flagTorre = true;
		}	
	}
	
}

//===============================================================
// "Construtor" geral 
void Jogador::Init(){
	
	soldado0 = (Soldado *) malloc(sizeof(Soldado));
	torre0 = (Torre *) malloc(sizeof(Torre));
	soldado0->prox = NULL;
	torre0->prox = NULL;
	dinheiro = DINHEIRO;
	envioSold.Atualiza();
	esperaIni.Atualiza();
	vida = VIDA;
	lado = NULL;
	flagTorre = false;
}

//=================================================================
// Chama o construtor geral e tamb�m passa dados espec�ficos
void Jogador::Init(char *meuLado){
	
	Init();
	lado = meuLado;	
	
		
	if(meuLado == LADO1 || meuLado == LADO2){
		
		if(meuLado == LADO1){
	
			guiNameSoldX = EUA_TEXT_X;
			guiNameSoldY = EUA_TEXT_Y;
			guiSoldTextX = SOLD_EUA_X;
			guiSoldTextY = SOLD_EUA_Y;
			guiDinX = MONEY_EUA_X;
			guiDinY = MONEY_EUA_Y;
			guiSoldX = GUI_EUA_X ;
			guiSoldY = GUI_EUA_Y ;
			guiCircleX = guiSoldX + 16;
			guiCircleY = guiSoldY + 16;
			meuLider.Init("Roosevelt");
		}
			
		else if(meuLado == LADO2){
			guiNameSoldX = URSS_TEXT_X;
			guiNameSoldY = URSS_TEXT_Y;
			guiSoldTextX = SOLD_URSS_X;
			guiSoldTextY = SOLD_URSS_Y;
			guiDinX = MONEY_URSS_X;
			guiDinY = MONEY_URSS_Y;
			meuLider.Init("Stalin");
			guiSoldX = GUI_URSS_X ;
			guiSoldY = GUI_URSS_Y;
			guiCircleX = guiSoldX + 16;
			guiCircleY = guiSoldY + 16;	
		}		
		
		soldGUI.Init(meuLado);
		soldGUI.GoTo(guiSoldX,guiSoldY);
		soldGUI.TrocaDir(CIMA);
		torreGUI.Init(meuLado,TORRE1_X,TORRE1_Y);		
	}
	else
		meuLider.Init("Hitler");
	
}

//======================================================================
// Procedimento de arrastar a torre ap�s o click
void Jogador::ArrastaTorre(CampoJogo meuCampo){
	
	int tMouseX,tMouseY, meuX, meuY;
	Torre tempTorre;
	
	if(flagTorre == true){
		
		tempTorre.Init(lado,0,0);
		
		tMouseX = mousex() / TILE_W;
		tMouseY = mousey() / TILE_H;
		
		if(tMouseX < 1 )
			tMouseX = 1;
		else if(tMouseX > 38)
			tMouseX = 38;
		
		if(tMouseY < 1)
			tMouseY = 1;
		else if(tMouseY > 17)
			tMouseY = 17;
		
		meuX = tMouseX * TILE_W; 
		meuY = tMouseY * TILE_H;
	
		tempTorre.x = meuX;
		tempTorre.y = meuY;
		
		tempTorre.MostraTorre();
		
		if(ismouseclick(WM_LBUTTONUP )){
			
			clearmouseclick(WM_LBUTTONUP);
			
			if(meuCampo.PosExist(tMouseX,tMouseY) == true && 
			meuCampo.PosExist(tMouseX,tMouseY - 1) == true){
			
				if(meuCampo.CheckPosTorre(tMouseX,tMouseY,lado) == true){
					
				//	if(SemTorrePerto(torre0,tempTorre.x,tempTorre.y) == true)
						ColocaTorre(meuX,meuY);
				}
			}
			
			flagTorre = false;		
		}
	}
	
}

/*Cria uma nova torre para o jogador e coloca na posi��o
 determinada*/
void Jogador::ColocaTorre(int meuX, int meuY){
	torre0->Insere(torre0,lado,meuX,meuY);
}
