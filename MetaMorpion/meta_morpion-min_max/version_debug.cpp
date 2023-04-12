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

using namespace std;
int cptId=0;
//-----------------------------------------------------------------------------------------------------------------------------------------//
int tictactoe_id_row(int i, int j);
int tictactoe_id_col(int i, int j);
void version(int (&move)[2], int i, int j);
void theme(int (&move)[2], int i, int j);
void copy_tab1(int occ[SIZE],int (&tab)[SIZE]);
void copy_tab2(int occ[SIZE][SIZE], int (&tab)[SIZE][SIZE]);
//-----------------------------------------------------------------------------------------------------------------------------------------//
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


class State{
  public :
    //MetaMorpion board; a utiliser quand tout marche
  int win;
  int last_col;
  int last_row;
  int next_col;
  int next_row;
  int free_choice_count;
  int sum;
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


    //contructeurs
  State();
  State(int last_col, int last_row,int (&occ)[SIZE][SIZE], int (&avail)[SIZE], int sum);
  int winner(int id_row, int player_turn);
  int winner_meta();
  int eval();
  int tictactoe_mult(int id_row);
  void update_avaible(int player_turn, int x);
};
//-----------------------------------------------------------------------------------------------------------------------------------------//
State::State() : win(0), last_col(-1), last_row(-1), next_col(-1), next_row(-1), sum(0), free_choice_count(0)
{
    for (int i=0;i<SIZE;i++)
    {
        avaible[i]=0;
        for (int j=0;j<SIZE;j++)
        {
            occupied[i][j]=0;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
State::State(int last_col, int last_row,int (&occ)[SIZE][SIZE], int (&avail)[SIZE], int sum) : last_col(last_col),last_row(last_row)
{
    copy_tab2(occ,occupied);
    copy_tab1(avail,avaible);
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
int State::winner(int id_row, int player_turn)
{
    if
        (
            (occupied[id_row][0]==player_turn    && occupied[id_row][1]==player_turn      && occupied[id_row][2]==player_turn) ||
            (occupied[id_row][3]==player_turn    && occupied[id_row][4]==player_turn      && occupied[id_row][5]==player_turn) ||
            (occupied[id_row][6]==player_turn    && occupied[id_row][7]==player_turn      && occupied[id_row][8]==player_turn) ||
            (occupied[id_row][0]==player_turn    && occupied[id_row][3]==player_turn      && occupied[id_row][6]==player_turn) ||
            (occupied[id_row][1]==player_turn    && occupied[id_row][4]==player_turn      && occupied[id_row][7]==player_turn) ||
            (occupied[id_row][2]==player_turn    && occupied[id_row][5]==player_turn      && occupied[id_row][8]==player_turn) ||
            (occupied[id_row][0]==player_turn    && occupied[id_row][4]==player_turn      && occupied[id_row][8]==player_turn) ||
            (occupied[id_row][2]==player_turn    && occupied[id_row][4]==player_turn      && occupied[id_row][6]==player_turn)
            )
    {
        return player_turn;
    }
    else
    {
        return 0;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
int State::winner_meta()
{
    for(int player_turn=-1;player_turn<2;player_turn=player_turn+2) //de 0 a 2 
    {
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
            win=player_turn;
            return player_turn;
        }
    }
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
//a séparer en deux fonctions
int State::eval()
{

    // pour chaque cases du meta morpion, evaluer sa valeur, sommer les  points de chaque case
    int sum=1; // une simulation suivante peut être plus defavorable donc recalculer de 0 (perte de points car l'adversaire s'interpose par exemple)
    /*
    sum+=winner_meta(); if(sum!=0){return sum*MAXIPOINT;} // winner meta renvoie -1 ou 1

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
    */
    return sum;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
int State::tictactoe_mult(int id_row)
{
    int mult = 0;

    for (int j=0;j<SIZE;j++)
    {
        mult*=occupied[id_row][j];
    }
    return mult;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
void State::update_avaible(int player_turn, int x)
{
    if (avaible[x]==0)
    {
        int stock=winner(x,player_turn);
        if(tictactoe_mult(x)!=0 && stock==0) // multiplication par 0 qui veut dire libre dans occupied, donc si 1 seul libre, retourne mult==0
        {
            avaible[x]=2; //valeur arbitraire pour eviter de refouiller un tableau complet sans gagnant
        }
        /*else
        {
            avaible[x]=stock;
            if(stock==1) 
            {
                /*for (int k=0;k<SIZE;k++)
                {
                    occupied[x][k]=1;
                }
            } else if (stock==-1)
            {
                for (int k=0;k<SIZE;k++)
                {
                    occupied[x][k]=-1;
                }
            }
        }*/
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
class Node {
public:
    State state;
    weak_ptr<Node> parent;
    vector<shared_ptr<Node>> childArray;
    int children_count;
    vector<pair<int,int>> playable_next;
    bool childrenKnowledge;
    int sum_total;

public:
    Node();
    int possibleDepth(int children_count);
    void setParent(weak_ptr<Node> p);
    const weak_ptr<Node> getParent() const;
    State getState() const;
    const vector<shared_ptr<Node>> getChildArray() const;
    int playable_next_generate(bool& free);
    void children_generate(int player_turn, int i, int j);
    void minimax(int h, int player_turn, int& alpha, int& beta);
    int exist_children(int i, int j);
};
//-----------------------------------------------------------------------------------------------------------------------------------------//
Node::Node() : children_count(0), sum_total(0), childrenKnowledge(false)
{
    vector<shared_ptr<Node>> childArray;
    state=State();
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
int Node::possibleDepth(int children_count)
{
      //methode de calcul de la hauteur en fonction du nombre d'enfant
      // prendre en compte le nombre d'enfant du père, et la hauteur (depth) actuelle de         la simulation
      // calcul à base de factoriel
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
void Node::setParent(weak_ptr<Node> p)
{
    parent = p;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
const weak_ptr<Node> Node::getParent() const
{
    return parent;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
State Node::getState() const
{
    return state;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
const vector<shared_ptr<Node>> Node::getChildArray() const
{
    return childArray;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
int Node::playable_next_generate(bool &free){
 int next_children_count=0;

    if(this->state.avaible[this->state.next_col]!=0) // si le morpion numero id_col est indisponible alors on rend dispo tout le meta morpion sauf ce qui n'est pas dispo (inverse d'occupied) en plus du morpion actuellement indisponible qui n'est pas forcement à jour dans avaible à cause des passages par references, puisque c'est dangereux de le modifier dans les simulations
    {
        for (int i = 0;i<9;i++)
        {
            for (int j = 0;j<9;j++)
            {   
                if((i!=state.next_col) && state.occupied[i][j]==0) //evaluation paresseuse optimisante
                {   
                    playable_next.push_back(make_pair (i, j));
                    //cerr<<playable_next.back().first<<" "<<playable_next.back().second<<endl;
                    next_children_count++;
                }
            }
        }
        if (children_count>0)
        {
            free=true;
        }
    } else // si pas de probleme de disponibilité sur le morpion destination, alors on fait un inverse de occupied du morpion local
    {
        for (int k = 0;k<9;k++)
        {
            if(state.occupied[state.next_col][k]==0)
            {
                playable_next.push_back(make_pair (state.next_col, k));
                //cerr<<playable_next.back().first<<" "<<playable_next.back().second<<endl;
                next_children_count++;
            }
        }
    } 
    childrenKnowledge=true;

    return next_children_count;
}

//-----------------------------------------------------------------------------------------------------------------------------------------//
void Node::children_generate(int player_turn, int i, int j)
{
  shared_ptr<Node> child = make_shared<Node>();
  if(child==0){cerr<<"erreur creation pointeur null"<<endl;exit(2);}
  child->state=this->state;
  child->state.last_row=state.next_row;
  child->state.last_col=state.next_col;
  this->childArray.push_back(child);
  this->children_count++;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
int Node::exist_children(int i, int j){
 //cerr<<this->childArray.size()<<endl;
  for (int a = 0; a<this->childArray.size();a++){
    if (childArray[a]->state.last_row == i && childArray[a]->state.last_col ==j ){
      return a;
  }    
}
return -1;
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
void Node::minimax(int h, int player_turn, int& alpha, int& beta)
{
    cout<<"afficha h"<<h<<" "<<state.next_row<<state.next_col<<endl;
    state.occupied[state.next_row][state.next_col]=player_turn;
    state.update_avaible(player_turn,state.next_row);

    // cas d'arret
    if (h<=0 || state.win!=0)
    {
        state.sum=state.eval();
        //cerr<<"sum i j: "<<state.last_row<<state.last_col<<summ<<endl;
        this->sum_total+=state.sum;
        state.occupied[state.next_row][state.next_col]=0;
        state.update_avaible(player_turn,state.next_row);
    } else
    {
        int k=exist_children(state.next_row,state.next_col); // retourne l'indice du fils qui existe deja sinon -1
        if (k==-1)
        {
            children_generate(player_turn,state.next_row,state.next_col);
            k=childArray.size()-1; // le fils n'existait pas, maintenant qu'il est créé, k est son indice
            bool free=false;
            int next_children_count=childArray[k]->playable_next_generate(free);
            if (free && player_turn==-1)
            {
                childArray[k]->state.free_choice_count++;
            }
            if(next_children_count==0)
            {
                childArray[k]->state.win=2;
            }
        } else
        {
            h++;  // si le noeud existait déjà on descend +1 en profondeur
            cout<<"children not created : "<<childArray[k]->state.next_row<<childArray[k]->state.next_col<<endl;
        }



        
        for (int i=0; i<childArray[k]->playable_next.size(); ++i) 
        {   

            childArray[k]->state.next_row=childArray[k]->playable_next[i].first;
            childArray[k]->state.next_col=childArray[k]->playable_next[i].second;
            
            if (player_turn==1)
            {
                /*
                alpha=max(alpha,childArray[k]->minimax(h-1,-1,alpha,beta));
                state.occupied[state.last_row][state.last_col]=0;
                if(alpha>=beta)
                {
                    return beta;
                }
                return alpha;
                */
                childArray[k]->minimax(h-1,-1,alpha,beta);
                state.occupied[state.next_row][state.next_col]=0;
                state.update_avaible(player_turn,state.next_row);

            }
            else 
            {
                /*
                beta=min(beta,childArray[k]->minimax(h-1,1,alpha,beta));
                state.occupied[state.last_row][state.last_col]=0;
                if(alpha>=beta)
                {
                    return alpha;
                }
                return beta;
                */
                childArray[k]->minimax(h-1,1,alpha,beta);
                state.occupied[state.next_row][state.next_col]=0;
                state.update_avaible(player_turn,state.next_row);

            }
        }
        //state.occupied[state.next_row][state.next_col]=0;
        //state.update_avaible(player_turn,state.next_row);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------//
//convertisseur [morpion][case](surtout pour eval)
int tictactoe_id_row(int x,int y)
{
    return (x/3)*3 + (y/3);
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------------------//
void version(int (&move)[2], int x,int y) // on ne passe pas directement x et y en référence pour éviter les effets de bord dans theme qui teste version pour emprunter le chemin inverse de sa bijection
{
    move[0] = tictactoe_id_row(x,y);
    move[1] = tictactoe_id_col(x,y);
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------------------//
void copy_tab1(int occ[SIZE],int(&tab)[SIZE])
{
    for(int i=0;i<SIZE; i++){
        tab[i]=occ[i];
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------//
int main()
{
    //1) charger un objet de départ
    //2) charger dans l'objet les coups précédents, si -1 (ou valid action 81) c'est au bot de commencer
    //3) actualiser  le nombre d'enfant (children/coups jouables/simulations)
    //4) fixer la profondeur du parcours et réinitialiser les autres variables
    //5) sauvegarder avaible au préalable
    //6) parcourir les coups possibles
    //7) appeler minimax pour chaque coup et stocker le retour
    //8) comparer les resultats de chaque coup
    //9) restituer l'état initial de avaible, occupied est géré dans minimax, la sauvegarde externe de avaible genere moins de mouvements inutiles
    //10) actualiser root child correspondant au best_score
    //11) jouer
//-----------------------------------------------------------------------------------------------------------------------------------------//
    //1)
    std::chrono::system_clock::time_point chronoStart = std::chrono::system_clock::now();
    Node root = Node();
    shared_ptr<Node> nosuppress(new Node());
    root.childArray.push_back(nosuppress);
    nosuppress = nullptr;
    shared_ptr<Node> bestChild;
    int move[2]={};
    int alpha,beta;
    int save[SIZE];
    int h;
    int row, col, nbChild0;
    int score_minimax=0;
    int best_score_minimax=-MAXIPOINT;



//-----------------------------------------------------------------------------------------------------------------------------------------//
    while (1) {
        int playable[9][9]={};   // matrice pour ordonner le temps de debug
        //2)
        cerr<<"coup adverse"<<endl;
        cin >> root.childArray[0]->state.last_row >> root.childArray[0]->state.last_col; cin.ignore();
        //ici
        
        
        cerr<<"current pre opp : "<<root.childArray[0]<<endl;
        if (root.childArray[0]->state.last_col!=-1 )
        {
            version(move,root.childArray[0]->state.last_row,root.childArray[0]->state.last_col);
            root.childArray[0]->state.occupied[move[0]][move[1]]=-1; // va devenir inutil, actualisé après 
            root.childArray[0]->state.update_avaible(-1,move[0]);

        }

        //3) // faire descendre sur l'arbre après le coup adverse
        cerr<<"childcount : "<<root.childArray[0]->children_count<<endl;
        if (root.childArray[0]->state.last_row!=-1)
        {

            int opp = root.childArray[0]->exist_children(move[0], move[1]);
            if (opp!=-1)
            {
                bestChild=root.childArray[0]->childArray[opp];
                cerr<<"best opp i j: "<<bestChild<<" "<<bestChild->state.last_row<<bestChild->state.last_col<<endl;
                bestChild->state.occupied[move[0]][move[1]]=-1;
                bestChild->state.update_avaible(-1,move[0]);
                root.childArray[0]=bestChild;
/*
                for (int t=0;t<9;t++)
                            {
                                for (int y=0;y<9;y++)
                                {
                                    cerr<<bestChild->state.occupied[t][y]<<" ";

                                }
                                cerr<<endl;
                            }
                            cerr<<endl;*/
            }
        }
        // je l'ai rajouté un peu au pif
        cerr<<"current post opp : "<<root.childArray[0]<<endl;    
        
        //3)
        cout<<"occupied"<<endl;
        for (int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout<<root.childArray[0]->state.occupied[i][j]<<" ";
            }
            cout<<endl;
        }
        cerr<<endl;

        bool free=false;
        root.childArray[0]->state.next_row=move[0];
        root.childArray[0]->state.next_col=move[1];
        if (root.childArray[0]->playable_next.size()==0){
            int nbChild0 = root.childArray[0]->playable_next_generate(free);
        }        
        //affichage
        cout<<"playable_next_apres"<<endl;
        for (int i=0; i<root.childArray[0]->playable_next.size(); ++i) 
        {  
            cout<<root.childArray[0]->playable_next[i].first<<root.childArray[0]->playable_next[i].second<<" ";
        }
        cout<<endl;


        //cin >> nbChild0; cin.ignore();
        //4)
        h=2; // appel à possibleDepth()
        score_minimax=0;
        best_score_minimax=-MAXIPOINT;
        //5)
        copy_tab1(root.childArray[0]->state.avaible,save);
        //6)
        /*
        for (int i = 0; i < nbChild0; i++) {
            cin >>row>>col; cin.ignore();
            version(move,row,col);
            playable[move[0]][move[1]]=5;
        }

        int i=0;
        for (int t=0;t<9;t++)
        {
            for (int y=0;y<9;y++)
            {
                if (playable[t][y]==5)
                {
                    root.childArray[0]->state.next_row=t; 
                    root.childArray[0]->state.next_col=y; 
                    //7)
                    cerr<<"minimax i j: "<<t<<y<<endl;
                    root.childArray[0]->minimax(h,1,alpha,beta);
                    score_minimax=root.childArray[0]->childArray[i]->sum_total;
                    root.childArray[0]->childArray[i]->state.next_row=t; 
                    root.childArray[0]->childArray[i]->state.next_col=y; 
                    
                    //8)

                    for (int t=0;t<9;t++)
                    {
                        for (int y=0;y<9;y++)
                        {
                            cerr<<root.childArray[0]->childArray[i]->state.occupied[t][y]<<" ";

                        }
                        cerr<<endl;
                    }
                    cerr<<endl;

                    if(best_score_minimax<score_minimax)
                    {
                        best_score_minimax=score_minimax;
                        bestChild=root.childArray[0]->childArray[i];
                        cerr<<" &  found : "<<root.childArray[0]->childArray[i]<<endl;
                        cerr<<"childcountalafin : "<<root.childArray[0]->children_count<<endl;

                    }
                    //9)
                    copy_tab1(save,root.childArray[0]->state.avaible);
                    i++;
                }
            }
        }*/
        for (int i=0; i<root.childArray[0]->playable_next.size(); ++i) 
        {   

            root.childArray[0]->state.next_row=root.childArray[0]->playable_next[i].first;
            root.childArray[0]->state.next_col=root.childArray[0]->playable_next[i].second;
            //7)
               

            root.childArray[0]->minimax(h,1,alpha,beta);
            score_minimax=root.childArray[0]->childArray[i]->sum_total;   
            root.childArray[0]->childArray[i]->state.next_row=root.childArray[0]->playable_next[i].first; 
            root.childArray[0]->childArray[i]->state.next_col=root.childArray[0]->playable_next[i].second; 
            cout<<root.childArray[0]->childArray[i]->state.next_row<<" "<<root.childArray[0]->childArray[i]->state.next_col<<endl; 
                    //8)

            /*
            for (int t=0;t<9;t++)
            {
                for (int y=0;y<9;y++)
                {
                    cerr<<root.childArray[0]->childArray[i]->state.occupied[t][y]<<" ";

                }
                cerr<<endl;
            }
            cerr<<endl;
            */

            if(best_score_minimax<score_minimax)
            {
                best_score_minimax=score_minimax;
                bestChild=root.childArray[0]->childArray[i];
                cerr<<" &  found : "<<root.childArray[0]->childArray[i]<<endl;
                cerr<<"childcountalafin : "<<root.childArray[0]->children_count<<endl;

            }
                    //9)
            copy_tab1(save,root.childArray[0]->state.avaible);
        }




        //10)
        cerr<<"root child : "<<root.childArray[0]<<endl;
        root.childArray[0]=bestChild;
        cerr<<"nouveau root child : "<<root.childArray[0]<<endl;
        //11)
        cerr<<"childcountalafin : "<<root.childArray[0]->children_count<<endl;
        cout<<"pas trad :"<<bestChild->state.last_row<<bestChild->state.last_col<<endl;
        theme(move,bestChild->state.last_row,bestChild->state.last_col);
        cerr<<"traduit : "<<move[0]<<move[1]<<endl;
        cout <<move[0]<<" "<<move[1]<< endl;
        cout<<"--------------------------------------------------------------------------------------"<<endl;
    }
}