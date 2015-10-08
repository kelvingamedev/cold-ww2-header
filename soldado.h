// Rela��o entre tipo de sprite e valor
enum NomeSprit{ CIMA1 = 0, CIMA2, CIMA3,
	BAIXO1, BAIXO2, BAIXO3,
	ESQRD1,ESQRD2,ESQRD3,
	DIREITA1,DIREITA2,DIREITA3,
	numSprit
};

// Dire��o do soldado
enum Direcao{
	CIMA, BAIXO, ESQUERDA, DIREITA 
};

// Sequ�ncia da anim��o
enum SeqAnim{
	DO1ATE3, DO3ATE1
};


struct Soldado{
	//==========================================================================
		
	// Constantes do "construtor" geral do soldado
	static const int VIDA = 100;
	static const int SPEED = 8;
	static const int X = 64;
	static const int Y = 32;
	static const SeqAnim SEQANIM = DO1ATE3;
	static const Direcao DIRECAO = BAIXO;
	static const int IMGATUAL = 4; // corresponde ao "BAIXO2"
	static const NomeSprit QTD_IMG = numSprit;
	static const bool MOVNUNTIL = FALSE;
	static const int UNDEFINE = -1;
	static const bool POSCEGO = false;
	static const bool DEST = false;
	static const bool VISIVEL = false;
	static const bool SAIU = false;
	
	// Vari�veis	
	int vida;	
	int speed;	
	int imgAtual;
	int x, y;	
	char *tipo;
	Direcao direcao; // Para onde ele estar a se movimentar
	SeqAnim seqAnim; // sequ�ncia da anima��o(1,2 ou 3)
	void *imagens[QTD_IMG];	// Imagens/ Sprites do soldado
	bool movNUntil; // Flag para indicar 
					//movimenta��o baseada na fun��o MovUntil
	int untilPos[2]; // Armazena um destino para o soldado
	bool posCego; // Indica se soldado passou pelo ponto cego
	bool dest; // Indica se o soldado chegou ao destino
	bool visivel; // Indica se o soldado chegou ao ponto visivel
	bool saiu;
	Soldado *prox;	// Pr�xima c�lula da lista encadeada

	//=============================================================================
	
	// Fun��es
	void Carrega(char rPath[]);
	void GoTo(int novoX, int novoY);
	bool MoveDest(CampoJogo meuCampo,int tileXF, int tileYF);
	void Move();
	void Until(int untilX, int untilY);
	bool MovUntil();
	void Show();
	void TrocaImg();
	void TrocaDir(Direcao trocaDir);
	void IA(CampoJogo meuCampo, Soldado *soldado0);
	void UltTile(int *ultTile);
	void Morre(Soldado *anterior);
	Soldado* Insere(Soldado *soldado0, char* tipo);
	void Remove(Soldado *anterior);
	void Enviar(Soldado *soldado0, CampoJogo meuCampo);
	void LimpaNo(Soldado *soldado0);
	void Chegou(Soldado *anterior);
	Soldado* Anterior(Soldado *soldado0);


	// "Construtores"
	void Init(char* tipo);
	void Init();
};

//==================================================================

// Calcula o soldado anterior a partir posi��o atual 
Soldado* Soldado::Anterior(Soldado *soldado0){
	Soldado *p;
	Soldado *atual;
	
	atual = this;
	p = soldado0;
	
	while( p != NULL && p->prox != atual)
		p = p->prox;
		
	return p;
}


//===========================================================================
// Comportamento encadeada pela morte do soldado
void Soldado::Morre(Soldado *anterior){
	// Insira o comportamento de morte aqui (algum som, troca de sprite,...)
	//[...]
	
	// Reomove o soldado da lista encadeada
	Remove(anterior);
}

//===========================================================================

// Comportamento do soldado ao chegar na base inimiga
void Soldado::Chegou(Soldado *anterior){
	
	// Insira o comportamento de infrigir dano aqui
	//[...]
	
	// Remove o soldado da lista encadeada
	Remove(anterior);
}


//===========================================================================
// Remove o soldado da lista encadeada com base em seu antecessor
void Soldado::Remove(Soldado *anterior){
	Soldado *remove;
	remove = anterior->prox;
	anterior->prox = remove->prox;
	free(remove);
}



//===========================================================================
// Limpa n� da lista encadeada
void Soldado::LimpaNo(Soldado *soldado0){
	Soldado *p, *aux;
	p = soldado0;
	while(p != NULL){
		aux = p;
		p = p->prox;
		free(aux->imagens);
		free(aux);
	}
	soldado0 = NULL;	
}


//===========================================================================

