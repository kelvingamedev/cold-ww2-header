
// Representa o jogador do game em um dos dois avatares
// (Churchill ou Stallin)
struct Jogador{
	
	/*=========================
			Constantes
	===========================*/
	static const int DINHEIRO = 120;
	static const int X_E_Y = 2;

	
	/*=========================
			Propriedades
	===========================*/

	// Cabe�a da lista encadeada de soldados do jogador
	Soldado *soldado0;
	
	// Caeb�a da lista encadeada de torres do jogador
	Torre *torre0;
	
	// Vida do jogador
	int vida;
	
	//  Velocidade do jogo
	int *gameSpeed;
	
	// Lado do jogador
	char* lado;
	
	// Marcador de tempo de envio de soldados
	TDelay envioSold;
	
	// Marcador de tempo para espera de inimigo
	TDelay esperaIni;
	
	// Marcador de tempo depois da pr�pria morte do lider
	TDelay esperaMorte;
	
	// Dinheiro do jogador
	int dinheiro;
	
	// Avatar do jogador (Roosevalt, Stallin ou Hitler)
	Lider lider;	
	
	// Flag para indicar que ele est� colocando uma torre
	bool flagTorre;
	
	// Torre que o jogador visualiza na GUI 
	Torre torreGUI;
	
	// Torre que o jogador arrasta (GUI)
	Torre tempTorre;
	
	// Indica a qutantidade de soldados que o jogador est� em enviando
	int qtdSoldEspera;
	
	// Indica as coordendas da torre que o jogador comprou recentemente
	int novaTorreXeY[QTD_NOVATORRE][X_E_Y];
	
	// Indica que o outro jogador est� morto
	bool outroJogMorto;
	
		
	// Soldado tempor�rio do jogador (tamb�m faz parte da GUI)
	Soldado soldGUI;
	
	// Coordenadas para GUI
	int guiSoldX, guiSoldY, guiDinX, guiDinY,
	guiNameSoldX,guiNameSoldY,guiSoldTextX,guiSoldTextY,
	guiCircleX,guiCircleY;
	
	/*===========================
				Fun��es
	==============================*/
	
	void MostraGUI(TipoGameplay tipoGameplay);
	void InputGUI();
	void NovoIni();
	void EnviaIni();
	void ArrastaTorre(Cenario meuCampo);
	bool Compra(int preco);

		
	// "Construtores"
	void Init();
	void Init(char* meuLado, int *velocidadeJogo);
	
};


