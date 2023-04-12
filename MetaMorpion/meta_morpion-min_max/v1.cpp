#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

class Node{
private:
    Node *pere;
    list<Node> childArray;
    int quality;
public:
    int occupied[9];//tableau qui stocke la plateau de jeu
    Node();
    void setoccupied(int occupied[]);
    void tostring_occupied();
    int getsize();
    int getquality();
    Node getarray(int i);
    void setarray(Node node);
    void setquality(int quality);
    int fonction_eval(Node node);
    int minimax(Node node,int depth, int alpha, int beta, bool maximize);
};

//constructeur
Node::Node(){
  this->pere=NULL;
  list<Node>childArray={};
  this->quality=0;
}
//remplire le tableau
void Node::setoccupied(int tab[]){
  for (int i=0;i<9;i++){
    this->occupied[i]=tab[i];
  }
}

//affichage du plateau de jeu
void Node::tostring_occupied(){
  for(int i=0;i<9;i++){
    cout<<this->occupied[i]<<" ";
  }
  return ; 
}

int Node::getsize(){
    return childArray.size();
}

int Node::getquality(){
    return quality;
}

Node Node::getarray(int i){
    int cpt=0;
    list <Node> :: iterator it;
    for(it=this->childArray.begin();it!=this->childArray.end();it++){
        cpt++;
        if (cpt==i){
            return *it;
        }
    }
   
}

void Node::setarray(Node node){
  auto i=this->childArray.end();
  i++;
  this->childArray.insert(i,node);
}

void Node::setquality(int quality){
    this->quality = quality;
}
//fonction alexis des trucs a modifier comme le fait de passer le noeud en argument (faux pas faire ca c'est une méthode)
int Node::fonction_eval(Node node){
    if ((occupied[0] == 1 && occupied[1] == 1 && occupied[2] == 1) ||
        (occupied[3] == 1 && occupied[4] == 1 && occupied[5] == 1) ||
        (occupied[6] == 1 && occupied[7] == 1 && occupied[8] == 1) ||
        (occupied[0] == 1 && occupied[3] == 1 && occupied[6] == 1) ||
        (occupied[1] == 1 && occupied[4] == 1 && occupied[7] == 1) ||
        (occupied[2] == 1 && occupied[5] == 1 && occupied[8] == 1) ||
        (occupied[2] == 1 && occupied[4] == 1 && occupied[6] == 1) ||
        (occupied[0] == 1 && occupied[4] == 1 && occupied[8] == 1)) return 1;
    else if ((occupied[0] == -1 && occupied[1] == -1 && occupied[2] == -1) ||
        (occupied[3] == -1 && occupied[4] == -1 && occupied[5] == -1) ||
        (occupied[6] == -1 && occupied[7] == -1 && occupied[8] == -1) ||
        (occupied[0] == -1 && occupied[3] == -1 && occupied[6] == -1) ||
        (occupied[1] == -1 && occupied[4] == -1 && occupied[7] == -1) ||
        (occupied[2] == -1 && occupied[5] == -1 && occupied[8] == -1) ||
        (occupied[2] == -1 && occupied[4] == -1 && occupied[6] == -1) ||
        (occupied[0] == -1 && occupied[4] == -1 && occupied[8] == -1)) return -1;
    else { return 0; }
};

