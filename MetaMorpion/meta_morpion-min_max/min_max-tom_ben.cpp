#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <chrono>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <memory>

#define SIZE 9
#define MAXIPOINT 50000000

int tictactoe_id_row(int i, int j);
int tictactoe_id_col(int i, int j);
void version(int (&move)[2], int i, int j);
void theme(int (&move)[2], int i, int j);
void copy_tab1(int occ[SIZE],int (&tab)[SIZE]);
void copy_tab2(int occ[SIZE][SIZE], int (&tab)[SIZE][SIZE]);
void delete_save(int ** save);

using namespace std;


class Position{

  private:

  int x;
  int y;
  
  public:

  //contructeurs

  Position() : x(0), y(0)
  {}
  
  Position(double x, double y) : x(x), y(y)
  {}

  //getters et setters
  void setX(int x1){
      x = x1;
  }
    void setY(int y1){
      y = y1;
  }
  int getX(){

    return x;
  }

  int getY(){

    return y;
  }
};


// - Classe representant une grille par un vector 1D avec les methodes associees -
template <class T>
class Grid{
  private:
    vector<T> gridContainer;
  public:  
    // - constructeur par defaut: creer un vector de taille 1 -
    Grid(): gridContainer(vector<T>(1))
    {}

    // - constructeur parametre: creer un vector de taille specifiee en parametre -
    Grid(int taille): gridContainer(vector<T>(taille))
    {}

    // - methode renvoyant l'element a l'indice i -
    T getValue(int i) const{
        return gridContainer[i];
    }

    // - methode renvoyant l'element a la place (i, j) (car on stocke une grille 2D sous forme de tableau en 1D) -
    T getValueXY(int i, int j) const{
        return gridContainer[j*gridContainer.size()+i];
    }

    // - methode qui ajoute un element au conteneur -
    void ajouter(T x){
        gridContainer.push_back(x);
    }

};

// - classe abstraite pour "MetaMorpion" et "Morpion" -
template <class T>
class AbstractMorpion{

    // - variables membres et fonctions virtuelles (a redefinir dans les classes Morpion et MetaMorpion) -
    protected:
        
        Grid<T> container;
    

    public:

        //- constructeur par defaut: creer une Grid de type T et de taille 9 -
        AbstractMorpion(): container(Grid<T>(9))
        {}


        // - constructeur parametre: creer une Grid de type T et de taille passee en parametre -
        AbstractMorpion(int taille): container(Grid<T>(taille))
        {}


        //renvoi la Grid
        Grid<T> getContainer() const{

            return container;
        }


};

// - classe representant un Morpion classique (grille de 9 int representant le symbole present sur la case) -
class Morpion : public AbstractMorpion<int>{

  public:

    // - construit un Morpion classique de 3x3 (9 cases) avec comme valeur 0 (case vide pas encore jouee) -
    Morpion(): AbstractMorpion(9)
    {     
        for(int i = 0; i<9; i++) container.ajouter(0);
    }

    // - renvoie une liste de positions representant les cases libres jouables dans la grille -
    //a modifier puisque qu'on utilise plus position
    vector<Position> getEmptyPositions() {
      
      vector<Position> temp;
      
      for (int i = 0; i < 3; i++) {
        
        for (int j = 0; j < 3; j++) {
          
          if (container.getValueXY(i, j) == 0)           
            temp.push_back(Position(i, j));
        }
      }
      
      return temp;
    }

};

// - classe representant un MetaMorpion (grille de 9 Morpions classiques) -
class MetaMorpion : public AbstractMorpion<Morpion>{

  public:


    const int IN_PROGRESS = -1;
    const int DRAW = 0;
    const int P1 = 1;
    const int P2 = 2;


    // - constructeur par defaut: construit une grille de 9 morpions -
    MetaMorpion(): AbstractMorpion(9)
    {}

    MetaMorpion& operator=(const MetaMorpion& t)
    {
        return *this;
    }

};




//convertisseurs
int tictactoe_id_row();
int tictactoe_id_col();
void version();