// Envia todos soldados ativos
void Soldado::Enviar(Soldado *soldado0, CampoJogo meuCampo){


	Soldado *pSold;
	
	for(pSold = soldado0->prox; pSold != NULL; pSold = pSold->prox){
		
		// Enquanto o soldado estiver vivo
		if(pSold->vida >=0){
			
			// Mostra soldado
			pSold->Show();
			
			// Usa IA 
			pSold->IA(meuCampo, soldado0);
			
		}

	}
}


//===========================================================================

// Insere um novo soldado na lista encadeada
Soldado* Soldado::Insere(Soldado *soldado0, char * tipo){
	Soldado *novo;
	novo = (Soldado *) malloc(sizeof(Soldado));
	novo->Init(tipo); // Inicializa o soldado
	novo->prox = soldado0->prox;
	soldado0->prox = novo;
	
	// Retorna a nova tropa
	return novo;
}


//===========================================================================
// Movimenta o soldado com base na dire��o dele
void Soldado::Move(){
		
		// Troca a imagem de movimento do personagem
		TrocaImg();
		
		// Verifica a dire��o e movimenta-se com base nisso
		if(direcao == ESQUERDA){
			x -= speed;
		} 
		
		if (direcao == DIREITA){
			x += speed; 
		}
		
		if( direcao == CIMA){
			y += speed;
		}
		
		if(direcao == BAIXO){
			y -= speed;
		}	
}


//===========================================================================
// "Construtor" sem par�metros
void Soldado::Init(){
	
	// qtd. de vida inicial
	vida = VIDA;
	speed = SPEED;
	x = X;
	y = Y;
	tipo = "default";
	direcao = BAIXO;
	imgAtual = IMGATUAL;
	seqAnim = SEQANIM;
	movNUntil = MOVNUNTIL;
	untilPos[0] = UNDEFINE;
	untilPos[1] = UNDEFINE;
	posCego = POSCEGO;
	dest = DEST;
	visivel = VISIVEL;
	saiu = SAIU;
	prox = NULL;
}
//===========================================================================

// "Construtor" que recebe o tipo de soldado 
//e atribui valores baseado nisso
void Soldado::Init(char* tipoSold ){
	
	// Caminho para encontrar os sprites dos soldados
	char *CHARA = "/Soldado/Chara/Chara";
	
	// Faz altera��es gerais
	Init();
	
	// Faz altera��es espec�ficas
	if(tipoSold == "Chara"){
		
		// Carrega as imagens do soldado
		Carrega(CHARA);
	}
	
	
}
 

//===========================================================================
// Muda a posi��o do soldado
void Soldado::GoTo(int novoX, int novoY){
	x = novoX;
	y = novoY;
}
//===========================================================================
// Mostra o soldado
void Soldado::Show(){

	// Cria uma vari�vel para utilizar o gerenciador do sprite
	Sprite spritHnd;

	// Mostra o sprite atual
	spritHnd.Show(imagens[imgAtual],x,y);
}

//===========================================================================
// Carrega todas imagens do soldado atrav�s do caminho relativo
// a partir da pasta assets
void Soldado::Carrega(char rPath[]){
	
	
	int i; // contador
	int indiceH;	// Indice mais humano (indice array + 1)
	Sprite imgHandl; // Para manipular imagens
	char caminho[70]; 	// Caminho para acessar a pasta
	char temp[3]; // indice do loop em char array

				
	for(i = 0; i < QTD_IMG; i++){
		
		// O caminho exato - com o numero do sprite - ainda n�o foi calculado
		// Ent�o copie o caminho para a pasta assets
		strcpy(caminho,ASSETS);
		
		// Agora, adicione o caminho relativo (argumento que foi passado)
		strcat(caminho,rPath);
		
		// Converte o indice do contador para o formato "humano"
		// que � o n�mero do sprite
		indiceH = i + 1;
		
		// Verifica se o n�mero do sprite � menor que 10 (dois algarismos)
		if(indiceH < 10){
			
			// Se sim, acresenta-se um '0'
			strcat(caminho,"0");
		}
		
		// Recebe a convers�o do n�mero do sprite para o tipo string
		itoa(indiceH,temp,DECIMAL);
		
		// Acresenta esse valor
		strcat(caminho,temp);
		
		// Adicione a especifica��o de arquivo bitmap
		strcat(caminho,BITMAP);
		
		// Recebe a imagem especificada pelo caminho
		imgHandl.GetImage(&imagens[i],caminho,TILE_W,TILE_H);
		
	}
}  

