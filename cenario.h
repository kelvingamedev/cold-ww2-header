// Esta struct trabalha com tiles formando cen�rios
struct Cenario{
	
	// Qtd. padr�o de tiles de campo de jogo
	static const int QTD_TILE = 42;
	
	// Matriz do Campo de Jogo com o tipo de tile de cada posi��o
	int posTile[TILE_QTDX][TILE_QTDY]; 
	
	// Tipos de tiles (sprites de tiles)
	Sprite tipoTile[QTD_TILE];	

	// Fun��es
	void Mostrar();
	void Mostrar(int tX0,int tY0,int tXF,int tYF);
	void Console();
	void Arquiva(char nomeArq[8]);
	void Zera(int tileZero);
	void TileLoad();
	bool PosLoad(char nomeArq[8]);
	bool PosExist(int tileX, int tileY);
	bool Caminho(int tileX, int tileY);
	void LimpaD();
	void LimpaMem();
	bool CheckPosTorre(int tileX,int tileY, char *lado);


	//"Construtor" 
	void Init();

};
//=========================================================================

// Limpa a mem�ria que foi alocada dinamicamente 
// aos membros da struct Cenario
void Cenario::LimpaMem(){
	
	free(tipoTile);
}



//=========================================================================

// Limpa a zona de carregamento de imagens
void Cenario::LimpaD(){

	Mostrar(0,0,1,2); // Intervalo de tiles de desenho
}
//=========================================================================

// Verifica se o tile corresponde a um tile de caminho ou n�o
bool Cenario::Caminho(int tileX, int tileY){

	bool caminho;
	
	if(posTile[tileX][tileY] >= 18 && posTile[tileX][tileY] <= 29 )
		caminho  = true; 
	else 
		caminho = false;
	
	return caminho;
}

//=========================================================================


// Preenche o campo de jogo com um tile b�sico
void Cenario::Zera(int tileZero){
	
	int i, j;
	
	for( i =0; i < TILE_QTDY; i++){
		for(j = 0; j < TILE_QTDX; j++)
			posTile[j][i] = tileZero;
		
	}
}

//=========================================================================

// Coloca os sprites na tela
void Cenario::Mostrar(){
	
	int j, i,  meuTipo, x,y;
		
	for(i = 0; i < TILE_QTDY; i++){ 
	
		for(j = 0; j < TILE_QTDX; j++) { 
			
			meuTipo = posTile[j][i]; // Debug encontrou um erro aqui
	
			x = j * TILE_W;
			y = i * TILE_H;
			
			putimage(x,y,tipoTile[meuTipo].image,0);
		}
	}
}
//=========================================================================

// Coloca os sprites de campo apenas aonde determinado
void Cenario::Mostrar(int tX0,int tY0,int tXF,int tYF){
	
	int j, i,  meuTipo, x,y;
		
	for(i = tY0; i < tYF; i++){ 
	
		for(j = tX0; j < tXF; j++) { 
			
			meuTipo = posTile[j][i];
	
			x = j * TILE_W;
			y = i * TILE_H;
			
			putimage(x,y,tipoTile[meuTipo].image,0);
		}
	
	}
}



//=========================================================================


// Arquiva a matriz de coordenadas dos tiles
// (cria um arquivo com nome dado e o conte�do citado)
void Cenario::Arquiva(char *nomeArq){
	
	int i, j;	
	
	std::ofstream escreve;
	
	escreve.open(nomeArq);
	
	for(i = 0; i < TILE_QTDY; i++){
		for(j = 0; j < TILE_QTDX; j++){

			escreve << posTile[j][i];
			escreve << "|"; 

		}
	}

	escreve.close();
	
	std:: cout << "\nArquivo gravado com sucesso!\n";
}


//=========================================================================


// Imprime a posi��o dos tiles no console
void Cenario::Console(){
		
	int i, j;
	
	for(i = 0; i < TILE_QTDY; i++){
		
		std::cout << "\nColuna " << i << std::endl; 
		for(j = 0; j < TILE_QTDX; j++){
			std::cout << posTile[j][i] << "|";
		}
		
	}
	
}

//=========================================================================
// "Construtor" que apenas carrega as imagens dos tiles
void Cenario::Init(){
	
	Zera(T_PRETO);
	TileLoad();
}


//=========================================================================
	