class State{
  public :
    //MetaMorpion board; a utiliser quand tout marche 
    int win;
    int last_col;
    int last_row;
    int children_count;
    int occupied[SIZE][SIZE]; 
    int avaible[SIZE];
    static constexpr int matrix_point[SIZE][SIZE]= 
    {
      {30,20,30,20,25,20,30,20,30},
      {24,16,24,16,20,16,24,16,24},
      {30,20,30,20,25,20,30,20,30},
      {24,16,24,16,20,16,24,16,24},
      {36,24,36,24,30,24,36,24,36},
      {24,16,24,16,20,16,24,16,24},
      {30,20,30,20,25,20,30,20,30},
      {24,16,24,16,20,16,24,16,24},
      {30,20,30,20,25,20,30,20,30}
    }; 
    int free_choice_count; 
    int sum;

    //contructeurs
    State();

    State(int last_col, int last_row, int children_count,int occ[SIZE][SIZE], int avail[SIZE],
     int sum) : win(win),last_col(last_col),last_row(last_row),children_count(children_count){
    copy_tab2(occ,occupied);
    copy_tab1(avail,avaible);
    } 

    /*MetaMorpion getBoard(){
        return board;
    }*/
    int winner(int id_row, int p_t);
    int winner_meta();
    int eval();
    int tictactoe_mult(int id_row);
    void update_avaible(int p_t,int move[2]);
};





    int State::winner(int id_row, int p_t)
{
    if 
    (
        (occupied[id_row][0]==p_t    && occupied[id_row][1]==p_t      && occupied[id_row][2]==p_t) ||
        (occupied[id_row][3]==p_t    && occupied[id_row][4]==p_t      && occupied[id_row][5]==p_t) ||
        (occupied[id_row][6]==p_t    && occupied[id_row][7]==p_t      && occupied[id_row][8]==p_t) ||
        (occupied[id_row][0]==p_t    && occupied[id_row][3]==p_t      && occupied[id_row][6]==p_t) ||
        (occupied[id_row][1]==p_t    && occupied[id_row][4]==p_t      && occupied[id_row][7]==p_t) ||
        (occupied[id_row][2]==p_t    && occupied[id_row][5]==p_t      && occupied[id_row][8]==p_t) ||
        (occupied[id_row][0]==p_t    && occupied[id_row][4]==p_t      && occupied[id_row][8]==p_t) ||
        (occupied[id_row][2]==p_t    && occupied[id_row][4]==p_t      && occupied[id_row][6]==p_t)
    )
    {
        return p_t;
    } 
    else 
    {
        return 0;
    }
}
    
    int State::winner_meta(){
    for(int player_turn=-1;player_turn<2;player_turn=player_turn+2){
         if 
        (
            (avaible[0]==player_turn  && avaible[1]==player_turn      && avaible[2]==player_turn) ||
            (avaible[3]==player_turn  && avaible[4]==player_turn      && avaible[5]==player_turn) ||
            (avaible[6]==player_turn  && avaible[7]==player_turn      && avaible[8]==player_turn) ||
            (avaible[0]==player_turn  && avaible[3]==player_turn      && avaible[6]==player_turn) ||
            (avaible[1]==player_turn  && avaible[4]==player_turn      && avaible[7]==player_turn) ||
            (avaible[2]==player_turn  && avaible[5]==player_turn      && avaible[8]==player_turn) ||
            (avaible[0]==player_turn  && avaible[4]==player_turn      && avaible[8]==player_turn) ||
            (avaible[2]==player_turn  && avaible[4]==player_turn      && avaible[6]==player_turn)
        )
        {
          // effet de bord changer turn en max = 81   this.num_turn = 81 ou win=player_turn;
          // le but étant de pouvoir stopper l'evaluation prématuremment en testant cet attribut
            return player_turn;
        } 
        return 0;
    }  
}
    //a séparer en deux fonctions
    int State::eval(){
    // pour chaque cases du meta morpion, evaluer sa valeur, sommer les  points de chaque case
    int sum=0; // une simulation suivante peut être plus defavorable donc recalculer de 0 (perte de points car l'adversaire s'interpose par exemple)
    sum+=winner_meta()*MAXIPOINT; if(sum>=MAXIPOINT){/*cerr<<"fin"<<sum<<endl;*/return sum;} // winner meta renvoie -1 ou 1

    for (int i=0;i<SIZE;i++)
    {   
        //if(winner(occupied,i,1)==1){sum+=5000;}
        if(winner(i,-1)==-1){sum-=20000;}
        for (int j=0;j<SIZE;j++)
        {
            int turn=occupied[i][j];
            sum+=matrix_point[i][j]*turn; // points de cases pondérées possédées // quand un morpion n'est plus jouable toutes les cases deviennent celle du gagnant donc score = 45(morpion) x 4-6(depend le morpion) 
            sum-=free_choice_count*100;  // chaque coup libre pour l'adversaire est une penalité
            int coef=tictactoe_id_col(i,j);
            if(i==4){coef=6;}  // centre du meta
            else if(i==0 || i==2 || i==6 || i==8){coef=5;} // coins du meta
            else {coef=4;} // le reste du meta
            // coupé ici si on sépare
//--------------------------------------------------------------------------------------------------------------------

          
            if (turn!=0)
            {   
                //verifie si une deuxième case en colonne comporte le meme symbole, sans être bloqué par l'adversaire sur le 3ème (donc libre)
                if ((occupied[i][(j+3)%9]==turn || occupied[i][(j+6)%9]==turn) && (occupied[i][(j+3)%9]==0 || occupied[i][(j+6)%9]==0))
                {
                    sum+=5*turn*coef; //va être compté 2 fois, exemple (0 et 3) et (3 et 0)
                }
                
                //verifie si une deuxième case en ligne comporte le meme symbole, sans être bloqué par l'adversaire sur le 3ème (donc libre)
                if ((occupied[i][(j+1)%3+(j/3)*3]==turn || occupied[i][(((j+2)%3)+(j/3)*3)]==turn) && (occupied[i][(j+1)%3+(j/3)*3]==0 || occupied[i][(((j+2)%3)+(j/3)*3)]==0))
                {
                    sum+=5*turn*coef;
                }
        
                //verifie si une deuxième case en diagonale \ comporte le meme symbole, sans être bloqué par l'adversaire sur le 3ème (donc libre)
                if (j==0||j==4||j==8) 
                {
                    if ((occupied[i][((j+4)%12)]==turn || occupied[i][((j+8)%12)]==turn) && (occupied[i][((j+4)%12)]==0 || occupied[i][((j+8)%12)]==0))
                    {
                        sum+=5*turn*coef;
                    }
                }
                //verifie si une deuxième case en diagonale / comporte le meme symbole, sans être bloqué par l'adversaire sur le 3ème (donc libre)
                if (occupied[i][2]==turn)
                {
                    if ((occupied[i][4]==turn || occupied[i][6]==turn) && (occupied[i][4]==0 || occupied[i][6]==0))
                    {
                        sum+=5*turn*coef; // compte 2 fois aussi avec le if suivant
                    }
                }
                if (occupied[i][4]==turn)
                {
                    if ((occupied[i][2]==turn || occupied[i][6]==turn) && (occupied[i][2]==0 || occupied[i][6]==0))
                    {
                        sum+=5*turn*coef;
                    }
                }
                if (occupied[i][6]==turn)
                {
                    if ((occupied[i][4]==turn || occupied[i][2]==turn) && (occupied[i][4]==0 || occupied[i][2]==0))
                    {
                        sum+=5*turn*coef;
                    }
                }
            }
        }
    }
    //cerr<<"sum : "<<sum<<endl;
    return sum;
}