//========================================================================
// Troca o indice da anima��o do soldado na dire��o atual
void Soldado::TrocaImg(){
	
	// Indice da anima��o
	int iAnim;
			
	// Fun��o para achar o indice da anima��o
	iAnim = (imgAtual % 3) + 1;
	
	// Verifica o indice de imagem e atribui o valor conforme ele
	switch(iAnim){
		case 1:
			imgAtual +=  1;
			break;
		case 2:
			
			// Verifica o tipo de sequencia e altera com base nisso
			if(seqAnim == DO1ATE3){
				imgAtual += 1;
				seqAnim = DO3ATE1;
			} else{
				imgAtual -= 1;
				seqAnim = DO1ATE3;
			}
			
			break;
		case 3:
			imgAtual -= 1;
			break;		
	}

}
//===========================================================================
// Troca a dire��o do soldado
void Soldado::TrocaDir(Direcao trocaDir){
		
		// Recebe o valor da dire��o
		direcao = trocaDir;
	
		// Verifica a dire��o 
		switch(direcao){	
			
			// A imagem atual � igual a dire��o no movimento 2
			case CIMA:
				imgAtual = CIMA2;
				break;
			case BAIXO:
				imgAtual = BAIXO2;
				break;
			case ESQUERDA:
				imgAtual = ESQRD2;
				break;
			case DIREITA:
				imgAtual = DIREITA2;
				break;
	}	
}

//=====================================================
// Calcula o �ltimo tile que o soldado esteve
void Soldado::UltTile(int *ultTile){
	
	// Assume, incialmente o valor das coordenadas atuais
	ultTile[0] = x / TILE_W;
	ultTile[1] = y / TILE_H;
	
	// Verifica o �ltimo movimento feito 
	switch(direcao){
		
		//Calcula �ltimo movimento feito 
		case ESQUERDA:
			ultTile[0] += 1; // Inverso da esquerda (direita)
			break;
		case DIREITA:
			ultTile[0] -= 1; // Inverso da direita (esquerda)
			break;
		case BAIXO:
			ultTile[1] += 1; // Inverso de para baixo (cima)
			break;
		case CIMA:
			ultTile[1] -= 1; // Inverso de para cima (baixo)
			break;
	}
	
	
}

//===========================================================================

// Vai at� o tile de destino com a pathfind
bool Soldado::MoveDest(CampoJogo meuCampo,int tileXF, int tileYF){
	
	// Calcula o tile do soldado
	int tileX,  tileY;
	
	// Flag que indica que o soldado encontrou uma posi��o 
	// para onde ir
	bool myPath = false;
		
	// Inicialmente, sup�e-se que o soldado n�o chegou ao destino
	bool moveDest = false;
	
	// Recebe as coordendas do ultimo tile do soldado
	int ultTile[2];
	UltTile(ultTile);
	
	// Calcula o tile atual com base na posi��o x e y do soldado
	tileX = x / TILE_W;
	tileY = y / TILE_H;	
		
	// Se o tile existir
	if(meuCampo.PosExist(tileXF, tileYF)){
	
		// Se o tile de destino for um tile de caminho
		if(meuCampo.Caminho(tileXF, tileYF)){
					
			/* ========================
			Ap�s verificar o tile de destino...
			1 - Verifique se o tile existe no campo de jogo;
			2 - Verifique se o tile � um tile de caminho;
			3 - Verfique se o tile n�o � o �ltimo tile percorrido
			4 - V� at� a nova posi��o se tudo estiver certo
			============================*/
			
			// Se o soldado n�o estiver no destino
			if(tileX != tileXF || tileY != tileYF){
				
				// Verifica se o tile da esquerda � v�lido
				if(meuCampo.PosExist(tileX - 1,tileY)){
					
					// Verifica se � um tile de caminho
					if(meuCampo.Caminho(tileX - 1, tileY)){
						
						// Verifica se ele n�o � igual ao ultimo tile
						if(ultTile[0] != tileX - 1  || ultTile[1] != tileY ){
							
							// Indica que o soldado encontrou 
							// um caminho v�lido
							myPath = true;
							
							// Registra uma coordenada de movimenta��o
							Until(x - TILE_W,y);
						}
					}
				}
				
				// Direita
				if(myPath == false && meuCampo.PosExist(tileX + 1,tileY)){ 
					if(meuCampo.Caminho(tileX + 1, tileY)){
						if(ultTile[0] != tileX + 1  || ultTile[1] != tileY ){
							
														
							// Indica que o soldado encontrou 
							// um caminho v�lido
							myPath = true;
							
							// Registra uma coordenada de movimenta��o
							Until(x + TILE_W,y);
						}
					}
				}
				
				// Cima
				if(myPath == false && meuCampo.PosExist(tileX,tileY + 1) ){
					if(meuCampo.Caminho(tileX, tileY + 1)){
						if(ultTile[0] != tileX  || ultTile[1] != tileY + 1 ){
							
							// Indica que o soldado encontrou 
							// um caminho v�lido
							myPath = true;
							
							// Registra uma coordenada de movimenta��o
							Until(x ,y + TILE_H);
						}
					}
				}
				
				// Baixo			
				if(myPath == false && meuCampo.PosExist(tileX,tileY - 1)){
					if(meuCampo.Caminho(tileX , tileY - 1)){
						if(ultTile[0] != tileX  || ultTile[1] != tileY - 1 ){
							
							// Indica que o soldado encontrou 
							// um caminho v�lido
							myPath = true;
							
							// Registra uma coordenada de movimenta��o
							Until(x,y - TILE_H);
						}
					}
				}
				
		}
			// Se o soldado estiver no destino
			else{
				moveDest = true; // Confirma a chegada ao destino
			}							
		}
	}

	
	// Retorna se o soldado chegou ao destino ou n�o
	return moveDest;

}