// Carrega os tipos de tiles do campo de jogo	
void Cenario::TileLoad(){
	
	/*
			INFORMA��ES PARA ACRESENTAR TILES
		- Primeiramente, aumente o tamanho do array. O n�mero do array
		deve ser igual a quantidade de tiles que voc� vai armazenar
		
		- Ap�s isso, use BasicTile, caso voc� queira criar prot�tipos de tiles
		,e use Init para criar tiles com imagens bitmpas criados por voc�
		
		- N�o se esque�a de ter uma pasta chamada Assets. ELa deve estar
		no mesmo local que o caminho dos tiles que usam Init, como mostra os 
		exemplos abaixo. E, obviamente,	ela deve conter
	    os bitmaps que voc� especifica no nosso "construtor" Init
	
	*/
	
	tipoTile[0].BasicTile(TILE_W,TILE_H, BLACK, "Preto"); 
	tipoTile[1].BasicTile(TILE_W,TILE_H, BROWN, "Marrom"); // Tiles de prot�tipo
	tipoTile[2].BasicTile(TILE_W,TILE_H, WHITE, "Branco"); 
	tipoTile[3].BasicTile(TILE_W,TILE_H, RED,"Vermelho");
	tipoTile[4].BasicTile(TILE_W,TILE_H, LIGHTGREEN, "Verde claro"); 
	
	// Sprites de campo
	tipoTile[5].Init("../../Assets/Campo/eua.bmp","Campo do EUA e Aliados",TILE_W,TILE_H);
	tipoTile[6].Init("../../Assets/Campo/urss.bmp","Campo da URSS", TILE_W, TILE_H);
	tipoTile[7].Init("../../Assets/Campo/muro.bmp","Muro de Tijolos Brancos",TILE_W,TILE_H);
	tipoTile[8].Init("../../Assets/Campo/rota0.bmp","Rota dos Soldados",TILE_W,TILE_H);
	tipoTile[9].Init("../../Assets/Campo/sacos1.bmp","Trincheira - Baixo",TILE_W,TILE_H);
	tipoTile[10].Init("../../Assets/Campo/sacos2.bmp","Trincheira - Grama",TILE_W,TILE_H);
	tipoTile[11].Init("../../Assets/Campo/sacos3.bmp","Trincheira - Neve",TILE_W,TILE_H);
	tipoTile[12].Init("../../Assets/Campo/cerca1.bmp","Cerca - Grama",TILE_W,TILE_H);
	tipoTile[13].Init("../../Assets/Campo/cerca2.bmp","Cerca 1 - Grama",TILE_W,TILE_H);
	tipoTile[14].Init("../../Assets/Campo/cerca3.bmp","Cerca 2 - Grama",TILE_W,TILE_H);
	tipoTile[15].Init("../../Assets/Campo/cerca4.bmp","Cerca - Neve",TILE_W,TILE_H);
	tipoTile[16].Init("../../Assets/Campo/cerca5.bmp","Cerca 1 - Neve",TILE_W,TILE_H);
	tipoTile[17].Init("../../Assets/Campo/cerca6.bmp","Cerca 2 - Neve",TILE_W,TILE_H);
	tipoTile[18].Init("../../Assets/Campo/rota1a.bmp","Rota - Horiz Grama",TILE_W,TILE_H);
	tipoTile[19].Init("../../Assets/Campo/rota2a.bmp","Rota - Verti Grama",TILE_W,TILE_H);
	tipoTile[20].Init("../../Assets/Campo/rota3a.bmp","Rota - Sup Esq Grama",TILE_W,TILE_H);
	tipoTile[21].Init("../../Assets/Campo/rota4a.bmp","Rota - Sup Dir Grama",TILE_W,TILE_H);
	tipoTile[22].Init("../../Assets/Campo/rota5a.bmp","Rota - Inf Esq Grama",TILE_W,TILE_H);
	tipoTile[23].Init("../../Assets/Campo/rota6a.bmp","Rota - Inf Dir Grama",TILE_W,TILE_H);
	tipoTile[24].Init("../../Assets/Campo/rota1b.bmp","Rota - Horiz Neve",TILE_W,TILE_H);
	tipoTile[25].Init("../../Assets/Campo/rota2b.bmp","Rota - Verti Neve",TILE_W,TILE_H);
	tipoTile[26].Init("../../Assets/Campo/rota3b.bmp","Rota - Sup Esq Neve",TILE_W,TILE_H);
	tipoTile[27].Init("../../Assets/Campo/rota4b.bmp","Rota - Sup Dir Neve",TILE_W,TILE_H);
	tipoTile[28].Init("../../Assets/Campo/rota5b.bmp","Rota - Inf Esq Neve",TILE_W,TILE_H);
	tipoTile[29].Init("../../Assets/Campo/rota6b.bmp","Rota - Inf Dir Neve",TILE_W,TILE_H);
	tipoTile[30].Init("../../Assets/Campo/baseeua1.bmp","Base EUA - Parte 1",TILE_W,TILE_H);
	tipoTile[31].Init("../../Assets/Campo/baseeua2.bmp","Base EUA - Parte 2",TILE_W,TILE_H);
	tipoTile[32].Init("../../Assets/Campo/baseeua3.bmp","Base EUA - Parte 3",TILE_W,TILE_H);
	tipoTile[33].Init("../../Assets/Campo/baseeua4.bmp","Base EUA - Parte 4",TILE_W,TILE_H);
	tipoTile[34].Init("../../Assets/Campo/baseeua5.bmp","Base EUA - Parte 5",TILE_W,TILE_H);
	tipoTile[35].Init("../../Assets/Campo/baseeua6.bmp","Base EUA - Parte 6",TILE_W,TILE_H);
	tipoTile[36].Init("../../Assets/Campo/baseurss1.bmp","Base URSS - Parte 1",TILE_W,TILE_H);
	tipoTile[37].Init("../../Assets/Campo/baseurss2.bmp","Base URSS - Parte 2",TILE_W,TILE_H);
	tipoTile[38].Init("../../Assets/Campo/baseurss3.bmp","Base URSS - Parte 3",TILE_W,TILE_H);
	tipoTile[39].Init("../../Assets/Campo/baseurss4.bmp","Base URSS - Parte 4",TILE_W,TILE_H);
	tipoTile[40].Init("../../Assets/Campo/baseurss5.bmp","Base URSS - Parte 5",TILE_W,TILE_H);
	tipoTile[41].Init("../../Assets/Campo/baseurss6.bmp","Base URSS - Parte 6",TILE_W,TILE_H);
	
	

}