int State::tictactoe_mult(int id_row)
{
    int mult = 0;

    for (int j=0;j<SIZE;j++)
    {
        mult*=occupied[id_row][j];
    }
    return mult;
}

void State::update_avaible(int p_t,int move[2])
{
    if (avaible[move[0]]==0)
    {   
        int stock=winner(move[0],p_t);
        if(tictactoe_mult(move[0])!=0 && stock==0) // multiplication par 0 qui veut dire libre dans occupied, donc si 1 seul libre, retourne mult==0
        {
            avaible[move[0]]=2; //valeur arbitraire pour eviter de refouiller un tableau complet sans gagnant
        } 
        else
        {   
            avaible[move[0]]=stock;
            if(stock==1)
            {
                for (int k=0;k<SIZE;k++)
                {
                    occupied[move[0]][k]=1;
                }
            } else if (stock==-1)
            {
                for (int k=0;k<SIZE;k++)
                {
                    occupied[move[0]][k]=-1;
                }
            }
        }
    }
}



class Node { // ajouter position et valeur 
  private:
    State state;
    weak_ptr<Node> parent;
    vector<shared_ptr<Node>> childArray;//TAILLE 81 C'EST PLUS DU DYNAMIQUE
    int nb_enfant; //pas sur de le garder 

  public:
    Node() : state(State()), parent(make_shared<Node>(new Node))
        {}