//fonction alexis min max pareil faut supprimer le node en argument puisqu'on applique la méthode sur le noeud
int Node::minimax(Node node, int depth, int alpha, int beta, bool maximize)
{
    if (depth == 0 or ((occupied[0] == 1 && occupied[1] == 1 && occupied[2] == 1) ||
        (occupied[3] == 1 && occupied[4] == 1 && occupied[5] == 1) ||
        (occupied[6] == 1 && occupied[7] == 1 && occupied[8] == 1) ||
        (occupied[0] == 1 && occupied[3] == 1 && occupied[6] == 1) ||
        (occupied[1] == 1 && occupied[4] == 1 && occupied[7] == 1) ||
        (occupied[2] == 1 && occupied[5] == 1 && occupied[8] == 1) ||
        (occupied[2] == 1 && occupied[4] == 1 && occupied[6] == 1) ||
        (occupied[0] == 1 && occupied[4] == 1 && occupied[8] == 1))
        or (occupied[0] == -1 && occupied[1] == -1 && occupied[2] == -1) ||
        (occupied[3] == -1 && occupied[4] == -1 && occupied[5] == -1) ||
        (occupied[6] == -1 && occupied[7] == -1 && occupied[8] == -1) ||
        (occupied[0] == -1 && occupied[3] == -1 && occupied[6] == -1) ||
        (occupied[1] == -1 && occupied[4] == -1 && occupied[7] == -1) ||
        (occupied[2] == -1 && occupied[5] == -1 && occupied[8] == -1) ||
        (occupied[2] == -1 && occupied[4] == -1 && occupied[6] == -1) ||
        (occupied[0] == -1 && occupied[4] == -1 && occupied[8] == -1)){
        node.setquality(fonction_eval(node));
        return 1;
    }
    if (maximize)
    {   
        int i = 0;
        while (i < node.getsize()) {
            node.setquality(max(node.getquality(), minimax(node.getarray(i), depth - 1, alpha, beta, false)));
            alpha = max(alpha, max(node.getquality(), minimax(node.getarray(i), depth - 1, alpha, beta, false)));
            if (beta <= alpha) break;
        }
    }
    else {
        int i = 0;
        while (i < node.getsize()) {
            node.setquality(min(node.getquality(), minimax(node.getarray(i), depth - 1, alpha, beta, false)));
            alpha = min(alpha, min(node.getquality(), minimax(node.getarray(i), depth - 1, alpha, beta, false)));
            if (beta <= alpha) break;
        }
    }
    return node.getquality();
};

void creation_arbre(int tab[], int nb_coup){
    int cpt=nb_coup-1;
    int nb_noeux=0;
        while (cpt>2){
            int acc=1;
            for(int i=cpt;i>=2;i--){
                acc=acc*i;
            }
            nb_noeux=nb_noeux+acc;       
            cpt=cpt-1;
        }
    return ;
}




int main(int argc, char const *argv[])
{  
  
    Node noeux;
    Node noeux2;
    cout<<noeux.getquality()<<endl;
    noeux.setarray(noeux2);
    int test[9];
    for(int i=0;i<9;i++){
      test[i]=1;
    }
    noeux.setoccupied(test);
    noeux.tostring_occupied();
  
  while(1){
    int opponent_row;
    int opponent_col;
    int tab[9];
    cin >> opponent_row >> opponent_col; cin.ignore();
    int valid_action_count;
    cin >> valid_action_count; cin.ignore();
    for (int i = 0; i < valid_action_count; i++) {
        int row;
        int col;
        cin >> row >> col; cin.ignore();
    }
    //code pour stocker le coup jouer par l'adversaire
    if (opponent_row==1){
      tab[opponent_row+opponent_col]=-1;
    }else{
      if(opponent_row==2){
        tab[opponent_row+opponent_col+2]=-1;
      }else{
        tab[opponent_row+opponent_col+4]=-1;
      }
    }

    //si personne n'a jouer on joue on centre 
    if (valid_action_count==9){
        cout<<"1 1"<<endl;
    }


    int my_row;
    int my_col;

    
    //création de l'arbre
    Node racine;
    //faut aussi stocker le plateau de jeu dans chaque noeud grace noeux.setoccupied(tab)
    racine.setoccupied(tab);
    //application des qualités avec l'algo de tom en utlisant setquality(int)

    //min max qui renvoie le coup a jouer

    //code pour stocker mon coup
    if (my_row==1){
      tab[my_row+my_col]=1;
    }else{
      if(my_row==2){
        tab[my_row+my_col+2]=1;
      }else{
        tab[my_row+my_col+4]=1;
      }
    }
    
    cout<<my_row<<" "<<my_col<<endl;

    }
    return 0;
}