//=========================================================================


// Carrega a matriz do campo de jogo com os dados de um arquivo
bool Cenario::PosLoad(char nomeArq[8]){
			
	std::ifstream leitor;
	char c;
	bool mtxCheia = false;
	int i, j;
	char temp[4] = "   ";
	int  tempPos = 0;
	
	leitor.open(nomeArq);
	
	if(!leitor.is_open()){
		std::cout << "N�o foi poss�vel abrir o arquivo " << nomeArq[8];
		return false;
	}
	else{
		
	
		i = 0;  
		j = 0;
		
		while(leitor.get(c) && mtxCheia!= true ){
			
			// Verifique se o char � um valor n�merico na tabela ASC
			if (c >= 48 && c <= 57 ){
				
				temp[tempPos] = c;
				
				tempPos++;
			} 
			
			else if(c == '|'){
				
				posTile[j][i] = atoi(temp);
			 	strcpy(temp, "   ");
				tempPos = 0;
				j++;
		
			    if(j == TILE_QTDX){
					
					j = 0;
			    	i++;
			    	
					if(i == TILE_QTDY)
						mtxCheia = true; 
					
				}
				
			}
			
		}
		
		leitor.close();
		return true;
			
	}
}
//=========================================================================

// Verifica se a coordenada de tile � v�lida
bool Cenario::PosExist(int tileX, int tileY){
	
	bool existe;
	
	if( ( (tileX >= 0) && (tileX <= (TILE_QTDX - 1) ) )
	 && ( (tileY >= 0) && (tileY <= (TILE_QTDY - 1) ) ) )
	 	existe = true; 
	 else
	 	existe = false; 
	 	 
	 return existe; 
}	
	
/*Retorna se o tile da torre � valido ou n�o*/
bool Cenario::CheckPosTorre(int tileX, int tileY, char *lado){
	
	bool validPos = false;
	int nTileCima, nTileBaixo;
	int tileCampo, inicioTCerca,fimTCerca,inicioTRota,fimTRota;
	
	nTileCima = posTile[tileX][tileY];
	nTileBaixo = posTile[tileX][tileY + 1];
	

	
	if(lado == "Eua"){
		
		tileCampo = 5; 
		inicioTCerca = 12;
		fimTCerca = 14;
		
	} else if(lado == "Urss"){
		tileCampo = 6;
		inicioTCerca = 15;
		fimTCerca = 17;
	}
		
			
	if( (nTileCima == tileCampo) ||
	 (nTileCima >= inicioTCerca && nTileCima <= fimTCerca)){
		
		if( (nTileBaixo == tileCampo) ||
		 (nTileBaixo >= inicioTCerca && nTileBaixo <= fimTCerca))		
		 	validPos = true;
	
	}	
	
	return validPos;
}



		
	