    Node(State s, weak_ptr<Node> p, vector<shared_ptr<Node>> c) : state(s), parent(p), childArray(c)
        {}
        
    Node(State s): state(s)
        {}


    int possibleDepth(int nb_enfant); 
    void setParent(weak_ptr<Node> p);
    const weak_ptr<Node> getParent() const;
    State getState() const;
    const vector<shared_ptr<Node>> getChildArray() const;
    void play();
    void playable_next_generate(int id_col, bool *free,int p_t);   
    int minimax(int h, int p_t,int move[2],int alpha, int beta, int player_turn);
};


    int Node::possibleDepth(int nb_enfant){
      //methode de calcul de la hauteur en fonction du nombre d'enfant 
      // prendre en compte le nombre d'enfant du père, et la hauteur (depth) actuelle de         la simulation
      // calcul à base de factoriel
        return 0;
    }
    

    void Node::setParent(weak_ptr<Node> p){
            parent = p;
        }
        
    const weak_ptr<Node> Node::getParent() const{
            return parent;
        }
        
    State Node::getState() const{
            return state;
        }
        
    const vector<shared_ptr<Node>> Node::getChildArray() const{
            return childArray;
        }

    //penser a update_avaible apres avoir modif occupied
      void Node::play(){
        //l'enfant qu'on choisit devient le root (supprimer son père et c frere)
        //cout le to_play
      }
    
void Node::playable_next_generate(int id_col, bool *free, int p_t)
{

    if(state.avaible[id_col]!=0) // si le morpion numero id_col est indisponible alors on rend dispo tout le meta morpion sauf ce qui n'est pas dispo (inverse d'occupied) en plus du morpion actuellement indisponible qui n'est pas forcement à jour dans avaible à cause des passages par references, puisque c'est dangereux de le modifier dans les simulations
    {
        for (int i = 0;i<9;i++)
        {
            for (int j = 0;j<9;j++)
            {   
                if(state.occupied[i][j]==0 && (i!=id_col))
                {   
                    shared_ptr<Node> root = make_shared<Node>(this); //pere
                    vector<shared_ptr<Node>> children; //enfant vide
                    int tab[SIZE][SIZE];
                    copy_tab2(state.occupied,tab);
                    tab[i][j]=p_t;
                    State st= State(i,j,0,tab,state.avaible,state.sum);
                    Node test = Node(st,root,children); 

                    shared_ptr<Node> child = make_shared<Node>(test);
                    childArray.push_back(child);
                    nb_enfant++;
                    *free=true;
                }
            }
        }
                
    } else // si pas de probleme de disponibilité sur le morpion destination, alors on fait un inverse de occupied du morpion local
    {
        for (int k = 0;k<9;k++)
            {   
                if(state.occupied[id_col][k]==0)
                {   
                    shared_ptr<Node> root = make_shared<Node>(this); //pere
                    vector<shared_ptr<Node>> children; //enfant vide
                    int tab[SIZE][SIZE];
                    copy_tab2(state.occupied,tab);
                    tab[id_col][k]=p_t;
                    State st= State(id_col,k,0,tab,state.avaible,state.sum);
                    Node test = Node(st,root,children); 

                    shared_ptr<Node> child = make_shared<Node>(test); 
                    childArray.push_back(child);
                    nb_enfant++;
                }
            }

    } 
    //au lieu de créé une matrice des coup jouable ,remplir child aray du node correspondant directement ?
}