//=====================================================================
// Trabalha com a intera��o com a GUI
void Jogador::InputGUI(){
	
	int mouseX, mouseY;
	
	if(GetKeyState(VK_LBUTTON) & 0x80){
					
		mouseX = mousex();
		mouseY = mousey();
		
		if(outroJogMorto == false && 
		mouseX >= guiSoldX && mouseX <= guiSoldX + TILE_W &&
		mouseY >= guiSoldY && mouseY <= guiSoldY + TILE_H) {
			
			if(envioSold.PassouDelay(ESPERA_DELAY) == true){
				
				envioSold.Atualiza();	
			
				if (Compra(PRECO_SOLDADO) == true){
 					soldado0->Insere(soldado0,&soldGUI,*gameSpeed);	
					qtdSoldEspera = 1;			
				}	
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
	int i;
	soldado0 = (Soldado *) malloc(sizeof(Soldado));
	torre0 = (Torre *) malloc(sizeof(Torre));
	soldado0->prox = NULL;
	torre0->prox = NULL;
	dinheiro = DINHEIRO;
	envioSold.Atualiza();
	esperaIni.Atualiza();
	esperaMorte.marcador = NULL;
	vida = VIDA;
	lado = NULL;
	gameSpeed = NULL;
	qtdSoldEspera = 0;
	flagTorre = false;
	outroJogMorto = false;
	for( i = 0; i < QTD_NOVATORRE; i++){
		novaTorreXeY[i][0] = UNDEFINED;
		novaTorreXeY[i][1] = UNDEFINED;
	}

}

//=================================================================
// Chama o construtor geral e tamb�m passa dados espec�ficos
void Jogador::Init(char *meuLado, int *velocidadeJogo){
	
	Init();
	lado = meuLado;	
	gameSpeed = velocidadeJogo;
		
	if(meuLado == LADOEUA || meuLado == LADOURSS){
		
		if(meuLado == LADOEUA){
	
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
			lider.Init("Roosevelt",&vida);
			tempTorre.Init(lado,0,0,true);
			soldGUI.Carrega(EUA);
			soldGUI.tipo = "Eua";
		}
			
		else if(meuLado == LADOURSS){
			guiNameSoldX = URSS_TEXT_X;
			guiNameSoldY = URSS_TEXT_Y;
			guiSoldTextX = SOLD_URSS_X;
			guiSoldTextY = SOLD_URSS_Y;
			guiDinX = MONEY_URSS_X;
			guiDinY = MONEY_URSS_Y;
			lider.Init("Stalin",&vida);
			guiSoldX = GUI_URSS_X ;
			guiSoldY = GUI_URSS_Y;
			guiCircleX = guiSoldX + 16;
			guiCircleY = guiSoldY + 16;
			soldGUI.Carrega(URSS);
			soldGUI.tipo = "Urss";	
		}		
		
		soldGUI.GoTo(guiSoldX,guiSoldY);
		soldGUI.TrocaDir(CIMA);
		torreGUI.Init(meuLado,TORRE1_X,TORRE1_Y,true);
		tempTorre.Init(lado,0,0,true);	
	}
	else{
		lider.Init("Hitler",&vida);
		soldGUI.Carrega(NAZI);
		soldGUI.tipo = "Nazi";
	}
	
}

//======================================================================
// Procedimento de arrastar a torre ap�s o click
void Jogador::ArrastaTorre(Cenario meuCampo){
	
	int tMouseX,tMouseY, meuX, meuY;
		
	if(flagTorre == true){

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
		
		setcolor(BLUE);
		circle(meuX + 16,meuY + 32,TORRE_RAIO);
		
		if(ismouseclick(WM_LBUTTONUP )){
			
			clearmouseclick(WM_LBUTTONUP);
			
				if(meuCampo.PosExist(tMouseX,tMouseY) == true && 
				meuCampo.PosExist(tMouseX,tMouseY - 1) == true){
				
					if(meuCampo.CheckPosTorre(tMouseX,tMouseY,lado) == true){
						
						if(torre0->SemTorrePerto(torre0,meuX,meuY) == true){
							if(Compra(PRECO_TORRE) == true){
								torre0->Insere(torre0,lado,meuX,meuY);
								novaTorreXeY[0][0] = meuX;
								novaTorreXeY[0][1] = meuY;
							}

						}
					}
				}
			flagTorre = false;		
		}
	}
}



/*Compra e paga algum recurso. 
Retorna true ou false dependendo do dinheiro para compra*/
bool Jogador::Compra(int preco){

	if(dinheiro >= preco){
		dinheiro -= preco;
		return true;
	} 
	else
		return false;
}

// Mostra a GUI depedendo do tipo de gameplay
void Jogador::MostraGUI(TipoGameplay tipoGameplay)
{	
	char textDin[19];
	char buffer[8];
	int laranja;
	
	strcpy(textDin,linguagem.GetText(62));	
	settextjustify(LEFT_TEXT,TOP_TEXT);

	// Dinheiro
	itoa(dinheiro,buffer,10);
	strcat(textDin,buffer);
	setcolor(GREEN);
	outtextxy(guiDinX,guiDinY,textDin );

	// Preco
	setcolor(GREEN);
	outtextxy(PRECO_ITENS_X, PRECO_ITENS_Y,linguagem.GetText(51));
	outtextxy(PRECO_TORRE_X, PRECO_TORRE_Y,linguagem.GetText(52));
	outtextxy(PRECO_SOLD_X, PRECO_SOLD_Y,linguagem.GetText(53));
	
	if(tipoGameplay != MULTIPLAYER_SPLIT )
	{
		// GUI da Torre
		torreGUI.MostraTorre();
		
		// "Colocar Torre" (GUI)
		setcolor(LIGHTBLUE);
		outtextxy(TORRE_TEXT_X,TORRE_TEXT_Y,linguagem.GetText(54));
		outtextxy(TORRE_TEXT_X ,TORRE_TEXT_Y + 32,linguagem.GetText(55));
	}


	if(outroJogMorto == false && tipoGameplay != MULTIPLAYER_SPLIT){
		
		// GUI do Soldado
		soldGUI.Show();	
		
		// "Enviar Soldado" (GUI)
		setcolor(WHITE);
		
		if(lado == LADOEUA)
			outtextxy(guiNameSoldX,guiNameSoldY,linguagem.GetText(106));
		else
			outtextxy(guiNameSoldX,guiNameSoldY,linguagem.GetText(107));
		
		
		// Texto do Soldado
		setcolor(LIGHTRED);
		outtextxy(guiSoldTextX,guiSoldTextY,linguagem.GetText(56));	
				
		// C�rculo em volta do soldado
		setcolor(BLACK);	
		circle(guiCircleX ,guiCircleY,16);	
	} 
	
	else if(outroJogMorto == true)
	{		
		setcolor(LIGHTRED);
		if(lado == LADOEUA)
			outtextxy(guiSoldTextX - 144,guiSoldTextY + 16,linguagem.GetText(57));
		else
			outtextxy(guiSoldTextX,guiSoldTextY + 16,linguagem.GetText(57));
	}	
}