//===========================================================================

/*Registra uma coordenada de movimenta��o*/
void Soldado::Until(int untilX, int untilY){
	
	//=======================================================
	/*ATEN��O: � necess�rio que a coordenada seja m�ltiplo da velocidade*/	
	//=======================================================
	
	// Recebe as coordenadas de destino
	untilPos[0] = untilX;
	untilPos[1] = untilY;
	
	// Altera o estilo de movimenta��o
	movNUntil = true;
}

//========================================================

/*Movimenta-se at� a coordenada registrada no soldado*/
bool Soldado::MovUntil(){
	
	// Indica que se o soldado chegou ou n�o no destino
	bool reach;
	
	// Se o estilo de movimento foi ativado
	if(movNUntil == true){
		
		// Verifica o tipo de diferen�a no eixo y 
		//e troca dire��o com base nisso
		if(y < untilPos[1] && direcao != CIMA)
			TrocaDir(CIMA);	
		else if(y > untilPos[1] && direcao != BAIXO)
			TrocaDir(BAIXO);
		
		// Se a coordenada do soldado n�o for igual a coord. de
		// destino
		if( y != untilPos[1])
			Move();	// O soldado move-se um pouco

		// Caso o soldado esteja na posi�ao Y do destino
		else{
			
			// Verifica o tipo de diferen�a no eixo x e troca dire��o com base nisso
			if(x < untilPos[0] && direcao != DIREITA){
				TrocaDir(DIREITA);
			} else if(x > untilPos[0] && direcao != ESQUERDA ){
				TrocaDir(ESQUERDA);
			}
			
			// Se a coordenada do soldado n�o for igual  a coordenada de
			// destino
			if(x != untilPos[0]){
				
				// O soldado se move um pouco
				Move();
			}
		
		}	
	}
	
	// Se o soldado estiver na posi��o de destino
	if(x == untilPos[0] && y == untilPos[1]){
		
		// Confirma isso atrav�s da vari�vel de retorno
		reach = true;
		
		// Altera o estilo de movimenta��o
		movNUntil = false;
		
		// Reseta os valores de movimenta��o
		untilPos[0] = UNDEFINE;
		untilPos[1] = UNDEFINE;
	} else{
		
		// Nega a chegada atrav�s desta vari�vel
		reach = false;
	}
	
	// Retorna se o soldado chegou no destino ou n�o
	return reach;
}


//===========================================================
// Comportamento geral do soldado
void Soldado::IA(CampoJogo meuCampo, Soldado *soldado0){
	
	Soldado *anterior;
	
	// Coordenadas do ponto cego
	int P_CEGOX = X + (TILE_W * 21);
	int P_CEGOY = Y - (TILE_H * 3);
		
	// Se o soldado n�o estiver no "ponto cego"
	if(posCego == false){
		
		
		// Se o soldado n�o souber para onde ir
		if(movNUntil == false){
			
			// Define o ponto cego como destino
			Until(P_CEGOX,P_CEGOY);
		}
		
		// Movimenta-se at� o ponto cego
		posCego = MovUntil();
	} 
	// Se o soldado estiver no "ponto cego"
	else{
		
		// Se o soldado n�o estiver no ponto vis�vel
		if(visivel == false){
				
				// Se o soldado n�o souber para onde ir
				if(movNUntil == false){
					
					// Define a coordenada do ponto vis�vel como destino
					Until(x, 64);
				} 
				
				// Movimente o soldado area coordena do ponto visivel
				visivel = MovUntil();
		} 
		
		// Se o soldado chegou a �rea vis�vel
		else{
			
			// Se o soldado n�o chegou ao destino
			if(dest  == false){
				
				// Se o soldado n�o souber para onde ir
				if(movNUntil == false){
					
					// Usa a Pathfind
					dest = MoveDest(meuCampo,DEST1_X,DEST1_Y);
				} 
				
				// Movimenta-se at� o ponto definido
				MovUntil();
			} else{
				
				// Calcula o soldado anterior (para exclus�o do atual)
				anterior = Anterior(soldado0);
				
				// Executa comportamento de chegar na base inimiga
				Chegou(anterior);
			}
			
		}		
	}
}