int Node::minimax(int h, int p_t,int move[2],int alpha, int beta, int player_turn)
{
    // cas d'arret
    if (h<=0 || state.win!=0)
    {   
        return state.sum+state.eval();
    }

    int temp_avaible=state.avaible[move[0]];
    int temp_occupied[SIZE];
    //int **save=save_occupied(this->occupied);
    state.occupied[move[0]][move[1]]=p_t;
    state.update_avaible(p_t,move);
    State simulation=State(this->state.last_row,this->state.last_col,this->state.children_count,this->state.occupied,this->state.avaible,this->state.sum);
    // parametre playable_next inutile puisque actualisé directement après, idem pour children_count, player_turn inutil comme attribut car chaque fois je decide dans lappel et pas par rapport à la valeur de lobjet ?

    // superieur à 0 pour ne pas créer une matrice inutile
    if (h>0) 
    {
        bool free=false;
        playable_next_generate(move[1], &free,p_t);
        if (free && p_t==-1)
        {
            state.free_choice_count++; // l'attribut du père ou du fils ? risque d'incrementer avec les simulations non choisies après...pas utile pour le moment, facteur de calcul dans eval
        }
        if(nb_enfant==0){
            state.win=2;
        }
    }

    for (int i=0;i<9;i++)
    {   
        
        for (int j=0;j<SIZE;j++)
        {
            //rattaché le state simulation au node correspondant (dans les child array du pere)
            for (int k=0;k<nb_enfant;k++){
                //generer un nouvel objet de simulation
                //lancer la simulation avec ce nouvel objet
                //renvoyer la simulation pour qu'elle soit comparée
                if (player_turn==1)
                {   
                    alpha=max(alpha,minimax(h-1,-1,move,alpha,beta,player_turn));
                    //restore_occ(save);
                    state.occupied[move[0]][move[1]]=0;
                    state.avaible[move[0]]=temp_avaible;
                    if(alpha>=beta)
                    {
                        return beta;
                    }
                    return alpha;
                } 
                else
                {   
                    beta=min(beta,minimax(h-1,1,move,alpha,beta,player_turn));
                    //restore_occ(save);
                    state.occupied[move[0]][move[1]]=0;
                    state.avaible[move[0]]=temp_avaible;
                    if(alpha>=beta)
                    {
                        return alpha;
                    }
                    return beta;
                }
            }     
        }
    }
}


//convertisseur [morpion][case](surtout pour eval)
int tictactoe_id_row(int x,int y){
    return (x/3)*3 + (y/3);
}


int tictactoe_id_col(int x,int y)
{
    int id_col = y;
    if(x==0 || x==3 or x==6)
    {
        if (y>2 && y<6) {id_col-=3;}
        if (y>5) {id_col-=6;}
    } 
    if(x==1 || x==4 || x==7)
    {   
        if (y<3) {id_col+=3;}
        if (y>5) {id_col-=3;}
    } 
    if(x==2 || x==5 || x==8)
    {
        if (y<3) {id_col+=6;}
        if (y>2 && y<6) {id_col+=3;}
    } 
    return id_col;
}

void version(int (&move)[2], int x,int y)
{
    move[0] = tictactoe_id_row(x,y);
    move[1] = tictactoe_id_col(x,y);
}

void theme(int (&move)[2],int x,int y)
{
    bool translated=false;
    for (double m=0;m<SIZE;m++)
    {   
        if (!translated)
        {
            for (double n=0;n<SIZE;n++)  
            {   //bijection donc reversible facilement
                version(move,m,n);
                if ((move[0]==x) && (move[1]==y))
                {
                    move[0]=m;
                    move[1]=n;
                    translated=true;
                    break;
                }
            }
        } 
        else
        {
            break;
        }
    }
}

void copy_tab1(int occ[SIZE],int(&tab)[SIZE]){
    for(int i=0;i<SIZE; i++){
            tab[i]=occ[i];
        }
}

void copy_tab2(int occ[SIZE][SIZE],int(&tab)[SIZE][SIZE])
{
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            tab[i][j]=occ[i][j];
        }
    }
}

int main()
{
    //test_constructor(); //bug dans les processus automatiques de fin de fonction/bloc...

    //1) charger un objet de départ
    //2) l'objet courant est l'unique objet donc le père est vide
    //3) charger dans l'objet les coups précédents, si -1 (ou valid action 81) c'est au bot de commencer
    //4) une fois les données chargées on actualise l'objet courant, le nombre de fils 
    //5) on fixe l'attribut statique starting_turn à 81 sinon 80, on pourrait mettre un booleen mais on va surement uiliser un calcul soustractif 
    //pour connaitre le tour actuel dans la simulation en soustrayant avec le numero courant
    //6) on fixe la profondeur du parcours
    //7) on parcours les coups possibles (nombre de fils) on stocke chaque coup joué dans une pile pour restituer du dernier coup au premier joué dans l'ideal 
    //ou alors on fait une copie sauvegarde de occupied
    //7,5) on peut faire l'application apres l'appel à minimax, grâce à la sauvegarde on peut passer le coup à jouer sur les attribut move[2] ca factorise le code 
    //8) à chaque coup possible on génère une simulation (un objet fils), qui appelle minimax / montecarlo / autres stratégies
    //9) on compare les resultats des simulations
    //10) on restitue l'état initial de occupied grâce à la pile de coup joués
    //11) goto 7) jusqu'a épuisement des coups possibles, supprimer la sauvegarde, puis lancer play() avec le coup correspondant au best_score
    //12) play se charge d'actualiser l'objet courant

    //play
    //le fils dont last move, est celui choisis par le meilleur score devient l'objet courant, 
    //le précedent objet courant met tout ses autres fils à 0/NULL pour que le share pointer s'occupe de les delete
    //on delete le père, on modifie le pointeur père de l'objet courant à NULL
    //le père n'est pas un pointer shared pour éviter de créer un cycle avec ses fils que le "regardent", c'est donc un weak ?
    // ce n'est pas un unique car il ne pourrait pas être regardé par plus d'une fils à la fois


    //1)
    shared_ptr<Node> root = make_shared<Node>(new Node);
    MetaMorpion current_board = MetaMorpion();
    State st = State();
    vector<shared_ptr<Node>> children;
    Node nod = Node(st,root,children);
    int move[2]={};
    // creer alpha beta ici plutot qu'en attribut ?
    int alpha,beta,player_turn;
    while (1) {
        //2)
        //3)
        cin >> st.last_row>> st.last_col; cin.ignore();
        if (st.last_col!=-1)
        {   
            version(move,st.last_row,st.last_col);
            st.occupied[move[0]][move[1]]=-1;
            st.update_avaible(-1,move);
        }
        //4)
        cin >> st.children_count; cin.ignore();
        //6)
        int h=5;
        int score_minimax=0;
        int best_score_minimax=-MAXIPOINT;
        int to_play[2]={};
        //7)
        int save[SIZE][SIZE];
        copy_tab2(st.occupied,save);
        for (int i = 0; i < st.children_count; i++) {
            cin >> st.last_row >> st.last_col; cin.ignore();
            version(move,st.last_row,st.last_col);
            st.last_row=move[0]; // securité, création nouvel objet avec des coordonées traduites
            st.last_col=move[1];
            //8) 
            score_minimax=nod.minimax(h, 1,move,alpha,beta,player_turn);
            //9)
            if(best_score_minimax<score_minimax)
            {
                best_score_minimax=score_minimax;
                to_play[0]=move[0];
                to_play[1]=move[1];
            }
            //10)
            copy_tab2(save,st.occupied); //possible de ne pas le faire car on va chnager la racine sur le coup a jouer
        }
        
        //12)
        nod.play(to_play,root);

        cout <<to_play[0]<<" "<<to_play[1]<< endl;
    }
}